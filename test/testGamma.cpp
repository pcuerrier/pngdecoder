#include "common.h"

TEST(Gamma, 01_Grayscale_G035)
{
    checkPng("data/g03n0g16.png");
}

TEST(Gamma, 02_RGB_G035)
{
    checkPng("data/g03n2c08.png");
}

TEST(Gamma, 03_Paletted_G035)
{
    checkPng("data/g03n3p04.png");
}

TEST(Gamma, 04_Grayscale_G045)
{
    checkPng("data/g04n0g16.png");
}

TEST(Gamma, 05_RGB_G045)
{
    checkPng("data/g04n2c08.png");
}

TEST(Gamma, 06_Paletted_G045)
{
    checkPng("data/g04n3p04.png");
}

TEST(Gamma, 07_Grayscale_G055)
{
    checkPng("data/g05n0g16.png");
}

TEST(Gamma, 08_RGB_G055)
{
    checkPng("data/g05n2c08.png");
}

TEST(Gamma, 09_Paletted_G055)
{
    checkPng("data/g05n3p04.png");
}

TEST(Gamma, 10_Grayscale_G070)
{
    checkPng("data/g07n0g16.png");
}

TEST(Gamma, 11_RGB_G070)
{
    checkPng("data/g07n2c08.png");
}

TEST(Gamma, 12_Paletted_G070)
{
    checkPng("data/g07n3p04.png");
}

TEST(Gamma, 13_Grayscale_G100)
{
    checkPng("data/g10n0g16.png");
}

TEST(Gamma, 14_RGB_G100)
{
    checkPng("data/g10n2c08.png");
}

TEST(Gamma, 15_Paletted_G100)
{
    checkPng("data/g10n3p04.png");
}

TEST(Gamma, 16_Grayscale_G250)
{
    checkPng("data/g25n0g16.png");
}

TEST(Gamma, 17_RGB_G250)
{
    checkPng("data/g25n2c08.png");
}

TEST(Gamma, 18_Paletted_G250)
{
    checkPng("data/g25n3p04.png");
}
