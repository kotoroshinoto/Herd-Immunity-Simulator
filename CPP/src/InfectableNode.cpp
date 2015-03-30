//
// Created by mgooch on 3/30/15.
//

#include "InfectableNode.h"
//*
std::random_device InfectableNode::rd;
std::mt19937_64  InfectableNode::gen(rd());
std::unique_ptr<std::bernoulli_distribution> InfectableNode::infection_randomizer_unvaccinated;
std::unique_ptr<std::bernoulli_distribution> InfectableNode::infection_randomizer_vaccinated;
//*/
void InfectableNode::setVaccinatedImmunity(double immunity){
    InfectableNode::infection_randomizer_vaccinated.reset(new std::bernoulli_distribution(1.0-immunity));
}

void InfectableNode::setUnvaccinatedImmunity(double immunity){
    InfectableNode::infection_randomizer_unvaccinated.reset(new std::bernoulli_distribution(1.0-immunity));
}

void InfectableNode::setImmunity(double vaccinated_immunity, double unvaccinated_immunity){
    InfectableNode::setUnvaccinatedImmunity(unvaccinated_immunity);
    InfectableNode::setVaccinatedImmunity(vaccinated_immunity);
}

InfectableNode::InfectableNode(): vaccinated(false), infected(false){}

InfectableNode::InfectableNode(bool _vaccinated) : vaccinated(_vaccinated), infected(false){}

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

bool InfectableNode::expose(std::bernoulli_distribution& boolGen){
    if( this->infected ) {
        return false;
    } else {
        if (this->vaccinated) {
            this->infected = (InfectableNode::infection_randomizer_vaccinated.operator*()).operator()(InfectableNode::gen);
        } else {
            this->infected = (InfectableNode::infection_randomizer_unvaccinated.operator*()).operator()(InfectableNode::gen);
        }
        return this->infected;
    }
}