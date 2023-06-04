#include "String.h"

String() : str_(new char[1]), size_(0), capacity_(1)
{
    str_[0] = '\0';
}

String(const char *str)
{
    size_ = strlen(str);
    capacity_ = size_ + 1;
    str_ = new char[capacity_];
    std::strcpy(str_, str);
}

String(const String &other) : size_(other.size_), capacity_(other.capacity_), str_(new char[other.capacity_])
{
    std::strcpy(str_, other.str_);
}

~String()
{
    delete[] str_;
}

size_t size() const
{
    return size_;
}

const char *c_str() const
{
    return str_;
}

char &operator[](size_t index)
{
    return str_[index];
}

const char &operator[](size_t index) const
{
    return str_[index];
}

String &operator+=(const String &rhs)
{
    if (size_ + rhs.size_ >= capacity_)
    {
        capacity_ = (size_ + rhs.size_) * 2;
        char *new_str = new char[capacity_];
        std::strcpy(new_str, str_);
        delete[] str_;
        str_ = new_str;
    }
    std::strcat(str_, rhs.str_);
    size_ += rhs.size_;
    return *this;
}

void clear()
{
    delete[] str_;
    str_ = new char[1];
    str_[0] = '\0';
    size_ = 0;
    capacity_ = 1;
}

String &operator=(String other)
{
    swap(other);
    return *this;
}

void swap(String &other)
{
    std::swap(str_, other.str_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

// Relational Operators
friend bool operator<(const String &lhs, const String &rhs)
{
    return std::strcmp(lhs.str_, rhs.str_) < 0;
}

friend bool operator>(const String &lhs, const String &rhs)
{
    return rhs < lhs;
}

friend bool operator<=(const String &lhs, const String &rhs)
{
    return !(lhs > rhs);
}

friend bool operator>=(const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}

friend bool operator==(const String &lhs, const String &rhs)
{
    return std::strcmp(lhs.str_, rhs.str_) == 0;
}

friend bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

friend std::ostream &operator<<(std::ostream &os, const String &str)
{
    os << str.str_;
    return os;
}

friend std::istream &operator>>(std::istream &is, String &str)
{
    std::string buffer;
    std::getline(is, buffer);
    str = String(buffer.c_str());
    return is;
}

// Arithmetic Operators
friend String operator+(String lhs, const String &rhs)
{
    lhs += rhs;
    return lhs;
}