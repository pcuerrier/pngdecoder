#pragma once
#include "../pngdecoder/pngdecoder.h"
#include "gtest/gtest.h"
#include "lodepng.h"

void checkPng(const char* fileName);
void checkErrorCode(const char* fileName, PNGErrorCode code);