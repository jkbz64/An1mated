cmake_minimum_required(VERSION 3.1)
project(An1mated CXX)

#Options
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build(Release or Debug)")
set(LIB_AN1MATED_BUILD_TYPE Shared CACHE STRING "Choose the type of libAn1mated build(Static OR Shared)")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Enable build of tests" ON)

#LIBRARY PACKAGES
#QT5
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

#Setup libAn1mated library
set(LIB_AN1MATED_INCLUDE_DIR "include/libAn1mated/")
set(LIB_AN1MATED_HDRS
	${LIB_AN1MATED_INCLUDE_DIR}/Animation.hpp
)

set(LIB_AN1MATED_SRCS_DIR "src/libAn1mated/")
set(LIB_AN1MATED_SRCS 
	${LIB_AN1MATED_SRCS_DIR}/Animation.hpp)
	
if (${LIB_AN1MATED_BUILD_TYPE} MATCHES "Static")
	add_library(libAn1mated STATIC ${LIB_AN1MATED_SRCS_DIR})
elseif (${LIB_AN1MATED_BUILD_TYPE} MATCHES "Shared")
	add_library(libAn1mated SHARED ${LIB_AN1MATED_SRCS_DIR})
else()
	message( FATAL_ERROR "Wrong libAn1mated build type")
endif()

set_target_properties(libAn1mated PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(libAn1mated PROPERTIES PREFIX "")

target_include_directories(libAn1mated PUBLIC
 ${LIB_AN1MATED_INCLUDE_DIR}
 ${Qt5Core_INCLUDE_DIRS}
)

#Setup An1mated
option(CMAKE_AUTOMOC "Enable automoc" ON)
option(CMAKE_AUTOUIC "Enable autouic" ON)
option(CMAKE_AUTORCC "Enable autouic" ON)

set(AN1MATED_INCLUDE_DIR "include/An1mated/")
set(AN1MATED_SRCS_DIR "src/An1mated/")

set(AN1MATED_HDRS
	${AN1MATED_INCLUDE_DIR}/mainwindow.hpp
	${AN1MATED_INCLUDE_DIR}/document.hpp

	)
set(AN1MATED_SRCS
	${AN1MATED_SRCS_DIR}/main.cpp
	${AN1MATED_SRCS_DIR}/mainwindow.cpp
	${AN1MATED_SRCS_DIR}/document.cpp
)
set(AN1MATED_UI
	${AN1MATED_SRCS_DIR}/mainwindow.ui
	)
set(AN1MATED_RES
	)

add_executable(An1mated 
	${AN1MATED_HDRS} 
	${AN1MATED_SRCS} 
	${AN1MATED_UI} 
	${AN1MATED_RES})

target_include_directories(An1mated PUBLIC
	${LIB_AN1MATED_INCLUDE_DIR}
	${AN1MATED_INCLUDE_DIR}
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS})

target_link_libraries(An1mated 
	libAn1mated 
	Qt5::Core 
	Qt5::Widgets)

#tests here

if(TESTS)

endif()


