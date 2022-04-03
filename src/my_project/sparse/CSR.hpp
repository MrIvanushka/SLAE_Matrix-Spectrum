//
// Created by petrov on 12.02.2022.
//

#ifndef SOLE2022_CSR_HPP
#define SOLE2022_CSR_HPP

#include <vector>
#include <set>
#include <ostream>
#include <algorithm>

#include "../utility/triplet.hpp"
#include "../Exceptions/UndeclaredElementCallException.hpp"

template<typename T>
class CSR {
public:
    using elm_t = T;          // Тип данных элементов матрицы
    using idx_t = std::size_t;// Тип индекса

private:
    const idx_t H, W;         //Размеры матрицы
    std::vector<elm_t> _values;//Вектор значений (размер N - кол-во ненулевых элементов)
    std::vector<idx_t> _cols;  // Вектор номеров столбцов, соответствующих значениям (размер N - кол-во ненулевых элементов)
    std::vector<idx_t> _rows;  // Вектор индексации строк размера H+1, первый элемент = 0 в качестве запирающего

    template<typename EL>
    friend std::vector<EL> Jacobi(const CSR<EL> &A, const std::vector<EL> &b, const std::vector<EL>& initialState, const EL& tolerance);
    template<typename EL>
    friend std::vector<EL> GaussSeidel(const CSR<EL> &A, const std::vector<EL> &b, const std::vector<EL>& initialState, const EL& tolerance);

public:
    /***
     * Конструктор разреженной матрицы по готовым векторам с внутренней структурой
     * @param h число строк
     * @param w число столбцов
     * @param v вектор ненулевых значений
     * @param c вектор индексации столбцов
     * @param r вектор индексации строк
     */
    CSR(const idx_t &h, const idx_t &w, const std::vector<T>& v,const std::vector<idx_t>& c, const std::vector<idx_t>& r): H(h), W(w){
        _values = v;
        _rows = r;
        _cols = c;
    };

    /***
     * Конструктор разреженной матрицы по сету из Triplet
     * @param h -- число строк
     * @param w -- число столбцов
     */
    CSR(const idx_t &h, const idx_t &w, const std::set<Triplet<elm_t>>& in): H(h), W(w){
        _values.resize(in.size());
        _cols.resize(in.size());
        _rows.resize(h + 1, 0);
        int countInRow_row = 0;
        int currRow = 0;
        auto it = in.begin();
        for(idx_t k = 0; k < in.size(); ++k){
            while (currRow < it->i){
                _rows[currRow + 1] = _rows[currRow] + countInRow_row;
                ++currRow;
                countInRow_row = 0;
            }
            _values[k] = it->value;
            _cols[k] = it->j;
            ++countInRow_row;
            it = std::next(it);

        }
        for(++currRow;currRow <= H; ++currRow){
            _rows[currRow] = in.size();
        }

    };

    /***
     * Оператор получения элемента матрицы по индексам
     * @param i -- Номер строки
     * @param j -- Номер столбца
     * @return Значение элемента в позиции (i, j)
     */
    const elm_t operator()(idx_t const i, idx_t const j) const{
        idx_t skip = _rows[i];
        idx_t count = _rows[i+1] - skip;
        for(idx_t k = skip; k < skip + count; ++k){
            if(_cols[k] == j) return _values[k];
        }
        return std::move(static_cast<elm_t>(0));
    };

    /***
     * Оператор умножения матрицы на вектор
     * @param b -- Вектор, на который умножается матрица
     * @return Вектор - результат перемножения
     */
    std::vector<elm_t> operator*(const std::vector<elm_t> &b) const{
        std::vector<elm_t> res(this->H);
        for(idx_t i = 0; i < H; ++i){
            idx_t skip = this->_rows[i];
            idx_t count = this->_rows[i+1] - skip;
            for(idx_t k = skip; k < skip + count; ++k){
                res[i] += _values[k] * b[_cols[k]];
            }
        }
        return res;
    };

    /***
     * Метод, позволяющий узнать количество строк матрицы
     * @return количество строк
     */
    [[nodiscard]] int sizeH() const{
        return H;
    }
    /***
     * Метод, позволяющий узнать количество столбцов матрицы
     * @return количество столбцов
     */
    [[nodiscard]] int sizeW() const{
        return W;
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const CSR<T> &A){
    for(int i = 0; i < A.sizeH(); ++i){
        for(int j = 0; j < A.sizeW(); ++j){
            os << A(i, j) << " ";
        }
        os <<"\n";
    }
    return os;
};

#endif//SOLE2022_CSR_HPP
