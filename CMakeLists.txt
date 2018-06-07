cmake_minimum_required(VERSION 3.0)

project(Using-STL VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Chapter 1: Introducing the Standard Template Library
add_executable(Misc1 ${CMAKE_SOURCE_DIR}/Chapter01/misc.cpp)
add_executable(Ex1_01 ${CMAKE_SOURCE_DIR}/Chapter01/Ex1_01.cpp)
add_executable(Ex1_02 ${CMAKE_SOURCE_DIR}/Chapter01/Ex1_02.cpp)
add_executable(Ex1_03 ${CMAKE_SOURCE_DIR}/Chapter01/Ex1_03.cpp)

# Chapter 2: Using Sequence Containers
add_executable(Misc2 ${CMAKE_SOURCE_DIR}/Chapter02/misc.cpp)
add_executable(Ex2_01 ${CMAKE_SOURCE_DIR}/Chapter02/Ex2_01.cpp)
add_executable(Ex2_02A ${CMAKE_SOURCE_DIR}/Chapter02/Ex2_02A.cpp)
add_executable(Ex2_02 ${CMAKE_SOURCE_DIR}/Chapter02/Ex2_02.cpp)
add_executable(Ex2_03 ${CMAKE_SOURCE_DIR}/Chapter02/Ex2_03.cpp)
add_executable(Ex2_04 ${CMAKE_SOURCE_DIR}/Chapter02/Ex2_04.cpp)
add_executable(Ex2_05 ${CMAKE_SOURCE_DIR}/Chapter02/Ex2_05.cpp)
add_executable(Ex2_06 ${CMAKE_SOURCE_DIR}/Chapter02/Ex2_06/Ex2_06.cpp)
add_executable(Ex2_07 ${CMAKE_SOURCE_DIR}/Chapter02/Ex2_07/Ex2_07.cpp)

# Chapter 3: Container Adapters
add_executable(Misc3 ${CMAKE_SOURCE_DIR}/Chapter03/misc.cpp)
add_executable(Ex3_01 ${CMAKE_SOURCE_DIR}/Chapter03/Ex3_01.cpp)
add_executable(Ex3_02 ${CMAKE_SOURCE_DIR}/Chapter03/Ex3_02/Ex3_02.cpp)
add_executable(Ex3_03 ${CMAKE_SOURCE_DIR}/Chapter03/Ex3_03.cpp)
add_executable(Ex3_04 ${CMAKE_SOURCE_DIR}/Chapter03/Ex3_04.cpp)
add_executable(Ex3_05 ${CMAKE_SOURCE_DIR}/Chapter03/Ex3_05/Ex3_05.cpp)
add_executable(Ex3_06 ${CMAKE_SOURCE_DIR}/Chapter03/Ex3_06/Ex3_06.cpp ${CMAKE_SOURCE_DIR}/Chapter03/Ex3_06/Box.cpp)

# Chapter 4: Map Containers
add_executable(Misc4 ${CMAKE_SOURCE_DIR}/Chapter04/misc.cpp)
add_executable(Ex4_01 ${CMAKE_SOURCE_DIR}/Chapter04/Ex4_01/Ex4_01.cpp)
add_executable(Ex4_02 ${CMAKE_SOURCE_DIR}/Chapter04/Ex4_02.cpp)
add_executable(Ex4_03 ${CMAKE_SOURCE_DIR}/Chapter04/Ex4_03/Ex4_03.cpp)
add_executable(Ex4_04 ${CMAKE_SOURCE_DIR}/Chapter04/Ex4_04.cpp)
add_executable(Ex4_05 ${CMAKE_SOURCE_DIR}/Chapter04/Ex4_05.cpp)
add_executable(Ex4_06 ${CMAKE_SOURCE_DIR}/Chapter04/Ex4_06.cpp)
add_executable(Ex4_07 ${CMAKE_SOURCE_DIR}/Chapter04/Ex4_07/Ex4_07.cpp)

# Chapter 5: Working with Sets
# add_executable(Ex5_01 ${CMAKE_SOURCE_DIR}/Chapter05/Ex5_01/Ex5_01.cpp)
# add_executable(Ex5_02 ${CMAKE_SOURCE_DIR}/Chapter05/Ex5_02/Ex5_02.cpp)
# add_executable(Ex5_03 ${CMAKE_SOURCE_DIR}/Chapter05/Ex5_03/Ex5_03.cpp)
add_executable(Ex5_04 ${CMAKE_SOURCE_DIR}/Chapter05/Ex5_04.cpp)
# add_executable(Ex5_05 ${CMAKE_SOURCE_DIR}/Chapter05/Ex5_05/Ex5_05.cpp)
# add_executable(Ex5_06 ${CMAKE_SOURCE_DIR}/Chapter05/Ex5_06/Ex5_06.cpp)
# add_executable(Ex5_07 ${CMAKE_SOURCE_DIR}/Chapter05/Ex5_07/Ex5_07.cpp)

# Chapter 6: Sorting, Merging, Searching, and Partitioning
# add_executable(Ex6_01 ${CMAKE_SOURCE_DIR}/Chapter06/Ex6_01/Ex6_01.cpp)
add_executable(Ex6_02 ${CMAKE_SOURCE_DIR}/Chapter06/Ex6_02/Ex6_02.cpp)
add_executable(Ex6_03 ${CMAKE_SOURCE_DIR}/Chapter06/Ex6_03.cpp)
add_executable(Ex6_04 ${CMAKE_SOURCE_DIR}/Chapter06/Ex6_04.cpp)
add_executable(Ex6_05 ${CMAKE_SOURCE_DIR}/Chapter06/Ex6_05.cpp)

# Chapter 7: More Algorithms
add_executable(Ex7_01 ${CMAKE_SOURCE_DIR}/Chapter07/Ex7_01.cpp)
add_executable(Ex7_02 ${CMAKE_SOURCE_DIR}/Chapter07/Ex7_02.cpp)
add_executable(Ex7_03 ${CMAKE_SOURCE_DIR}/Chapter07/Ex7_03.cpp)
add_executable(Ex7_04 ${CMAKE_SOURCE_DIR}/Chapter07/Ex7_04.cpp)
add_executable(Ex7_05 ${CMAKE_SOURCE_DIR}/Chapter07/Ex7_05.cpp)

# Chapter 8: Generating Random Numbers
add_executable(Ex8_01 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_01.cpp)
# add_executable(Ex8_02 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_02.cpp)
add_executable(Ex8_03 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_03.cpp)
add_executable(Ex8_04 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_04.cpp)
# add_executable(Ex8_05 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_05.cpp)
# add_executable(Ex8_06 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_06.cpp)
add_executable(Ex8_07 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_07/Ex8_07.cpp)
add_executable(Ex8_08 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_08.cpp)
add_executable(Ex8_09 ${CMAKE_SOURCE_DIR}/Chapter08/Ex8_09.cpp)

# Chapter 9: Stream Operations
add_executable(Ex9_01 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_01.cpp)
add_executable(Ex9_02 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_02.cpp)
add_executable(Ex9_03 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_03.cpp)
add_executable(Ex9_04 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_04.cpp)
add_executable(Ex9_05 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_05.cpp)
add_executable(Ex9_06 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_06.cpp)
add_executable(Ex9_07 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_07.cpp)
add_executable(Ex9_08 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_08.cpp)
add_executable(Ex9_09 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_09.cpp)
add_executable(Ex9_10 ${CMAKE_SOURCE_DIR}/Chapter09/Ex9_10.cpp)

# Chapter 10: Working with Numerical, Time, and Complex Data
add_executable(Ex10_01 ${CMAKE_SOURCE_DIR}/Chapter10/Ex10_01.cpp)
# add_executable(Ex10_02 ${CMAKE_SOURCE_DIR}/Chapter10/Ex10_02.cpp)
add_executable(Ex10_03 ${CMAKE_SOURCE_DIR}/Chapter10/Ex10_03/Ex10_03.cpp ${CMAKE_SOURCE_DIR}/Chapter10/Ex10_03/gaussian.cpp)
add_executable(Ex10_04 ${CMAKE_SOURCE_DIR}/Chapter10/Ex10_04.cpp)
add_executable(Ex10_05 ${CMAKE_SOURCE_DIR}/Chapter10/Ex10_05/Ex10_05.cpp ${CMAKE_SOURCE_DIR}/Chapter10/Ex10_05/gaussian.cpp)
add_executable(Ex10_06 ${CMAKE_SOURCE_DIR}/Chapter10/Ex10_06.cpp)

# target_compile_features(Chapter01 PUBLIC cxx_std_17)

add_custom_target(compile_commands ALL)

add_custom_command(
  TARGET compile_commands POST_BUILD
  COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
  COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}
  )
