# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build

# Include any dependencies generated for this target.
include CMakeFiles/MP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MP.dir/flags.make

CMakeFiles/MP.dir/main.cpp.o: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/main.cpp.o: /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/main.cpp
CMakeFiles/MP.dir/main.cpp.o: CMakeFiles/MP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MP.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MP.dir/main.cpp.o -MF CMakeFiles/MP.dir/main.cpp.o.d -o CMakeFiles/MP.dir/main.cpp.o -c /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/main.cpp

CMakeFiles/MP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/main.cpp > CMakeFiles/MP.dir/main.cpp.i

CMakeFiles/MP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/main.cpp -o CMakeFiles/MP.dir/main.cpp.s

CMakeFiles/MP.dir/MPEngine.cpp.o: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/MPEngine.cpp.o: /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/MPEngine.cpp
CMakeFiles/MP.dir/MPEngine.cpp.o: CMakeFiles/MP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MP.dir/MPEngine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MP.dir/MPEngine.cpp.o -MF CMakeFiles/MP.dir/MPEngine.cpp.o.d -o CMakeFiles/MP.dir/MPEngine.cpp.o -c /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/MPEngine.cpp

CMakeFiles/MP.dir/MPEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/MPEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/MPEngine.cpp > CMakeFiles/MP.dir/MPEngine.cpp.i

CMakeFiles/MP.dir/MPEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/MPEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/MPEngine.cpp -o CMakeFiles/MP.dir/MPEngine.cpp.s

CMakeFiles/MP.dir/Bardo.cpp.o: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/Bardo.cpp.o: /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Bardo.cpp
CMakeFiles/MP.dir/Bardo.cpp.o: CMakeFiles/MP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MP.dir/Bardo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MP.dir/Bardo.cpp.o -MF CMakeFiles/MP.dir/Bardo.cpp.o.d -o CMakeFiles/MP.dir/Bardo.cpp.o -c /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Bardo.cpp

CMakeFiles/MP.dir/Bardo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/Bardo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Bardo.cpp > CMakeFiles/MP.dir/Bardo.cpp.i

CMakeFiles/MP.dir/Bardo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/Bardo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Bardo.cpp -o CMakeFiles/MP.dir/Bardo.cpp.s

CMakeFiles/MP.dir/ArcballCam.cpp.o: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/ArcballCam.cpp.o: /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/ArcballCam.cpp
CMakeFiles/MP.dir/ArcballCam.cpp.o: CMakeFiles/MP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MP.dir/ArcballCam.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MP.dir/ArcballCam.cpp.o -MF CMakeFiles/MP.dir/ArcballCam.cpp.o.d -o CMakeFiles/MP.dir/ArcballCam.cpp.o -c /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/ArcballCam.cpp

CMakeFiles/MP.dir/ArcballCam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/ArcballCam.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/ArcballCam.cpp > CMakeFiles/MP.dir/ArcballCam.cpp.i

CMakeFiles/MP.dir/ArcballCam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/ArcballCam.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/ArcballCam.cpp -o CMakeFiles/MP.dir/ArcballCam.cpp.s

CMakeFiles/MP.dir/Peanut.cpp.o: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/Peanut.cpp.o: /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Peanut.cpp
CMakeFiles/MP.dir/Peanut.cpp.o: CMakeFiles/MP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MP.dir/Peanut.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MP.dir/Peanut.cpp.o -MF CMakeFiles/MP.dir/Peanut.cpp.o.d -o CMakeFiles/MP.dir/Peanut.cpp.o -c /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Peanut.cpp

CMakeFiles/MP.dir/Peanut.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/Peanut.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Peanut.cpp > CMakeFiles/MP.dir/Peanut.cpp.i

CMakeFiles/MP.dir/Peanut.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/Peanut.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Peanut.cpp -o CMakeFiles/MP.dir/Peanut.cpp.s

CMakeFiles/MP.dir/Dorock.cpp.o: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/Dorock.cpp.o: /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Dorock.cpp
CMakeFiles/MP.dir/Dorock.cpp.o: CMakeFiles/MP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MP.dir/Dorock.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MP.dir/Dorock.cpp.o -MF CMakeFiles/MP.dir/Dorock.cpp.o.d -o CMakeFiles/MP.dir/Dorock.cpp.o -c /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Dorock.cpp

CMakeFiles/MP.dir/Dorock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/Dorock.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Dorock.cpp > CMakeFiles/MP.dir/Dorock.cpp.i

CMakeFiles/MP.dir/Dorock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/Dorock.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/Dorock.cpp -o CMakeFiles/MP.dir/Dorock.cpp.s

# Object files for target MP
MP_OBJECTS = \
"CMakeFiles/MP.dir/main.cpp.o" \
"CMakeFiles/MP.dir/MPEngine.cpp.o" \
"CMakeFiles/MP.dir/Bardo.cpp.o" \
"CMakeFiles/MP.dir/ArcballCam.cpp.o" \
"CMakeFiles/MP.dir/Peanut.cpp.o" \
"CMakeFiles/MP.dir/Dorock.cpp.o"

# External object files for target MP
MP_EXTERNAL_OBJECTS =

MP: CMakeFiles/MP.dir/main.cpp.o
MP: CMakeFiles/MP.dir/MPEngine.cpp.o
MP: CMakeFiles/MP.dir/Bardo.cpp.o
MP: CMakeFiles/MP.dir/ArcballCam.cpp.o
MP: CMakeFiles/MP.dir/Peanut.cpp.o
MP: CMakeFiles/MP.dir/Dorock.cpp.o
MP: CMakeFiles/MP.dir/build.make
MP: CMakeFiles/MP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable MP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MP.dir/build: MP
.PHONY : CMakeFiles/MP.dir/build

CMakeFiles/MP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MP.dir/clean

CMakeFiles/MP.dir/depend:
	cd /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build /home/charlesmowbray/Documents/CSCI441/midtermProject/groupProject/CSCI441MP/build/CMakeFiles/MP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MP.dir/depend

