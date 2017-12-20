cmake_minimum_required(VERSION 3.5)
project(cal_white)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_CURRENT_INCLUDE ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
set(Qt_lib Qt5::Widgets Qt5::Core Qt5::Gui)

#opencv
find_package(OpenCV REQUIRED)

#halcon
set(Halcon_ROOT 3rdparty/halcon12)
include_directories(${Halcon_ROOT}/include)
include_directories(${Halcon_ROOT}/include/halconcpp/)
link_directories(${Halcon_ROOT}/lib/x64-win64/)
set(Halcon_LIBS  halconcpp)

file(GLOB_RECURSE SRC src/*.cc)
file(GLOB_RECURSE HDR src/*.h)

add_executable(cal_white WIN32 src/cal_white.rc ${SRC} ${HDR})

target_link_libraries(cal_white ${OpenCV_LIBS})
target_link_libraries(cal_white ${Halcon_LIBS})
target_link_libraries(cal_white ${Qt_lib})