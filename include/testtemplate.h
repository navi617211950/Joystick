#include <iostream>

using namespace std;

/// @brief 函数模板测试命名空间
namespace methodtemplate
{
    void swapInteger(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    /// @brief 声明一个参数交换的函数模板
    /// @tparam T 模板类
    /// @param t1 参数1
    /// @param t2 参数2
    template <typename T>
    void swapParam(T &t1, T &t2)
    {
        T temp = t1;
        t1 = t2;
        t2 = temp;
    }

    void test()
    {
        int a = 3;
        int b = 5;
        // 两种使用函数模板的方式
        // 1. 类型自动推导
        swapParam(a, b);
        cout << "a = " << a << ", b = " << b << endl;
        double c = 4.5;
        double f = 3.4;
        // 2. 显式指定类型
        swapParam<double>(c, f);
        cout << "c = " << c << ", f = " << f << endl;
    }

} // namespace methodtemplate
