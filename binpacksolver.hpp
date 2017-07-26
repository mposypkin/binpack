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

namespace binpack {

    class BinPackSolver {
    public:

        BinPackSolver(std::shared_ptr<BinPackProblem> bp) : mBP(bp) {
        }
        
        /**
         * Solve the problem 
         * @param bestPacking best packing found so far (to be updated by the solver)
         * @param on entry - maximal number of steps to perform, on exit - actual number
         */
        void solve(BinSub& bestPacking, int& nsteps) {
            int maxSteps = nsteps;
            nsteps = 0;
            std::vector<binpack::BinSub> bsv;
            const int nbins = mBP->mWeights.size();
            binpack::BinSub ibs(nbins, mBP->mBinCapacity);
            bsv.push_back(std::move(ibs));
            while ((!bsv.empty()) && (nsteps < maxSteps)) {
                nsteps ++;
                binpack::BinSub bs(std::move(bsv.back()));
                const int curItem = bs.mItem2bin.size();
                bsv.pop_back();
                if (bs.mUsedBins >= bestPacking.mUsedBins)
                    continue;
                //std::cout << "Processing subproblem: \n" << bs << "\n";
                for (int i = 0; i < nbins; i++) {
                    if (i + 1 >= bestPacking.mUsedBins)
                        break;
                    const int rc = bs.mRemCapacity[i] - mBP->mWeights[curItem];
                    if (rc < 0)
                        continue;
                    binpack::BinSub bsn(bs);
                    bsn.mRemCapacity[i] = rc;
                    if (bsn.mRemCapacity[i] < 0)
                        continue;
                    bsn.mItem2bin.push_back(i);
                    bsn.mUsedBins = std::max(bs.mUsedBins, i + 1);
                    if (curItem == mBP->mWeights.size() - 1) {
                        if (bsn.mUsedBins < bestPacking.mUsedBins)
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
        }
        
    private:
        std::shared_ptr<BinPackProblem> mBP;
    };
}

#endif /* BINPACKSOLVER_HPP */

