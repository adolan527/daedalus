cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
#project(torqueCalculator C)
project(daedalus C)


# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

set(HEADERS
        "src/projectManagement/projectManagement.h"
        "src/display/drawMain.h"

)

set(SOURCES
    "src/projectManagement/createProject.c"
    "src/objectManagement/calculations.c"
    "src/projectManagement/initProgram.c"
    "src/projectManagement/deleteProject.c"
    "src/projectManagement/openProject.c"
    "src/projectManagement/openProject.c"
        "src/projectManagement/closeProject.c"
    "src/display/initDraw.c"
    "src/display/drawMain.c"
    "src/display/screens/titleScreen.c"
    "src/display/screens/settingsScreen.c"
    "src/display/screens/editObjectScreen.c"
        "src/display/screens/projectMainScreen.c"
    "src/display/screens/logoScreen.c"
        src/display/buttons.c
        src/display/screens/openProjectScreen.c
        src/objectManagement/objectList.c
        src/display/drawTextInRectangle.c
        src/display/drawObject.c
        src/main.h
        src/display/modelObject.c
        src/projectManagement/projectUtils.c
        src/projectManagement/dataIO.c
        src/display/textbox.c
        src/display/ObjectBoxGUI.c
        src/display/CustomMesh.c
        src/display/rlights.c
        src/display/screens/materialsScreen.c
        src/projectManagement/materialsList.c
        src/display/MaterialsGui.c
        src/display/ColorGui.c
)

# Our Project

add_executable(${PROJECT_NAME} src/main.c
        ${HEADERS}
        ${SOURCES}

)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)


# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
