solution "rocky_shores"
	location("./")
	targetdir("./bin")
	configurations { "debug", "release" }
	objdir("obj/" .. os.get() .. "/")

	project "rocky_shores-app"
		kind "ConsoleApp"
		language "C++"
		files { "../src/*.cpp" }

		configuration "windows"
			links {"glu32", "opengl32", "gdi32", "winmm", "user32","GLEW"}

		configuration "linux"
			links {"GL","glfw","GLEW", "png"}

		configuration "macosx"
			links {"GL","glfw","GLEW", "CoreFoundation.framework"}
			libdirs {"/opt/local/lib"}
			includedirs {"/opt/local/include"}

		configuration "haiku"
			links {"GL","glfw","GLEW"}

		configuration "freebsd"
			links {"GL","glfw","GLEW"}

		configuration "debug"
			defines { "DEBUG" }
			flags { "Symbols" }
			buildoptions{ "-Wall" }
			targetname "rocky_shores-debug"

		configuration "release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			buildoptions{ "-Wall" }
			targetname "rocky_shores-release"