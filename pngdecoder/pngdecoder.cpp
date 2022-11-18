#include "pngdecoder.h"

#include <cstdio>
#include <utility>

static uint8_t PNGSignature[8] = {137, 80, 78, 71, 13, 10, 26, 10};

static const uint32_t CRC_TABLE_SIZE = 256;
/* Table of CRCs of all 8-bit messages. */
static unsigned long crcTable[CRC_TABLE_SIZE];

/* Flag: has the table been computed? Initially false. */
static int crcTableComputed = 0;

struct ImageFile
{
    uint32_t fileSize;
    void* content;
};

/* Make the table for a fast CRC. */
static void makeCRCTable()
{
    unsigned long c;
    uint32_t n, k;

    for (n = 0; n < CRC_TABLE_SIZE; ++n)
    {
        c = (unsigned long) n;
        for (k = 0; k < 8; ++k)
        {
            if (c & 1)
            {
                c = 0xedb88320L ^ (c >> 1);
            }
            else
            {
                c = c >> 1;
            }
        }
        crcTable[n] = c;
    }
    crcTableComputed = 1;
}

/* Update a running CRC with the bytes buf[0..len-1]--the CRC
    should be initialized to all 1's, and the transmitted value
    is the 1's complement of the final running CRC (see the
    crc() routine below). */

static unsigned long updateCRC(unsigned long crc, unsigned char *buf, int len)
{
    unsigned long c = crc;
    int n;

    if (!crcTableComputed)
    {
        makeCRCTable();
    }

    for (n = 0; n < len; n++)
    {
        c = crcTable[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }
    return c;
}

/* Return the CRC of the bytes buf[0..len-1]. */
static unsigned long crc(unsigned char *buf, int len)
{
    return updateCRC(0xffffffffL, buf, len) ^ 0xffffffffL;
}

#define Read(File, type) (type *)readSize(File, sizeof(type))
static void* readSize(ImageFile* file, uint32_t size)
{
    void* result = 0;
    if (file->fileSize >= size)
    {
        result = file->content;
        file->content = (uint8_t *)file->content + size;
        file->fileSize -= size;
    }
    else
    {
        fprintf(stderr, "File underflow\n");
        file->fileSize = 0;
    }

    return result;
}

static void endianSwap(uint32_t* value)
{
    uint32_t v = (*value);
    *value = (( v << 24) |
              ((v & 0xFF00) << 8) |
              ((v >> 8) & 0xFF00) |
              ( v >> 24));
}

static ImageFile readFile(const char* filename)
{
    ImageFile result = {};
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Could open file located at %s.\n", filename);
        return result;
    }

    // Go at the end of the file
    fseek(file, 0, SEEK_END);
    result.fileSize = ftell(file);

    // Go back to the beginning
    fseek(file, 0, SEEK_SET);

    result.content = new char[result.fileSize + 1];
    fread(result.content, result.fileSize, 1, file);

    fclose(file);
    // Make sure string is null-terminated
    char* end = reinterpret_cast<char *>(result.content) + result.fileSize;
    *end = 0;

    return result;
}

static bool checkPNGSignature(const PngHeader* header)
{
    for (int i = 0; i < 8; ++i)
    {
        if (header->signature[i] != PNGSignature[i])
        {
            return false;
        }
    }
    return true;
}

PngResult decodePng(const char* filename)
{
    PngResult result = {};

    ImageFile fileContent = readFile(filename);

    // Bad file content
    if (!fileContent.content)
    {
        result.errorCode = 0x1;
        return result;
    }

    // Check PNG signature
    if (!checkPNGSignature(Read(&fileContent, PngHeader)))
    {
        result.errorCode = 0x2;
        return result;
    }

    // Parsing the chunks
    while (fileContent.fileSize > 0)
    {
        PngChunkHeader* chunkHeader = Read(&fileContent, PngChunkHeader);
        if (chunkHeader)
        {
            endianSwap(&chunkHeader->lenght);
            endianSwap(&chunkHeader->typeU32);

            uint8_t* crcChunk = reinterpret_cast<uint8_t*>(chunkHeader) + sizeof(chunkHeader->lenght);
            int crcChunkLen = chunkHeader->lenght + sizeof(chunkHeader->type);

            void* chunkData = readSize(&fileContent, chunkHeader->lenght);
            PngChunkFooter* chunkFooter = Read(&fileContent, PngChunkFooter);
            endianSwap(&chunkFooter->crc);

            if (chunkHeader->typeU32 == (int)'IHDR')
            {
                printf("IHDR\n");
                PngIHDR* ihdr = reinterpret_cast<PngIHDR*>( chunkData );

                endianSwap(&ihdr->width);
                endianSwap(&ihdr->height);

                if (chunkFooter->crc != crc(crcChunk, crcChunkLen))
                {
                    result.errorCode = PNG_INVALID_CHECKSUM;
                    return result;
                }
            }
        }
    }

    return result;
}