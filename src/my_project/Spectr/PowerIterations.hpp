//
// Created by ivanb on 26.03.2022.
//

#include<vector>
#include <random>
#include <algorithm>
#include <iterator>
#include "my_project/utility/Norm.hpp"
#include "my_project/sparse/CSR.hpp"
#include "my_project/dense/densematrix.hpp"

class PowerIterations {
public:
    template<typename T>
    static std::vector<T> scoreAllLambdas(DenseMatrix<T> A, const T &tolerance)
    {
        std::vector<T> startVector(A.get_col_size());
        startVector[0] = static_cast<T>(1);
        std::vector<T> lambdas;

        for(int i = 0; i < A.get_col_size(); i++)
        {
            auto pair = scoreAll(A, startVector, tolerance);
            lambdas.push_back(pair.first);
            A -= pair.first * DenseMatrix(pair.second.size(), 1, pair.second) *
                    DenseMatrix(1, pair.second.size(), pair.second);
        }

        return lambdas;
    }

    template<typename T>
    static T scoreLambda(const CSR<T> &A, const std::vector<T> scoreVector,
                         const T &tolerance) {
        return scoreAll(A, scoreVector, tolerance).first;
    }

    template<typename T>
    static std::vector<T> scoreSelfVector(const CSR<T> &A, const std::vector<T> scoreVector,
                         const T &tolerance) {
        return scoreAll(A, scoreVector, tolerance).second;
    }

private:
    template<typename T>
    static std::pair<T, std::vector<T>> scoreAll(const DenseMatrix<T> &A, std::vector<T> scoreVector,
                                                 const T &tolerance) {
        std::vector<T> temp;

        T lambda = static_cast<T>(0);
        do {
            temp = A * scoreVector;
            scoreVector = temp * (static_cast<T>(1) / norm(temp, NormType::ThirdNorm));
            lambda = scoreVector * (A * scoreVector) / (scoreVector * scoreVector);
        } while (norm(A * scoreVector - lambda * scoreVector, NormType::ThirdNorm) > tolerance);

        return std::pair(lambda, scoreVector);
    }

    template<typename T>
    static std::pair<T, std::vector<T>> scoreAll(const CSR<T> &A, std::vector<T> scoreVector,
                             const T &tolerance) {
        std::vector<T> temp;
        T lambda = static_cast<T>(0);
        do {
            temp = A * scoreVector;
            scoreVector = temp * (static_cast<T>(1) / norm(temp, NormType::ThirdNorm));
            lambda = scoreVector * (A * scoreVector) / (scoreVector * scoreVector);
        } while (norm(A * scoreVector - lambda * scoreVector, NormType::ThirdNorm) > tolerance);

        return std::pair(lambda, scoreVector);
    }
};