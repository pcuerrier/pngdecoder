project "test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files { "**.h", "**.hpp", "**.cpp", "../pngdecoder/pngdecoder.*" }

    buildoptions { "-Wno-multichar" }

    includedirs { "%{wks.location}/external/googletest/googletest/include/" }
    libdirs { "%{wks.location}/external/googletest/build/lib/" }

    links { ":libgtest_main.a", ":libgtest.a" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"