#include "common.h"

TEST(ImageFiltering, 01_Grayscale_Filter_0)
{
    checkPng("data/f00n0g08.png");
}

TEST(ImageFiltering, 02_Color_Filter_0)
{
    checkPng("data/f00n2c08.png");
}

TEST(ImageFiltering, 03_Grayscale_Filter_1)
{
    checkPng("data/f01n0g08.png");
}

TEST(ImageFiltering, 04_Color_Filter_1)
{
    checkPng("data/f01n2c08.png");
}

TEST(ImageFiltering, 05_Grayscale_Filter_2)
{
    checkPng("data/f02n0g08.png");
}

TEST(ImageFiltering, 06_Color_Filter_2)
{
    checkPng("data/f02n2c08.png");
}

TEST(ImageFiltering, 07_Grayscale_Filter_3)
{
    checkPng("data/f03n0g08.png");
}

TEST(ImageFiltering, 08_Color_Filter_3)
{
    checkPng("data/f03n2c08.png");
}

TEST(ImageFiltering, 09_Grayscale_Filter_4)
{
    checkPng("data/f04n0g08.png");
}

TEST(ImageFiltering, 10_Color_Filter_4)
{
    checkPng("data/f04n2c08.png");
}

TEST(ImageFiltering, 11_Grayscale_BitDepth_4_Filter_Changing_Per_Scanline)
{
    checkPng("data/f99n0g04.png");
}
