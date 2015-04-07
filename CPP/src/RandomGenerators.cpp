//
// Created by mgooch on 3/31/15.
//

#include "RandomGenerators.h"

HerdImmunityRandomGenerators::HerdImmunityRandomGenerators(double _VaccImmune, double _NatImmune, double _VaccRate, std::size_t _population, std::size_t _Rnull,double _Rnull_std_dev):
        rd(),
        VaccImmune(_VaccImmune),
        NatImmune(_NatImmune),
        VaccRate(_VaccRate),
        population(_population),
        Rnull(_Rnull),
        Rnull_std_dev(_Rnull_std_dev),
        _gen(rd()),
        infection_randomizer_unvaccinated(1-_NatImmune),
        infection_randomizer_vaccinated(1-_VaccImmune),
        vaccination_randomizer(_VaccRate),
        rnull_randomizer(_Rnull,_Rnull_std_dev),
        node_randomizer(0,(_population - 1)){

}

HerdImmunityRandomGenerators::~HerdImmunityRandomGenerators(){

}

bool HerdImmunityRandomGenerators::getRandomInfectResultVaccinated(){
    return infection_randomizer_vaccinated(_gen);
}

bool HerdImmunityRandomGenerators::getRandomInfectResultUnvaccinated(){
    return infection_randomizer_unvaccinated(_gen);
}

bool HerdImmunityRandomGenerators::getRandomVaccineResult(){
    return vaccination_randomizer(_gen);
}

std::size_t HerdImmunityRandomGenerators::getRandomNode(){
    return node_randomizer(_gen);
}

std::size_t HerdImmunityRandomGenerators::getRandomRnull(){
    double randval=-1.0;
    while(randval < 0){
        randval=rnull_randomizer(_gen);
    }
    return (std::size_t)(std::round(randval));
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
    return this->population;
}
std::size_t HerdImmunityRandomGenerators::getRnull(){
    return this->Rnull;
}

double HerdImmunityRandomGenerators::getRnullStdDev(){
    return this->Rnull_std_dev;
}