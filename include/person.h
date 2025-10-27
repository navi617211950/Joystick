#pragma once

#include <iostream>
using namespace std;

class Person
{
public:
    string name;

    int *age;

    string address;

    Person() {
        // cout << "> Person类 无参构造函数被调用" << endl;
    };

    Person(string p_name, int p_age) : name(p_name)
    {
        age = new int(p_age);
    }

    // Person(string p_name, int p_age): name(p_name), age(p_age){
    //     cout << "> Person类 有参(name)构造函数被调用" << endl;
    // }

    Person(const Person &p)
    {
        // cout << "> Person类 拷贝构造函数被调用" << endl;
        this->name = p.name;

        // 编译器默认实现的浅拷贝操作
        // this->age = p.age;
        // 通过自己申请内存空间进行深拷贝
        this->age = new int(*p.age);

        this->address = p.address;
    }

    ~Person()
    {
        delete age;
        age = NULL;
        // cout << "> Person类 析构函数被调用" << endl;
    };
};

/// @brief 空指针调用成员函数测试类
class NullTestPerson
{
private:
    int m_age;

public:
    void showClassName()
    {
        cout << "this is the NullTestPerson Class" << endl;
    }
    void showPersonAge()
    {
        // 这段代码用于增加健壮性，现注释掉仅做运行时错误演示
        // if(this == NULL){
        //     return;
        // }

        cout << "age=" << m_age << endl;
    }
};

class ConstTestPerson
{
public:
    int m_age;

    mutable int m_boll;

    ConstTestPerson()
    {
    }
    // 常量函数的实现是 this指针的本质是指针常量，指针的指向是不可以修改的
    //  在成员函数后加const，修饰的是this指针，让指针指向的值也不可修改
    void showPerson() const
    {
        // 常量函数中不可以修改属性
        //  this 相当于是 ConstTestPerson * const this
        // this->m_age = 100;
        //  mutable修饰的成员变量在常函数中也可以修改
        m_boll = 200;
    }

    void func()
    {
        m_age = 20;
    }
};

class OperatorOverloadPerson
{
public:
    string name;
    int m_age;
    float m_height;

    /// @brief 通过成员函数重载加号运算符
    /// @param p 被加数参数
    /// @return 相加结果
    OperatorOverloadPerson operator+(const OperatorOverloadPerson &p)
    {
        OperatorOverloadPerson temp;
        temp.name = "成员函数重载: " + this->name + p.name;
        temp.m_age = this->m_age + p.m_age;
        temp.m_height = this->m_height + p.m_height;
        return temp;
    }

    /// @brief 运算符重载也可以通过参数的不同进行函数重载
    /// @param addAge 增加的年龄
    /// @return 运算结果
    OperatorOverloadPerson operator+(const int addAge)
    {
        this->m_age += addAge;
        return *this;
    }
};

/// @brief 通过全局变量重载OperatorOverloadPerson相加运算
/// @param p1 加数对象
/// @param p2 被加数对象
/// @return 相加结果
// OperatorOverloadPerson operator+(const OperatorOverloadPerson &p1, const OperatorOverloadPerson &p2)
// {
//     OperatorOverloadPerson temp;
//     temp.name = "全局函数重载: " + p1.name + p2.name;
//     temp.m_age = p1.m_age + p2.m_age;
//     temp.m_height = p1.m_height + p2.m_height;
//     return temp;
// }

/// @brief 使用全局函数进行左移运算符重载，实现标准输出
/// @param cout 标准输出对象
/// @param p 输出对象
/// @return 标准输出对象，方便进行链式访问
ostream &operator<<(ostream &cout, OperatorOverloadPerson &p)
{
    cout << "OperatorOverloadPerson: name=" + p.name + ", age=" << p.m_age << ", height=" << p.m_height;
    return cout;
}

class SelfInteger
{
    friend ostream &operator<<(ostream &out, SelfInteger self);

private:
    int num;

public:
    SelfInteger(int num)
    {
        this->num = num;
    }

    /// @brief 前置自增运算符重载，无参数
    /// @return 自增后对象
    SelfInteger &operator++()
    {
        this->num++;
        return *this;
    }

    /// @brief 后置自增运算符重载，参数仅通过数据类型占位
    /// @param  数据类型占位符
    /// @return 自增前对象
    SelfInteger operator++(int)
    {
        SelfInteger temp = *this;
        this->num++;
        return temp;
    }
};

ostream &operator<<(ostream &out, const SelfInteger self)
{
    cout << self.num;
    return out;
}

void test03()
{
    SelfInteger s(20);
    ++s;
    cout << s << endl;
}

class EqualOverloadPerson
{

public:
    int *m_age;
    EqualOverloadPerson(int age)
    {
        m_age = new int(age);
    }

    ~EqualOverloadPerson()
    {
        if (m_age != NULL)
        {
            delete m_age;
            m_age = NULL;
        }
    }

    EqualOverloadPerson &operator=(EqualOverloadPerson &p)
    {
        this->m_age = new int(*p.m_age);
        return *this;
    }

    bool operator==(const EqualOverloadPerson &p){
        return *this->m_age == *p.m_age;
    }

    bool operator!=(const EqualOverloadPerson &p)
    {
        return *this->m_age != *p.m_age;
    }

};

void test04()
{
    EqualOverloadPerson p(20);
    EqualOverloadPerson p2(30);
    EqualOverloadPerson p3(40);
    p3 = p2 = p;
    cout << "P1:" << *p.m_age << endl;
    cout << "P2:" << *p2.m_age << endl;
    cout << "P3:" << *p2.m_age << endl;
    cout << "p1 == p2: " << (p == p2) << endl;
}


class SelfPrint
{
    public:
    /// @brief 函数调用运算符重载
    /// @param text 重载函数形参
    void operator()(string text)
    {
        std::cout << "自定义输出: " << text << std::endl;
    }
};

void test05()
{
    SelfPrint print;
    print("Hi");
}

/// @brief 函数调用运算符重载第二种实现
class SelfAdd
{
    public:
    /// @brief 仿函数
    /// @param n1 形参1
    /// @param n2 形参2
    /// @return 返回结果
    int operator()(int n1, int n2)
    {
        return n1 + n2;
    }
};

void test06()
{
    cout << SelfAdd()(4,5) << endl;
}