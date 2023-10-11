#pragma once
#include "vector.h"
#include <cassert>

namespace MathNS
{

/*!
    @brief Класс матрицы
*/
template <typename T>
class Matrix
{
public:
    /*!
        @brief  Конструктор
        @param  row - Количество строк
        @param  col - Количество столбцов
    */
    Matrix( size_t row, size_t col ) : row( row ), col( col ),
        data( row, Vector<T>(col) ) {}

    /*!
        @brief  Оператор доступа к элементу матрицы
        @param  i - Индекс строки
        @param  j - Индекс столбца
        @return Элемент матрицы (i, j)
    */
    T& operator()(size_t i, size_t j)
    {
        return data[i][j];
    }

    /*!
        @brief  Оператор доступа к элементу матрицы (для константных объектов)
        @param  i - Индекс строки
        @param  j - Индекс столбца
        @return Элемент матрицы (i, j)
    */
    const T& operator()(size_t i, size_t j) const
    {
        return data[i][j];
    }

    /*!
        @brief  Оператор присваивания
        @param  right - Матрица справа
        @return Матрицу после операции присваивания
    */
    Matrix<T> & operator=( const Matrix<T> & right )
    {
        assert( row == right.rows() && col == right.cols() && "dimenstions must agree" );

        for(size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < col; ++j)
                data[i][j] = right(i, j);

        return *this;
    }

    /*!
        @brief  Оператор умножения с матрицей
        @param  right - Матрица справа
        @return Матрицу-результат умножения
    */
    Matrix<T> operator*( const Matrix<T> & right )
    {
        assert( col == right.rows() && "dimenstions must agree" );

        Matrix<T> result( row, right.cols() );

        for(size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < right.cols(); ++j)
                result(i, j) = 0;

        for(size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < right.cols(); ++j)
                for(size_t k = 0; k < col; ++k)
                {
                    result(i, j) += data[i][k] * right(k, j);
                }

        return result;
    }

    /*!
        @brief  Оператор умножения с вектором
        @param  right - Вектор справа
        @return Вектор-результат умножения
    */
    Vector<T> operator*( const Vector<T> & right )
    {
        assert( col == right.size() && "dimenstions must agree" );

        Vector<T> result( row );

        for(size_t i = 0; i < row; ++i)
            result[i] = 0;

        for(size_t i = 0; i < row; ++i)
            for(size_t k = 0; k < col; ++k)
            {
                result[i] += data[i][k] * right[k];
            }

        return result;
    }

    /*!
        @brief  Оператор суммы
        @param  right - Матрица справа
        @return Матрицу-результат суммы
    */
    Matrix<T> operator+( const Matrix<T> & right )
    {
        assert( row == right.rows() && col == right.cols() && "dimenstions must agree" );

        Matrix<T> result(row, col);

        for(size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < col; ++j)
            {
                result(i, j) = data[i][j] + right(i, j);
            }

        return result;
    }

    /*!
        @brief  Оператор разности
        @param  right - Матрица справа
        @return Матрицу-результат разности
    */
    Matrix<T> operator-( const Matrix<T> & right )
    {
        assert( row == right.rows() && col == right.cols() && "dimenstions must agree" );

        Matrix<T> result(row, col);

        for(size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < col; ++j)
            {
                result(i, j) = data[i][j] - right(i, j);
            }

        return result;
    }

    /*!
        @brief  Метод возвращает столбец по индексу
        @param  col - Индекс столбца
        @return Необходимый вектор-столбец
    */
    Vector<T> getCol( size_t colIndex ) const
    {
        Vector<T> result( row );

        for(size_t i = 0; i < row; ++i)
            result[i] = data[i][colIndex];

        return result;
    }

    /*!
        @brief  Метод возвращает строку по индексу
        @param  row - Индекс строки
        @return Необходимый вектор-строку
    */
    const Vector<T> & getRow( size_t rowIndex ) const
    {
        return data[rowIndex];
    }

    /*!
        @brief  Метод устанавливает столбец матрицы по указанному индексу
        @param           col - Индекс столбца
        @param  columnVector - Вектор-столбец
    */
    void setCol( size_t colIndex, const Vector<T> & columnVector )
    {
        assert( row == columnVector.size() && "dimenstions must agree" );

        for(size_t i = 0; i < row; ++i)
            data[i][colIndex] = columnVector[i];
    }

    void setRow( size_t rowIndex, const Vector<T> & rowVector )
    {
        assert( col == rowVector.size() && "dimenstions must agree" );

        data[rowIndex] = rowVector;
    }

    /*!
        @brief  Метод транспонирует матрицу
        @return Транспонированную матрицу
    */
    Matrix<T> transpose()
    {
        Matrix<T> result(col, row);

        for(size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < col; ++j)
            {
                result(j, i) = data[i][j];
            }

        return result;
    }

    /*!
        @brief  Метод находит обратную матрицу
        @return Обратную матрицу
    */
    Matrix<T> inv()
    {
        assert( row == col && "matrix must be square" );

        Matrix<T> result = *this;


        double temp;

        Matrix<T> E(row, col);

        for(size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < col; ++j)
            {
                if (i == j)
                    E(i, j) = 1;
                else
                    E(i, j) = 0;
            }

        for (size_t k = 0; k < row; k++)
        {
            temp = result(k, k);

            for (size_t j = 0; j < col; j++)
            {
                result(k, j) /= temp;
                     E(k, j) /= temp;
            }

            for (size_t i = k + 1; i < row; i++)
            {
                temp = result(i, k);

                for (size_t j = 0; j < col; j++)
                {
                    result(i, j) -= result(k, j) * temp;
                         E(i, j) -=      E(k, j) * temp;
                }
            }
        }

        for (size_t k = col - 1; k > 0; k--)
        {
            for (int i = k - 1; i >= 0; i--)
            {
                temp = result(i, k);

                for (size_t j = 0; j < col; j++)
                {
                    result(i, j) -= result(k, j) * temp;
                         E(i, j) -=      E(k, j) * temp;
                }
            }
        }

        result = E;

        return result;
    }

    /*!
        @brief  Метод изменяет размерность матрицы
        @param  row - Количество строк
        @param  col - Количество столбцов
    */
    void resize( size_t row, size_t col )
    {
        data.resize( row );
        this->row = row;

        for ( size_t i = 0; i < row; ++i )
            data[i].resize( col );

        this->col = col;
    }

    /*!
        @brief  Метод возвращает количество строк матрицы
        @return Количество строк
    */
    size_t rows() const  { return row; }

    /*!
        @brief  Метод возвращает количество столбцов матрицы
        @return Количество столбцов
    */
    size_t cols() const  { return col; }

private:
                  size_t row; ///< Количество строк
                  size_t col; ///< Количество столбцов
    Vector< Vector<T> > data; ///< Двумерный вектор, хранящий элементы матрицы
};

}
