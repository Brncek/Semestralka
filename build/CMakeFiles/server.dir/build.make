# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/brncek/Desktop/Semestralka

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/brncek/Desktop/Semestralka/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/server.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server.c.o: ../server.c
CMakeFiles/server.dir/server.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brncek/Desktop/Semestralka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/server.c.o -MF CMakeFiles/server.dir/server.c.o.d -o CMakeFiles/server.dir/server.c.o -c /home/brncek/Desktop/Semestralka/server.c

CMakeFiles/server.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brncek/Desktop/Semestralka/server.c > CMakeFiles/server.dir/server.c.i

CMakeFiles/server.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brncek/Desktop/Semestralka/server.c -o CMakeFiles/server.dir/server.c.s

CMakeFiles/server.dir/fileManager.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/fileManager.c.o: ../fileManager.c
CMakeFiles/server.dir/fileManager.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brncek/Desktop/Semestralka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/server.dir/fileManager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/fileManager.c.o -MF CMakeFiles/server.dir/fileManager.c.o.d -o CMakeFiles/server.dir/fileManager.c.o -c /home/brncek/Desktop/Semestralka/fileManager.c

CMakeFiles/server.dir/fileManager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/fileManager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brncek/Desktop/Semestralka/fileManager.c > CMakeFiles/server.dir/fileManager.c.i

CMakeFiles/server.dir/fileManager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/fileManager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brncek/Desktop/Semestralka/fileManager.c -o CMakeFiles/server.dir/fileManager.c.s

CMakeFiles/server.dir/symulator.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/symulator.c.o: ../symulator.c
CMakeFiles/server.dir/symulator.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brncek/Desktop/Semestralka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server.dir/symulator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/symulator.c.o -MF CMakeFiles/server.dir/symulator.c.o.d -o CMakeFiles/server.dir/symulator.c.o -c /home/brncek/Desktop/Semestralka/symulator.c

CMakeFiles/server.dir/symulator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/symulator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brncek/Desktop/Semestralka/symulator.c > CMakeFiles/server.dir/symulator.c.i

CMakeFiles/server.dir/symulator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/symulator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brncek/Desktop/Semestralka/symulator.c -o CMakeFiles/server.dir/symulator.c.s

CMakeFiles/server.dir/serverIPC.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/serverIPC.c.o: ../serverIPC.c
CMakeFiles/server.dir/serverIPC.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/brncek/Desktop/Semestralka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/server.dir/serverIPC.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/serverIPC.c.o -MF CMakeFiles/server.dir/serverIPC.c.o.d -o CMakeFiles/server.dir/serverIPC.c.o -c /home/brncek/Desktop/Semestralka/serverIPC.c

CMakeFiles/server.dir/serverIPC.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/serverIPC.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/brncek/Desktop/Semestralka/serverIPC.c > CMakeFiles/server.dir/serverIPC.c.i

CMakeFiles/server.dir/serverIPC.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/serverIPC.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/brncek/Desktop/Semestralka/serverIPC.c -o CMakeFiles/server.dir/serverIPC.c.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server.c.o" \
"CMakeFiles/server.dir/fileManager.c.o" \
"CMakeFiles/server.dir/symulator.c.o" \
"CMakeFiles/server.dir/serverIPC.c.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/server.c.o
server: CMakeFiles/server.dir/fileManager.c.o
server: CMakeFiles/server.dir/symulator.c.o
server: CMakeFiles/server.dir/serverIPC.c.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/brncek/Desktop/Semestralka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/brncek/Desktop/Semestralka/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/brncek/Desktop/Semestralka /home/brncek/Desktop/Semestralka /home/brncek/Desktop/Semestralka/build /home/brncek/Desktop/Semestralka/build /home/brncek/Desktop/Semestralka/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

