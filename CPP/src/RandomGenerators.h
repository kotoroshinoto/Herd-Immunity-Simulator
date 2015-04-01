//
// Created by mgooch on 3/31/15.
//

#ifndef HERDIMMUNITYSIMULATOR_RANDOMGENERATORS_H
#define HERDIMMUNITYSIMULATOR_RANDOMGENERATORS_H


#include <random>
#include <memory>

class HerdImmunityRandomGenerators {
private:
    std::random_device rd;
    //using all these independent generators is probably overkill, but i'm being safer than needed
    std::mt19937_64 gen_infection_randomizer_unvaccinated;
    std::mt19937_64 gen_infection_randomizer_vaccinated;
    std::mt19937_64 gen_vaccination_randomizer;
    std::mt19937_64 gen_node_randomizer;
    std::bernoulli_distribution infection_randomizer_unvaccinated;
    std::bernoulli_distribution infection_randomizer_vaccinated;
    std::bernoulli_distribution vaccination_randomizer;
    std::uniform_int_distribution<std::size_t> node_randomizer;
    double VaccImmune;
    double NatImmune;
    double VaccRate;
    std::size_t population;
    std::size_t Rnull;

public:
    HerdImmunityRandomGenerators(double _VaccImmune, double _NatImmune, double _VaccRate, std::size_t _population, std::size_t _Rnull);
    virtual ~HerdImmunityRandomGenerators();

     bool getRandomInfectResultVaccinated();
     bool getRandomInfectResultUnvaccinated();
     bool getRandomVaccineResult();
     std::size_t getRandomNode();
    double getVaccineImmunity();
    double getNaturalImmunity();
    double getVaccinationRate();
    std::size_t getPopulation();
    std::size_t getRnull();
};

extern HerdImmunityRandomGenerators * herd_rand;

#endif //HERDIMMUNITYSIMULATOR_RANDOMGENERATORS_H
