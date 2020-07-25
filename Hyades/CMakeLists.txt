### Create Hyades Library ###
add_library(Hyades SHARED
            src/Application.cpp)


set_target_properties(Hyades PROPERTIES VERSION ${PROJECT_VERSION})

# set include directories
target_include_directories(Hyades PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


include(GNUInstallDirs)

install(TARGETS Hyades
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})