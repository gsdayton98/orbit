set(CMAKE_CXX_STANDARD 23)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS} ../include)

add_executable (testvector3 testvector3.cpp)
target_link_libraries (testvector3 ${Boost_LIBRARIES} orbit)