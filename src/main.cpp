#include <cstdint>
#include <cstdio>
#include <Windows.h>

#ifdef _DEBUG
#define Assert(expression) if(!(expression)) {*(int *)0 = 0;} // DebugBreak()?
#else
#define Assert(expression)
#endif

#define SKIP_BYTES(mem, byte_num) (mem += byte_num);

static constexpr uint32_t IHDR_HEADER = 'I' << 24 | 'H' << 16 | 'D' << 8 | 'R' << 0;
static constexpr uint32_t gAMA_HEADER = 'g' << 24 | 'A' << 16 | 'M' << 8 | 'A' << 0;
static constexpr uint32_t IDAT_HEADER = 'I' << 24 | 'D' << 16 | 'A' << 8 | 'T' << 0;
static constexpr uint32_t IEND_HEADER = 'I' << 24 | 'E' << 16 | 'N' << 8 | 'D' << 0;

static uint32_t crc32_table[256] =
{
    0x00000000,0x77073096,0xee0e612c,0x990951ba,0x076dc419,0x706af48f,0xe963a535,0x9e6495a3,
    0x0edb8832,0x79dcb8a4,0xe0d5e91e,0x97d2d988,0x09b64c2b,0x7eb17cbd,0xe7b82d07,0x90bf1d91,
    0x1db71064,0x6ab020f2,0xf3b97148,0x84be41de,0x1adad47d,0x6ddde4eb,0xf4d4b551,0x83d385c7,
    0x136c9856,0x646ba8c0,0xfd62f97a,0x8a65c9ec,0x14015c4f,0x63066cd9,0xfa0f3d63,0x8d080df5,
    0x3b6e20c8,0x4c69105e,0xd56041e4,0xa2677172,0x3c03e4d1,0x4b04d447,0xd20d85fd,0xa50ab56b,
    0x35b5a8fa,0x42b2986c,0xdbbbc9d6,0xacbcf940,0x32d86ce3,0x45df5c75,0xdcd60dcf,0xabd13d59,
    0x26d930ac,0x51de003a,0xc8d75180,0xbfd06116,0x21b4f4b5,0x56b3c423,0xcfba9599,0xb8bda50f,
    0x2802b89e,0x5f058808,0xc60cd9b2,0xb10be924,0x2f6f7c87,0x58684c11,0xc1611dab,0xb6662d3d,
    0x76dc4190,0x01db7106,0x98d220bc,0xefd5102a,0x71b18589,0x06b6b51f,0x9fbfe4a5,0xe8b8d433,
    0x7807c9a2,0x0f00f934,0x9609a88e,0xe10e9818,0x7f6a0dbb,0x086d3d2d,0x91646c97,0xe6635c01,
    0x6b6b51f4,0x1c6c6162,0x856530d8,0xf262004e,0x6c0695ed,0x1b01a57b,0x8208f4c1,0xf50fc457,
    0x65b0d9c6,0x12b7e950,0x8bbeb8ea,0xfcb9887c,0x62dd1ddf,0x15da2d49,0x8cd37cf3,0xfbd44c65,
    0x4db26158,0x3ab551ce,0xa3bc0074,0xd4bb30e2,0x4adfa541,0x3dd895d7,0xa4d1c46d,0xd3d6f4fb,
    0x4369e96a,0x346ed9fc,0xad678846,0xda60b8d0,0x44042d73,0x33031de5,0xaa0a4c5f,0xdd0d7cc9,
    0x5005713c,0x270241aa,0xbe0b1010,0xc90c2086,0x5768b525,0x206f85b3,0xb966d409,0xce61e49f,
    0x5edef90e,0x29d9c998,0xb0d09822,0xc7d7a8b4,0x59b33d17,0x2eb40d81,0xb7bd5c3b,0xc0ba6cad,
    0xedb88320,0x9abfb3b6,0x03b6e20c,0x74b1d29a,0xead54739,0x9dd277af,0x04db2615,0x73dc1683,
    0xe3630b12,0x94643b84,0x0d6d6a3e,0x7a6a5aa8,0xe40ecf0b,0x9309ff9d,0x0a00ae27,0x7d079eb1,
    0xf00f9344,0x8708a3d2,0x1e01f268,0x6906c2fe,0xf762575d,0x806567cb,0x196c3671,0x6e6b06e7,
    0xfed41b76,0x89d32be0,0x10da7a5a,0x67dd4acc,0xf9b9df6f,0x8ebeeff9,0x17b7be43,0x60b08ed5,
    0xd6d6a3e8,0xa1d1937e,0x38d8c2c4,0x4fdff252,0xd1bb67f1,0xa6bc5767,0x3fb506dd,0x48b2364b,
    0xd80d2bda,0xaf0a1b4c,0x36034af6,0x41047a60,0xdf60efc3,0xa867df55,0x316e8eef,0x4669be79,
    0xcb61b38c,0xbc66831a,0x256fd2a0,0x5268e236,0xcc0c7795,0xbb0b4703,0x220216b9,0x5505262f,
    0xc5ba3bbe,0xb2bd0b28,0x2bb45a92,0x5cb36a04,0xc2d7ffa7,0xb5d0cf31,0x2cd99e8b,0x5bdeae1d,
    0x9b64c2b0,0xec63f226,0x756aa39c,0x026d930a,0x9c0906a9,0xeb0e363f,0x72076785,0x05005713,
    0x95bf4a82,0xe2b87a14,0x7bb12bae,0x0cb61b38,0x92d28e9b,0xe5d5be0d,0x7cdcefb7,0x0bdbdf21,
    0x86d3d2d4,0xf1d4e242,0x68ddb3f8,0x1fda836e,0x81be16cd,0xf6b9265b,0x6fb077e1,0x18b74777,
    0x88085ae6,0xff0f6a70,0x66063bca,0x11010b5c,0x8f659eff,0xf862ae69,0x616bffd3,0x166ccf45,
    0xa00ae278,0xd70dd2ee,0x4e048354,0x3903b3c2,0xa7672661,0xd06016f7,0x4969474d,0x3e6e77db,
    0xaed16a4a,0xd9d65adc,0x40df0b66,0x37d83bf0,0xa9bcae53,0xdebb9ec5,0x47b2cf7f,0x30b5ffe9,
    0xbdbdf21c,0xcabac28a,0x53b39330,0x24b4a3a6,0xbad03605,0xcdd70693,0x54de5729,0x23d967bf,
    0xb3667a2e,0xc4614ab8,0x5d681b02,0x2a6f2b94,0xb40bbe37,0xc30c8ea1,0x5a05df1b,0x2d02ef8d
};

