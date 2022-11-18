#include "common.h"

TEST(Transparency, 01_Transparent_Black_Background)
{
    checkPng("data/tbbn0g04.png");
}

TEST(Transparency, 02_Transparent_Blue_Background)
{
    checkPng("data/tbbn2c16.png");
}

TEST(Transparency, 03_Transparent_Black_Background)
{
    checkPng("data/tbbn3p08.png");
}

TEST(Transparency, 04_Transparent_Green_Background)
{
    checkPng("data/tbgn2c16.png");
}

TEST(Transparency, 05_Transparent_LightGray_Background)
{
    checkPng("data/tbgn3p08.png");
}

TEST(Transparency, 06_Transparent_Red_Background)
{
    checkPng("data/tbrn2c08.png");
}

TEST(Transparency, 07_Transparent_White_Background)
{
    checkPng("data/tbwn0g16.png");
}

TEST(Transparency, 08_Transparent_White_Background)
{
    checkPng("data/tbwn3p08.png");
}

TEST(Transparency, 09_Transparent_Yellow_Background)
{
    checkPng("data/tbyn3p08.png");
}

TEST(Transparency, 10_Not_Transparent_Gray_Background)
{
    checkPng("data/tp0n0g08.png");
}

TEST(Transparency, 11_Not_Transparent_Gray_Background)
{
    checkPng("data/tp0n2c08.png");
}

TEST(Transparency, 12_Not_Transparent_Gray_Background)
{
    checkPng("data/tp0n3p08.png");
}

TEST(Transparency, 13_Transparent_No_Background)
{
    checkPng("data/tp1n3p08.png");
}

TEST(Transparency, 14_Multiple_Levels_Transparency)
{
    checkPng("data/tm3n3p02.png");
}
