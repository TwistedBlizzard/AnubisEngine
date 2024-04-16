cmake_minimum_required(VERSION 3.17)

# Set the C++ Version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AnubisEngine
    VERSION 0.1
    LANGUAGES CXX)

option(BUILD_ANUBISENGINE_DEMO "Build demo for AnubisEngine" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${AnubisEngine_SOURCE_DIR}/lib>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${AnubisEngine_SOURCE_DIR}/lib>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${AnubisEngine_SOURCE_DIR}/bin>)

option(USE_VENDORED_SDL "Download SDL3 from GitHub" ON)

if(${USE_VENDORED_SDL})
    # Disable Shared Libs
    set(BUILD_SHARED_LIBS OFF)
    set(SDL_SHARED OFF CACHE BOOL "Disable Shared Libs")
    set(SDL_STATIC ON CACHE BOOL "Enable Static Libs")

    # Disable AVIF Support because it's currently broken
    set(SDL3IMAGE_AVIF OFF)

    # Enable FetchContent
    include(FetchContent)

    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG origin/main
        OVERRIDE_FIND_PACKAGE
    )

    # FetchContent_MakeAvailable(SDL3)

    FetchContent_Declare(
        SDL3_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG origin/main
        OVERRIDE_FIND_PACKAGE
    )

    set(SDL3IMAGE_INSTALL OFF)
    set(SDL3IMAGE_BUILD_SHARED_LIBS OFF)

    # FetchContent_MakeAvailable(SDL3_image)

endif()

find_package(SDL3)
find_package(SDL3_image)

# Collect our header files
file(GLOB AnubisEngine_HEADER_LIST CONFIGURE_DEPENDS ${AnubisEngine_SOURCE_DIR}/include/*.hpp)

# Set our source files
set(AnubisEngine_SOURCE_LIST
    src/BoxCollider.cpp
    src/CircleCollider.cpp
    src/Collider.cpp
    src/GameObject.cpp
    src/GameObjectFactory.cpp
    src/InputHandler.cpp
    src/Sprite.cpp
    src/SpriteFactory.cpp
    src/Timer.cpp
    src/Timing.cpp)

# Add our library
add_library(AnubisEngine ${AnubisEngine_SOURCE_LIST} ${AnubisEngine_HEADER_LIST})

# Set the include directory
target_include_directories(AnubisEngine PUBLIC include)

# Link SDL3 and SDL3_image to our engine
target_link_libraries(AnubisEngine PUBLIC SDL3::SDL3 SDL3_image::SDL3_image)

if (${BUILD_ANUBISENGINE_DEMO})
    # Collect the header files for the demo
    file(GLOB AnubisDemo_HEADER_LIST CONFIGURE_DEPENDS ${AnubisEngine_SOURCE_DIR}/app/*.hpp)

    # Set the source files for the demo
    set(AnubisDemo_SOURCE_LIST
        app/Enemy.cpp
        app/Engine.cpp
        app/Game.cpp
        app/main.cpp
        app/Player.cpp)

    # This is our only executable currently
    add_executable(AnubisDemo ${AnubisDemo_SOURCE_LIST} ${AnubisDemo_HEADER_LIST})
    target_link_libraries(AnubisDemo PRIVATE AnubisEngine)

    # Copy images to image folder
    file(GLOB IMAGE_FILE_LIST CONFIGURE_DEPENDS ${AnubisEngine_SOURCE_DIR}/res/img/*)
    foreach(IMAGE_FILE ${IMAGE_FILE_LIST})
        get_filename_component(FILENAME ${IMAGE_FILE} NAME)
        configure_file(${IMAGE_FILE} ${AnubisEngine_SOURCE_DIR}/bin/img/${FILENAME} COPYONLY)
    endforeach(IMAGE_FILE ${IMAGE_FILE_LIST})
endif()