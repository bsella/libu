cmake_minimum_required(VERSION 3.12)
project(libu)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -pedantic -Wextra")
set(CMAKE_FLAGS "--no-print-directory")

add_library(libu
	widget.cpp
	window.cpp
	text.cpp
	)
target_link_libraries(libu -lSDL2 -lSDL2_ttf)
target_include_directories(libu PUBLIC include)

##########################################################

add_executable(testu
       main.cpp
)
target_link_libraries(testu libu)
