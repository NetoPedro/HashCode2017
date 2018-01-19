//
// Created by Pedro Neto on 19/01/18.
//

#include "GeneticAlgorithm.h"

#define POPULATION_SIZE 10
#define MUTATION_TAX 0.15
void GeneticAlgorithm::init(int generations, DataCenter dataCenter,int geneSize) {
    std::list<int> bestSolution ;
    srand (time(NULL));
    this->generateInitialPopulation(POPULATION_SIZE,geneSize);
    for (int i = 0; i < generations; ++i) {
        crossover(geneSize);
        mutation();
        selection();
    }
}

void GeneticAlgorithm::crossover(int geneSize) {
    std::list<int> newMembers;
    std::string mask= "" ;

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
//Tournament selection
void GeneticAlgorithm::selection() {
    for (int j = 0; j < POPULATION_SIZE ; j+=2) {
        /*   auto it1 = std::next(this->population.begin(), j);
           std::list<int> parent1 = ( std::list<int>) *it1;
           auto it2 = std::next(this->population.begin(), j+1);*/

    }
}

void GeneticAlgorithm::mutation() {
    for (std::list<int> chromosome  : this->population) {
        int rand = std::rand();
        if (rand <= MUTATION_TAX){
            //Apply mutation
        }

    }
}

float GeneticAlgorithm::fitness(std::list<int> chromosome) {
    return 0 ;
}

float GeneticAlgorithm::generateInitialPopulation(int populationElementsCount, int geneSize) {
    return 0 ; 
}