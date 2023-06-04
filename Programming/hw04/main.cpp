#include "String.h"

int main() {
    // 測試 default constructor with empty string
    String s1;
    std::string std_s1;
    assert(s1.size() == std_s1.size());
    assert(std::strcmp(s1.c_str(), std_s1.c_str()) == 0);

    // 測試 default constructor
    String s2("NTNU");
    std::string std_s2("NTNU");
    assert(s2.size() == std_s2.size());
    assert(std::strcmp(s2.c_str(), std_s2.c_str()) == 0);

    // 測試 copy
    String s3(s2);
    std::string std_s3(std_s2);
    assert(s3.size() == std_s3.size());
    assert(std::strcmp(s3.c_str(), std_s3.c_str()) == 0);

    // 測試 operator =
    s1 = s2;
    std_s1 = std_s2;
    assert(s1.size() == std_s1.size());
    assert(std::strcmp(s1.c_str(), std_s1.c_str()) == 0);

    // 測試 operator []
    assert(s2[1] == std_s2[1]);

    // 測試 operator +=
    s2 += s3;
    std_s2 += std_s3;
    assert(s2.size() == std_s2.size());
    assert(std::strcmp(s2.c_str(), std_s2.c_str()) == 0);

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

    // 測試 size()
    assert(s2.size() == std_s2.size());

    // 測試 c_str()
    assert(std::strcmp(s2.c_str(), std_s2.c_str()) == 0);

    // 測試關係運算子
    assert((s1 == s2) == (std_s1 == std_s2));
    assert((s1 < s2) == (std_s1 < std_s2));
    assert((s1 > s2) == (std_s1 > std_s2));
    assert((s1 <= s2) == (std_s1 <= std_s2));
    assert((s1 >= s2) == (std_s1 >= std_s2));
    assert((s1 != s2) == (std_s1 != std_s2));
    
    // 測試 operator <<
    std::stringstream out;
    out << s1;
    assert(out.str() == std_s1);

    // 測試 operator >>
    std::stringstream in("New String");
    String s4;
    std::string std_s4;
    std::getline(in, std_s4);
    in.seekg(0);
    in >> s4;
    assert(s4.size() == std_s4.size());
    assert(std::strcmp(s4.c_str(), std_s4.c_str()) == 0);


    std::cout << "All tests passed!\n";

    return 0;
}
