set(CMAKE_CXX_STANDARD 23)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS} ../include)

add_executable (test-vector3 test-vector3.cpp test-matrix3x3.cpp test-orbit.cpp )
target_link_libraries (test-vector3 ${Boost_LIBRARIES} orbit)