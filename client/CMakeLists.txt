### Create Client Application executable ###
add_executable(HyadesClient
                src/ClientApplication.cpp)

# link Hyades library to executable
target_link_libraries(HyadesClient PUBLIC Hyades)
