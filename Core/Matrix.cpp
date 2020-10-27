#include "Matrix.h"

Math::Matrix::Matrix(int row_size, int col_size, double value_init)
{
	m_rowSize = row_size;
	m_colSize = col_size;
	m_matrix.resize(row_size);
	for (int i = 0; i < m_matrix.size(); i++)
	{
		m_matrix[i].resize(row_size, value_init);
	}
}

Math::Matrix::Matrix(int row_size, int col_size, vector<vector<double>> value_init)
{
	m_rowSize = row_size;
	m_colSize = col_size;
	m_matrix.resize(row_size);
	m_matrix = value_init;
}

Math::Matrix::Matrix(const Matrix& B)
{
	this->m_colSize = B.getCols();
	this->m_rowSize = B.getRows();
	this->m_matrix = B.m_matrix;
}

Math::Matrix::~Matrix()
{
}

Matrix Math::Matrix::operator+(Matrix& B)
{
	Matrix temp(m_colSize, m_rowSize, 0.0);
	int i;
	int j;
	for (i = 0; i < m_rowSize; i++)
	{
		for (j = 0; j < m_colSize; j++)
		{
			temp(i, j) = this->m_matrix[i][j] + B(i, j);
		}
	}
	return temp;
}

Matrix Math::Matrix::operator-(Matrix& B)
{
	Matrix temp(m_colSize, m_rowSize, 0.0);
	int i;
	int j;
	for (i = 0; i < m_rowSize; i++)
	{
		for (j = 0; j < m_colSize; j++)
		{
			temp(i, j) = this->m_matrix[i][j] - B(i, j);
		}
	}

	return temp;
}

Matrix Math::Matrix::operator*(Matrix& B)
{
	Matrix multip(m_rowSize, B.getCols(), 0.0);
	if (m_colSize == B.getRows())
	{
		int i;
		int j;
		int k;
		double temp = 0.0;
		for (i = 0; i < m_rowSize; i++)
		{
			for (j = 0; j < B.getCols(); j++)
			{
				temp = 0.0;
				for (k = 0; k < m_colSize; k++)
				{
					temp += m_matrix[i][k] * B(k, j);
				}
				multip(i, j) = temp;
			}
		}
		return multip;
	}
	return multip;
}

Matrix Math::Matrix::operator+(double scalar)
{
	Matrix temp(m_rowSize, m_colSize, 0.0);
	int i;
	int j;
	for (i = 0; i < m_rowSize; i++)
	{
		for (j = 0; j < m_colSize; j++)
		{
			temp(i, j) = this->m_matrix[i][j] + scalar;
		}
	}
	return temp;
}

Matrix Math::Matrix::operator-(double scalar)
{
	Matrix temp(m_rowSize, m_colSize, 0.0);
	int i;
	int j;
	for (i = 0; i < m_rowSize; i++)
	{
		for (j = 0; j < m_colSize; j++)
		{
			temp(i, j) = this->m_matrix[i][j] - scalar;
		}
	}
	return temp;
}

Matrix Math::Matrix::operator*(double scalar)
{
	Matrix temp(m_rowSize, m_colSize, 0.0);
	int i;
	int j;
	for (i = 0; i < m_rowSize; i++)
	{
		for (j = 0; j < m_colSize; j++)
		{
			temp(i, j) = this->m_matrix[i][j] * scalar;
		}
	}
	return temp;
}

Matrix Math::Matrix::operator/(double scalar)
{
	Matrix temp(m_rowSize, m_colSize, 0.0);
	int i;
	int j;
	for (i = 0; i < m_rowSize; i++)
	{
		for (j = 0; j < m_colSize; j++)
		{
			temp(i, j) = this->m_matrix[i][j] / scalar;
		}
	}
	return temp;
}

double& Math::Matrix::operator()(const int& rowNo, const int& colNo)
{
	return this->m_matrix[rowNo][colNo];
}

void Math::Matrix::print() const
{
	cout << "Matrix: " << endl;
	for (int i = 0; i < m_rowSize; i++) {
		for (int j = 0; j < m_colSize; j++) {
			cout << "[" << m_matrix[i][j] << "] ";
		}
		cout << endl;
	}
}

int Math::Matrix::getRows() const
{
	return this->m_rowSize;
}

int Math::Matrix::getCols() const
{
	return this->m_colSize;
}