### Create Hyades Library ###
add_library(Hyades SHARED
            src/Application.cpp
            src/Logger.cpp
            src/Window.cpp)


set_target_properties(Hyades PROPERTIES VERSION ${PROJECT_VERSION})

# set include directories
target_include_directories(Hyades PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Hyades PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/spdlog/include)
target_include_directories(Hyades PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
target_link_libraries(Hyades glfw)

# precompile header
target_precompile_headers(Hyades PRIVATE src/HyadesPCH.hpp)

include(GNUInstallDirs)

install(TARGETS Hyades
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})