//
// Created by Pedro Neto on 19/01/18.
//

#include "GeneticAlgorithm.h"

#define POPULATION_SIZE 10

void GeneticAlgorithm::init(int generations, DataCenter dataCenter,int geneSize) {
    std::list<int> bestSolution ;
    this->generateInitialPopulation(POPULATION_SIZE);
    for (int i = 0; i < generations; ++i) {
        crossover(geneSize);
        mutation();
        selection();
    }
}

void GeneticAlgorithm::crossover(int geneSize) {
    std::list<int> newMembers;
    std::string mask= "" ;
    srand (time(NULL));

    for (int i = 0; i < geneSize; ++i) {
        int rand = std::rand() % 2 ;
        mask += rand;
    }

    for (int j = 0; j < POPULATION_SIZE ; j+=2) {
     /*   auto it1 = std::next(this->population.begin(), j);
        std::list<int> parent1 = ( std::list<int>) *it1;
        auto it2 = std::next(this->population.begin(), j+1);*/
    }

}