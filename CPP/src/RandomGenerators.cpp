//
// Created by mgooch on 3/31/15.
//

#include "RandomGenerators.h"

HerdImmunityRandomGenerators::HerdImmunityRandomGenerators(double _VaccImmune, double _NatImmune,double _VaccRate, size_t _population):
        rd(),
        VaccImmune(_VaccImmune),
        NatImmune(_NatImmune),
        VaccRate(_VaccRate),
        population(_population),
        gen_infection_randomizer_unvaccinated(rd()),
        gen_infection_randomizer_vaccinated(rd()),
        gen_vaccination_randomizer(rd()),
        gen_node_randomizer(rd()),
        infection_randomizer_unvaccinated(NatImmune),
        infection_randomizer_vaccinated(VaccImmune),
        vaccination_randomizer(VaccRate),
        node_randomizer(0,(population -1)){

}
HerdImmunityRandomGenerators::~HerdImmunityRandomGenerators(){

}

bool HerdImmunityRandomGenerators::getRandomInfectResultVaccinated(){
    return infection_randomizer_vaccinated(gen_infection_randomizer_vaccinated);
}

bool HerdImmunityRandomGenerators::getRandomInfectResultUnvaccinated(){
    return infection_randomizer_unvaccinated(gen_infection_randomizer_unvaccinated);
}

bool HerdImmunityRandomGenerators::getRandomVaccineResult(){
    return vaccination_randomizer(gen_vaccination_randomizer);
}

std::size_t HerdImmunityRandomGenerators::getRandomNode(){
    return node_randomizer(gen_node_randomizer);
}


double HerdImmunityRandomGenerators::getVaccineImmunity(){
    return this->VaccImmune;
}

double HerdImmunityRandomGenerators::getNaturalImmunity(){
    return this->NatImmune;
}

double HerdImmunityRandomGenerators::getVaccinationRate(){
    return this->VaccRate;
}

std::size_t HerdImmunityRandomGenerators::getPopulation(){
    return this->getPopulation();
}
