#include "common.h"

TEST(BackgroundColors, 01_8Bit_Grayscale_Alpha_No_Background_Interlaced)
{
    checkPng("data/bgai4a08.png");
}

TEST(BackgroundColors, 02_16_bit_Grayscale_Alpha_No_Background_Interlaced)
{
    checkPng("data/bgai4a16.png");
}

TEST(BackgroundColors, 03_3x8Bit_RGB_Alpha_No_Background)
{
    checkPng("data/bgan6a08.png");
}

TEST(BackgroundColors, 04_3x16Bit_RGB_Alpha_No_Background)
{
    checkPng("data/bgan6a16.png");
}

TEST(BackgroundColors, 05_8Bit_Grayscale_Alpha_Black_Background)
{
    checkPng("data/bgbn4a08.png");
}

TEST(BackgroundColors, 06_16Bit_Grayscale_Alpha_Gray_Background)
{
    checkPng("data/bggn4a16.png");
}

TEST(BackgroundColors, 07_3x8Bit_RGB_Alpha_White_Background)
{
    checkPng("data/bgwn6a08.png");
}

TEST(BackgroundColors, 08_3x16Bit_RGB_Alpha_Yellow_Background)
{
    checkPng("data/bgyn6a16.png");
}
