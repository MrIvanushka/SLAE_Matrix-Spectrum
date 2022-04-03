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
    std::vector<double> elms = {3., 2., 3., 4., 2., 6., 3., 1., 3., 3, 8, 9, 4, 1, 9, 4};
    DenseMatrix<double> matrix(4, 4, elms);
    std::cout << "-------------------dense-----------------------";
    std::cout << std::endl << "Matrix" << std::endl << matrix << std::endl;
    auto result = PowerIterations::scoreAllLambdas(matrix, 0.0001);

    std::cout << "Lambdas:";
    for(const auto& lambda : result)
        std::cout << lambda << " ";
}

