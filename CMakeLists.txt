cmake_minimum_required ( VERSION 3.1.0...3.27.0 )

project(
    simple-raytracer
    VERSION 1.0
    LANGUAGES CXX)

set ( CMAKE_CXX_STANDARD 11)
add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
add_compile_options(-Wmaybe-uninitialized) # Variable improperly initialized
add_compile_options(-Wunused-variable) # Variable is defined but unused

set(PROJECT_BINARY_DIR out/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})


add_executable(ppm_writer utils/ppm_writer.cpp)
