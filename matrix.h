#include "bigfraction.h"

#ifndef MATRIX_
#define MATRIX_

class Matrix
{
	BigFraction** data_; // данные матрицы.
	int rows_; // число строк.
	int cols_; // число столбцов.

public:
	Matrix (int rows, int cols);
	Matrix () : Matrix(1, 1) 
	{
		data_[0][0] = BigFraction();
	}
	Matrix (std::string str) : Matrix(1, 1)
	{
		data_[0][0] = BigFraction (str);
	}
	Matrix (const BigFraction& num) : Matrix (1, 1)
	{
		data_[0][0] = num;
	}
	Matrix (unsigned short num) : Matrix (1, 1)
	{
		data_[0][0] = BigFraction (num);
	}
	Matrix (signed short num) : Matrix (1, 1)
	{
		data_[0][0] = BigFraction (num);
	}
	Matrix (unsigned int num) : Matrix (1, 1)
	{
		data_[0][0] = BigFraction (num);
	}
	Matrix (signed int num) : Matrix (1, 1)
	{
		data_[0][0] = BigFraction (num);
	}
	Matrix (unsigned long num) : Matrix (1, 1)
	{
		data_[0][0] = BigFraction (num);
	}
	Matrix (signed long num) : Matrix (1, 1)
	{
		data_[0][0] = BigFraction (num);
	}
	Matrix (unsigned long long num) : Matrix (1, 1)
	{
		data_[0][0] = BigFraction (num);
	}
	Matrix (signed long long num) : Matrix (1, 1)
	{
		data_[0][0] = BigFraction (num);
	}

	Matrix (const Matrix&);
	Matrix (Matrix&&) noexcept;

	Matrix& operator= (const Matrix&);
	Matrix& operator= (Matrix&&) noexcept;

	Matrix operator-() const;
	Matrix& operator*= (const Matrix&);
	Matrix& operator/= (const Matrix&);
	Matrix& operator^= (const Matrix&);
	Matrix& operator|= (const Matrix&);
	Matrix& operator+= (const Matrix&);
	Matrix& operator-= (const Matrix&);

	size_t rows () const;
	size_t cols () const;
	BigFraction& operator() (size_t, size_t);
	BigFraction operator()(size_t, size_t) const;

	Matrix transpose () const;
	Matrix inv() const;
	Matrix det() const;
	Matrix sum () const;
	Matrix prod () const;

	operator BigFraction()
	{
		return data_[0][0];
	}

	operator int ()
	{
		return data_[0][0];
	}

	~Matrix ();
};

std::ostream& operator<< (std::ostream&, const Matrix&);

Matrix operator* (const Matrix&, const Matrix&);
Matrix operator/ (const Matrix&, const Matrix&);
Matrix operator^ (const Matrix&, const Matrix&);
Matrix operator| (const Matrix&, const Matrix&);
Matrix operator+ (const Matrix&, const Matrix&);
Matrix operator- (const Matrix&, const Matrix&);

Matrix min (const Matrix&, const Matrix&);
Matrix max (const Matrix&, const Matrix&);

Matrix vcat (const Matrix&, const Matrix&);
Matrix hcat (const Matrix&, const Matrix&);

Matrix linspace (const BigFraction&, const BigFraction&, int);
Matrix zeros (int, int);
Matrix ones (int, int);
Matrix eye (int);

#endif // MATRIX_
