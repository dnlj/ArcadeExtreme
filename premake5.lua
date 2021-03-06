require "buildcfg/actions"

workspace "ArcadeWorkspace"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	characterset "Unicode"

project "Arcade"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}_%{cfg.platform}"
	objdir "obj/%{cfg.buildcfg}_%{cfg.platform}"
	rtti "Off"
	debugdir "src"
	files {
		"src/**.cpp",
		"include/**.hpp",
	}
	includedirs {
		"include",
		"dependencies/SFML/include",
	}
	debugenvs {
		-- Start PATH
		"PATH="
		.."%{wks.location}/dependencies/SFML/build/lib/%{cfg.buildcfg};"
		.."%PATH%"
		-- End PATH
	}
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		libdirs {
			"dependencies/SFML/build/lib/Debug",
		}
		links {
			"sfml-audio-d.lib",
			"sfml-graphics-d.lib",
			"sfml-main-d.lib",
			"sfml-network-d.lib",
			"sfml-system-d.lib",
			"sfml-window-d.lib",
		}
		
	filter "configurations:Release"
		defines { "NDEBUG", "RELEASE" }
		optimize "On"
		libdirs {
			"dependencies/SFML/build/lib/Release",
		}
		links {
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-main.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib",
		}

	filter { "platforms:x64" }
		system "Windows"
		architecture "x64"

































