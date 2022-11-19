#include "common.h"

void checkPng(const char* fileName)
{
    uint8_t* ref = nullptr;
    uint32_t widthRef = 0;
    uint32_t heightRef = 0;

    lodepng_decode32_file(&ref, &widthRef, &heightRef, fileName);
    PngResult result = decodePng(fileName);
    ASSERT_EQ(result.errorCode, PNG_OK);
    ASSERT_EQ(widthRef, result.width);
    ASSERT_EQ(heightRef, result.height);

    /*uint32_t pixelBytes = 4 * sizeof(uint8_t);
    uint32_t bytesPerRow = pixelBytes * widthRef;
    for ( uint32_t i = 0; i < bytesPerRow * heightRef; ++i )
    {
        EXPECT_EQ(*ref, *result.image);
        ref += sizeof(uint8_t);
        result.image += sizeof(uint8_t);
    }*/
}


void checkErrorCode(const char* fileName, PNGErrorCode code)
{
    PngResult result = decodePng(fileName);
    ASSERT_EQ(result.errorCode, code);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
