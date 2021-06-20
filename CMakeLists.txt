cmake_minimum_required(VERSION 3.13)
project(Breakout-SDL2 VERSION 0.1.0)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    if(${CMAKE_CXX_COMPILER_VERSION} STREQUAL "11.1.0")
        set(SWITCH true)
        message(STATUS "Is switch compiler")
    endif()
endif ()

if(WIN32)
    SET(SDL2_DIR libs/SDL2)
    find_package(SDL2 REQUIRED)
    set(SDL2_IMAGE_LIBRARY ${CMAKE_CURRENT_LIST_DIR}/libs/SDL2_image/lib/x64)
    set(SDL2_IMAGE_INCLUDE_DIRS libs/SDL2_image/include)
ENDIF()

if(UNIX)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
ENDIF()
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Breakout-SDL2 src/main.cpp src/render/SDLRender.cpp src/events/eventManager.cpp src/player/player.cpp src/resourceManager/assetsManager.cpp)


if(WIN32)
    target_link_libraries(Breakout-SDL2 ${SDL2_LIBRARY})
    target_link_libraries(Breakout-SDL2 ${SDL2_IMAGE_LIBRARY}/SDL2_image.lib)
    file(COPY ${SDL2_DIR}/lib/x64/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SDL2_IMAGE_LIBRARY}/SDL2_image.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SDL2_IMAGE_LIBRARY}/libjpeg-9.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SDL2_IMAGE_LIBRARY}/libpng16-16.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SDL2_IMAGE_LIBRARY}/zlib1.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${SDL2_IMAGE_LIBRARY}/libtiff-5.dll DESTINATION ${CMAKE_BINARY_DIR})
ENDIF()
if(UNIX)
    target_link_libraries(Game ${SDL2_LIBRARY})
    target_link_libraries(Game ${SDL2_IMAGE_LIBRARY})
ENDIF()


file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})