#include "common.h"

TEST(ZlibCompression, 01_Compression_0_None)
{
    checkPng("data/z00n2c08.png");
}

TEST(ZlibCompression, 02_Compression_3)
{
    checkPng("data/z03n2c08.png");
}

TEST(ZlibCompression, 03_Compression_6_Default)
{
    checkPng("data/z06n2c08.png");
}

TEST(ZlibCompression, 04_Compression_9_Maximum)
{
    checkPng("data/z09n2c08.png");
}
