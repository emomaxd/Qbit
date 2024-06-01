project(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCES "${CMAKE_SOURCE_DIR}/Sandbox/src/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS "${CMAKE_SOURCE_DIR}/Sandbox/src/*.hpp")

add_executable(Sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})
target_link_libraries(Sandbox PRIVATE Engine)
target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Engine)
