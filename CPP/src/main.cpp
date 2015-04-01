#include "InfectableNode.h"
#include "InfectablePopulation.h"

HerdImmunityRandomGenerators * herd_rand;

int main() {
    herd_rand = new HerdImmunityRandomGenerators(0.9,0.1,0.9,1000,5);
    InfectablePopulation infpop;
    infpop.runSimulation();
    infpop.eval();
    return 0;
}