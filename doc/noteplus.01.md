# C++提高编程

* 本阶段主要针对C++泛型编程和STL技术做详细讲解，探讨C++更深层的使用

## 1 模板

### 1.1 模板的概念

模板就是建立通用的模具，大大提高复用性

模板的特点:
* 模板不可以直接使用，他只是一个框架
* 模板的通用不是万能的

### 1.2 函数模板
* C++另一种编程思想成为*泛型编程*，主要利用的基数就是模板
* C++提供两种模板机制: 函数模板 和类模板

#### 1.2.1 函数模板语法

函数模板的作用：
    建立一个通用函数，其函数返回值类型和形参类型可以不具体定制，用一个虚拟的类型来代表

语法:
```
template<typename|class T>
函数声明或定义
```

解释:
    template -- 声明创建模板  
    typename -- 表明其后面的符号是一种数据类型, 可以用class代替  
    T -- 通用的数据类型, 名称可以替换, 通常为大写字母  

函数模板的声明和调用

```
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

```

output

```
Joystick started.
a = 5, b = 3
c = 3.4, f = 4.5
Joystick end.
```
##### 总结
* 函数模板利用关键字template
* 使用函数模板有两种方式: 自动类型推导、显示指定类型
* 模板的目的是为了提高复用性, 将类型参数化

#### 1.2.2 函数模板的注意事项

注意事项：
* 自动类型推导必须推导出一致的数据类型T才可以使用
* 模板必须要确定出T的数据类型才可以使用

### 1.3 类模板



## 2 STL初识


## 3 STL-常用容器


## 4 STL-函数对象


## 5 STL-常用算法
