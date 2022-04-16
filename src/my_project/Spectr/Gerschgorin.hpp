//
// Created by ivan on 16.04.22.
//

#ifndef MY_PROJECT_GERSCHGORIN_HPP
#define MY_PROJECT_GERSCHGORIN_HPP

#include<vector>
#include "my_project/utility/Norm.hpp"
#include "my_project/dense/densematrix.hpp"

template<typename T>
struct Segment
{
    T Min;
    T Max;

    Segment(T min, T max) : Min(min), Max(max)
    {}
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const Segment<T> &l)
{
    os << "[" << l.Min << "; " << l.Max << "]";

    return os;
}

template<typename T>
std::vector<Segment<T>> findLambdas(const DenseMatrix<T>& A)
{
    std::vector<Segment<T>> segments;

    for(int j = 0; j < A.get_col_size(); j++)
    {
        T r = static_cast<T>(0);

        for(int i = 0; i < A.get_row_size(); i++)
            if(i != j)
                r += std::abs(A(i, j));

        segments.push_back(Segment(A(j, j) - r, A(j, j) + r));
    }
    return segments;
}

#endif //MY_PROJECT_GERSCHGORIN_HPP
