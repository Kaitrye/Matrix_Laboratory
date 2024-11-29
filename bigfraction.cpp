#include "bigfraction.h"

BigFraction min (const BigFraction& left, const BigFraction& right)
{
	return BigFraction (min (left.num_ * right.denom_, right.num_ * left.denom_), left.denom_ * right.denom_);
}
BigFraction max (const BigFraction& left, const BigFraction& right)
{
	return BigFraction (max (left.num_ * right.denom_, right.num_ * left.denom_), left.denom_ * right.denom_);
}

std::ostream& operator<<(std::ostream& out, const BigFraction& A)
{
	out << to_string (A.num_);

	if (A.denom_ != BigInteger (1))
	{
		out << "/" << to_string (A.denom_);
	}

	return out;
}

BigFraction operator*(const BigFraction& left, const BigFraction& right)
{
	BigFraction tmp (left);
	return tmp *= right;
}
BigFraction operator+(const BigFraction& left, const BigFraction& right)
{
	BigFraction tmp (left);
	return tmp += right;
}
BigFraction operator-(const BigFraction& left, const BigFraction& right)
{
	BigFraction tmp (left);
	return tmp -= right;
}
BigFraction operator/(const BigFraction& left, const BigFraction& right)
{
	BigFraction tmp (left);
	return tmp /= right;
}

std::string to_string (const BigFraction& x)
{
	std::string result = "";
	result += to_string (x.num_);
	
	if (x.denom_ != BigInteger(1)) 
	{
		result += "/" + to_string (x.denom_);
	}

	return result;
}

bool operator==(const BigFraction& left, const BigFraction& right)
{
	return left.is_equal (right);
}
bool operator!=(const BigFraction& left, const BigFraction& right)
{
	return !(left == right);
}
bool operator<(const BigFraction& left, const BigFraction& right)
{
	return left.is_less (right);
}
bool operator<=(const BigFraction& left, const BigFraction& right)
{
	return (left < right) || (left == right);
}
bool operator>(const BigFraction& left, const BigFraction& right)
{
	return right < left;
}
bool operator>=(const BigFraction& left, const BigFraction& right)
{
	return !(left < right);
}
