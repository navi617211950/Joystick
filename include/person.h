#pragma once

#include <iostream>
using namespace std;

class Person
{
public:
    string name;
    int *age;
    string address;

    Person(){
        cout << "> Person类 无参构造函数被调用" << endl;
    };

    Person(string p_name, int p_age): name(p_name){
        age = new int(p_age);
    }

    // Person(string p_name, int p_age): name(p_name), age(p_age){
    //     cout << "> Person类 有参(name)构造函数被调用" << endl;
    // }

    Person(const Person &p){
        cout << "> Person类 拷贝构造函数被调用" << endl;
        this->name = p.name;
         
        //编译器默认实现的浅拷贝操作
        //this->age = p.age;
        //通过自己申请内存空间进行深拷贝
        this->age = new int(*p.age);

        this->address = p.address;
    }

    ~Person(){
        delete age;
        age = NULL;
        cout << "> Person类 析构函数被调用" << endl;
    };

};