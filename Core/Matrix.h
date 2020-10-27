#pragma once

#include "Vector4F.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace Math;
using namespace std;

namespace Math {
	class Matrix
	{
	public:
        int m_rowSize;
        int m_colSize;
        vector<vector<double> > m_matrix;
    public:
        Matrix(int row_size, int col_size, double value_init);
        Matrix(int row_size, int col_size, vector<vector<double>> value_init);
        Matrix(const Matrix&);
        ~Matrix();

        // Matrix Operations
        Matrix operator+(Matrix&);
        Matrix operator-(Matrix&);
        Matrix operator*(Matrix&);

        //Scalar Operation
        Matrix operator+(double);
        Matrix operator-(double);
        Matrix operator*(double);
        Matrix operator/(double);

        //get value of matrix at (row, col)
        double& operator()(const int&, const int&);

        // debug print
        void print() const;

        int getRows() const;
        int getCols() const;


	};
}

