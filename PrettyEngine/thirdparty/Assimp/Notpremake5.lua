project "Assimp"
        kind "StaticLib"
		language "C++"
        --location "build/"
        warnings "Off"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        defines {
            "ASSIMP_BUILD_NO_C4D_IMPORTER", -- Cinema4D is MSVC only and needs some weird headers to work
			--"ASSIMP_BUILD_NO_3DS_EXPORTER",
            "OPENDDL_STATIC_LIBARY"
        }
        files {
			"revision.h",
            "code/**.cpp",
            "code/**.h",
            "contrib/irrXML/*.cpp",
            "contrib/irrXML/*.h",
            "contrib/unzip/*.c",
            "contrib/unzip/*.h",
			"contrib/zip/src/*.h",
			"contrib/zip/src/*.c",
			"contrib/zlib/*.h",
			"contrib/zlib/*.c",
            "contrib/openddlparser/code/*.cpp",
            "contrib/poly2tri/poly2tri/**.cc",
            "contrib/clipper/*.cpp",
        }
        includedirs {
			"%{prj.name}",
			"code/",
			"code/*",
            "include/",
            "contrib/irrXML/",
            "contrib/rapidjson/include/",
            "contrib/openddlparser/include/",
			"contrib/zlib",
			"contrib/zip/src",
            "contrib/unzip/"  
        }
        removefiles {
            "code/Importer/IFC/IFCReaderGen_4.*",
        }

        filter "system:windows"
			systemversion "latest"
            buildoptions {
                "/bigobj",
            }
            defines {
                "_CRT_SECURE_NO_WARNINGS",
            }