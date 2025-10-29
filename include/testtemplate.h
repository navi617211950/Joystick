#include <iostream>

using namespace std;

/// @brief 函数模板测试命名空间
namespace methodtemplate
{
    /// @brief 声明一个参数交换的函数模板
    /// @tparam T 模板类
    /// @param t1 参数1
    /// @param t2 参数2
    /// @param u 另一种类型参数
    template <typename T, typename U>
    void swapParam(T &t1, T &t2, const U &u)
    {
        T temp = t1;
        t1 = t2;
        t2 = temp;
        cout << u << endl;
    }

    /// @brief 声明一个参数交换的函数模板
    /// @tparam T 模板类
    /// @param t1 参数1
    /// @param t2 参数2
    template<class T>
    void swapParam(T &t1, T &t2)
    {
        T temp = t1;
        t1 = t2;
        t2 = temp;
    }


    /// @brief 排序函数模板
    /// @tparam T 模板参数
    /// @param arr 排序数组
    /// @param len 数组长度
    template<class T>
    void sortArray(T arr[], int len)
    {
        for(int i = 0; i< len; i++)
        {
            int max = i;
            for(int j=i+1;j < len; j++)
            {
                if(arr[max] < arr[j])
                {
                    max = j;
                }
            }
            if(max != i)
            {
                swapParam(arr[max], arr[i]);
            }
        }
    }

    /// @brief 打印数组
    /// @tparam T 模板参数类型
    /// @param arr 数组
    /// @param len 数组长度
    template<class T>
    void print(T arr, int len)
    {
        for(int i = 0; i< len; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }


    void test()
    {
        char char_arr[] = "Hello World";
        int len = sizeof(char_arr) / sizeof(char);
        sortArray(char_arr, len);
        print(char_arr, len);

        int int_arr[] = {25,65,2,55,66,982,14,0};
        len = sizeof(int_arr) / sizeof(int);
        sortArray(int_arr, len);
        print(int_arr, len);
    }

} // namespace methodtemplate