struct ReadResult
{
    uint32_t contentSize;
    void* content;
};

struct PngChunk
{
    uint32_t    lenght;
    uint32_t    type;
    const void* data;
    uint32_t    crc;
    const void* crc_data;
};

struct PngMetadata
{
    uint32_t width;
    uint32_t height;
    uint8_t  bitDepth;
    uint8_t  colorType;
    uint8_t  compression;
    uint8_t  filter;
    uint8_t  interlace;
    uint32_t gamma;
};

struct PngBitStream
{
    uint8_t* dataStream;
    uint32_t bitBuffer;
    uint32_t bitsRemaining;
};

struct ZlibBlock
{
    uint8_t        compressionMethod;
    uint8_t        extraFlags;
    const uint8_t* data;
    uint16_t       checkValue; // Adler32
};

constexpr uint8_t readInt8( const void* ptr, const uint32_t offset = 0 )
{
    return ((const uint8_t*)ptr)[offset];
}

constexpr uint32_t readInt16( const void* ptr )
{
    return static_cast<uint32_t>(readInt8( ptr, 0 )) <<  8 |
           static_cast<uint32_t>(readInt8( ptr, 1 )) <<  0;
}

constexpr uint32_t readInt32( const void* ptr )
{
    return static_cast<uint32_t>(readInt8( ptr, 0 )) << 24 |
           static_cast<uint32_t>(readInt8( ptr, 1 )) << 16 |
           static_cast<uint32_t>(readInt8( ptr, 2 )) <<  8 |
           static_cast<uint32_t>(readInt8( ptr, 3 )) <<  0;
}

