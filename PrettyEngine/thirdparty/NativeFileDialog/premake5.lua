  project "NativeFileDialog"
    kind "StaticLib"
	language "C++"
	--staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   

    -- common files
    files 
	{
		"src/*.h",
        "src/include/*.h",
        "src/nfd_common.c",
		"src/nfd_win.cpp"
    }

	
	includedirs {"src/include/"}
    warnings "extra"

    -- system build filters
    filter "system:windows"
     -- language "C++"
     -- files {"src/nfd_win.cpp"} -- >> I think this generates a LINK error
	  systemversion "latest"

	  --NO Support for linux and macOS at the moment 
--    filter {"action:gmake or action:xcode4"}
--      buildoptions {"-fno-exceptions"}
--
--    filter "system:macosx"
--      language "C"
--      files {"src/nfd_cocoa.m"}
--
--
--
--    filter {"system:linux", "options:linux_backend=gtk3"}
--      language "C"
--      files {"src/nfd_gtk.c"}
--      buildoptions {"`pkg-config --cflags gtk+-3.0`"}
--    filter {"system:linux", "options:linux_backend=zenity"}
--      language "C"
--      files {"src/nfd_zenity.c"}
--
--
--	    filter "system:macosx"
--    platforms {"x64"}
--  filter "system:windows or system:linux"
--    platforms {"x64", "x86"}
  

	 filter "configurations:Release"
		defines {"NDEBUG"}
		runtime "Release"
		optimize "On"


		  -- architecture filters
  filter "configurations:x86"
    architecture "x86"
  
  filter "configurations:x64"
    architecture "x86_64"

		  -- debug/release filters
  filter "configurations:Debug"
    defines {"DEBUG"}
	 runtime "Debug"
    symbols "On"
    targetsuffix "_d"

    -- visual studio filters
    filter "action:vs*"
      defines { "_CRT_SECURE_NO_WARNINGS" }      


