cmake_minimum_required(VERSION 3.1)
project(An1mated CXX)

# Options
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build(Release or Debug)")
set(LIB_AN1MATED_BUILD_TYPE Shared CACHE STRING "Choose the type of libAn1mated build(Static OR Shared)")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")


# Enable some flags when not using msvc compiler
if (NOT MSVC)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -pedantic -pedantic-errors -g")
	elseif (CMAKE_BUILD_TYPE MATCHES "Release")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
	endif()
endif()


# Enforce C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Enable automoc / autoic
option(CMAKE_AUTOMOC "Enable automoc" ON)
option(CMAKE_AUTOUIC "Enable autouic" ON)
# Enable tests?
option(TESTS "Enable build of tests" ON)
# Enable defaul writers and readers?
option(DEFAULTS "Copy default writers and readers" ON)

# Detect Qt5 package with Core and Widgets components
find_package(Qt5 REQUIRED Core Widgets OPTIONAL_COMPONENTS Test)
find_package(Lua53 REQUIRED)

set(SOL2_ROOT ${CMAKE_SOURCE_DIR}/lib/sol2)

## Setup libAn1mated library
# Get include dir and headers
set(LIB_AN1MATED_INCLUDE_DIR "include/libAn1mated/")
file(GLOB LIB_AN1MATED_HDRS include/libAn1mated/*.hpp)
# Get src dir and sources
set(LIB_AN1MATED_SRCS_DIR "src/libAn1mated/")
file(GLOB LIB_AN1MATED_SRCS src/libAn1mated/*.cpp)

# Detect if build type of libAn1mated is shared or static
if (${LIB_AN1MATED_BUILD_TYPE} MATCHES "Static")
	add_library(libAn1mated STATIC ${LIB_AN1MATED_SRCS} ${LIB_AN1MATED_HDRS})
elseif (${LIB_AN1MATED_BUILD_TYPE} MATCHES "Shared")
	add_library(libAn1mated SHARED ${LIB_AN1MATED_SRCS} ${LIB_AN1MATED_HDRS})
else()
	message( FATAL_ERROR "Wrong libAn1mated build type")
endif()

# Fix cmake error not detecting libAn1mated as C++ project
set_target_properties(libAn1mated PROPERTIES LINKER_LANGUAGE CXX)
# Delete lib prefix for convenience
set_target_properties(libAn1mated PROPERTIES PREFIX "")

target_include_directories(libAn1mated PUBLIC
 ${LIB_AN1MATED_INCLUDE_DIR}
 ${Qt5Core_INCLUDE_DIRS}
 ${LUA53_INCLUDE_DIR}
 ${SOL2_ROOT}
)

target_link_libraries(libAn1mated
	Qt5::Core
	${LUA53_LIBRARIES}
)

# Get include dir and headers
set(AN1MATED_INCLUDE_DIR "include/An1mated/")
file(GLOB AN1MATED_HDRS include/An1mated/*.hpp)

# Get source dir and sources
set(AN1MATED_SRCS_DIR "src/An1mated/")
file(GLOB AN1MATED_SRCS src/An1mated/*.cpp)

# Get ui files
file(GLOB AN1MATED_UIS src/An1mated/*.ui)

add_executable(An1mated 
	${AN1MATED_HDRS}
	${AN1MATED_SRCS} 
	${AN1MATED_UIS})

target_include_directories(An1mated PUBLIC
	${LIB_AN1MATED_INCLUDE_DIR}
	${AN1MATED_INCLUDE_DIR}
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${SOL2_ROOT}
	${LUA53_INCLUDE_DIR}
)

target_link_libraries(An1mated 
	libAn1mated 
	Qt5::Core 
	Qt5::Widgets
	${LUA53_LIBRARIES}
)

### Unit testing
if (TESTS)
	enable_testing()
	# Take all test files
	file(GLOB TEST_SRC tests/test*.cpp)
	# Organise them in a group and iterate them individually
	source_group(tests FILES ${TEST_SRC})
	foreach(test_source_file ${TEST_SRC})
		# Get filename without extension
		get_filename_component(test_name ${test_source_file} NAME_WE)
		# Create test
		add_executable(${test_name} ${test_source_file})
		target_include_directories(${test_name} PUBLIC
			${LIB_AN1MATED_INCLUDE_DIR}
			${QT5Core_INCLUDE_DIRS}
			${QT5Test_INCLUDE_DIRS}
			${SOL2_ROOT}
			${LUA53_INCLUDE_DIR}
		)
		target_link_libraries(${test_name}
			libAn1mated
			Qt5::Test
			Qt5::Core
			${LUA53_LIBRARIES})
		# Add test to cmmake's CTest
		add_test(${test_name} ${test_name})
	endforeach()
endif()


# Copy default writers / readers into binary dir
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/readers)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/writers)

if(DEFAULTS)
	file(GLOB READERS_SRC default/readers/*.lua)
	source_group(READERS FILES ${READERS_SRC})
	foreach(READER ${READERS_SRC})
		get_filename_component(READER_NAME ${READER} NAME)
		configure_file(default/readers/${READER_NAME} ${CMAKE_BINARY_DIR}/readers/${READER_NAME} @ONLY)
	endforeach()

	file(GLOB WRITERS_SRC default/writers/*.lua)
	source_group(WRITERS FILES ${WRITERS_SRC})
	foreach(WRITER ${WRITERS_SRC})
		get_filename_component(WRITER_NAME ${WRITER} NAME)
		configure_file(default/writers/${WRITER_NAME} ${CMAKE_BINARY_DIR}/writers/${WRITER_NAME} @ONLY)
	endforeach()
endif()
