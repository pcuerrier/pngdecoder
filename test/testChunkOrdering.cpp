#include "common.h"

TEST(ChunkOrdering, 01_Grayscale_1_IDAT_Chunk)
{
    checkPng("data/oi1n0g16.png");
}

TEST(ChunkOrdering, 02_Color_1_IDAT_Chunk)
{
    checkPng("data/oi1n2c16.png");
}

TEST(ChunkOrdering, 03_Grayscale_2_IDAT_Chunk)
{
    checkPng("data/oi2n0g16.png");
}

TEST(ChunkOrdering, 04_Color_2_IDAT_Chunk)
{
    checkPng("data/oi2n2c16.png");
}

TEST(ChunkOrdering, 05_Grayscale_4_IDAT_Chunk_Unequal)
{
    checkPng("data/oi4n0g16.png");
}

TEST(ChunkOrdering, 06_Color_4_IDAT_Chunk_Unequal)
{
    checkPng("data/oi4n2c16.png");
}

TEST(ChunkOrdering, 07_Grayscale_Multiple_IDAT_length_1)
{
    checkPng("data/oi9n0g16.png");
}

TEST(ChunkOrdering, 08_Color_Multiple_IDAT_length_1)
{
    checkPng("data/oi9n2c16.png");
}
