#include <iostream>
#include <cstring>
#include <iomanip>
#include "matrix.h"

Matrix::Matrix (int rows, int cols) : rows_ (rows), cols_ (cols)
{
	data_ = new BigFraction* [rows_];

	for (int i = 0; i < rows_; ++i)
	{
		data_[i] = new BigFraction[cols_];
	}
}
Matrix::Matrix (const Matrix& other)
{
	rows_ = other.rows_;
	cols_ = other.cols_;

	data_ = new BigFraction * [rows_];

	for (int i = 0; i < rows_; ++i)
	{
		data_[i] = new BigFraction[cols_];
	}

	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j)
		{
			data_[i][j] = other.data_[i][j];
		}
	}
}
Matrix::Matrix (Matrix&& other) noexcept
{
	rows_ = other.rows_;
	other.rows_ = 0;

	cols_ = other.cols_;
	other.cols_ = 0;

	data_ = other.data_;
	other.data_ = nullptr;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		for (size_t i = 0; i < rows_; ++i)
		{
			delete[] data_[i];
		}

		delete[] data_;

		rows_ = other.rows_;
		cols_ = other.cols_;

		data_ = new BigFraction*[rows_];

		for (size_t i = 0; i < rows_; ++i)
		{
			data_[i] = new BigFraction[cols_];
		}

		for (size_t i = 0; i < rows_; ++i)
		{
			for (size_t j = 0; j < cols_; ++j)
			{
				data_[i][j] = other.data_[i][j];
			}
		}
	}

	return *this;
}
Matrix& Matrix::operator=(Matrix&& other) noexcept
{
	if (this != &other)
	{
		std::swap (rows_, other.rows_);
		std::swap (cols_, other.cols_);
		std::swap (data_, other.data_);
	}

	return *this;
}

Matrix Matrix::operator-() const
{
	Matrix result(rows_, cols_);

	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j)
		{
			result (i, j) = -data_[i][j];
		}
	}

	return result;
}
Matrix& Matrix::operator*= (const Matrix& other)
{
	if (cols_ == 1 && rows_ == 1) {
		
		BigFraction coef = data_[0][0];
		*this = other;

		for (size_t i = 0; i < rows_; ++i)
		{
			for (size_t j = 0; j < cols_; ++j)
			{
				data_[i][j] *= coef;
			}
		}
		return *this;
	}
	else if (other.rows_ == 1 && other.cols_ == 1)
	{
		BigFraction coef = other.data_[0][0];

		for (size_t i = 0; i < rows_; ++i)
		{
			for (size_t j = 0; j < cols_; ++j)
			{
				data_[i][j] *= coef;
			}
		}
		return *this;
	}

	if (cols_ != other.rows_)
	{
		throw "error";
	}

	size_t rows = rows_;
	size_t cols = other.cols_;

	Matrix result = zeros (rows, cols);

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			for (size_t k = 0; k < cols_; ++k)
			{
				result(i, j) += data_[i][k] * other.data_[k][j];
			}
		}
	}

	*this = std::move(result);

	return *this;
}

Matrix& Matrix::operator/= (const Matrix& other)
{
	if (cols_ != other.rows_)
	{
		throw "error";
	}

	*this *= other.inv();

	return *this;
}
Matrix& Matrix::operator+= (const Matrix& other)
{
	if (cols_ != other.cols_ || rows_ != other.rows_)
	{
		throw "error";
	}

	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j)
		{
			data_[i][j] += other.data_[i][j];
		}
	}

	return *this;
}
Matrix& Matrix::operator-= (const Matrix& other)
{
	if (cols_ != other.cols_ || rows_ != other.rows_)
	{
		throw "error";
	}

	*this += -other;

	return *this;
}
Matrix& Matrix::operator^= (const Matrix& other)
{
	if (cols_ != other.cols_ || rows_ != other.rows_)
	{
		throw "error";
	}

	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j)
		{
			data_[i][j] *= other.data_[i][j];
		}
	}

	return *this;
}
Matrix& Matrix::operator|= (const Matrix& other)
{
	if (cols_ != other.cols_ || rows_ != other.rows_)
	{
		throw "error";
	}

	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j)
		{
			data_[i][j] /= other.data_[i][j];
		}
	}

	return *this;
}

