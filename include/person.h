#pragma once

#include <iostream>
using namespace std;

class Person
{
public:
    string name;
    int age;
    string address;

    Person(){
        cout << "> Person类 无参构造函数被调用" << endl;
    };
    ~Person(){
        cout << "> Person类 析构函数被调用" << endl;
    };

    Person(string p_name){
        cout << "> Person类 有参(name)构造函数被调用" << endl;
        this->name = p_name;
    }

    Person(const Person &p){
        cout << "> Person类 拷贝构造函数被调用" << endl;
        this->name = p.name;
        this->age = p.age;
        this->address = p.address;
    }

};