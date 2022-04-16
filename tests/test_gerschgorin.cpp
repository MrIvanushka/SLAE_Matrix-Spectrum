//
// Created by ivanb on 14.02.2022.
//
#include "gtest/gtest.h"
#include "my_project/utility/overloads.hpp"
#include "my_project/Spectr/Gerschgorin.hpp"
#include "my_project/dense/densematrix.hpp"
#include<iostream>
TEST(TEST_POWER_METHOD, NODISCARD){
    std::vector<double> elms = {3., 2., 3., 4., 2., 6., 3., 1., 3., 3, 8, 9, 4, 1, 9, 4};
    DenseMatrix<double> matrix(4, 4, elms);

    auto result = findLambdas(matrix);
    for(auto res : result)
        std::cout << res << " ";
}