constexpr uint64_t readInt64( const void* ptr )
{
    return static_cast<uint64_t>(readInt8( ptr, 0 )) << 56 |
           static_cast<uint64_t>(readInt8( ptr, 1 )) << 48 |
           static_cast<uint64_t>(readInt8( ptr, 2 )) << 40 |
           static_cast<uint64_t>(readInt8( ptr, 3 )) << 32 |
           static_cast<uint64_t>(readInt8( ptr, 4 )) << 24 |
           static_cast<uint64_t>(readInt8( ptr, 5 )) << 16 |
           static_cast<uint64_t>(readInt8( ptr, 6 )) <<  8 |
           static_cast<uint64_t>(readInt8( ptr, 7 )) <<  0;
}

/* https://lxp32.github.io/docs/a-simple-example-crc32-calculation/ */
const uint32_t crc32_fast(const uint8_t* memory, size_t n)
{
    uint32_t crc = 0xFFFFFFFF;

	for(size_t i = 0; i < n; i++) {
		uint8_t ch = memory[i];
		uint32_t t = (ch^crc) & 0xFF;
		crc = (crc >> 8) ^ crc32_table[t];
	}

	return ~crc;
}

constexpr bool checkPNGSign( const void* memory )
{
    return readInt64( memory ) == 0x89504E470D0A1A0A;
} 
const PngChunk readChunk( const void* ptr )
{
    PngChunk result = {};

    const uint8_t* byte = (const uint8_t*)ptr;

    result.lenght = readInt32( byte );
    SKIP_BYTES(byte, 4);

    result.type = readInt32( byte );
    result.crc_data = byte;
    SKIP_BYTES(byte, 4);

    result.data = byte;
    SKIP_BYTES(byte, result.lenght);

    result.crc = readInt32( byte );

    return result;
}

const ZlibBlock readZlibBlock( const uint8_t* memory, uint32_t lenght )
{
    ZlibBlock result = {};

    result.compressionMethod = *memory;
    SKIP_BYTES(memory, 1);

    result.extraFlags = *memory;
    SKIP_BYTES(memory, 1);

    result.data = memory;
    SKIP_BYTES(memory, lenght - 2);

    result.checkValue = readInt16(memory);
    SKIP_BYTES(memory, 2);
}

// function that will make sure we have the required number of bits inside bit buffer
void PngGetBits(PngBitStream* bits, uint32_t bitsRequired)
{
    //this is an extremely stupid way to make sure the unsigned integer doesn't underflow, this is just a replacement for abs() but on unsigned integers.
    uint32_t extraBitsNeeded = (bits->bitsRemaining > bitsRequired) ? (bits->bitsRemaining - bitsRequired) : (bitsRequired - bits->bitsRemaining);
    uint32_t bytesToRead = extraBitsNeeded / 8;

    //because the above is integer division, there is a possibility of bits to be remaining, i.e: imagine extra_bits_needed is 14, if you do integer division by 8, you get 1, but an extra 6 bits remain 
    if(extraBitsNeeded % 8) { //do we have any remaining bits?
        //if we do have extra bits they won't be more than 8 bits, so we will add one extra byte for those bits and we are good to go
        bytesToRead++; 
    }

    for(uint32_t i = 0; i < bytesToRead; ++i) {
        uint32_t byte = *bits->dataStream++;
        bits->bitBuffer |= byte << (i*8 + bits->bitsRemaining); //we need to be careful to not overwrite the remaining bits if any
    }

    bits->bitsRemaining += bytesToRead * 8;
}

uint32_t PngReadBits(PngBitStream* bits, uint32_t bitsToRead)
{
    uint32_t result = 0;

    if (bitsToRead > bits->bitsRemaining)
    {
        PngGetBits(bits, bitsToRead);
    }

    for (uint32_t i = 0; i < bitsToRead; ++i)
    {
        uint32_t bit = bits->bitBuffer & (1 << i);
        result |= bit;
    }

    bits->bitBuffer >>= bitsToRead;
    bits->bitsRemaining-= bitsToRead;

    return result;
}

