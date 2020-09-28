### Create Client Application executable ###
add_executable(HyadesClient
                src/ClientApplication.cpp)

# link Hyades library to executable
target_link_libraries(HyadesClient PUBLIC Hyades)

# add shader directory from Hyades library to client build directory
add_custom_command (
        TARGET HyadesClient POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Hyades/src/shaders $<TARGET_FILE_DIR:HyadesClient>/shaders
        COMMENT "Copying shaders" VERBATIM
)
