# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/williammurari/dev/mynecraft

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/williammurari/dev/mynecraft

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target package
package: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Run CPack packaging tool..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cpack --config ./CPackConfig.cmake
.PHONY : package

# Special rule for the target package
package/fast: package
.PHONY : package/fast

# Special rule for the target package_source
package_source:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Run CPack packaging tool for source..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cpack --config ./CPackSourceConfig.cmake /Users/williammurari/dev/mynecraft/CPackSourceConfig.cmake
.PHONY : package_source

# Special rule for the target package_source
package_source/fast: package_source
.PHONY : package_source/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.24.2/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/williammurari/dev/mynecraft/CMakeFiles /Users/williammurari/dev/mynecraft//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/williammurari/dev/mynecraft/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -P /Users/williammurari/dev/mynecraft/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Shitcraft

# Build rule for target.
Shitcraft: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Shitcraft
.PHONY : Shitcraft

# fast build rule for target.
Shitcraft/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/build
.PHONY : Shitcraft/fast

#=============================================================================
# Target rules for targets named uninstall

# Build rule for target.
uninstall: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 uninstall
.PHONY : uninstall

# fast build rule for target.
uninstall/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/CMakeFiles/uninstall.dir/build.make lib/glfw/CMakeFiles/uninstall.dir/build
.PHONY : uninstall/fast

#=============================================================================
# Target rules for targets named glfw

# Build rule for target.
glfw: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 glfw
.PHONY : glfw

# fast build rule for target.
glfw/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/src/CMakeFiles/glfw.dir/build.make lib/glfw/src/CMakeFiles/glfw.dir/build
.PHONY : glfw/fast

#=============================================================================
# Target rules for targets named update_mappings

# Build rule for target.
update_mappings: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 update_mappings
.PHONY : update_mappings

# fast build rule for target.
update_mappings/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/src/CMakeFiles/update_mappings.dir/build.make lib/glfw/src/CMakeFiles/update_mappings.dir/build
.PHONY : update_mappings/fast

#=============================================================================
# Target rules for targets named docs

# Build rule for target.
docs: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 docs
.PHONY : docs

# fast build rule for target.
docs/fast:
	$(MAKE) $(MAKESILENT) -f lib/glfw/docs/CMakeFiles/docs.dir/build.make lib/glfw/docs/CMakeFiles/docs.dir/build
.PHONY : docs/fast

#=============================================================================
# Target rules for targets named glad

# Build rule for target.
glad: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 glad
.PHONY : glad

# fast build rule for target.
glad/fast:
	$(MAKE) $(MAKESILENT) -f lib/glad/CMakeFiles/glad.dir/build.make lib/glad/CMakeFiles/glad.dir/build
.PHONY : glad/fast

src/application.o: src/application.cpp.o
.PHONY : src/application.o

# target to build an object file
src/application.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/application.cpp.o
.PHONY : src/application.cpp.o

src/application.i: src/application.cpp.i
.PHONY : src/application.i

# target to preprocess a source file
src/application.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/application.cpp.i
.PHONY : src/application.cpp.i

src/application.s: src/application.cpp.s
.PHONY : src/application.s

# target to generate assembly for a file
src/application.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/application.cpp.s
.PHONY : src/application.cpp.s

src/gfx/camera.o: src/gfx/camera.cpp.o
.PHONY : src/gfx/camera.o

# target to build an object file
src/gfx/camera.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/camera.cpp.o
.PHONY : src/gfx/camera.cpp.o

src/gfx/camera.i: src/gfx/camera.cpp.i
.PHONY : src/gfx/camera.i

# target to preprocess a source file
src/gfx/camera.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/camera.cpp.i
.PHONY : src/gfx/camera.cpp.i

src/gfx/camera.s: src/gfx/camera.cpp.s
.PHONY : src/gfx/camera.s

# target to generate assembly for a file
src/gfx/camera.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/camera.cpp.s
.PHONY : src/gfx/camera.cpp.s

src/gfx/shader.o: src/gfx/shader.cpp.o
.PHONY : src/gfx/shader.o

# target to build an object file
src/gfx/shader.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/shader.cpp.o
.PHONY : src/gfx/shader.cpp.o

src/gfx/shader.i: src/gfx/shader.cpp.i
.PHONY : src/gfx/shader.i

# target to preprocess a source file
src/gfx/shader.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/shader.cpp.i
.PHONY : src/gfx/shader.cpp.i

src/gfx/shader.s: src/gfx/shader.cpp.s
.PHONY : src/gfx/shader.s

