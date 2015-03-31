//
// Created by mgooch on 3/30/15.
//

#include "InfectablePopulation.h"
#include <sstream>
InfectablePopulation::InfectablePopulation(){

}

InfectablePopulation::~InfectablePopulation(){

}

void InfectablePopulation::eval(){
    size_t unVac = 0;
    size_t vac = 0;
    size_t iVac = 0;
    size_t iUnVac = 0;
    size_t hVac = 0;
    size_t hUnVac = 0;
    double herd = 1.0 - (1.0 / ((double)Rnull));
    for(int i =0 ; i < this->population; i++){
        if(this->pop[i].is_vaccinated()){
            vac++;
            if(this->pop[i].is_infected()){
                iVac++;
            } else {
                hVac++;
            }
        }else{
            unVac++;
            if(this->pop[i].is_infected()){
                iUnVac++;
            } else {
                hUnVac++;
            }
        }
    }

    double immune = (((double)vac) * herd_rand->getVaccineImmunity() + ((double)unVac) * herd_rand->getNaturalImmunity()) / ((double)population);
    bool isHerd = immune >= herd;

    //divbyzero error fixes
    double hVacP=0;
    double iVacP=0;
    double hUnVacP=0;
    double iUnVacP=0;

    if (vac != 0){
        hVacP=std::round((((double)hVac)*100.0)/((double)vac)*10)/10;
        iVacP=std::round((((double)iVac)*100.0)/((double)vac)*10)/10;
    }

    if(unVac != 0 ){
        hUnVacP=std::round((((double)hUnVac)*100.0)/((double)unVac)*10.0)/10.0;
        iUnVacP=std::round((((double)iUnVac)*100.0)/((double)unVac)*10.0)/10.0;
    }
    std::cout<<"Vaccinated: "<<vac<<" ("<< std::round(((double)vac) * 100.0 / ((double)population)*10.0)/10.0<<"%)<<std::endl";
    std::cout<<"Unvaccinated: "<<unVac<<" ("<< std::round(((double)unVac) * 100.0 / ((double)population)*10.0)/10.0<<"%)<<std::endl";
    std::cout<<"Healthy Vaccinated: "<<hVac<<" ("<<hVacP<<"% of vaccinated"<<std::endl;
    std::cout<<"Healthy Unvaccinated: "<<hUnVac<<" ("<<hUnVacP<<"% of unvaccinated"<<std::endl;
    std::cout<<"Infected Vaccinated: "<<iVac<<" ("<<iVacP<<"% of vaccinated"<<std::endl;
    std::cout<<"Infected Unvaccinated: "<<iUnVac<<" ("<<iUnVacP<<"% of unvaccinated"<<std::endl;
    std::cout<<"Herd Immunity: "<<isHerd<<" ("<<round(herd*100.0*10.0)/10.0<<"% needed for Herd Immunity; we have "<<round(immune*100.0*10.0)/10.0<<"%)"<<std::endl;
}

void InfectablePopulation::runSimulation(){
    this->init_population();
    this->initial_infection();
    {
        size_t i = 0;
        while (!this->infection_stack.empty()) {
            i = this->infection_stack.top();
            this->infection_stack.pop();
            this->spread_infection(i);
        }
    }
}

void InfectablePopulation::initial_infection(){
    std::cout<<"TESTDERP1"<<std::endl;
    std::size_t patient_zero=herd_rand->getRandomNode();
    std::cout<<"TESTDERP2"<<std::endl;
    this->pop[patient_zero].infect();
    std::cout<<"TESTDERP3"<<std::endl;
    this->infection_stack.push(patient_zero);
    std::cout<<"TESTDERP4"<<std::endl;
//    std::cout<<"First infected node: "<<patient_zero<<std::endl;
}

void InfectablePopulation::spread_infection(size_t entry){
    std::vector<std::size_t > rNodes = getRandomSample(entry);
//    std::cout<<"spreading from infected node: "<<entry<<std::endl;
    for(size_t i = 0; i < rNodes.size();i++){
        size_t index=rNodes[i];
        if( ! this->pop[index].is_infected()){
            this->pop[index].expose();
            if(this->pop[index].is_infected()){
                this->infection_stack.push(index);
//                std::cout<<index<<" became infected"<<std::endl;
            }
        }
    }
}

void InfectablePopulation::init_population(){
    this->pop.reset(new InfectableNode[this->population]);
}

void InfectablePopulation::setPopulation(std::size_t _population){
    this->population=_population;
}

void InfectablePopulation::setRnull(unsigned int _Rnull){this->Rnull=_Rnull;}

std::vector<std::size_t> InfectablePopulation::getRandomSample(size_t current_node){
    std::vector<std::size_t > sample;
    std::size_t tmp;
    while(sample.size() < this->Rnull){
        tmp=herd_rand->getRandomNode();
        if(tmp == current_node) {
            //std::cout << "discarding random node: " << tmp << " it is the current node" << std::endl;
            continue;
        }
        if(std::find(sample.begin(),sample.end(),tmp) == sample.end()){
            sample.push_back(tmp);
        } else {
            std::stringstream ss;
            for(int i=0;i<sample.size();i++){
                ss<<sample[i];
                if(i != sample.size() -1){
                    ss<<", ";
                }
            }
            //std::cout<<"discarding random node: "<<tmp<<" it is already in the random sample["<<sample.size()<<"]: "<< ss.str() <<std::endl;
        }
    }
    return sample;
}