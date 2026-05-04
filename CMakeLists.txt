cmake_minimum_required(VERSION 3.10)

# 1. Name your project
project(train-game VERSION 1.0 LANGUAGES CXX)

# 2. Modern C++ standards are best for game dev
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Find the SDL2 package
# On Linux: sudo apt install libsdl2-dev
# On Mac: brew install sdl2
find_package(SDL2 REQUIRED)

# 4. Include directories (where your headers are)
include_directories(${SDL2_INCLUDE_DIRS})

# 5. Define your executable and source files
# I'm assuming your main code is in src/main.cpp
add_executable(${PROJECT_NAME} src/main.cpp)

# 6. Link the SDL2 libraries to your game
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

# 7. ASSET MANAGEMENT (Optional but helpful)
# This creates a symbolic link or copies your 'assets' folder to the build directory
# so your game can find its train sprites when you run it from the IDE.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")
endif()

# 8. WINDOWS SPECIFIC: Copy SDL2.dll to the executable folder
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()