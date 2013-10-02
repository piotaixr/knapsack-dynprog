/* 
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 */


#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>


#include "Instance.h"
#include "InstanceLoader.h"
#include "ChainLoader.h"
#include "FileLoader.h"
#include "StreamLoader.h"
#include "AbstractKnapsackAlgorithm.h"
#include "MatrixAlgorithm.h"
#include "SwapVectorsAlgorithm.h"
#include "InstanceReducer.h"
#include "EventDispatcher.h"
#include "ResultPrinter.h"
#include "DispatcherCreator.h"

#ifndef KP_NOCUDA
#include "CudaAcceleratedAlgorithm.cu.h"
#include "ResultPrinter.h"
#include "ThrustAlgorithm.h"
#endif

using namespace std;
using namespace boost;
namespace ublas = boost::numeric::ublas;
namespace po = boost::program_options;

template<typename P, typename W>
void solveKnapsack(shared_ptr<Instance<P, W> > instance, AbstractKnapsackAlgorithm<P, W>* algorithm, DispatcherCreator& creator) {
    shared_ptr<EventDispatcher<P, W> > dispatcher = creator.getDispatcher<P, W>();

    boost::shared_ptr<Event<P, W> > event(new Event<P, W>(instance));

    dispatcher->dispatch(BaseEvent::BEFORE_COMPUTATION, event);

    P optimalSolution;
    if (event->hasOptimalSolution()) {
        optimalSolution = event->getOptimalSolution();
    } else {
        Counter c = Counter("Computation");
        c.start();
        optimalSolution = event->getInstance()->getObjective(*algorithm);
        c.stop();
        event->addTime("Computation", c.getTime());
        event->setOptimalSolution(optimalSolution);
    }

    cout << "L'optimal est: " << optimalSolution << endl;

    dispatcher->dispatch(BaseEvent::OPTIMAL_SOLUTION_FOUND, event);
}

/*
 * 
 */
int main(int argc, char** argv) {
    vector<string> inputFiles;
    int numThreads = 0;
    string outputFile;
    string benchmarkFile;
    bool matrixVersion = false;
    bool reduce = false;
    bool readCin = false;
    bool useCuda = false;
    bool outputTimes = false;
    bool useThrust = false;

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "Produce help message")
            ("input-file,i", po::value<vector<string> >(&inputFiles), "Input files")
            ("benchmark,b", po::value<string>(&benchmarkFile), "Print computation times in files with pattern: 'file_SIZE'.ext")
            ("matrix,m", "Use the matrix version")
            ("reduce,r", "Reduce the instance size based on some heuristics")
            ("cuda", "Use the cuda-accelerated algorithm")
            ("output-file,o", po::value<string>(&outputFile)->default_value(""), "Print the results in a file")
            ("times", "Also output the times")
            ("read-stdin,s", "check stdin for instances")
            ("num-threads,t", po::value<int>(&numThreads)->default_value(0), "Set num Threads for OMP")
            ("thrust", "Use the thrust algorithm")
            ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).positional(p).options(desc).run(), vm);
    po::notify(vm);

    if (vm.count("read-stdin")) {
        readCin = true;
    }

    if (vm.count("help") || inputFiles.size() == 0 && !readCin) {
        cout << desc << endl;
        return 1;
    }

    if (vm.count("reduce")) {
        reduce = true;
    }
    if (vm.count("times")) {
        outputTimes = true;
    }
    if (vm.count("cuda")) {
        useCuda = true;
    }
    if (vm.count("read-stdin")) {
        readCin = true;
    }
    if (vm.count("thrust")) {
        useThrust = true;
    }
    if (vm.count("matrix")) {
        matrixVersion = true;
    }
    if (useCuda && matrixVersion) {
        matrixVersion = false;
        cout << "Ussage of cuda impossible with the matrix algorithm" << endl;
    }

    DispatcherCreator creator(reduce, outputFile, outputTimes, benchmarkFile);

    AbstractKnapsackAlgorithm<unsigned, unsigned>* algorithm;
    if (matrixVersion) {
        algorithm = new MatrixAlgorithm<unsigned, unsigned>();
    } else if (useCuda) {
#ifndef KP_NOCUDA
        algorithm = new CudaAcceleratedAlgorithm<unsigned, unsigned>();
#else
        cout << "Le programme a été compilé sans le support CUDA" << endl << "Fermeture..." << endl;
        exit(0);
#endif
    } else if (useThrust) {
#ifndef KP_NOCUDA
        algorithm = new ThrustAlgorithm<unsigned, unsigned>();
#else
        cout << "Le programme a été compilé sans le support CUDA (et donc thrust) " << endl << "Fermeture..." << endl;
        exit(0);
#endif   
    } else {
        algorithm = new SwapVectorsAlgorithm<unsigned, unsigned>(numThreads);
    }


    shared_ptr<ChainLoader<unsigned, unsigned> > loader(new ChainLoader<unsigned, unsigned>());
    if (inputFiles.size() != 0)
        loader->addLoader(shared_ptr<InstanceLoader<unsigned, unsigned> >(new FileLoader<unsigned, unsigned>(inputFiles)));
    if (readCin)
        loader->addLoader(shared_ptr<InstanceLoader<unsigned, unsigned> >(new StreamLoader<unsigned, unsigned>(cin)));


    while (loader->hasNext()) {
        shared_ptr<Instance<unsigned, unsigned> > instance = loader->nextInstance();
        try {
            solveKnapsack(instance, algorithm, creator);
        } catch (std::exception& ex) {
            cout << endl << "Erreur lors du traitement du fichier " << instance->getName() << endl
                    << '\t' << ex.what() << endl << endl;
        }
    }
    cout << endl << "YaY!" << endl;

    return (EXIT_SUCCESS);
}
