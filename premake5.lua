workspace "PrettyEngine"
	architecture "x64"

	startproject "PrettyEngine"

	configurations 
	{
		"Debug",
		"Release"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "PrettyEngine/thirdparty/GLFW/include"
IncludeDir["Glad"] = "PrettyEngine/thirdparty/Glad/include"
IncludeDir["ImGUI"] = "PrettyEngine/thirdparty/ImGUI"
IncludeDir["glm"] = "PrettyEngine/thirdparty/glm"
IncludeDir["stb"] = "PrettyEngine/thirdparty/stb"
IncludeDir["Box2D"] = "PrettyEngine/thirdparty/Box2D"
IncludeDir["Assimp"] = "PrettyEngine/thirdparty/Assimp/include"
IncludeDir["TinyXML"] = "PrettyEngine/thirdparty/TinyXML2/tinyxml2"
IncludeDir["NFD"] = "PrettyEngine/thirdparty/NativeFileDialog/src/Include"
IncludeDir["FMOD"] = "PrettyEngine/thirdparty/FMOD/include"
IncludeDir["Enet"] = "PrettyEngine/thirdparty/Enet/include"


group "Dependencies"
	include "PrettyEngine/thirdparty/GLFW"
	include "PrettyEngine/thirdparty/Glad"
	include "PrettyEngine/thirdparty/ImGUI"
	include "PrettyEngine/thirdparty/Box2D"
	include "PrettyEngine/thirdparty/NativeFileDialog"
	include "PrettyEngine/thirdparty/Enet"
group ""



project "PrettyEngine"
	location "PrettyEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..  outputdir .. "/%{prj.name}")

	pchheader "pepch.h"
	pchsource "PrettyEngine/src/pepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.Assimp}",
		"%{IncludeDir.TinyXML}",
		"%{IncludeDir.NFD}",
		"%{IncludeDir.FMOD}",
		"%{IncludeDir.Enet}"
	}
	
	libdirs 
		{
	
			--"PrettyEngine/thirdparty/Assimp/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Assimp",
			"PrettyEngine/thirdparty/Assimp/bin/Release-windows-x86_64/Assimp",
			--"PrettyEngine/thirdparty/Assimp/lib/%{cfg.buildcfg}"
			"PrettyEngine/thirdparty/Assimp/lib/Release",
			"PrettyEngine/thirdparty/TinyXML2/bin/Release-windows-x86_64/tinyxml",
			"PrettyEngine/thirdparty/FMOD/bin/Release-windows-x86_64/FMOD"
		}
	

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
		"Box2D",
		"Enet",
		"NativeFileDialog",

		"assimp-vc141-mt.lib",
		"IrrXML.lib",
		"zlibstatic.lib",
		"opengl32.lib",
		"tinyxml2.lib",
		"fmod64_vc.lib",
		"fmodL64_vc.lib",
		"fmodstudio64_vc.lib",
		"fmodstudioL64_vc.lib",
		"fsbank64_vc.lib",
		"winmm.lib",
		"ws2_32.lib"
	}


	filter "system:windows"
		systemversion "latest"


		defines 
		{
			"PE_PLATFORM_WINDOWS",
			"PE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"STB_IMAGE_IMPLEMENTATION"
		}


	filter "configurations:Debug"
		defines "PE_DEBUG"
		runtime "Debug"
		symbols "on"
		
		buildoptions 
		{
			"/MDd"
		}
		

	filter "configurations:Release"
		defines "PE_RELEASE"
		runtime "Release"
		staticruntime "off"
		optimize "on"
	
		buildoptions 
		{
			"/MD"
		}