size_t Matrix::rows () const
{
	return rows_;
}
size_t Matrix::cols () const
{
	return cols_;
}

BigFraction& Matrix::operator()(size_t i, size_t j)
{
	return data_[i][j];
}
BigFraction Matrix::operator()(size_t i, size_t j) const
{
	return data_[i][j];
}

std::ostream& operator<<(std::ostream& out, const Matrix& M)
{
	int rows = M.rows();
	int cols = M.cols();

	if (rows == 1 && cols == 1)
	{
		out << M (0, 0);
		return out;
	}

	int* lens = new int[cols]{0};
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			int len = M (i, j).len ();
			if (lens[j] < len)
			{
				lens[j] = len;
			}
		}
	}

	out << "[" << std::endl;
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			if (j != 0)
			{
				out << " ";
			}
			out << std::setw(lens[j]) << to_string (M (i, j));
		}

		out << std::endl;
	}
	out << "]";

	delete[] lens;
	return out;
}

Matrix operator* (const Matrix& left, const Matrix& right)
{
	Matrix tmp (left);
	return tmp *= right;
}
Matrix operator/ (const Matrix& left, const Matrix& right)
{
	Matrix tmp (left);
	return tmp /= right;
}
Matrix operator^ (const Matrix& left, const Matrix& right)
{
	Matrix tmp (left);
	return tmp ^= right;
}
Matrix operator| (const Matrix& left, const Matrix& right)
{
	Matrix tmp (left);
	return tmp |= right;
}
Matrix operator+ (const Matrix& left, const Matrix& right)
{
	Matrix tmp (left);
	return tmp += right;
}
Matrix operator- (const Matrix& left, const Matrix& right)
{
	Matrix tmp (left);
	return tmp -= right;
}

Matrix Matrix::transpose () const
{
	Matrix result (cols_, rows_);

	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j)
		{
			result(j, i) = data_[i][j];
		}
	}

	return result;
}
Matrix Matrix::inv () const
{
	if (cols_ != rows_)
	{
		throw "error";
	}

	size_t n = rows_;
	Matrix A(*this);
	Matrix B = eye (n);

	int nozero = 0;
	for (int j = 0; j < n; ++j)
	{
		nozero = j;
		while (A.data_[nozero][j] == BigFraction(0))
		{
			++nozero;
			if (nozero >= n)
			{
				throw "error";
			}
		}

		if (nozero != j)
		{
			std::swap (A.data_[j], A.data_[nozero]);
			std::swap (B.data_[j], B.data_[nozero]);
		}

		BigFraction diag = A.data_[j][j];
		for (int k = 0; k < n; ++k)
		{
			if (k >= j)
			{
				A.data_[j][k] /= diag;
			}
			B.data_[j][k] /= diag;
		}

		for (int i = 0; i < n; ++i)
		{
			if (i != j)
			{
				BigFraction coef = A.data_[i][j];
				for (int k = 0; k < n; ++k)
				{
					if (k >= j)
					{
						A.data_[i][k] -= A.data_[j][k] * coef;
					}
					B.data_[i][k] -= B.data_[j][k] * coef;
				}
			}
		}
	}

	return B;
}
Matrix Matrix::det () const
{
	if (cols_ != rows_)
	{
		throw "error";
	}

	size_t n = rows_;
	Matrix A(*this);
	BigFraction det(1);

	int nozero;
	for (int j = 0; j < n; ++j)
	{
		nozero = j;
		while (A.data_[nozero][j] == BigFraction(0))
		{
			++nozero;
			if (nozero >= n)
			{
				return Matrix(0);
			}
		}

		if (nozero != j)
		{
			det *= BigFraction(-1);
			std::swap (A.data_[j], A.data_[nozero]);
		}

		det *= A.data_[j][j];
		for (int i = j + 1; i < n; ++i)
		{
			BigFraction coef = A.data_[i][j] / A.data_[j][j];
			for (int k = j; k < n; ++k)
			{
				A.data_[i][k] -= A.data_[j][k] * coef;
			}
		}
	}

	return Matrix(det);
}
Matrix Matrix::sum () const
{
	BigFraction result(0);

	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j)
		{
			result += data_[i][j];
		}
	}

	return Matrix(result);
}
Matrix Matrix::prod () const
{
	BigFraction result(1);
	
	for (size_t i = 0; i < rows_; ++i)
	{
		for (size_t j = 0; j < cols_; ++j)
		{
			result *= data_[i][j];
		}
	}

	return Matrix(result);
}

