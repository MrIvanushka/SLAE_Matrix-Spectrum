//
// Created by ivanb on 14.02.2022.
//
#include "gtest/gtest.h"
#include "my_project/sparse/CSR.hpp"
#include "my_project/utility/triplet.hpp"
#include "my_project/utility/overloads.hpp"
#include "my_project/Spectr/PowerIterations.hpp"
#include<iostream>
TEST(TEST_POWER_METHOD, NODISCARD){
    //std::set<Triplet<double>> data{{0, 0, 1}, {2, 1, 5}};
    //CSR<double> matrix(3, 3, data);
    std::vector<double> a {1, 2, 3, 4};
    std::vector<double> b {1, 2, 3, 4 };
    std::cout << "-------------------CSR-----------------------";
    CSR<double> matrix =  matrixProduct(a, b);
    std::cout << std::endl << "Matrix" << std::endl << matrix << std::endl;
    auto result = PowerIterations::scoreLambda(matrix, a, 1.0);
    std::cout << "Max lambda:" << result;
}

