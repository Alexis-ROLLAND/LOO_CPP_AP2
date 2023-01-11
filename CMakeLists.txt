cmake_minimum_required(VERSION 3.4)		# never set less 3.4 min version
project(SinusGenerator)

include_directories(include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE debug)


add_executable(Sinus src/sinus_main_test.cpp src/Sinus.cpp)




