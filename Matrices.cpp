#include "Matrices.h"
#include <iomanip>

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;

		a.resize(rows);

		for (int i = 0; i < rows; i++)
		{
			a[i].resize(cols, 0);
		}

	}

	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), a.getCols());

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}

		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		double sum;

		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), b.getCols());


		for (int k = 0; k < b.getCols(); k++)
		{
			for (int i = 0; i < a.getRows(); i++)
			{
				sum = 0;

				for (int j = 0; j < a.getCols(); j++)
				{
					sum += a(i, j) * b(j, k);
				}

				c(i, k) = sum;
			}
		}

		return c;
	}

	bool operator==(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			return false;
		}

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) >= 0.001)
				{
					return false;
				}
			}
		}

		return true;
	}

	bool operator!=(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			return true;
		}

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) >= 0.001)
				{
					return true;
				}
			}
		}

		return false;
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j) << " ";
			}

			os << " \n";

			os << "\n";
		}

		return os;
	}

    RotationMatrix::RotationMatrix(double theta) : Matrix (2, 2)
    {
        a = {{cos(theta), -sin(theta)}, {sin(theta), cos(theta)}};
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix (2, 2)
    {
        a = {{scale, 0}, {0, scale}};
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix (2, nCols)
    {
        for (int j = 0; j < nCols; j++)
        {
            a[0][j] = xShift;
            a[1][j] = yShift;
        }
    }
}