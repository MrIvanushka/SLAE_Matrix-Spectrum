//
// Created by ivanb on 14.02.2022.
//
#include "gtest/gtest.h"
#include "my_project/dense/densematrix.hpp"
#include "my_project/Spectr/QR.hpp"
TEST(TEST_POWER_METHOD, NODISCARD){

    std::vector<double> elms = {3., 2., 3., 4., 2., 6., 3., 1., 3., 3, 8, 9, 4, 1, 9, 4};
    DenseMatrix<double> matrix(4, 4, elms);
    std::vector<double> a = {1., 0., 0., 0.};
    std::cout << "Matrix A:" << std::endl << matrix << std::endl << std::endl;

    auto result = QR::scoreAllLambdas(matrix, 0.1);

    std::cout << "Lambdas:";
    for(const auto& lambda : result)
        std::cout << lambda << " ";
}

