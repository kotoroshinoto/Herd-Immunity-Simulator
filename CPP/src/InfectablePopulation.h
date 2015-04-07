//
// Created by mgooch on 3/30/15.
//

#ifndef RANDOMTEST_INFECTABLEPOPULATION_H
#define RANDOMTEST_INFECTABLEPOPULATION_H

#include "RandomGenerators.h"
#include <iostream>
#include <stack>
#include "InfectableNode.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
class InfectablePopulation {
private:
    InfectableNode * pop;
    std::stack <int> infection_stack;
    void initial_infection();
    void spread_infection(size_t entry);
    void init_population();
    std::vector<std::size_t> getRandomSample(size_t current_node);
public:
    InfectablePopulation();
    virtual ~InfectablePopulation();
    void eval();
    void runSimulation();
};

#endif //RANDOMTEST_INFECTABLEPOPULATION_H