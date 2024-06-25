cmake_minimum_required(VERSION 3.16)
project(PracticeSFML LANGUAGES CXX)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to build shared libraries (OFF for static linking)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Include FetchContent module to download dependencies
include(FetchContent)

# Declare and fetch the SFML library from GitHub
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# Define the main executable and add all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(main ${SOURCES})

# Link all SFML modules to the executable for static linking
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Set the C++ standard to C++17
target_compile_features(main PRIVATE cxx_std_17)

# Add the headers directory to the include path
target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/headers")

# Enable assumption of finite loops
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffinite-loops")

# Enable fast floating point math
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")

# Windows-specific command to copy the OpenAL DLL
#if (WIN32)
#    add_custom_command(
#        TARGET main
#        COMMENT "Copy OpenAL DLL"
#        PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy 
#                ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll 
#                $<TARGET_FILE_DIR:main>
#        VERBATIM
#    )
#endif()
