#include "rational.hpp"

#include <cstdio>
#include <cassert>

namespace algebra
{
int gcd(int a, int b);

Rational::Rational(int a_numerator, int a_denominator)
{

    assert(a_denominator != 0);

    //this handles all cases if both are negative or just one of them
    if(a_denominator < 0 )
    {
        a_denominator *= -1;
        a_numerator *= -1;
    }

    m_numerator = a_numerator;
    m_denominator = a_denominator;

    this->reduce_frac();
}

Rational::Rational(int a_numerator)
{
    m_numerator = a_numerator;
    m_denominator = 1;
}

Rational::Rational()
{
    m_numerator = 0;
    m_denominator = 1;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------- */

int Rational::get_numerator() const
{
    return this->m_numerator;
}


int Rational::get_denominator() const
{
    return this->m_denominator;
}

void Rational::f_swap(Rational& a_other)
{
    Rational tmp = *this;
    *this = a_other;
    a_other = tmp;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------- */

Rational& Rational::operator++()
{//pre
    m_numerator += m_denominator;
    return *this;
}

Rational Rational::operator++(int)
{//post
    Rational original = *this;
    m_numerator += m_denominator;
    return original;
}

Rational Rational::operator+(const Rational& a_other)
{
    Rational result = *this; 
    result += a_other; 
    return result;
}

Rational& Rational::operator+=(const Rational& a_other)
{
    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = (this->m_numerator*a_other.m_denominator) + (a_other.m_numerator*this->m_denominator);

    this->m_denominator = common_denominator;
    this->m_numerator = new_numerator;
    this->reduce_frac();
    return *this;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------- */

Rational& Rational::operator--()
{//pre
    m_numerator -= m_denominator;
    return *this;
}

Rational Rational::operator--(int)
{//post
    Rational original = *this;
    m_numerator -= m_denominator;
    return original;
}

Rational Rational::operator-(const Rational& a_other)
{
    Rational result = *this; 
    result -= a_other; 
    return result;
}

Rational& Rational::operator-=(const Rational& a_other)
{
    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = (this->m_numerator*a_other.m_denominator) - (a_other.m_numerator*this->m_denominator);

    this->m_denominator = common_denominator;
    this->m_numerator = new_numerator;
    this->reduce_frac();
    return *this;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------- */    

Rational& Rational::operator*=(const Rational& a_other)
{
    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = this->m_numerator*a_other.m_numerator;

    this->m_denominator = common_denominator;
    this->m_numerator = new_numerator;

    this->reduce_frac();
    return *this;
}

Rational Rational::operator*(const Rational& a_other)
{
    Rational result = *this; 
    result *= a_other; 
    return result;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------- */ 
   
Rational& Rational::operator/=(const Rational& a_other)
{
    int new_denominator = this->m_denominator * a_other.m_numerator;
    int new_numerator = this->m_numerator*a_other.m_denominator;

    this->m_denominator = new_denominator;
    this->m_numerator = new_numerator;
    this->reduce_frac();
    return *this;
}

Rational Rational::operator/(const Rational& a_other)
{
    Rational result = *this; 
    result /= a_other; 
    return result;
}

/* --------------------------------------------------------------------------------------------------------------------------------------------- */  

bool operator<(const Rational& a_lhs, const Rational& a_rhs)
{
    return ((a_lhs.get_numerator() * a_rhs.get_denominator()) < (a_rhs.get_numerator() * a_lhs.get_denominator()));
}

bool operator>(const Rational& a_lhs, const Rational& a_rhs)
{
    return ((a_lhs.get_numerator() * a_rhs.get_denominator()) > (a_rhs.get_numerator() * a_lhs.get_denominator()));
}

bool operator==(const Rational& a_lhs, const Rational& a_rhs) 
{
    return ((a_lhs.get_numerator() * a_rhs.get_denominator()) == (a_rhs.get_numerator() * a_lhs.get_denominator()));
}

bool operator!=(const Rational& a_lhs, const Rational& a_rhs)
{
    return !(a_lhs == a_rhs);
}

bool operator<=(const Rational& a_lhs, const Rational& a_rhs)
{
    return (a_lhs < a_rhs) || (a_lhs == a_rhs);
}

bool operator>=(const Rational& a_lhs, const Rational& a_rhs)
{
    return (a_lhs > a_rhs) || (a_lhs == a_rhs);
}

int compare(const Rational& a_lhs, const Rational& a_rhs)
{
    if(a_lhs == a_rhs)
    {
        return 0;
    }
    else if(a_lhs > a_rhs)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

 /* --------------------------------------------------------------------------------------------------------------------------------------------- */     

void Rational::print() const
{
    printf("%d/%d\n", m_numerator, m_denominator);
}

double Rational::value()
{
    return (double)m_numerator/m_denominator;
}

bool Rational::less(Rational a_other)
{
    return this->value() < a_other.value();
}

Rational& Rational::inverse()
{
    assert(m_numerator != 0);
    
    int tmp = m_numerator;
    m_numerator = m_denominator;
    m_denominator = tmp;
    
    return *this;
}

void swap(Rational *a_this, Rational *a_other)
{
    assert(a_this && a_other);
    Rational tmp = *a_this;
    *a_this = *a_other;
    *a_other = tmp;
}

Rational Rational::fraction_add(const Rational& a_other)
{

    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = (this->m_numerator*a_other.m_denominator) + (a_other.m_numerator*this->m_denominator);

    Rational result(new_numerator, common_denominator);
    result.reduce_frac();
    return result;
}

void Rational::fraction_add_to(const Rational& a_other)
{
    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = (this->m_numerator*a_other.m_denominator) + (a_other.m_numerator*this->m_denominator);

    this->m_denominator = common_denominator;
    this->m_numerator = new_numerator;
    this->reduce_frac();
}

Rational Rational::fraction_sub(const Rational& a_other)
{

    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = (this->m_numerator*a_other.m_denominator) - (a_other.m_numerator*this->m_denominator);

    Rational result(new_numerator, common_denominator);
    result.reduce_frac();
    return result;
}

void Rational::fraction_sub_from(const Rational& a_other)
{

    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = (this->m_numerator*a_other.m_denominator) - (a_other.m_numerator*this->m_denominator);

    this->m_denominator = common_denominator;
    this->m_numerator = new_numerator;

    this->reduce_frac();
}

Rational Rational::fraction_mul(const Rational& a_other)
{

    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = this->m_numerator*a_other.m_numerator;

    Rational result(new_numerator, common_denominator);
    result.reduce_frac();
    return result;
}

void Rational::fraction_mul_with(const Rational& a_other)
{

    int common_denominator = this->m_denominator * a_other.m_denominator;
    int new_numerator = this->m_numerator*a_other.m_numerator;

    this->m_denominator = common_denominator;
    this->m_numerator = new_numerator;

    this->reduce_frac();
}

Rational Rational::fraction_div(const Rational& a_other)
{

    int new_denominator = this->m_denominator * a_other.m_numerator;
    int new_numerator = this->m_numerator*a_other.m_denominator;

    Rational result(new_numerator, new_denominator);
    result.reduce_frac();
    return result;
}

void Rational::fraction_div_by(const Rational& a_other)
{

    int new_denominator = this->m_denominator * a_other.m_numerator;
    int new_numerator = this->m_numerator*a_other.m_denominator;

    this->m_denominator = new_denominator;
    this->m_numerator = new_numerator;
    this->reduce_frac();
}

void Rational::reduce_frac()
{
    int common_div = gcd(m_numerator, m_denominator);
    while (common_div != 1) {
        m_numerator /= common_div;
        m_denominator /= common_div;
        common_div = gcd(m_numerator, m_denominator);
    }
}

double sumd(Rational const *a_rational_arr, size_t a_size)
{

    Rational sum = sumf(a_rational_arr, a_size);

    return sum.value();
}

Rational sumf(Rational const *a_rational_arr, size_t a_size)
{
    Rational sum;
    for (size_t i = 0; i < a_size; i++){
        sum.fraction_add_to(a_rational_arr[i]);
    }
    sum.reduce_frac();
    return sum;
}

bool equal_to(Rational a_r1, Rational a_r2)
{
    return ( (a_r1.get_numerator() == a_r2.get_numerator()) && (a_r1.get_denominator() == a_r2.get_denominator()) );
}

bool not_equal_to(Rational a_r1, Rational a_r2)
{
    return !equal_to(a_r1, a_r2);
}

int gcd(int a, int b) 
{
    if (b == 0) 
    {
        return a;
    } 
    else 
    {
        return gcd(b, a % b);
    }
}

}//namespace algebra