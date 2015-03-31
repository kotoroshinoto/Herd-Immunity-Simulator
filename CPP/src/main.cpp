#include "InfectableNode.h"
#include "InfectablePopulation.h"

HerdImmunityRandomGenerators * herd_rand;

int main() {
    herd_rand = new HerdImmunityRandomGenerators(0.9,0.1,0.9,1000);
    InfectablePopulation infpop;
    infpop.setPopulation(1000);
    infpop.setRnull(5);
    infpop.runSimulation();
    infpop.eval();
    return 0;
}