//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_DENSEMATRIX_HPP
#define SLAE_DENSEMATRIX_HPP
#include <vector>
#include <set>
#include "../utility/triplet.hpp"
#include "../Exceptions/UndeclaredElementCallException.hpp"

#include <vector>
#include <set>
#include "../utility/triplet.hpp"

template<typename T>
class DenseMatrix{
public:
    using elm_t = T;
    using idx_t = std::size_t;

private:

    std::vector<T> matrix_;
    idx_t row_size_, col_size_;

    template<typename EL>
    friend std::vector<EL> operator*(const DenseMatrix<EL> &A, const std::vector<EL> &b);
public:

    /***
     *
     * @param h
     * @param w
     */
    DenseMatrix(const idx_t &h, const idx_t& w)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
    }

    /***
     *
     * @param h
     * @param w
     */
    DenseMatrix(const idx_t &h, const idx_t& w, const std::vector<T> &data)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
        for (int i = 0; i < data.size(); i++)
        {
            matrix_[i] = data.at(i);
        }
    }

    /***
     *
     * @param h
     * @param w
     */
    DenseMatrix(const idx_t &h, const idx_t& w, T fill)
    {
        row_size_ = h;
        col_size_ = w;
        matrix_.resize(h * w);
        for (int i = 0; i < h * w; i++)
            matrix_[i] = fill;
    }


    /***
     *
     * @param h
     * @param w
     * @param in
     */
    DenseMatrix(const idx_t &h, const idx_t& w, const std::set<Triplet<T>>& in)
    {
        row_size_ = h;
        col_size_ = w;

        std::vector<T> vec(h * w, static_cast<T>(0));
        matrix_ = vec;
        for (auto &elem : in)
        {
            matrix_[elem.i * col_size_ + elem.j] = elem.value;
        }

    }


    /***
     *
     * @param i
     * @param j
     * @return
     */
    elm_t& operator()(const idx_t& i, const idx_t& j)
    {
        return matrix_[i * col_size_ + j];
    }


    /***
     *
     * @param i
     * @param j
     * @return
     */
    const elm_t& operator()(const idx_t& i, const idx_t& j) const
    {
        return matrix_[i * col_size_ + j];
    }

    /***
     *
     * @param A
     * @return
     */
    void operator-=(const DenseMatrix<elm_t> &A){
        for(int i = 0; i < matrix_.size(); i++)
        {
            matrix_[i] -= A.matrix_[i];
        }
    }


    /***
     *
     * @return
     */
    [[nodiscard]] const idx_t& get_row_size() const
    {
        return row_size_;
    }


    /***
     *
     * @return
     */
    [[nodiscard]] const idx_t& get_col_size() const
    {
        return col_size_;
    }


    /***
     * Return matrix column with index i
     * @param i column index (i <= col_size, begins from 0)
     * @return vector -- matrix column
     */
    std::vector<T> get_col(unsigned i) const
    {
        std::vector<T> col(row_size_);

        for (unsigned j = 0; j < row_size_; j++)
            col[j] = matrix_[j * col_size_ + i];

        return col;
    }


    /***
     *
     * @param first
     * @param second
     */
    void swap(const idx_t& first, const idx_t& second)
    {
        if (first == second)
        {
            std::stringstream buff;
            buff << "Index equal! Received index: " << first << " and " << second << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        if (first > row_size_ || second > row_size_)
        {
            std::stringstream buff;
            buff << "Index exceeds matrix row size! Received indexes: " << first << " and " << second
                 << ". Matrix size: " << row_size_ << "x" << col_size_ << ". File: " << __FILE__
                 << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        std::vector<T> tmp(col_size_);

        for (int i = 0; i < col_size_; ++i)
        {
            tmp[i] = matrix_[(first - 1) * col_size_ + i];
        }

        for (int i = 0; i < col_size_; ++i)
        {
            matrix_[(first - 1) * col_size_ + i] = matrix_[(second - 1) * col_size_ + i];
        }

        for (int i = 0; i < col_size_; ++i)
        {
            matrix_[(second - 1) * col_size_ + i] = tmp[i];
        }

    }


    /***
     * Deletes last row in matrix
     */
    void deleteLastRow()
    {
        matrix_.erase(matrix_.end() - col_size_, matrix_.end());
        row_size_--;
    }
};


/***
 *
 * @tparam T
 * @param os
 * @param A
 * @return
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const DenseMatrix<T> &A)
{
    for (int i = 0; i < A.get_row_size(); ++i)
    {
        for (int j = 0; j < A.get_col_size(); ++j)
            os << A(i, j) << " ";
        os << std::endl;
    }

    return os;
}

template <typename T>
DenseMatrix<T> operator*(const DenseMatrix<T> &A, const DenseMatrix<T> &B) {
    DenseMatrix<T> result(A.get_row_size(), B.get_col_size(), 0);

    for (int i = 0; i < A.get_row_size(); i++) {
        for (int j = 0; j < B.get_col_size(); j++) {
            for (int k = 0; k < A.get_col_size(); k++)
                result(i, j) += A(i, k) * B(k, j);
        }
    }

    return result;
}

template <typename T>
std::vector<T> operator*(const DenseMatrix<T> &A, const std::vector<T> &b) {
    auto result =  A * DenseMatrix(b.size(), 1, b);
    return result.matrix_;
}

template <typename T>
DenseMatrix<T> operator*(const T &a, const DenseMatrix<T> &A) {
    DenseMatrix<T> result(A.get_row_size(), A.get_col_size(), 0);

    for (int i = 0; i < A.get_row_size(); i++) {
        for (int j = 0; j < A.get_col_size(); j++) {
            result(i, j) = A(i, j) * a;
        }
    }

    return result;
}

#endif//SLAE_DENSEMATRIX_HPP
