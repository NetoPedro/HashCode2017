//
// Created by Pedro Neto on 19/01/18.
//

#include "GeneticAlgorithm.h"
#define POPULATION_SIZE 10
void GeneticAlgorithm::init(int generations, DataCenter dataCenter) {
    this->generateInitialPopulation(POPULATION_SIZE);
    for (int i = 0; i < generations; ++i) {
        crossover();
        mutation();
        selection();
    }

}