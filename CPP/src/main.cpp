#include "InfectableNode.h"
#include "InfectablePopulation.h"

#include <tclap/CmdLine.h>

#include "RangeConstraint.h"
#include <limits>

typedef RangeConstraint<double> RangeConstraintDouble;
typedef RangeConstraint<std::size_t> RangeConstraintSizeT;

HerdImmunityRandomGenerators * herd_rand;
void parseArgs(int argc, const char ** argv){

    std::numeric_limits<std::size_t > size_t_limits;
    std::numeric_limits<double> double_limits;
    TCLAP::CmdLine cmd("",' ',"0.1");
    RangeConstraintSizeT rnullConstraint(1,false);
    RangeConstraintSizeT popConstraint(2,false);
    RangeConstraintDouble probabilityConstraint(0.0,1.0);
    RangeConstraintDouble rnullStdDevConstraint(0.0,(double)size_t_limits.max());

    TCLAP::ValueArg<std::size_t> pop_arg("p","population","set the size of the population",false,1000,&popConstraint,cmd);
    TCLAP::ValueArg<std::size_t> rnull_arg("r","Rnull","The mean amount of people an infected person can infect",false,5,&rnullConstraint,cmd);
    TCLAP::ValueArg<double> vaccrate_arg("V","vaccRate","individual probability that any given node will be vaccinated",false,0.9,&probabilityConstraint,cmd);
    TCLAP::ValueArg<double> vaccimmune_arg("v","vacImmunity","immunity conferred by vaccination (chance to resist infection)",false,0.9,&probabilityConstraint,cmd);
    TCLAP::ValueArg<double> natimmune_arg("n","natImmunity","(chance of an exposed unvaccinated person of resisting infection)",false,0.1,&probabilityConstraint,cmd);
    TCLAP::ValueArg<double> rnull_std_dev_arg("R","Rnull_std_dev","standard deviation of Rnull",false,0.5,&rnullStdDevConstraint,cmd);
    cmd.parse(argc,argv);
    herd_rand = new HerdImmunityRandomGenerators(vaccimmune_arg.getValue(),natimmune_arg.getValue(),vaccrate_arg.getValue(),pop_arg.getValue(),rnull_arg.getValue(),rnull_std_dev_arg.getValue());
}

int main(int argc, const char ** argv) {
    parseArgs(argc,argv);
    InfectablePopulation infpop;
    infpop.runSimulation();
    infpop.eval();
    return 0;
}