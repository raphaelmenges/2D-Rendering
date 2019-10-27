cmake_minimum_required(VERSION 2.8.10)

# TODO
# MESSAGES
# clang support

####### GENERAL #######

PROJECT(Project)
set(APPNAME Game)

# Activate C++11 in GCC
IF(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

####### INCLUDING #######

include_directories(.)

file(GLOB LOCAL_SOURCES
    "*.cpp"
    "*.cc"
	"*.c")
	
file(GLOB LOCAL_HEADERS
    "*.h")
    
file(GLOB_RECURSE ENGINE_SOURCES
    "Engine/*.cpp"
    "Engine/*.cc"
	"Engine/*.c")
	
file(GLOB_RECURSE ENGINE_HEADERS
    "Engine/*.h")

set(SOURCES
    ${LOCAL_SOURCES}
    ${ENGINE_SOURCES}
    ${SPACE_GAME_SOURCES})

set(HEADERS
    ${LOCAL_HEADERS}
    ${ENGINE_HEADERS}
    ${SPACE_GAME_HEADERS})

# Filtering for Visual Studio
IF(MSVC)

	set(ALL_FILES
		${SOURCES}
		${HEADERS})
		
	# http://stackoverflow.com/questions/9701387/cmake-source-group-multiple-files
	foreach(f ${ALL_FILES})
		# Get the path of the file relative to ${CMAKE_CURRENT_SOURCE_DIR},
		# then alter it (not compulsory)
		file(RELATIVE_PATH SRCGR "${CMAKE_CURRENT_SOURCE_DIR}" ${f})
		set(SRCGR "${APPNAME}/${SRCGR}")

		# Extract the folder, ie remove the filename part
		string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

		# Source_group expects \\ (double antislash), not / (slash)
		string(REPLACE / \\ SRCGR ${SRCGR})
		source_group("${SRCGR}" FILES ${f})
	endforeach()
	
ENDIF(MSVC)

####### DEPENDENCIES #######

IF(WIN32)

	# GLFW 3
	set(GLFW_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Dependencies/Windows/glfw")
	include_directories("${GLFW_DIRECTORY}/include")
	
	IF(MSVC10)
		set(GLFW_LIBRARIES_DIRECTORY "${GLFW_DIRECTORY}/lib-vc2012")
	ELSEIF(MSVC11)
		set(GLFW_LIBRARIES_DIRECTORY "${GLFW_DIRECTORY}/lib-vc2013")
	ELSE()
		set(GLFW_LIBRARIES_DIRECTORY "${GLFW_DIRECTORY}/lib-vc2015")
	ENDIF()
	
	find_library(GLFW_LIBRARIES
		NAMES glfw glfw3
		HINTS "${GLFW_LIBRARIES_DIRECTORY}")
		
	set(GLFW_BINARIES_DIRECTORY "${GLFW_LIBRARIES_DIRECTORY}")

	# OpenGL 3.3
	# ${OPENGL_LIBRARIES}
	# ${OPENGL_INCLUDE_DIR}
	FIND_PACKAGE(OpenGL REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIR})
	
ELSE(WIN32)

	# GLFW 3
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	include_directories(${GLFW_INCLUDE_DIRS})

	# OpenGL 3.3
	# ${OPENGL_LIBRARIES}
	# ${OPENGL_INCLUDE_DIR}
	find_package(OpenGL REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIR})

ENDIF(WIN32)

####### ADDING #######

add_executable(${APPNAME} ${SOURCES} ${HEADERS})

####### LINKING #######

target_link_libraries(${APPNAME} ${GLFW_LIBRARIES})
target_link_libraries(${APPNAME} ${OPENGL_LIBRARIES})

IF(WIN32)

    # Copy dlls
	add_custom_command(TARGET ${APPNAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${GLFW_BINARIES_DIRECTORY}/glfw3.dll"
		"${PROJECT_BINARY_DIR}/glfw3.dll")
		
ENDIF(WIN32)

####### BUILDING #######

# Copy resources to build directory
add_custom_command(TARGET ${APPNAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Engine/Resources Engine/Resources)

# Copy assets to build directory
add_custom_command(TARGET ${APPNAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets Assets)
