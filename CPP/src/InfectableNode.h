//
// Created by mgooch on 3/30/15.
//

#ifndef RANDOMTEST_INFECTABLENODE_H
#define RANDOMTEST_INFECTABLENODE_H

#include "RandomGenerators.h"
#include <iostream>

class InfectableNode {
private:
    bool vaccinated;
    bool infected;

public:
    InfectableNode();
    virtual ~InfectableNode();
    void infect();
    void vaccinate();
    bool is_vaccinated();
    bool is_infected();
    bool expose();
};


#endif //RANDOMTEST_INFECTABLENODE_H
