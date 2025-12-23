project "Imgui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	warnings "off"

	targetdir ("Build/" .. output_directory .. "/%{prj.name}")
	objdir ("Build/" .. output_directory .. "/%{prj.name}/Intermediates")

	files {
        "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "imgui_tables.cpp",
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "backends/imgui_impl_dx11.h",
        "backends/imgui_impl_dx11.cpp",
        "backends/imgui_impl_win32.h",
        "backends/imgui_impl_win32.cpp",
        "backends/imgui_impl_opengl3.h",
        "backends/imgui_impl_opengl3.cpp",
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_glfw.cpp"
	}

	includedirs {
        "%{wks.location}/Neovoid/Vendor/Imgui",
        "%{wks.location}/Neovoid/Vendor/GLFW/include",
        "%{wks.location}/Neovoid/Vendor/Glad/include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
