project(server32)

add_executable(server32 server302.cpp main.cpp)

install(TARGETS server32 RUNTIME DESTINATION bin)
