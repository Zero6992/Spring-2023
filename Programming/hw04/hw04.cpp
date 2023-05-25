#include <cstring>
#include <iostream>
#include <cassert>

class String {
public:
    String() : str_(new char[1]), size_(0), capacity_(1) {
        str_[0] = '\0';
    }

    String(const char* str) {
        size_ = strlen(str);
        capacity_ = size_ + 1;
        str_ = new char[capacity_];
        std::strcpy(str_, str);
    }

    String(const String& other) : size_(other.size_), capacity_(other.capacity_), str_(new char[other.capacity_]) {
        std::strcpy(str_, other.str_);
    }

    ~String() {
        delete[] str_;
    }

    size_t size() const {
        return size_;
    }

    const char* c_str() const {
        return str_;
    }

    char& operator[](size_t index) {
        return str_[index];
    }

    const char& operator[](size_t index) const {
        return str_[index];
    }

    String& operator+=(const String& rhs) {
        if (size_ + rhs.size_ >= capacity_) {
            capacity_ = (size_ + rhs.size_) * 2;
            char* new_str = new char[capacity_];
            std::strcpy(new_str, str_);
            delete[] str_;
            str_ = new_str;
        }
        std::strcat(str_, rhs.str_);
        size_ += rhs.size_;
        return *this;
    }

    void clear() {
        delete[] str_;
        str_ = new char[1];
        str_[0] = '\0';
        size_ = 0;
        capacity_ = 1;
    }

    String& operator=(String other) {
        swap(other);
        return *this;
    }

    void swap(String& other) {
        std::swap(str_, other.str_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    friend bool operator<(const String &lhs, const String &rhs) {
        return std::strcmp(lhs.str_, rhs.str_) < 0;
    }

    friend bool operator>(const String &lhs, const String &rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const String &lhs, const String &rhs) {
        return !(lhs > rhs);
    }

    friend bool operator>=(const String &lhs, const String &rhs) {
        return !(lhs < rhs);
    }

    friend bool operator==(const String &lhs, const String &rhs) {
        return std::strcmp(lhs.str_, rhs.str_) == 0;
    }

    friend bool operator!=(const String &lhs, const String &rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream &os, const String &str) {
        os << str.str_;
        return os;
    }

  friend std::istream& operator>>(std::istream &is, String &str) {
      char* buffer = nullptr;
      size_t capacity = 100;
      size_t size = 0;
      buffer = new char[capacity];

      while (is.good()) {
          is.get(buffer + size, capacity - size);
          size = strlen(buffer);

          if (size == capacity - 1) {
              capacity *= 2;
              char* new_buffer = new char[capacity];
              std::strcpy(new_buffer, buffer);
              delete[] buffer;
              buffer = new_buffer;
          } else {
              break;
          }
      }

      str += String(buffer);
      delete[] buffer;

      return is;
  }

    friend String operator+(String lhs, const String& rhs) {
        lhs += rhs;
        return lhs;
    }

private:
    char* str_;
    size_t size_;
    size_t capacity_;
};




int main() {
    // 測試 default constructor with empty string
    String s1;
    std::string std_s1;
    assert(s1.size() == std_s1.size());

    // 測試 default constructor
    String s2("NTNU");
    std::string std_s2("NTNU");
    assert(s2.size() == std_s2.size());

    // 測試 copy
    String s3(s2);
    std::string std_s3(std_s2);
    assert(s3.size() == std_s3.size());

    // 測試 operator =
    s1 = s2;
    std_s1 = std_s2;
    assert(s1.size() == std_s1.size());

    // 測試 operator []
    assert(s2[1] == std_s2[1]);

    // 測試 operator +=
    s2 += s3;
    std_s2 += std_s3;
    assert(s2.size() == std_s2.size());

    // 測試 size()
    assert(s2.size() == std_s2.size());

    // 測試 c_str()
    assert(std::strcmp(s2.c_str(), std_s2.c_str()) == 0);

    // 測試關係運算子
    assert((s1 == s2) == (std_s1 == std_s2));
    assert((s1 < s2) == (std_s1 < std_s2));
    assert((s1 > s2) == (std_s1 > std_s2));

    // 測試 clear()
    s1.clear();
    std_s1.clear();
    assert(s1.size() == std_s1.size());

    // 測試 swap()
    s1 = "NTNU";
    std_s1 = "NTNU";
    s2 = "CSIE";
    std_s2 = "CSIE";
    s1.swap(s2);
    std_s1.swap(std_s2);
    assert(s1.size() == std_s1.size());
    assert(s2.size() == std_s2.size());
    assert(std::strcmp(s1.c_str(), std_s1.c_str()) == 0);
    assert(std::strcmp(s2.c_str(), std_s2.c_str()) == 0);
    std::cout << "All tests passed!\n";

    return 0;
}
