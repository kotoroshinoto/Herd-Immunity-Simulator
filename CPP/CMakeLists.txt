project(HerdImmunitySimulator CXX)
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

INCLUDE (CheckIncludeFileCXX)


CHECK_INCLUDE_FILE_CXX("tclap/CmdLine.h" HAVE_TCLAP_H)

if(NOT "${HAVE_TCLAP_H}" MATCHES "1")
    message(FATAL_ERROR "did not find tclap")
endif()

add_executable(HerdImmunitySimulator src/main.cpp src/InfectableNode.cpp src/InfectableNode.h src/InfectablePopulation.cpp src/InfectablePopulation.h src/RandomGenerators.cpp src/RandomGenerators.h src/RangeConstraint.h)
set_property(TARGET HerdImmunitySimulator PROPERTY CXX_STANDARD 14)
set_property(TARGET HerdImmunitySimulator PROPERTY CXX_STANDARD_REQUIRED ON)
