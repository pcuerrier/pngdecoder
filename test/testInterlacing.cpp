#include "common.h"

TEST(Interlacing, 01_Black_and_White)
{
    checkPng("data/basi0g01.png");
}

TEST(Interlacing, 02_2Bit_Grayscale)
{
    checkPng("data/basi0g02.png");
}

TEST(Interlacing, 03_4Bit_Grayscale)
{
    checkPng("data/basi0g04.png");
}

TEST(Interlacing, 04_8Bit_Grayscale)
{
    checkPng("data/basi0g08.png");
}

TEST(Interlacing, 05_16Bit_Grayscale)
{
    checkPng("data/basi0g16.png");
}

TEST(Interlacing, 06_3x8Bit_RGB_Color)
{
    checkPng("data/basi2c08.png");
}

TEST(Interlacing, 07_3x16Bit_RGB_Color)
{
    checkPng("data/basi2c16.png");
}

TEST(Interlacing, 08_1Bit_Palet)
{
    checkPng("data/basi3p01.png");
}

TEST(Interlacing, 09_2Bit_Palet)
{
    checkPng("data/basi3p02.png");
}

TEST(Interlacing, 10_4Bit_Palet)
{
    checkPng("data/basi3p04.png");
}

TEST(Interlacing, 11_8Bit_Palet)
{
    checkPng("data/basi3p08.png");
}

TEST(Interlacing, 12_8Bit_Grayscale_and_8Bit_Alpha)
{
    checkPng("data/basi4a08.png");
}

TEST(Interlacing, 13_16Bit_Grayscale_and_16Bit_Alpha)
{
    checkPng("data/basi4a16.png");
}

TEST(Interlacing, 14_3x8Bit_RGB_Color_and_8Bit_Alpha)
{
    checkPng("data/basi6a08.png");
}

TEST(Interlacing, 15_3x16Bit_RGB_Color_and_16Bit_Alpha)
{
    checkPng("data/basi6a16.png");
}