inline uint32_t safeTruncateUInt64(uint64_t value)
{
    Assert(value <= 0xFFFFFFFF);
    uint32_t result = (uint32_t)value;
    return result;
}

void  freeFileMemory(void* memory)
{
    if (memory)
    {
        VirtualFree(memory, 0, MEM_RELEASE);
    }
}

ReadResult readEntirefile(char* filename)
{
    ReadResult result = {};

    HANDLE fileHandle = CreateFileA(
        filename,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        NULL,
        NULL);

    if (fileHandle != INVALID_HANDLE_VALUE)
    {
        LARGE_INTEGER fileSize;
        if (GetFileSizeEx(fileHandle, &fileSize))
        {
            result.content = VirtualAlloc(0, fileSize.QuadPart, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

            if (result.content)
            {
                uint32_t fileSize32 = safeTruncateUInt64(fileSize.QuadPart);
                DWORD bytesRead = 0;
                if (ReadFile(fileHandle, result.content, fileSize32, &bytesRead, NULL))
                {
                    result.contentSize = fileSize32;
                }
                else
                {
                    freeFileMemory(result.content);
                    result.content = 0;
                    result.contentSize = 0;
                }
            }
        }

        CloseHandle(fileHandle);
    }
    
    return result;
}

int WINAPI WinMain( HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, int cmdShow )
{
    // TODO: Open File (Get bitstream)
    ReadResult file = readEntirefile("data/basi0g01.png");

    // TODO: Parse bitstream
    if ( !checkPNGSign( file.content ) ) 
    {
        printf("Error: Invalid PNG signature!\n");
    }
    else
    {
        const uint8_t* ptr = (const uint8_t*)file.content + 8;
        PngMetadata metadata = {};

        while ( ptr < ((const uint8_t*)file.content + file.contentSize) )
        {
            const PngChunk chunk = readChunk( ptr );

            if ( crc32_fast((const uint8_t*)chunk.crc_data, chunk.lenght + 4) != chunk.crc )
            {
                printf("CRC failed...\n");
            }

            switch (chunk.type)
            {
                case IHDR_HEADER:
                {
                    const uint8_t* byte = (const uint8_t*)chunk.data;
                    metadata.width = readInt32(byte);
                    SKIP_BYTES(byte, 4);
                    
                    metadata.height = readInt32(byte);
                    SKIP_BYTES(byte, 4);

                    metadata.bitDepth    = readInt8(byte);
                    SKIP_BYTES(byte, 1);
                    metadata.colorType   = readInt8(byte);
                    SKIP_BYTES(byte, 1);
                    metadata.compression = readInt8(byte);
                    SKIP_BYTES(byte, 1);
                    metadata.filter      = readInt8(byte);
                    SKIP_BYTES(byte, 1);
                    metadata.interlace   = readInt8(byte);
                    SKIP_BYTES(byte, 1);
                } break;

                case gAMA_HEADER:
                {
                    const uint8_t* byte = (const uint8_t*)chunk.data;
                    metadata.gamma = readInt32(byte);
                    SKIP_BYTES(byte, 4);
                } break;

                case IDAT_HEADER:
                {
                    // Join All IDAT

                    // Decompress data
                    const ZlibBlock zlib = readZlibBlock((const uint8_t*)chunk.data, chunk.lenght);

                } break;
            }

            ptr += chunk.lenght + 4 + 4 + 4;
        }
    }

    /*for(uint32_t i=0;i<256;i++) {
		uint32_t ch=i;
		uint32_t crc=0;
		for(size_t j=0;j<8;j++) {
			uint32_t b=(ch^crc)&1;
			crc>>=1;
			if(b) crc=crc^0xEDB88320;
			ch>>=1;
		}
		crc32_table[i]=crc;
        printf("%08x\n",crc);
	}*/

    // TODO: Display decoded image

    return 0;
}
