/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   binpack.cpp
 * Author: mposypkin
 *
 * Created on July 24, 2017, 1:37 PM
 */

#include <cstdlib>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include <limits>
#include "binsub.hpp"
#include "binpackproblem.hpp"
#include "mtbinpacksolver.hpp"

void g(int np) {
    //binpack::BinPackProblem bpp({10, 20, 20, 30}, 40);
    std::vector<int> v = {100, 98, 96, 93, 91, 87, 81, 59, 58, 55, 50, 43, 22, 21, 20, 15, 14, 10, 8, 6, 5, 4, 3, 1, 0};
    binpack::BinPackProblem  bpp(v, 100);
    std::cout << bpp << "\n";
    const int nbins = bpp.mWeights.size();
    binpack::MtBinPackSolver bs(bpp, true);
    int nsteps = std::numeric_limits<int>::max();
    binpack::BinSub bestGuess(nbins, bpp.mBinCapacity);
    bestGuess.mUsedBins = nbins;
    std::vector<binpack::BinSub> bsv;
    bsv.emplace_back(nbins, bpp.mBinCapacity);
    binpack::BinSub bestPacking = bs.solve(bestGuess, bsv, nsteps, np);
    std::cout << "Performed " << nsteps << " steps\n";
    std::cout << "Best packing: \n" << bestPacking;
}

/*
 * 
 */
int main(int argc, char** argv) {

    int np = 0;
    if(argc == 2) {
        np = atoi(argv[1]);
    } else {
        std::cerr << "usage: " << argv[0] << " number_of_threads\n";
        exit(-1);
    }
    g(np);
    return 0;
}

