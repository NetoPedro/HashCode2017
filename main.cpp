#include <iostream>
#include "Scanner/Importer.h"
#include "GA/GeneticAlgorithm.h"

int main() {
    DataCenter dataCenter = Importer::import("../ewf.txt");
    GeneticAlgorithm *geneticAlgorithm = new GeneticAlgorithm();
    geneticAlgorithm->init(1000,dataCenter);
    std::cout << "Hello, World!" << std::endl;

    return 0;
}