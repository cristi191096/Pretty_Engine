-- Box2D premake5 script. Modified to fit the purpose of the project
-- https://premake.github.io/



project 'Box2D'
	kind 'StaticLib'
	warnings 'Extra'
	language 'C++'
    cppdialect 'C++11'
--	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files { 'Box2D/**' }
	includedirs { '.' }



	    filter 'system:linux'
        platforms { 'x86_64' }
    filter 'system:macosx'
        platforms { 'x86_64' }
    filter 'system:windows'
		systemversion "latest"
		defines { '_CRT_SECURE_NO_WARNINGS' }
	filter {}
	
	filter 'configurations:Debug'
		runtime "Debug"
	 	defines { 'DEBUG' }
		symbols "on"
	filter 'configurations:Release'
		runtime "Release"
		defines { 'NDEBUG' }
		optimize 'On'
	filter {}
