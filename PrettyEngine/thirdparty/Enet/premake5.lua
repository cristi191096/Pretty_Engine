project "Enet"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files { "*.c" }
	
	includedirs { "include/" }

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "on"
		
	
	configuration "Release"
		defines { "NDEBUG" }
		optimize "on"
		

--project "enet"
--	kind "SharedLib"
--	language "C"
--	
--	files { "*.c" }
--	
--	includedirs { "include/" }
--	
--	defines({"ENET_DLL=1" })
--	
--	configuration "Debug"
--		targetsuffix "d"
--		
--		defines({ "DEBUG" })
--
--		flags { "Symbols" }
--	
--	configuration "Release"
--		defines({ "NDEBUG" })
--
--		flags { "Optimize" }
--		
--	configuration { "Debug", "x64" }
--		targetsuffix "64d"
--		
--	configuration { "Release", "x64" }
--		targetsuffix "64"
--
	