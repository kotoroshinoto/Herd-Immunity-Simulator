//
// Created by mgooch on 3/30/15.
//

#include "InfectableNode.h"

InfectableNode::InfectableNode(): vaccinated(herd_rand->getRandomVaccineResult()), infected(false){}

InfectableNode::~InfectableNode(){

}

void InfectableNode::infect(){
    this->infected = true;
}

void InfectableNode::vaccinate(){
    this->vaccinated = true;
}

bool InfectableNode::is_vaccinated(){
    return this->vaccinated;
}

bool InfectableNode::is_infected(){
    return this->infected;
}

bool InfectableNode::expose(){
    if( this->infected ) {
        return false;
    } else {
        if (this->vaccinated) {
            this->infected = (herd_rand->getRandomInfectResultVaccinated());
        } else {
            this->infected = (herd_rand->getRandomInfectResultUnvaccinated());
        }
        return this->infected;
    }
}