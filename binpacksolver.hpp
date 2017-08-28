/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   binpack.hpp
 * Author: mposypkin
 *
 * Created on July 26, 2017, 12:35 PM
 */

#ifndef BINPACKSOLVER_HPP
#define BINPACKSOLVER_HPP

#include <memory>
#include "binpackproblem.hpp"
#include "binsub.hpp"

namespace binpack {

    class BinPackSolver {
    public:

        BinPackSolver(const BinPackProblem& bp) : mBP(bp) {
        }
        
        /**
         * Solve the problem 
         * @param bestPacking best packing found before the call
         * @param subproblems on entry (to be updated by the solver)
         * @param on entry - maximal number of steps to perform, on exit - actual number
         * @return best packing
         */
        BinSub solve(const BinSub& bestPacking, std::vector<binpack::BinSub>& bsv, int& nsteps) {
            const int maxSteps = nsteps;
            BinSub localBestPacking(bestPacking);
            nsteps = 0;
            const int nbins = localBestPacking.mUsedBins;
            while ((!bsv.empty()) && (nsteps < maxSteps)) {
                nsteps ++;
                binpack::BinSub bs(std::move(bsv.back()));
                const unsigned int curItem = bs.mItem2bin.size();
                bsv.pop_back();
                if (bs.mUsedBins >= localBestPacking.mUsedBins)
                    continue;
                for (int i = 0; i < nbins; i++) {
                    if (i + 1 >= localBestPacking.mUsedBins)
                        break;
                    const int rc = bs.mRemCapacity[i] - mBP.mWeights[curItem];
                    if (rc < 0)
                        continue;
                    binpack::BinSub bsn(bs);
                    bsn.mRemCapacity[i] = rc;
                    bsn.mItem2bin.push_back(i);
                    bsn.mUsedBins = std::max(bs.mUsedBins, i + 1);
                    if (curItem == mBP.mWeights.size() - 1) {
                        if (bsn.mUsedBins < localBestPacking.mUsedBins)
                            localBestPacking = std::move(bsn);
                    } else
                        bsv.push_back(std::move(bsn));
                }
            }
            return localBestPacking;
        }
        
    private:
        const BinPackProblem& mBP;
    };
}

#endif /* BINPACKSOLVER_HPP */

