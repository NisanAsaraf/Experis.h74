#ifndef RATIONAL_HPP
#define RATIONAL_HPP
#include <cstddef>

/**
 * @brief represent a fraction
 *
 */
namespace algebra {
class Rational {
public:
    Rational(int a_numerator, int a_denominator);
    Rational(int a_numerator);
    Rational();

    void print() const; 
    double value();
    Rational& inverse();

    Rational fraction_add(const Rational& a_other);
    void fraction_add_to(const Rational& a_other);
    Rational& operator++();//pre
    Rational operator++(int);//post
    Rational& operator+=(const Rational& a_other);

    Rational operator+(const Rational& a_other);


    Rational fraction_sub(const Rational& a_other);
    void fraction_sub_from(const Rational& a_other);
    Rational& operator--();//pre
    Rational operator--(int);//post
    Rational& operator-=(const Rational& a_other);
    Rational operator-(const Rational& a_other);


    Rational fraction_mul(const Rational& a_other);
    void fraction_mul_with(const Rational& a_other);
    Rational& operator*=(const Rational& a_other);
    Rational operator*(const Rational& a_other);


    Rational fraction_div(const Rational& a_other);
    void fraction_div_by(const Rational& a_other);
    Rational operator/(const Rational& a_other);
    Rational& operator/=(const Rational& a_other);

    int get_numerator() const;
    int get_denominator() const;

    bool less(Rational a_other);

    void f_swap(Rational& a_other);
    void reduce_frac();

private:
    int m_numerator;
    int m_denominator;
};

bool operator<(const Rational& a_lhs, const Rational& a_rhs);
bool operator>(const Rational& a_lhs, const Rational& a_rhs);
bool operator==(const Rational& a_lhs, const Rational& a_rhs);
bool operator!=(const Rational& a_lhs, const Rational& a_rhs);
bool operator<=(const Rational& a_lhs, const Rational& a_rhs);
bool operator>=(const Rational& a_lhs, const Rational& a_rhs);

double sumd(Rational const *a_rational_arr, size_t a_size);
Rational sumf(Rational const *a_rational_arr, size_t a_size);
void swap(Rational *a_this, Rational *a_other);

bool equal_to(Rational a_r1, Rational a_r2);
bool not_equal_to(Rational a_r1, Rational a_r2);

}//namespace algebra
#endif // RATIONAL_HPP
