#include <iostream>
#include "Scanner/Importer.h"
#include "GA/GeneticAlgorithm.h"

int main() {
    int initial = time(NULL);
    DataCenter dataCenter = Importer::import("../Input/ewf.txt");
    GeneticAlgorithm *geneticAlgorithm = new GeneticAlgorithm();
    geneticAlgorithm->init(2500,dataCenter);
    std::cout << "Duration " << time(NULL) - initial << std::endl;

    return 0;
}