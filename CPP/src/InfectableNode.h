//
// Created by mgooch on 3/30/15.
//

#ifndef RANDOMTEST_INFECTABLENODE_H
#define RANDOMTEST_INFECTABLENODE_H

#include <random>
#include <memory>
class InfectableNode {
private:
    bool vaccinated;
    bool infected;
    //*
    static std::random_device rd;
    static std::mt19937_64 gen;
    static std::unique_ptr<std::bernoulli_distribution> infection_randomizer_unvaccinated;
    static std::unique_ptr<std::bernoulli_distribution> infection_randomizer_vaccinated;
    //*/
public:
    InfectableNode();
    InfectableNode(bool _vaccinated);
    virtual ~InfectableNode();
    void infect();
    void vaccinate();
    bool is_vaccinated();
    bool is_infected();
    bool expose(std::bernoulli_distribution& boolGen);
    static void setImmunity(double vaccinated_immunity, double unvaccinated_immunity);
    static void setVaccinatedImmunity(double immunity);
    static void setUnvaccinatedImmunity(double immunity);
};


#endif //RANDOMTEST_INFECTABLENODE_H
