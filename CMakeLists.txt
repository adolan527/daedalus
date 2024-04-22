cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(torqueCalculator C)


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
        "projectManagement/projectManagement.h"
        "../csvLib/csv.h"
        "../csvLib/csvUtils.h"
        "display/drawMain.h"

)

set(SOURCES
    "projectManagement/createProject.c"
    "objectManagement/calculations.c"
    "projectManagement/initProgram.c"
    "projectManagement/deleteProject.c"
    "projectManagement/openProject.c"
    "projectManagement/openProject.c"
        "projectManagement/closeProject.c"
    "../csvLib/csv.c"
    "../csvLib/csvUtils.c"
    "display/initDraw.c"
    "display/drawMain.c"
    "display/screens/titleScreen.c"
    "display/screens/settingsScreen.c"
    "display/screens/editObjectScreen.c"
        "display/screens/projectMainScreen.c"
    "display/screens/logoScreen.c"
    display/buttons.c
    display/screens/openProjectScreen.c
        objectManagement/objectList.c
        display/drawTextInRectangle.c
        display/drawObject.c
        main.h
        display/modelObject.c
        projectManagement/projectUtils.c
        projectManagement/dataIO.c
        display/textbox.c
        display/ObjectBoxGUI.c
        display/CustomMesh.c
        display/rlights.c
        display/screens/materialsScreen.c
        projectManagement/materialsList.c
        display/MaterialsGui.c
        display/ColorGui.c
)

# Our Project

add_executable(${PROJECT_NAME} main.c
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
