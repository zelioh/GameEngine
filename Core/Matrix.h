#pragma once

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

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
                for (int j = 0; i < colSize; ++i)
                {
                    m_matrix[i][j] = value_init[i][j];
                }
            }
        };
        Matrix(const Matrix& B)
        {
            this->m_colSize = B.getCols();
            this->m_rowSize = B.getRows();
            this->m_matrix = B.m_matrix;
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
            Matrix multip(rowSize, B.getCols(), 0.0);
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
        double & operator()(int row, int col)
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

