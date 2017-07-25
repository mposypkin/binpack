/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   binsub.hpp
 * Author: mposypkin
 *
 * Created on July 24, 2017, 1:38 PM
 */

#ifndef BINSUB_HPP
#define BINSUB_HPP

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

namespace binpack {

    /**
     * Bin packing subproblem
     */
    struct BinSub {

        /**
         * Constructor
         * @param nbins number of bins
         * @param cap initial capacity of a bin
         */
        BinSub(int nbins, int cap) : mUsedBins(0) {
            mRemCapacity.assign(nbins, cap);
        }

        /**
         * Move constructor
         * @param sub to move from
         */
        BinSub(BinSub&& bs) {
            mItem2bin = std::move(bs.mItem2bin);
            mRemCapacity = std::move(bs.mRemCapacity);
            mUsedBins = bs.mUsedBins;
        }

        /**
         * Copy constructor
         */
        BinSub(const BinSub& bs) = default;
           
        /**
         * Move assign
         * @param bs bin subproblem to move
         * @return this
         */
        BinSub& operator = (BinSub&& bs) {
            mItem2bin = std::move(bs.mItem2bin);
            mRemCapacity = std::move(bs.mRemCapacity);
            mUsedBins = bs.mUsedBins;            
            return *this;
        }


        /**
         * Contains numbers of bins (assignments of items to bins) for assigned items 
         * item2bin[i] is the number of a bin where i is stored
         */
        std::vector<int> mItem2bin;

        /**
         * The remaining capacities of bins
         */
        std::vector<int> mRemCapacity;

        /**
         * Number of bins used
         */
        int mUsedBins;

    };

    /**
     * Output operator
     * @param os output stream
     * @param bs binpack subproblem
     * @return output stream
     */
    std::ostream& operator<<(std::ostream& os, const BinSub& bs) {
        int nbins = bs.mRemCapacity.size();
        os << "used bins = " << bs.mUsedBins << "\n";
        for (int i = 0; i < nbins; i++) {
            os << "bin " <<  i  << ", rc = " << bs.mRemCapacity[i] << ", items : ";            
            auto it = bs.mItem2bin.cbegin();
            while (it != bs.mItem2bin.cend()) {
                it = std::find(it, bs.mItem2bin.cend(), i);
                if (it != bs.mItem2bin.cend()) {
                    os << it - bs.mItem2bin.cbegin() << " ";
                    it ++;
                } 
            }
            os << "\n";

        }
        return os;
    }

}
#endif /* BINSUB_HPP */

