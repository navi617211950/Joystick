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
