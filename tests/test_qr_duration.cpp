//
// Created by ivanb on 14.02.2022.
//
#include "gtest/gtest.h"
#include "my_project/dense/densematrix.hpp"
#include "my_project/Spectr/QR.hpp"
#include <time.h>

TEST(TEST_QR, NODISCARD){

    //for(int n = 3; n < 250; n++) {
        int n = 4;
        std::vector<double> elms;
        DenseMatrix<double> matrix(n, n, 0);

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++) {
                auto rn = rand();
                matrix(i, j) = rn;
                matrix(j, i) = rn;
            }
        }
        std::cout << "-----------------------------------" << std::endl;
        //clock_t t=clock();
        auto result = QR::scoreAllLambdas(matrix, 0.0001);
        //std:: cout << n << " " << (double)(clock()-t)/CLOCKS_PER_SEC << std::endl;
        //std::cout << "Lambdas:";
        //for(const auto& lambda : result)
        //    std::cout << lambda << " ";
    //}
}

