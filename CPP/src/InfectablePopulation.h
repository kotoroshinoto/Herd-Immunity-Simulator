//
// Created by mgooch on 3/30/15.
//

#ifndef RANDOMTEST_INFECTABLEPOPULATION_H
#define RANDOMTEST_INFECTABLEPOPULATION_H

#include <random>
#include <memory>
#include <iostream>
#include <stack>
#include "InfectableNode.h"
#include <vector>

class InfectablePopulation {
private:
    std::unique_ptr<InfectableNode> pop;
    void initial_infection();
    void spread_infection();
public:
    InfectablePopulation();
    virtual ~InfectablePopulation();
    void eval();
    void runSimulation();
};


#endif //RANDOMTEST_INFECTABLEPOPULATION_H
