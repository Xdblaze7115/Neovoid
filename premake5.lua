workspace "Neovoid"
	architecture "x64"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

output_directory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include_directory = {}
include_directory["magic_enum"] = "Neovoid/Vendor/magic_enum/include"
include_directory["glm"] = "Neovoid/Vendor/glm"
include_directory["Imgui"] = "Neovoid/Vendor/Imgui"
include_directory["GLFW"] = "Neovoid/Vendor/GLFW/include"
include_directory["Glad"] = "Neovoid/Vendor/Glad/include"

include "Neovoid/Vendor/Imgui"
include "Neovoid/Vendor/GLFW"
include "Neovoid/Vendor/Glad"

project "Neovoid"
	location "Neovoid"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("Build/" .. output_directory .. "/%{prj.name}")
	objdir ("Build/" .. output_directory .. "/%{prj.name}/Intermediates")

	files {
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Vendor/magic_enum/include/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.h",
		"%{prj.name}/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.inl",
		"%{prj.name}/Vendor/glm/glm/**.cpp"
	}

	includedirs {
		"%{prj.name}/",
		"%{prj.name}/Source",
		"%{prj.name}/Vendor",
		"%{include_directory.magic_enum}",
		"%{include_directory.glm}",
		"%{include_directory.Imgui}",
		"%{include_directory.GLFW}",
		"%{include_directory.Glad}"
	}

	links {
		-- DX3D ??
		-- OpenGL ??
        "d3d11",
        "dxgi",
        "d3dcompiler",
		"Imgui",
		"GLFW",
		"Glad",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"NEO_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "NEO_DEBUG"
        runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NEO_RELEASE"
        runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NEO_DIST"
        runtime "Release"
		optimize "on"