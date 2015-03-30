project(HerdImmunitySimulator CXX)
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

add_executable(HerdImmunitySimulator src/main.cpp src/InfectableNode.cpp src/InfectableNode.h src/InfectablePopulation.cpp src/InfectablePopulation.h)
set_property(TARGET HerdImmunitySimulator PROPERTY CXX_STANDARD 11)
set_property(TARGET HerdImmunitySimulator PROPERTY CXX_STANDARD_REQUIRED ON)