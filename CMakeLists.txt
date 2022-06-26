# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("DataStructureDemo")

# 将源代码添加到此项目的可执行文件。
add_executable (DataStructureDemo
	"src/FileIO.cpp"
	"src/Collection.cpp"
	"src/DataStructure/LinkedList.cpp"
	"src/main.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DataStructureDemo PROPERTY CXX_STANDARD 20)
endif()

