/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mtbinpacksolver.hpp
 * Author: posypkin
 *
 * Created on August 28, 2017, 2:21 PM
 */

#ifndef MTBINPACKSOLVER_HPP
#define MTBINPACKSOLVER_HPP

#include <thread>
#include <future>
#include "binpackproblem.hpp"
#include "binsub.hpp"
#include "binpacksolver.hpp"

namespace binpack {

    /**
     * Multithreaded bin-packing solver
     */
    class MtBinPackSolver {
    public:

        /**
         * Constructor
         * @param bp the problem
         * @param mode the isParallel (true - parallel, false - sequential)
         */
        MtBinPackSolver(const BinPackProblem& bp, bool isParallel) : mBP(bp), mSeq(!isParallel) {
        }


        /*
        BinSub solve1(const BinSub& bestPacking, std::vector<binpack::BinSub>& bsv, int& nsteps, int np) {
            auto fut1 = std::async(&MtBinPackSolver::solve1, this, bestPacking, bsv, nsteps, np);
        }
         */

        /**
         * Solve the problem 
         * @param bestPacking best packing found before the call
         * @param subproblems on entry (to be updated by the solver)
         * @param on entry - maximal number of steps to perform, on exit - actual number
         * @param np number of assigned processors
         * @return best packing found 
         */
        BinSub solve(const BinSub& bestPacking, std::vector<binpack::BinSub> bsv, int& nsteps, int np) {
            //std::cout << "in solve: np = " << np << "\n";
            if (np == 1) {
                BinPackSolver bps(mBP);
                return bps.solve(bestPacking, bsv, nsteps);
            } else {
                const int maxSteps = nsteps;
                nsteps = 0;
                BinSub localBestPacking(bestPacking);
                if (bsv.size() == 1) {
                     while ((!bsv.empty()) && (bsv.size() < 2) && (nsteps < maxSteps)) {
                        nsteps++;
                        binpack::BinSub bs(std::move(bsv.back()));
                        const unsigned int curItem = bs.mItem2bin.size();
                        bsv.pop_back();
                        if (bs.mUsedBins >= localBestPacking.mUsedBins)
                            continue;
                        const int nbins = std::min(bs.mUsedBins + 1, localBestPacking.mUsedBins - 1);
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
                }
                if (!bsv.empty()) {
                    const int sz = bsv.size();
                    if (sz >= 2) {
                        const int szh = sz / 2;
                        auto bi = bsv.cbegin() + szh;
                        auto ei = bsv.cend();
                        std::vector<binpack::BinSub> bsv2(std::make_move_iterator(bi), std::make_move_iterator(ei));
                        bsv.erase(bi, ei);
                        int *psteps1 = new int(maxSteps), *psteps2 = new int(maxSteps);
                        binpack::BinSub bestPacking1(localBestPacking);
                        binpack::BinSub bestPacking2(localBestPacking);
                        const int np1 = np / 2;
                        const int np2 = np - np1;
                        if (mSeq) {
                            bestPacking1 = std::move(solve(localBestPacking, bsv, *psteps1, np1));
                            bestPacking2 = std::move(solve(localBestPacking, bsv2, *psteps2, np2));
                        } else {
                            auto fut1 = std::async(&MtBinPackSolver::solve, this, localBestPacking, bsv, std::ref(*psteps1), np1);
                            auto fut2 = std::async(&MtBinPackSolver::solve, this, localBestPacking, bsv2, std::ref(*psteps2), np2);
                            bestPacking1 = std::move(fut1.get());
                            bestPacking2 = std::move(fut2.get());
                        }
                        if (bestPacking1.mUsedBins < localBestPacking.mUsedBins) {
                            localBestPacking = std::move(bestPacking1);
                        }
                        if (bestPacking2.mUsedBins < localBestPacking.mUsedBins) {
                            localBestPacking = std::move(bestPacking2);
                        }
                        nsteps += *psteps1 + *psteps2;
                    } else {
                        std::cerr << "bsv size should be > 2\n";
                        std::exit(-1);
                    }
                }
                return localBestPacking;
            }
        }

    private:
        const BinPackProblem& mBP;
        const bool mSeq;
    };
}


#endif /* MTBINPACKSOLVER_HPP */

