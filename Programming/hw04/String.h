#include <cstring>
#include <iostream>
#include <cassert>
#include <sstream>

class String {
public:
    String();
    String(const char* str);
    String(const String& other);
    ~String();

    size_t size() const;
    const char* c_str() const;
    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    String& operator+=(const String& rhs);
    String& operator=(String other);
    void clear();
    void swap(String& other);

    friend bool operator<(const String &lhs, const String &rhs);
    friend bool operator>(const String &lhs, const String &rhs);
    friend bool operator<=(const String &lhs, const String &rhs);
    friend bool operator>=(const String &lhs, const String &rhs);
    friend bool operator==(const String &lhs, const String &rhs);
    friend bool operator!=(const String &lhs, const String &rhs);

    friend std::ostream& operator<<(std::ostream &os, const String &str);
    friend std::istream& operator>>(std::istream &is, String &str);

    friend String operator+(String lhs, const String& rhs);

private:
    char* str_;
    size_t size_;
    size_t capacity_;
};