# target to generate assembly for a file
src/gfx/shader.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/shader.cpp.s
.PHONY : src/gfx/shader.cpp.s

src/gfx/texture.o: src/gfx/texture.cpp.o
.PHONY : src/gfx/texture.o

# target to build an object file
src/gfx/texture.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/texture.cpp.o
.PHONY : src/gfx/texture.cpp.o

src/gfx/texture.i: src/gfx/texture.cpp.i
.PHONY : src/gfx/texture.i

# target to preprocess a source file
src/gfx/texture.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/texture.cpp.i
.PHONY : src/gfx/texture.cpp.i

src/gfx/texture.s: src/gfx/texture.cpp.s
.PHONY : src/gfx/texture.s

# target to generate assembly for a file
src/gfx/texture.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/texture.cpp.s
.PHONY : src/gfx/texture.cpp.s

src/gfx/vendor/stb_image.o: src/gfx/vendor/stb_image.cpp.o
.PHONY : src/gfx/vendor/stb_image.o

# target to build an object file
src/gfx/vendor/stb_image.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/vendor/stb_image.cpp.o
.PHONY : src/gfx/vendor/stb_image.cpp.o

src/gfx/vendor/stb_image.i: src/gfx/vendor/stb_image.cpp.i
.PHONY : src/gfx/vendor/stb_image.i

# target to preprocess a source file
src/gfx/vendor/stb_image.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/vendor/stb_image.cpp.i
.PHONY : src/gfx/vendor/stb_image.cpp.i

src/gfx/vendor/stb_image.s: src/gfx/vendor/stb_image.cpp.s
.PHONY : src/gfx/vendor/stb_image.s

# target to generate assembly for a file
src/gfx/vendor/stb_image.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/vendor/stb_image.cpp.s
.PHONY : src/gfx/vendor/stb_image.cpp.s

src/gfx/window.o: src/gfx/window.cpp.o
.PHONY : src/gfx/window.o

# target to build an object file
src/gfx/window.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/window.cpp.o
.PHONY : src/gfx/window.cpp.o

src/gfx/window.i: src/gfx/window.cpp.i
.PHONY : src/gfx/window.i

# target to preprocess a source file
src/gfx/window.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/window.cpp.i
.PHONY : src/gfx/window.cpp.i

src/gfx/window.s: src/gfx/window.cpp.s
.PHONY : src/gfx/window.s

# target to generate assembly for a file
src/gfx/window.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/gfx/window.cpp.s
.PHONY : src/gfx/window.cpp.s

src/input.o: src/input.cpp.o
.PHONY : src/input.o

# target to build an object file
src/input.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/input.cpp.o
.PHONY : src/input.cpp.o

src/input.i: src/input.cpp.i
.PHONY : src/input.i

# target to preprocess a source file
src/input.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/input.cpp.i
.PHONY : src/input.cpp.i

src/input.s: src/input.cpp.s
.PHONY : src/input.s

# target to generate assembly for a file
src/input.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/input.cpp.s
.PHONY : src/input.cpp.s

src/level/chunk.o: src/level/chunk.cpp.o
.PHONY : src/level/chunk.o

# target to build an object file
src/level/chunk.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/chunk.cpp.o
.PHONY : src/level/chunk.cpp.o

src/level/chunk.i: src/level/chunk.cpp.i
.PHONY : src/level/chunk.i

# target to preprocess a source file
src/level/chunk.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/chunk.cpp.i
.PHONY : src/level/chunk.cpp.i

src/level/chunk.s: src/level/chunk.cpp.s
.PHONY : src/level/chunk.s

# target to generate assembly for a file
src/level/chunk.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/chunk.cpp.s
.PHONY : src/level/chunk.cpp.s

src/level/chunkmesh.o: src/level/chunkmesh.cpp.o
.PHONY : src/level/chunkmesh.o

# target to build an object file
src/level/chunkmesh.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/chunkmesh.cpp.o
.PHONY : src/level/chunkmesh.cpp.o

src/level/chunkmesh.i: src/level/chunkmesh.cpp.i
.PHONY : src/level/chunkmesh.i

# target to preprocess a source file
src/level/chunkmesh.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/chunkmesh.cpp.i
.PHONY : src/level/chunkmesh.cpp.i

src/level/chunkmesh.s: src/level/chunkmesh.cpp.s
.PHONY : src/level/chunkmesh.s

# target to generate assembly for a file
src/level/chunkmesh.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/chunkmesh.cpp.s
.PHONY : src/level/chunkmesh.cpp.s

