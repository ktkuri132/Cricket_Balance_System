# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\cmake-4.0.0-windows-x86_64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\cmake-4.0.0-windows-x86_64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\34575\Desktop\Cricket_Balance_System

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\34575\Desktop\Cricket_Balance_System\build

# Include any dependencies generated for this target.
include CMakeFiles/CBS.elf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CBS.elf.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CBS.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CBS.elf.dir/flags.make

CMakeFiles/CBS.elf.dir/codegen:
.PHONY : CMakeFiles/CBS.elf.dir/codegen

CMakeFiles/CBS.elf.dir/main.c.obj: CMakeFiles/CBS.elf.dir/flags.make
CMakeFiles/CBS.elf.dir/main.c.obj: C:/Users/34575/Desktop/Cricket_Balance_System/main.c
CMakeFiles/CBS.elf.dir/main.c.obj: CMakeFiles/CBS.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34575\Desktop\Cricket_Balance_System\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CBS.elf.dir/main.c.obj"
	C:\PROGRA~2\ARMGNU~1\133167~1.3RE\bin\AR19DD~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CBS.elf.dir/main.c.obj -MF CMakeFiles\CBS.elf.dir\main.c.obj.d -o CMakeFiles\CBS.elf.dir\main.c.obj -c C:\Users\34575\Desktop\Cricket_Balance_System\main.c

CMakeFiles/CBS.elf.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CBS.elf.dir/main.c.i"
	C:\PROGRA~2\ARMGNU~1\133167~1.3RE\bin\AR19DD~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\34575\Desktop\Cricket_Balance_System\main.c > CMakeFiles\CBS.elf.dir\main.c.i

CMakeFiles/CBS.elf.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CBS.elf.dir/main.c.s"
	C:\PROGRA~2\ARMGNU~1\133167~1.3RE\bin\AR19DD~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\34575\Desktop\Cricket_Balance_System\main.c -o CMakeFiles\CBS.elf.dir\main.c.s

# Object files for target CBS.elf
CBS_elf_OBJECTS = \
"CMakeFiles/CBS.elf.dir/main.c.obj"

# External object files for target CBS.elf
CBS_elf_EXTERNAL_OBJECTS =

CBS.elf: CMakeFiles/CBS.elf.dir/main.c.obj
CBS.elf: CMakeFiles/CBS.elf.dir/build.make
CBS.elf: h723_core/libh723_corelib.a
CBS.elf: bsp/libbsplib.a
CBS.elf: project/libprojectlib.a
CBS.elf: bsp/libbsplib.a
CBS.elf: h723_core/libh723_corelib.a
CBS.elf: CMakeFiles/CBS.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\34575\Desktop\Cricket_Balance_System\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CBS.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CBS.elf.dir\link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Building C:/Users/34575/Desktop/Cricket_Balance_System/build/CBS.hex"
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Building C:/Users/34575/Desktop/Cricket_Balance_System/build/CBS.bin"
	arm-none-eabi-objcopy -Oihex C:/Users/34575/Desktop/Cricket_Balance_System/build/CBS.elf C:/Users/34575/Desktop/Cricket_Balance_System/build/CBS.hex
	arm-none-eabi-objcopy -Obinary C:/Users/34575/Desktop/Cricket_Balance_System/build/CBS.elf C:/Users/34575/Desktop/Cricket_Balance_System/build/CBS.bin

# Rule to build all files generated by this target.
CMakeFiles/CBS.elf.dir/build: CBS.elf
.PHONY : CMakeFiles/CBS.elf.dir/build

CMakeFiles/CBS.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CBS.elf.dir\cmake_clean.cmake
.PHONY : CMakeFiles/CBS.elf.dir/clean

CMakeFiles/CBS.elf.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\34575\Desktop\Cricket_Balance_System C:\Users\34575\Desktop\Cricket_Balance_System C:\Users\34575\Desktop\Cricket_Balance_System\build C:\Users\34575\Desktop\Cricket_Balance_System\build C:\Users\34575\Desktop\Cricket_Balance_System\build\CMakeFiles\CBS.elf.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/CBS.elf.dir/depend

