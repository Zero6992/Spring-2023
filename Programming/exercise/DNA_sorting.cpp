#include <iostream>
#include <cstddef>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr size_t MaxStringLen = 50;

class String
{
friend ostream & operator << (ostream &os, const String &rhs);
public:
    void Set(const char s[]);
    const char & operator[](size_t i) const { return str_[i]; }
    size_t size() const { return strlen(str_); }
    size_t Unsortedness() const { return unsortedness_; }
private:
    static constexpr size_t MaxLen = MaxStringLen;
    char str_[MaxLen+1]={};
    size_t unsortedness_ = 0;
};
// ------------------------------------------------------------------
void String::Set(const char s[])
{
    strncpy(str_, s, MaxLen);
    str_[MaxLen] = '\0';
    unsortedness_ = 0;
    for (size_t i = 0; i < strlen(str_); i++)
    {
        for (size_t j = i + 1; j < strlen(str_); j++)
        {
            if (str_[i] > str_[j])
            {
                unsortedness_++;
            }
        }
    }
}
// ------------------------------------------------------------------
ostream & operator << (ostream &os, const String &rhs)
{
    os << rhs.str_;
    return os;
}
// ------------------------------------------------------------------
int main()
{
    int T=0;
    cin >> T;

    while (T--)
    {
        int L=0, N=0;
        cin >> L >> N;
        String data[100];

        for (int i=0; i<N; i+=1)
        {
            char str[MaxStringLen+1]={};
            cin >> str;
            data[i].Set(str);
        }

        stable_sort(data, data+N, [](const String &a, const String &b) { return a.Unsortedness() < b.Unsortedness(); });
        for (int i=0; i<N; i+=1)
        {
            cout << data[i] << endl;
        }

        if (T) cout << endl;
    }
}
