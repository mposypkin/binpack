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
#include <algorithm>
#include <iterator>
#include "binsub.hpp"
#include "binpackproblem.hpp"

void f() {
    //binpack::BinPackProblem bpp({10, 20, 20, 30}, 40);
    binpack::BinPackProblem bpp({100, 98, 96, 93, 91, 87, 81, 59, 58, 55, 50, 43, 22, 21, 20, 15, 14, 10, 8, 6, 5, 4, 3, 1, 0}, 100);
    std::cout << bpp << "\n";
    std::vector<binpack::BinSub> bsv;
    const int nbins = bpp.mWeights.size();
    binpack::BinSub ibs(nbins, bpp.mBinCapacity);
    bsv.push_back(std::move(ibs));
    binpack::BinSub bestPacking(nbins, bpp.mBinCapacity);
    bestPacking.mUsedBins = nbins;
    int nsteps = 0;
    while (!bsv.empty()) {
        nsteps ++;
        binpack::BinSub bs(std::move(bsv.back()));
        const int curItem = bs.mItem2bin.size();
        bsv.pop_back();
        if(bs.mUsedBins >= bestPacking.mUsedBins)
            continue;
        //std::cout << "Processing subproblem: \n" << bs << "\n";
        for (int i = 0; i < nbins; i++) {
            if(i + 1 >= bestPacking.mUsedBins)
                break;
            const int rc = bs.mRemCapacity[i] - bpp.mWeights[curItem];
            if(rc < 0)
                continue;
            binpack::BinSub bsn(bs);
            bsn.mRemCapacity[i] = rc;
            if (bsn.mRemCapacity[i] < 0)
                continue;
            bsn.mItem2bin.push_back(i);
            bsn.mUsedBins = std::max(bs.mUsedBins, i + 1);
            if (curItem == bpp.mWeights.size() - 1) {
                if(bsn.mUsedBins < bestPacking.mUsedBins) 
                    bestPacking = std::move(bsn);
            } else
                bsv.push_back(std::move(bsn));
        }
        //bsv.push_back(std::move(bs));

        //std::cout << "Current queue:\n";
        //std::copy(bsv.cbegin(), bsv.cend(), std::ostream_iterator<binpack::BinSub>(std::cout, "\n\n"));
        //char c;
        //std::cin >> c;
    }
    std::cout << "Performed " << nsteps << " steps\n";
    std::cout << "Best packing: \n" << bestPacking;
}

/*
 * 
 */
int main(int argc, char** argv) {

    f();
    return 0;
}

