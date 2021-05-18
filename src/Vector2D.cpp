#include "Vector2D.h"

Vector2D::Vector2D() : x_{0}, y_{0}
{
}

Vector2D::Vector2D(float x, float y) : x_{x}, y_{y}
{
}

Vector2D &Vector2D::Add(const Vector2D &other)
{
    x_ += other.x_;
    y_ += other.y_;

    return *this;
}

Vector2D &Vector2D::Subtract(const Vector2D &other)
{
    x_ -= other.x_;
    y_ -= other.y_;

    return *this;
}

Vector2D &Vector2D::Multiply(const Vector2D &other)
{
    x_ *= other.x_;
    y_ *= other.y_;

    return *this;
}

Vector2D &Vector2D::Divide(const Vector2D &other)
{
    x_ /= other.x_;
    y_ /= other.y_;

    return *this;
}

// Operator Overloads
// friend Vector2D &operator+(Vector2D &v1, const Vector2D &v2);
// friend Vector2D &operator-(Vector2D &v1, const Vector2D &v2);
// friend Vector2D &operator*(Vector2D &v1, const Vector2D &v2);
// friend Vector2D &operator/(Vector2D &v1, const Vector2D &v2);

Vector2D Vector2D::operator+(const Vector2D &other)
{
    return Vector2D(x_ + other.x_, y_ + other.y_);
}

Vector2D Vector2D::operator-(const Vector2D &other)
{
    return Vector2D(x_ - other.x_, y_ - other.y_);
}

Vector2D Vector2D::operator*(const Vector2D &other)
{
    return Vector2D(x_ * other.x_, y_ * other.y_);
}

Vector2D Vector2D::operator/(const Vector2D &other)
{
    return Vector2D(x_ / other.x_, y_ / other.y_);
}

Vector2D &Vector2D::operator+=(const Vector2D &other)
{
    return this->Add(other);
}

Vector2D &Vector2D::operator-=(const Vector2D &other)
{
    return this->Subtract(other);
}

Vector2D &Vector2D::operator*=(const Vector2D &other)
{
    return this->Multiply(other);
}

Vector2D &Vector2D::operator/=(const Vector2D &other)
{
    return this->Divide(other);
}

Vector2D &Vector2D::operator*(const int &i)
{
    this->x_ *= i;
    this->y_ *= i;
    
    return *this;
}

Vector2D &Vector2D::operator-()
{
    this->x_ = -(this->x_);
    this->y_ = -(this->y_);

    return *this;
}

Vector2D &Vector2D::Zero()
{
    this->x_ = 0;
    this->y_ = 0;

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vec)
{
    stream << "(" << vec.x_ << ", " << vec.y_ << ")";
    return stream;
}

