//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_OVERLOADS_HPP
#define SLAE_OVERLOADS_HPP
#include <iosfwd>
#include <vector>
#include <ostream>
#include "../sparse/CSR.hpp"
#include "../utility/triplet.hpp"
/***
 * Умножение числа на вектор
 * @tparam T Тип числа
 * @param k Число
 * @param b Вектор
 * @return Результат умножения
 */
template<typename T>
std::vector<T> operator*(const T &k, const std::vector<T> &b){
    std::vector<T> res(b.size());
    for (size_t i = 0; i < b.size(); ++i) {
        res[i] = b[i] * k;
    }
    return res;
};

/***
 * Умножение вектора на число
 * @tparam T Тип числа
 * @param b Вектор
 * @param k Число
 * @return Результат умножения
 */
template<typename T>
std::vector<T> operator*(const std::vector<T> &b, const T &k){
    return k * b;
};

/***
 * Скалярное перемножение векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат скалярного перемножения
 */
template<typename T>
T operator*(const std::vector<T> &a, const std::vector<T> &b){
    T res = 0;
    for (int i = 0; i < a.size(); ++i) {
        res += a[i] * b[i];
    }
    return res;
};

/***
 * Вычитание двух векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат вычитания векторов
 */
template<typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b){
    std::vector<T> res(a.size());
    for(int i = 0; i < a.size(); ++i){
        res[i] = a[i] - b[i];
    }
    return res;
};

/***
 * Сложение двух векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат сложения векторов
 */
template<typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b){
    return a - static_cast<T>(-1) * b;
};

/**
 * оператор вывода вектора в поток
 * @tparam T используемые тип данных
 * @param os поток
 * @param b вектор
 * @return поток с вектором
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &b){
    for (auto i: b) {
        os << i << " ";
    }
    os << "\n";
    return os;
};

template<typename T>
CSR<T> matrixProduct(std::vector<T> a, std::vector<T> b)
{
    std::set<Triplet<T>> triplets;

    for(int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            auto product = a[i] * b[j];
            if (product != static_cast<T>(0)) {
                triplets.insert({i, j, product });
            }
        }
    }

    return CSR(a.size(), b.size(), triplets);
}

#endif//SLAE_OVERLOADS_HPP
