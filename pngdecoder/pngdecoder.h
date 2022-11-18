#ifndef PNGDECODER_H
#define PNGDECODER_H

#include <cstdint>

enum PNGErrorCode
{
    PNG_OK = 0,
    PNG_FILE_NOT_FOUND,
    PNG_BAD_SIGNATURE,
    PNG_INVALID_CHECKSUM,
    PNG_MISSING_HEADER,
    PNG_INVALID_BYTE,
    PNG_INVALID_COLOR_TYPE,
    PNG_INVALID_BIT_DEPTH
};

#pragma pack(push, 1)
struct PngHeader
{
    uint8_t signature[8];
};

struct PngChunkHeader
{
    uint32_t lenght;
    union
    {
        uint32_t typeU32;
        char type[4];
    };
};

struct PngChunkFooter
{
    uint32_t crc;
};

struct PngIHDR
{
    uint32_t width;
    uint32_t height;
    uint8_t bitDepth;
    uint8_t colorType;
    uint8_t compressionMethod;
    uint8_t filterMethod;
    uint8_t interlaceMethod;
};

struct PngResult
{
    uint32_t width;
    uint32_t height;
    uint8_t* image;
    uint8_t errorCode;
};

PngResult decodePng(const char* filename);

#pragma pack(pop)

#endif
