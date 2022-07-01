# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project (DataStructureDemo
  LANGUAGES CXX
  VERSION 1.0.0
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH $ENV{PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

# 将源代码添加到此项目的可执行文件。
qt_add_executable (DataStructureDemo WIN32
	"src/res/res.rc"
	"src/res/res.qrc"
	"src/FileIO.cpp"
	"src/DataStructure/LinkedList.cpp"
	"src/DataStructure/Array.cpp"
	"src/DataStructure/Stack.cpp"
	"src/DataStructure/Heap.cpp"
	"src/DataStructure/Tree.cpp"
	"src/DataStructure/UndiG.cpp"
	"src/DataStructure/DiG.cpp"
	"src/utils.cpp"
	"src/Widgets/newWidgets.hpp"
	"src/Widgets/ui_MainWindow.h"
	"src/Widgets/ui_changeUnitSizeDialog.h"
	"src/Widgets/ui_createObjectDialog.h"
	"src/Widgets/ui_inputDialog.h"
	"src/Widgets/ui_about.h"
	"src/gui.cpp"
	"src/main.cpp"
 )

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)


