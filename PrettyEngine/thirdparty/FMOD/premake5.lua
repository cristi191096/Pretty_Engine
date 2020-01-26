project "FMOD"
	kind "StaticLib"
	--warnings 'Extra'
	language "C"
	--staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
	    "include/*.h",
	   "include/*.hpp"
	}
	
	includedirs { 'include' }
	
	filter "system:windows"
	    systemversion "latest"
	
	    defines 
	    { 
	        "_CRT_SECURE_NO_WARNINGS"
	    }
	
	filter "configurations:Debug"
	    runtime "Debug"
	    symbols "on"
	
	filter "configurations:Release"
	    runtime "Release"
	    optimize "on"
	
	