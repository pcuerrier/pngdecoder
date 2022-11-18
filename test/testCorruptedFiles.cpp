#include "common.h"

TEST(CorruptedFiles, 01_Signature_Reset_0x0)
{
    checkErrorCode("data/xs1n0g01.png", PNG_BAD_SIGNATURE);
}

TEST(CorruptedFiles, 02_Signature_Q)
{
    checkErrorCode("data/xs2n0g01.png", PNG_BAD_SIGNATURE);
}

TEST(CorruptedFiles, 03_Signature_Lowercase)
{
    checkErrorCode("data/xs4n0g01.png", PNG_BAD_SIGNATURE);
}

TEST(CorruptedFiles, 04_Signature_Swap_Characters)
{
    checkErrorCode("data/xs7n0g01.png", PNG_BAD_SIGNATURE);
}

TEST(CorruptedFiles, 05_Added_CR_Byte)
{
    checkErrorCode("data/xcrn0g04.png", PNG_INVALID_BYTE);
}

TEST(CorruptedFiles, 06_Added_LF_Byte)
{
    checkErrorCode("data/xlfn0g04.png", PNG_INVALID_BYTE);
}

TEST(CorruptedFiles, 07_IHDR_Incorrect_Checksum)
{
    checkErrorCode("data/xhdn0g08.png", PNG_INVALID_CHECKSUM);
}

TEST(CorruptedFiles, 08_Color_Type_1)
{
    checkErrorCode("data/xc1n0g08.png", PNG_INVALID_COLOR_TYPE);
}

TEST(CorruptedFiles, 09_Color_Type_9)
{
    checkErrorCode("data/xc9n2c08.png", PNG_INVALID_COLOR_TYPE);
}

TEST(CorruptedFiles, 10_Bit_Depth_0)
{
    checkErrorCode("data/xd0n2c08.png", PNG_INVALID_BIT_DEPTH);
}

TEST(CorruptedFiles, 11_Bit_Depth_3)
{
    checkErrorCode("data/xd3n2c08.png", PNG_INVALID_BIT_DEPTH);
}

TEST(CorruptedFiles, 12_Bit_Depth_99)
{
    checkErrorCode("data/xd9n2c08.png", PNG_INVALID_BIT_DEPTH);
}

TEST(CorruptedFiles, 13_IDAT_Missing)
{
    checkErrorCode("data/xdtn0g01.png", PNG_MISSING_HEADER);
}

TEST(CorruptedFiles, 14_IDAT_Incorrect_Checksum)
{
    checkErrorCode("data/xcsn0g01.png", PNG_INVALID_CHECKSUM);
}

TEST(CorruptedFiles, 15_Missing_File)
{
    checkErrorCode("data/missing.png", PNG_FILE_NOT_FOUND);
}
