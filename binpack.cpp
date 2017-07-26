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
#include "binpacksolver.hpp"


void g() {
    //binpack::BinPackProblem bpp({10, 20, 20, 30}, 40);
    std::vector<int> v = {100, 98, 96, 93, 91, 87, 81, 59, 58, 55, 50, 43, 22, 21, 20, 15, 14, 10, 8, 6, 5, 4, 3, 1, 0};
    auto bpp = std::make_shared<binpack::BinPackProblem>(v, 100);
    std::cout << *bpp << "\n";
    const int nbins = bpp->mWeights.size();
    binpack::BinSub bestPacking(nbins, bpp->mBinCapacity);    
    bestPacking.mUsedBins = nbins;
    binpack::BinPackSolver bs(bpp);
    int nsteps = std::numeric_limits<int>::max();
    bs.solve(bestPacking, nsteps);
    std::cout << "Performed " << nsteps << " steps\n";
    std::cout << "Best packing: \n" << bestPacking;
}

/*
 * 
 */
int main(int argc, char** argv) {

    g();
    return 0;
}

