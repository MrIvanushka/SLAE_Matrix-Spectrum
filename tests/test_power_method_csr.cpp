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
    std::vector<double> a {1.0, 2.0, 3.0, 5.0};
    std::vector<double> b {1.0, 2.0, 3.0, 5.0};
    std::cout << "-------------------CSR-----------------------";
    CSR<double> matrix_ =  matrixProduct(a, b);
    std::cout << std::endl << "Matrix" << std::endl << matrix_ << std::endl;
    auto result = PowerIterations::scoreLambda(matrix_, a, 0.0001);
    std::cout << "Max lambda:" << result << '\n';
    auto result2 = PowerIterations::scoreSelfVector(matrix_, a, 0.0001);
    std::cout << "Self Vector:" << result2;
}