src/level/gen.o: src/level/gen.cpp.o
.PHONY : src/level/gen.o

# target to build an object file
src/level/gen.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/gen.cpp.o
.PHONY : src/level/gen.cpp.o

src/level/gen.i: src/level/gen.cpp.i
.PHONY : src/level/gen.i

# target to preprocess a source file
src/level/gen.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/gen.cpp.i
.PHONY : src/level/gen.cpp.i

src/level/gen.s: src/level/gen.cpp.s
.PHONY : src/level/gen.s

# target to generate assembly for a file
src/level/gen.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/gen.cpp.s
.PHONY : src/level/gen.cpp.s

src/level/sky.o: src/level/sky.cpp.o
.PHONY : src/level/sky.o

# target to build an object file
src/level/sky.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/sky.cpp.o
.PHONY : src/level/sky.cpp.o

src/level/sky.i: src/level/sky.cpp.i
.PHONY : src/level/sky.i

# target to preprocess a source file
src/level/sky.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/sky.cpp.i
.PHONY : src/level/sky.cpp.i

src/level/sky.s: src/level/sky.cpp.s
.PHONY : src/level/sky.s

# target to generate assembly for a file
src/level/sky.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/sky.cpp.s
.PHONY : src/level/sky.cpp.s

src/level/tree.o: src/level/tree.cpp.o
.PHONY : src/level/tree.o

# target to build an object file
src/level/tree.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/tree.cpp.o
.PHONY : src/level/tree.cpp.o

src/level/tree.i: src/level/tree.cpp.i
.PHONY : src/level/tree.i

# target to preprocess a source file
src/level/tree.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/tree.cpp.i
.PHONY : src/level/tree.cpp.i

src/level/tree.s: src/level/tree.cpp.s
.PHONY : src/level/tree.s

# target to generate assembly for a file
src/level/tree.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/tree.cpp.s
.PHONY : src/level/tree.cpp.s

src/level/world.o: src/level/world.cpp.o
.PHONY : src/level/world.o

# target to build an object file
src/level/world.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/world.cpp.o
.PHONY : src/level/world.cpp.o

src/level/world.i: src/level/world.cpp.i
.PHONY : src/level/world.i

# target to preprocess a source file
src/level/world.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/world.cpp.i
.PHONY : src/level/world.cpp.i

src/level/world.s: src/level/world.cpp.s
.PHONY : src/level/world.s

# target to generate assembly for a file
src/level/world.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/level/world.cpp.s
.PHONY : src/level/world.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Shitcraft.dir/build.make CMakeFiles/Shitcraft.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... package"
	@echo "... package_source"
	@echo "... rebuild_cache"
	@echo "... docs"
	@echo "... uninstall"
	@echo "... update_mappings"
	@echo "... Shitcraft"
	@echo "... glad"
	@echo "... glfw"
	@echo "... src/application.o"
	@echo "... src/application.i"
	@echo "... src/application.s"
	@echo "... src/gfx/camera.o"
	@echo "... src/gfx/camera.i"
	@echo "... src/gfx/camera.s"
	@echo "... src/gfx/shader.o"
	@echo "... src/gfx/shader.i"
	@echo "... src/gfx/shader.s"
	@echo "... src/gfx/texture.o"
	@echo "... src/gfx/texture.i"
	@echo "... src/gfx/texture.s"
	@echo "... src/gfx/vendor/stb_image.o"
	@echo "... src/gfx/vendor/stb_image.i"
	@echo "... src/gfx/vendor/stb_image.s"
	@echo "... src/gfx/window.o"
	@echo "... src/gfx/window.i"
	@echo "... src/gfx/window.s"
	@echo "... src/input.o"
	@echo "... src/input.i"
	@echo "... src/input.s"
	@echo "... src/level/chunk.o"
	@echo "... src/level/chunk.i"
	@echo "... src/level/chunk.s"
	@echo "... src/level/chunkmesh.o"
	@echo "... src/level/chunkmesh.i"
	@echo "... src/level/chunkmesh.s"
	@echo "... src/level/gen.o"
	@echo "... src/level/gen.i"
	@echo "... src/level/gen.s"
	@echo "... src/level/sky.o"
	@echo "... src/level/sky.i"
	@echo "... src/level/sky.s"
	@echo "... src/level/tree.o"
	@echo "... src/level/tree.i"
	@echo "... src/level/tree.s"
	@echo "... src/level/world.o"
	@echo "... src/level/world.i"
	@echo "... src/level/world.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -P /Users/williammurari/dev/mynecraft/CMakeFiles/VerifyGlobs.cmake
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

