#include "common.h"

TEST(BasicFormats, 01_Black_and_White)
{
    checkPng("data/basn0g01.png");
}

TEST(BasicFormats, 02_2Bit_Grayscale)
{
    checkPng("data/basn0g02.png");
}

TEST(BasicFormats, 03_4Bit_Grayscale)
{
    checkPng("data/basn0g04.png");
}

TEST(BasicFormats, 04_8Bit_Grayscale)
{
    checkPng("data/basn0g08.png");
}

TEST(BasicFormats, 05_16Bit_Grayscale)
{
    checkPng("data/basn0g16.png");
}

TEST(BasicFormats, 06_3x8Bit_RGB_Color)
{
    checkPng("data/basn2c08.png");
}

TEST(BasicFormats, 07_3x16Bit_RGB_Color)
{
    checkPng("data/basn2c16.png");
}

TEST(BasicFormats, 08_1Bit_Palet)
{
    checkPng("data/basn3p01.png");
}

TEST(BasicFormats, 09_2Bit_Palet)
{
    checkPng("data/basn3p02.png");
}

TEST(BasicFormats, 10_4Bit_Palet)
{
    checkPng("data/basn3p04.png");
}

TEST(BasicFormats, 11_8Bit_Palet)
{
    checkPng("data/basn3p08.png");
}

TEST(BasicFormats, 12_8Bit_Grayscale_and_8Bit_Alpha)
{
    checkPng("data/basn4a08.png");
}

TEST(BasicFormats, 13_16Bit_Grayscale_and_16Bit_Alpha)
{
    checkPng("data/basn4a16.png");
}

TEST(BasicFormats, 14_3x8Bit_RGB_Color_and_8Bit_Alpha)
{
    checkPng("data/basn6a08.png");
}

TEST(BasicFormats, 15_3x16Bit_RGB_Color_and_16Bit_Alpha)
{
    checkPng("data/basn6a16.png");
}
