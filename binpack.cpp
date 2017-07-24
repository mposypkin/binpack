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

void f() {
    std::vector<binpack::BinSub> bsv;
    binpack::BinSub  bs(5,10);  
    //std::cout << bs << "\n";
    bs.mItem2bin.push_back(0);
    bs.mItem2bin.push_back(3);
    bs.mItem2bin.push_back(1);
    bs.mItem2bin.push_back(3);
    
    bsv.push_back(std::move(bs));
    std::copy(bsv.cbegin(), bsv.cend(), std::ostream_iterator<binpack::BinSub>(std::cout, "; "));
}

/*
 * 
 */
int main(int argc, char** argv) {

    f();
    return 0;
}

