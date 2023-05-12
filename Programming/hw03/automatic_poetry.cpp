#include <iostream>
#include <string>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; ++i) {
        std::string line1, line2;
        getline(std::cin, line1);
        getline(std::cin, line2);

        int s1 = line1.find('<');
        int s2 = line1.find('>');
        int s3 = line1.find('<', s2);
        int s4 = line1.find('>', s3);

        std::string str1 = line1.substr(s1 + 1, s2 - s1 - 1);
        std::string str2 = line1.substr(s3 + 1, s4 - s3 - 1);
        std::string str3 = line1.substr(s2 + 1, s3 - s2 - 1);
        std::string str4 = line1.substr(s4 + 1);

        line1.erase(std::remove(line1.begin(), line1.end(), '<'), line1.end());
        line1.erase(std::remove(line1.begin(), line1.end(), '>'), line1.end());

        std::cout << line1 << '\n';
        line2 = line2.substr(0, line2.size() - 3);
        line2 += str2 + str3 + str1 + str4;
        std::cout << line2 << '\n';
    }

    return 0;
}
