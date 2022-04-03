//
// Created by ivan on 03.04.2022.
//

#ifndef MY_PROJECT_QR_HPP
#define MY_PROJECT_QR_HPP

#include<vector>
#include "my_project/utility/Norm.hpp"
#include "my_project/dense/densematrix.hpp"
#include "my_project/decompose/Gram-Schmidt.hpp"
#include "iostream"
class QR
{
public:
    template<typename T>
    static std::vector<T> scoreAllLambdas(const DenseMatrix<T> &A, const T &tolerance) {
        DenseMatrix<T> multiQ(A.get_row_size(), A.get_col_size(), static_cast<T>(1));
        DenseMatrix<T> currentMatrix = A;
        std::vector<T> result(A.get_col_size());

        std::vector<bool> needToScore(A.get_col_size());
        for(int i = 0; i < needToScore.size(); i++)
            needToScore[i] = true;

        while(mustScore(needToScore)) {
            auto QRres = QR_decomposition_Gram_Schmidt(currentMatrix);
            multiQ = multiQ * QRres.first;
            currentMatrix = QRres.second * QRres.first;

            for(int i = 0; i < currentMatrix.get_col_size(); i++)
            {
                if(needToScore[i])
                {
                    auto selfVec = multiQ.get_col(i);
                    auto lambda = currentMatrix(i, i);

                    if(norm((lambda * selfVec) - (A * selfVec), NormType::FirstNorm) < tolerance)
                    {
                        result[i] = lambda;
                        needToScore[i] = false;
                    }
                }
            }
        }

        return result;
    }
private:
    static bool mustScore(const std::vector<bool>& needToScore) {
        for(int i = 0; i < needToScore.size(); i++)
            if(needToScore[i] == true)
                return true;
        return false;
    }
};

#endif //MY_PROJECT_QR_HPP
