#pragma once

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "public/Core/Core_utils.h"

namespace Math {
    template<typename T, int rowSize, int colSize>
    class Matrix
    {
    public:
        T m_matrix[rowSize][colSize];
    public:
        Matrix(T value_init)
        {

            for (int i = 0; i < rowSize; ++i)
            {
                for (int j = 0; j < colSize; ++j)
                {
                    m_matrix[i][j] = value_init;
                }
            }
        };
        Matrix(T value_init[rowSize][colSize])
        {
            for (int i = 0; i < rowSize; ++i)
            {
                for (int j = 0; j < colSize; ++j)
                {
                    m_matrix[i][j] = value_init[i][j];
                }
            }
        };
        Matrix(const Matrix& B)
        {
            for (int i = 0; i < rowSize; ++i)
            {
                for (int j = 0; j < colSize; ++j)
                {
                    m_matrix[i][j] = B.m_matrix[i][j];
                }
            }
        };

        // Matrix Operations
        Matrix operator+(const Matrix & B)
        {
            Matrix temp(0);
            int i;
            int j;
            for (i = 0; i < rowSize; i++)
            {
                for (j = 0; j < colSize; j++)
                {
                    temp(i, j) = this->m_matrix[i][j] + B(i, j);
                }
            }
            return temp;
        };
        Matrix operator-(const Matrix & B)
        {
            Matrix temp(0);
            int i;
            int j;
            for (i = 0; i < rowSize; i++)
            {
                for (j = 0; j < colSize; j++)
                {
                    temp(i, j) = this->m_matrix[i][j] - B(i, j);
                }
            }

            return temp;
        };
        Matrix operator*(const Matrix & B)
        {
            Matrix multip(0.0);
            if (colSize == B.getRows())
            {
                int i;
                int j;
                int k;
                double temp = 0.0;
                for (i = 0; i < rowSize; i++)
                {
                    for (j = 0; j < B.getCols(); j++)
                    {
                        temp = 0.0;
                        for (k = 0; k < colSize; k++)
                        {
                            temp += m_matrix[i][k] * B(k, j);
                        }
                        multip(i, j) = temp;
                    }
                }
                return multip;
            }
            return multip;
        };

        //Scalar Operation
        Matrix operator+(T scalar)
        {
            Matrix temp(0);
            for (int i = 0; i < rowSize; ++i)
            {
                for (int j = 0; j < colSize; ++j)
                {
                    temp(i, j) = this->m_matrix[i][j] + scalar;
                }
            }
            return temp;
        };
        Matrix operator-(T scalar)
        {
            Matrix temp(0);

            for (int i = 0; i < rowSize; i++)
            {
                for (int j = 0; j < colSize; j++)
                {
                    temp(i, j) = this->m_matrix[i][j] - scalar;
                }
            }
            return temp;
        };
        Matrix operator*(T scalar)
        {
            Matrix temp(0);
            for (int i = 0; i < rowSize; i++)
            {
                for (int j = 0; j < colSize; j++)
                {
                    temp(i, j) = this->m_matrix[i][j] * scalar;
                }
            }
            return temp;
        };
        Matrix operator/(T scalar)
        {
            ASSERT_MESSAGE(scalar != 0.f, "Can't divide by 0");

            Matrix temp(0);
            int i;
            int j;
            for (i = 0; i < rowSize; i++)
            {
                for (j = 0; j < colSize; j++)
                {
                    temp(i, j) = this->m_matrix[i][j] / scalar;
                }
            }
            return temp;
        };

        //get value of matrix at (row, col)
        T & operator()(int row, int col)
        {
            return this->m_matrix[row][col];
        };

        // debug print
        void print() const
        {
            std::cout << "Matrix: " << std::endl;
            for (int i = 0; i < rowSize; i++) {
                for (int j = 0; j < colSize; j++) {
                    std::cout << "[" << m_matrix[i][j] << "] ";
                }
                std::cout << std::endl;
            }
        };

        int getRows() const
        {
            return colSize;
        };
        int getCols() const
        {
            return rowSize;
        };


    };
}

