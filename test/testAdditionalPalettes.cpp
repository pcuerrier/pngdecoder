#include "common.h"

TEST(AdditionalPalettes, 01_Six_Cube_Palette_Chunk_True_Color)
{
    checkPng("data/pp0n2c16.png");
}

TEST(AdditionalPalettes, 02_Six_Cube_Palette_Chunk_True_Color_Alpha)
{
    checkPng("data/pp0n6a08.png");
}

TEST(AdditionalPalettes, 03_Six_Cube_Suggested_Palette_1Byte_Grayscale)
{
    checkPng("data/ps1n0g08.png");
}

TEST(AdditionalPalettes, 04_Six_Cube_Suggested_Palette_1Byte_True_Color)
{
    checkPng("data/ps1n2c16.png");
}

TEST(AdditionalPalettes, 05_Six_Cube_Suggested_Palette_2Bytes_Grayscale)
{
    checkPng("data/ps2n0g08.png");
}

TEST(AdditionalPalettes, 06_Six_Cube_Suggested_Palette_2Bytes_True_Color)
{
    checkPng("data/ps2n2c16.png");
}