Matrix min (const Matrix& A, const Matrix& B)
{
	if (A.cols() != B.cols() || A.rows() != B.rows())
	{
		throw "error";
	}

	Matrix result (A.rows(), A.cols());

	for (size_t i = 0; i < A.rows (); ++i)
	{
		for (size_t j = 0; j < A.cols(); ++j)
		{
			result(i, j) = min(A(i, j), B(i, j));
		}
	}

	return result;
}
Matrix max (const Matrix& A, const Matrix& B)
{
	if (A.cols () != B.cols () || A.rows () != B.rows ())
	{
		throw "error";
	}

	Matrix result (A.rows (), A.cols ());

	for (size_t i = 0; i < A.rows (); ++i)
	{
		for (size_t j = 0; j < A.cols (); ++j)
		{
			result (i, j) = max (A (i, j), B (i, j));
		}
	}

	return result;
}

Matrix vcat (const Matrix& left, const Matrix& right)
{
	if (left.cols () != right.cols ())
	{
		throw "error";
	}

	size_t new_rows = left.rows () + right.rows ();

	Matrix result(left.rows() + right.rows(), left.cols());

	for (size_t j = 0; j < left.cols (); ++j)
	{
		for (size_t i = 0; i < left.rows (); ++i)
		{
			result (i, j) = left (i, j);
		}

		for (size_t i = 0; i < right.rows(); ++i)
		{
			result (left.rows() + i, j) = right (i, j);
		}
	}

	return result;
}
Matrix hcat (const Matrix& left, const Matrix& right)
{
	if (left.rows () != right.rows ())
	{
		throw "error";
	}

	size_t new_cols = left.cols () + right.cols ();

	Matrix result (left.rows (), left.cols () + right.cols());

	for (size_t i = 0; i < left.rows (); ++i)
	{
		for (size_t j = 0; j < left.cols (); ++j)
		{
			result (i, j) = left (i, j);
		}

		for (size_t j = 0; j < right.cols(); ++j)
		{
			result (i, left.cols () + j) = right (i, j);
		}
	}

	return result;
}

Matrix linspace (const BigFraction& first, const BigFraction& last, int size)
{
	Matrix result (1, size);

	BigFraction value = first;
	for (size_t i = 0; i < size; ++i)
	{
		result (0, i) = value++;
	}

	return result;
}
Matrix zeros (int rows, int cols)
{
	Matrix result (rows, cols);

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			result(i, j) = BigFraction ();
		}
	}

	return result;
}

Matrix ones (int rows, int cols)
{
	Matrix result (rows, cols);

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			result (i, j) = BigFraction (1);
		}
	}

	return result;
}

Matrix eye (int size)
{
	Matrix result = zeros(size, size);

	for (size_t i = 0; i < size; ++i)
	{
		result(i, i) = BigFraction(1);
	}

	return result;
}

Matrix::~Matrix ()
{
	for (size_t i = 0; i < rows_; ++i)
	{
		delete[] data_[i];
	}

	delete[] data_;
}