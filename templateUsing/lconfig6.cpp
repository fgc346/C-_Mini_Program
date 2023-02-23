#include <iostream>

using namespace std;

class alloc {
};

template <typename T, typename Alloc = alloc>
class vector {
public:
    void swap(vector<T, Alloc>&)
    {
        cout << "swap()" << endl;
    }
};

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <typename T, typename Alloc>
inline void swap(vector<T, Alloc>& x, vector<T,Alloc>& y)
{
    x.swap(y);
}
#endif

int main()
{
    vector<int> x, y;
    // swap(x, y);
    // swap(x);
    // x.swap(y);
    swap(x, y);
    return 0;
}