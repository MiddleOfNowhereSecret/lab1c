#pragma once
#include <vector>
#include <cassert>

namespace MathNS
{

/*!
    @brief Класс вектора
*/
template<typename T>
class Vector : public std::vector<T>
{
public:
    /*!
        @brief  Конструктор по умолчанию
    */
    Vector<T>() : std::vector<T>(){}

    /*!
        @brief  Конструктор для списка инициализации
        @param  il - Список инициализации
    */
    Vector<T>(std::initializer_list<T> il) : std::vector<T>(il){}

    /*!
        @brief  Конструктор для выделения вектора под заданный размер
        @param  size - Размер вектора
    */
    Vector<T>(size_t size) : std::vector<T>(size){}

    /*!
        @brief  Конструктор для создания двумерного вектора
        @param  rowSize - Количество строк
        @param   vector - Вектор-строка
    */
    Vector<T>( size_t rowSize,  const T & vector  )
        : std::vector<T>( rowSize, vector ){}

    /*!
        @brief  Оператор умножения
        @param  right - Вектор справа
        @return Вектор-результат умножения
    */
    Vector<T> operator*(const Vector<T> & right) const
    {
        assert(this->size() == right.size());

        Vector<T> result(this->size());

        for (size_t i = 0; i < this->size(); ++i)
            result[i] = this->data()[i] * right[i];

        return result;
    }

    /*!
        @brief  Оператор суммы
        @param  right - Вектор справа
        @return Вектор-результат суммы
    */
    Vector<T> operator+(const Vector<T> & right) const
    {
        assert(this->size() == right.size());

        Vector<T> result(this->size());

        for (size_t i = 0; i < this->size(); ++i)
            result[i] = this->data()[i] + right[i];

        return result;
    }

    /*!
        @brief  Оператор разности
        @param  right - Вектор справа
        @return Вектор-результат разности
    */
    Vector<T> operator-(const Vector<T> & right) const
    {
        assert(this->size() == right.size());

        Vector<T> result(this->size());

        for (size_t i = 0; i < this->size(); ++i)
            result[i] = this->data()[i] - right[i];

        return result;
    }

    /*!
        @brief  Оператор разности с числом
        @param  num - Число справа
        @return Вектор-результат разности
    */
    Vector<T> operator-(double num) const
    {
        Vector<T> result(this->size());

        for (size_t i = 0; i < this->size(); ++i)
            result[i] = this->data()[i] - num;

        return result;
    }

    Vector<T> operator+(double num) const
    {
        Vector<T> result(this->size());

        for (size_t i = 0; i < this->size(); ++i)
            result[i] = this->data()[i] + num;

        return result;
    }

    Vector<T> operator*(double num) const
    {
        Vector<T> result(this->size());

        for (size_t i = 0; i < this->size(); ++i)
            result[i] = this->data()[i] * num;

        return result;
    }

    Vector<T> operator/(double num) const
    {
        Vector<T> result(this->size());

        for (size_t i = 0; i < this->size(); ++i)
            result[i] = this->data()[i] / num;

        return result;
    }

    /*!
        @brief  Метод берет квадрат у элементов вектора
        @return Вектор, содержащий квадраты исходных элементов
    */
    Vector<T> square()
    {
        return this->operator*( *this );
    }
};

/*!
    @brief  Функция находит сумму элементов вектора
    @param  v - Вектор
    @return Сумму элементов
*/
template<typename T>
double sum(const Vector<T> & v)
{
    double sum = 0;
    for (size_t i = 0; i < v.size(); ++i)
        sum += v[i];

    return sum;
}

/*!
    @brief  Функция берет квадратный корень у элементов вектора
    @param  v - Вектор
    @return Вектор, содержащий квадратные корни исходных элементов
*/
template<typename T>
Vector<T> sqrt(const Vector<T> & v)
{
    Vector<T> result( v.size() );

    for (size_t i = 0; i < v.size(); ++i)
        result[i] = sqrt( v[i] );

    return result;
}

}
