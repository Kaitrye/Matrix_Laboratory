#include "biginteger.h"

#ifndef BIGFRACTION_
#define BIGFRACTION_

class BigFraction
{
	BigInteger num_;
	BigInteger denom_;

	void normalize ()
	{
		if (denom_ < BigInteger (0))
		{
			num_ = -num_;
			denom_ = -denom_;
		}

		BigInteger gcd = GCD (num_.abs(), denom_.abs());

		num_ /= gcd;
		denom_ /= gcd;
	}

public:
	BigFraction () : num_(), denom_(1) {}
	BigFraction (std::string str) : num_ (str), denom_ (1) {}

	BigFraction (unsigned short num) : num_(num), denom_(1) {}
	BigFraction (signed short num) : num_(num), denom_(1) {}
	BigFraction (unsigned int num) : num_ (num), denom_ (1) {}
	BigFraction (signed int num) : num_ (num), denom_ (1) {}
	BigFraction (unsigned long num) : num_ (num), denom_ (1) {}
	BigFraction (signed long num) : num_ (num), denom_ (1) {}
	BigFraction (unsigned long long num) : num_ (num), denom_ (1) {}
	BigFraction (signed long long num) : num_ (num), denom_ (1) {}

	BigFraction (const BigInteger& up, const BigInteger& down) : num_(up), denom_(down) 
	{
		normalize ();
	}
	BigFraction (const BigFraction& other) : num_ (other.num_), denom_ (other.denom_) {}
	BigFraction (BigFraction&& other) noexcept : num_ (std::move (other.num_)), denom_ (std::move (other.denom_)) {}
	
	BigFraction operator-() const
	{
		BigFraction tmp (*this);
		tmp.num_ = -num_;

		return tmp;
	}
	BigFraction operator+() const
	{
		return *this;
	}

	BigFraction& operator=(const BigFraction& other)
	{
		if (this != &other)
		{
			num_ = other.num_;
			denom_ = other.denom_;
		}

		return *this;
	}
	BigFraction& operator=(BigFraction&& other) noexcept
	{
		if (this != &other)
		{
			num_ = std::move(other.num_);
			denom_ = std::move(other.denom_);
		}

		return *this;
	}

	BigFraction& operator+=(const BigFraction& other)
	{
		num_ = num_ * other.denom_ + other.num_ * denom_;
		denom_ = denom_ * other.denom_;

		normalize();

		return *this;
	}
	BigFraction& operator-=(const BigFraction& other)
	{
		*this += -other;

		return *this;
	}
	BigFraction& operator*=(const BigFraction& other)
	{
		num_ *= other.num_;
		denom_ *= other.denom_;

		normalize ();

		return *this;
	}
	BigFraction& operator/=(const BigFraction& other)
	{
		*this *= BigFraction (other.denom_, other.num_);

		return *this;
	}

	BigFraction& operator++()
	{
		*this += BigFraction (1);
		normalize();

		return *this;
	}
	BigFraction operator++(int)
	{
		BigFraction tmp (*this);
		*this += BigFraction (1);
		normalize ();

		return tmp;
	}
	BigFraction& operator--()
	{
		*this -= BigFraction (1);
		normalize ();

		return *this;
	}
	BigFraction operator--(int)
	{
		BigFraction tmp (*this);
		*this -= BigFraction (1);
		normalize ();

		return tmp;
	}

	operator BigInteger()
	{
		return num_;
	}

	operator int ()
	{
		return num_;
	}

	int len ()
	{
		return to_string(*this).size();
	}

	bool is_equal (const BigFraction& other) const
	{
		return num_ == other.num_ && denom_ == other.denom_;
	}
	bool is_less (const BigFraction& other) const
	{
		return num_ * other.denom_ < other.num_* denom_;
	}

	friend BigFraction min (const BigFraction& left, const BigFraction& right);
	friend BigFraction max (const BigFraction& left, const BigFraction& right);
	friend std::ostream& operator<<(std::ostream& out, const BigFraction& A);
	friend std::string to_string (const BigFraction& x);
};

BigFraction operator*(const BigFraction& left, const BigFraction& right);
BigFraction operator+(const BigFraction& left, const BigFraction& right);
BigFraction operator-(const BigFraction& left, const BigFraction& right);
BigFraction operator/(const BigFraction& left, const BigFraction& right);

bool operator==(const BigFraction& left, const BigFraction& right);
bool operator!=(const BigFraction& left, const BigFraction& right);
bool operator<(const BigFraction& left, const BigFraction& right);
bool operator<=(const BigFraction& left, const BigFraction& right);
bool operator>(const BigFraction& left, const BigFraction& right);
bool operator>=(const BigFraction& left, const BigFraction& right);

#endif // BIGFRACTION_