#include <iostream>
#include "Scanner/Importer.h"
#include "GA/GeneticAlgorithm.h"

int main() {
    int initial = time(NULL);
    DataCenter dataCenter = Importer::import("../Input/videos_worth_spreading.in");
    GeneticAlgorithm *geneticAlgorithm = new GeneticAlgorithm();
    geneticAlgorithm->init(5,dataCenter);
    std::cout << "Duration " << time(NULL) - initial << std::endl;

    return 0;
}