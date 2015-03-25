#!/usr/bin/env python3
#    Herd Immunity Simulator
#    Copyright 2015 Shane D. Killian
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

# User can set these values:

#function to provide limits to vaccination input values
def restricted_vaccination(float_input):
    x = float(float_input)
    if x < 0.0 or x > 1.0:
        raise argparse.ArgumentTypeError("%r not within range (0.0, 1.0)" % x)
    if x == 0.0 or x == 1.0:
        raise argparse.ArgumentTypeError("0 or 1 are not acceptable inputs for vaccination rate")
    return x
#function to provide limits to immunity input values
def restricted_immunity(float_input):
    x = float(float_input)
    if x < 0.0 or x > 1.0:
        raise argparse.ArgumentTypeError("%r not in range (0.0, 1.0)" % x)
    return x
#function to provide limits to population input values
def restricted_population(int_input):
    x=int(int_input)
    if x <= 0:
        raise argparse.ArgumentTypeError("must be greater than 0")
    return x
#function to provide limits to Rnull input values
def restricted_rnull(int_input):
    x=int(int_input)
    if x <= 0:
        raise argparse.ArgumentTypeError("must be greater than 0")
    return x
import argparse

parser = argparse.ArgumentParser(description='simulate spread of infection in a population')

parser.add_argument('-p', '--population', type=restricted_population, dest='population', default=[1000], nargs=1,
                    help='set the size of the population')
parser.add_argument('-r','--Rnull', type=restricted_rnull, dest='Rnull', default=[5], nargs=1,
                    help='The amount of people an infected person can infect')
parser.add_argument('-n','--natImmunity', type=restricted_immunity, dest='natImmunity', default=[0.1], nargs=1,
                    help='natural immunity of the population to the disease' +
                         '(chance of an exposed unvaccinated person of resisting infection)')
parser.add_argument('-v','--vacImmunity', type=restricted_immunity, dest='vacImmunity', default=[0.9], nargs=1,
                    help='immunity conferred by vaccination (chance to resist infection)')
parser.add_argument('-V','--vaccRate', type=restricted_vaccination, dest='vaccinated', default=[0.9], nargs=1,
                    help='percentage of the population that has been vaccinated')
parser.add_argument('--debug', dest='debug_flag', default=False, action='store_true',
                    help='print additional debug output')
args = parser.parse_args()

#set variable values from argparser
population = args.population[0]
Rnull = args.Rnull[0]
natImmunity = args.natImmunity[0]
vacImmunity = args.vacImmunity[0]
vaccinated = args.vaccinated[0]

if args.debug_flag:
    print("\n\npopulation value: %d" % population)
    print("Rnull value: %d" % Rnull)
    print("natImmunity value: %f" % natImmunity)
    print("vacImmunity value: %f" % vacImmunity)
    print("vaccinated value: %f\n\n" % vaccinated)
# End user-set values

import random,sys

sys.setrecursionlimit(population*Rnull+25)  # We're going to be doing a LOT of recursion!

class InfectableNode:
    def __init__(self):
        self.vaccinated = False
        self.infected = False
    def attempt_infection(self):
        r = random.random()
        if self.vaccinated:
            self.infected = (r > vacImmunity)  # infection attempt using immunity due to vaccine protection
        else:
            self.infected = (r > natImmunity)  # infection attempt using natural immunity

class InfectablePopulation:
    def __init__(self):
        self.nodes = []
        self.unresolved_infections = []
        for i in range(population):
            r = random.random()
            new_node = InfectableNode()
            new_node.vaccinated = (r <= vaccinated)
            self.nodes.append(new_node)

    def eval(self):
        unVac = 0
        vac = 0
        iVac = 0
        iUnVac = 0
        hVac = 0
        hUnVac = 0
        herd = 1 - (1 / Rnull)

        for i in range(0, population):
            current_node = pop.nodes[i]
            if current_node.vaccinated:
                vac += 1
                if current_node.infected:
                    iVac += 1
                else:
                    hVac += 1
            else:
                unVac += 1
                if current_node.infected:
                    iUnVac += 1
                else:
                    hUnVac += 1
        immune = (vac*vacImmunity + unVac*natImmunity)/population
        isHerd = immune >= herd
        print("Vaccinated: " + str(vac) + " (" + str(round(vac*100/population, 1)) + "%)")
        print("Unvaccinated: " + str(unVac) + " (" + str(round(unVac*100/population, 1)) + "%)")
        print("Healthy vaccinated: " + str(hVac) + " (" + str(round(hVac*100/vac, 1)) + "% of vaccinated)")
        print("Healthy unvaccinated: " + str(hUnVac) + " (" + str(round(hUnVac*100/unVac, 1)) + "% of unvaccinated)")
        print("Infected vaccinated: " + str(iVac) + " (" + str(round(iVac*100/vac, 1)) + "% of vaccinated)")
        print("Infected unvaccinated: " + str(iUnVac) + " (" + str(round(iUnVac*100/unVac, 1)) + "% of unvaccinated)")
        print("Herd Immunity: " + str(isHerd) + " (" + str(round(herd*100, 1)) + "% needed for Herd Immunity; we have "+str(round(immune*100,1))+"%)")

    def infect(self):
        # infect the first person
        self.initial_infection()
        #handle infection queue
        while len(self.unresolved_infections) > 0:
            node = self.unresolved_infections.pop(0)
            self.infect_spread(node)

    def initial_infection(self):
        node = int(random.random()*population)
        #first infection
        self.nodes[node].infected = True  # The first one is always infected no matter what
        self.infect_spread(node)  # begin recursive spread of infection

    def infect_spread(self, node):  # spread infection from infected individual recursively
        while True:  # Let's make sure our given node isn't in that list
            rNodes = random.sample(range(0, population), Rnull)  # generate a random sample of node numbers
            if not(node in rNodes):  # if infecting node is not in random sample, break out of loop
                break
        for n in rNodes:  # attempt to spread infection to nodes in random sample
            if not self.nodes[n].infected:
                self.nodes[n].attempt_infection()
                if self.nodes[n].infected:
                    self.unresolved_infections.append(n)  # recursively spread infection if infection was caught



pop = InfectablePopulation()  # infectable node population, automatically initialized

pop.infect()

pop.eval()

