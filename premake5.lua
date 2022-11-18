workspace "pngdecoder"
    configurations { "Debug", "Release" }
    architecture "x86_64"
    startproject "pngdecoder"
    warnings "Extra"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "pngdecoder"   -- main project
include "test"         -- unit tests