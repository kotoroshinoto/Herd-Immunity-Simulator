project(HerdImmunitySimulator CXX)
cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

INCLUDE (CheckIncludeFileCXX)

include_directories(AFTER ${PROJECT_SOURCE_DIR}/lib/tclap/include)
list(APPEND CMAKE_REQUIRED_INCLUDES ${PROJECT_SOURCE_DIR}/lib/tclap/include)
CHECK_INCLUDE_FILE_CXX("tclap/CmdLine.h" HAVE_TCLAP_H)

if(NOT "${HAVE_TCLAP_H}" MATCHES "1")
    message(FATAL_ERROR "did not find tclap")
endif()

add_executable(HerdImmunitySimulator src/main.cpp src/InfectableNode.cpp src/InfectableNode.h src/InfectablePopulation.cpp src/InfectablePopulation.h src/RandomGenerators.cpp src/RandomGenerators.h src/RangeConstraint.h)
set_property(TARGET HerdImmunitySimulator PROPERTY CXX_STANDARD 14)
set_property(TARGET HerdImmunitySimulator PROPERTY CXX_STANDARD_REQUIRED ON)
if(${STATIC_LINK})
    target_link_libraries(HerdImmunitySimulator -static)
endif()
