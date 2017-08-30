/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   binpackproblem.hpp
 * Author: mposypkin
 *
 * Created on July 25, 2017, 12:20 PM
 */

#ifndef BINPACKPROBLEM_HPP
#define BINPACKPROBLEM_HPP

#include <vector>
#include <iostream>

namespace binpack {

    /**
     * Bin packing problem data
     */
    struct BinPackProblem {

        /**
         * Constructor
         */
        BinPackProblem() :
        mBinCapacity(0) {
        }

        /**
         * Constructor
         * @param weights item weights
         * @param cap bin capacity
         */
        BinPackProblem(const std::vector<int>& weights, int cap) :
        mWeights(weights), mBinCapacity(cap) {
        }

        /**
         * Items' weights
         */
        std::vector <int> mWeights;

        /**
         * The capacity of the bin
         */
        int mBinCapacity;
    };

    /**
     * Output operator
     * @param os output stream
     * @param bp problem description
     * @return output stream
     */
    std::ostream& operator<<(std::ostream& os, const BinPackProblem& bp) {
        os << "items: {";
        std::copy(bp.mWeights.cbegin(), bp.mWeights.cend(), std::ostream_iterator<int>(std::cout, " "));
        os << "},";
        os << " capacity = " << bp.mBinCapacity;
        return os;
    }

    /**
     * Input operator
     * @param is output stream
     * @param bp problem description
     * @return output stream
     */
    std::istream& operator>>(std::istream& is, BinPackProblem& bp) {
        int n;
        is >> n;
        is >> bp.mBinCapacity;
        for (int i = 0; i < n; i++) {
            int x;
            is >> x;
            bp.mWeights.push_back(x);
        }
        return is;
    }



}

#endif /* BINPACKPROBLEM_HPP */

