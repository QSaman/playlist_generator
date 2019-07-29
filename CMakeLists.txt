set(CMAKE_MINIMUM_VERSION 3.1)
cmake_minimum_required(VERSION ${CMAKE_MINIMUM_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(InitHunter)

project(playlist_generator)

include(ucm)
include(DefaultOptions)

hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED system filesystem)

include(DownloadCxxopts)
include_directories(${CXXOPTS_INCLUDE_DIR})


#The following variable requires CMake 3.1
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)

add_executable(embed_mime_types resource/embed_mime_types.cpp)
add_custom_command(
	OUTPUT mime_types.cpp
	COMMAND embed_mime_types ${CMAKE_SOURCE_DIR}/resource/mime.types mime_types.cpp
	DEPENDS ${CMAKE_SOURCE_DIR}/resource/mime.types)

ucm_add_dirs(src TO SRC_LIST)
set(SRC_LIST ${SRC_LIST} mime_types.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})
add_dependencies(${PROJECT_NAME} external_cxxopts)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::system Boost::filesystem)

