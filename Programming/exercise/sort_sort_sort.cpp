#include <iostream>
#include <algorithm>
using namespace std;

class Compare
{
public:
    void SetDivisor(int d) { divisor_ = d; }

    bool operator()(int lhs, int rhs) const
    {
        int mod_lhs = lhs % divisor_;
        int mod_rhs = rhs % divisor_;

        if (mod_lhs != mod_rhs)
            return mod_lhs < mod_rhs;

        bool lhs_odd = lhs % 2 != 0;
        bool rhs_odd = rhs % 2 != 0;

        if (lhs_odd != rhs_odd)
            return lhs_odd > rhs_odd;

        if (lhs_odd && rhs_odd)
            return lhs > rhs;
        else
            return lhs < rhs;
    }

private:
    int divisor_ = 1;
};

int main()
{
    constexpr size_t MaxDataSize = 10000;
    int M=0, N=0, data[MaxDataSize]={};
    while (cin >> N >> M)
    {
        cout << N << ' ' << M << endl;
        if (N==0 && M==0) break;

        Compare comp;
        comp.SetDivisor(M);

        for (int i=0; i<N; i+=1)
        {
            cin >> data[i];
        }
        sort(data, data+N, comp);
        for (int i=0; i<N; i+=1)
        {
            cout << data[i] << endl;
        }
    }

}
