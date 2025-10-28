## 4.7 多态

### 4.7.1 多态的基本概念

多态是C++面向对象三大特性之一

多态分为两类：

*   静态多态: 函数重载和运算符重载属于静态多态, 复用函数名
*   动态多态: 派生类和虚函数实现运行时多态

静态多态和动态多态区别：

*   静态多态的函数地址早绑定 - 编译阶段确定函数地址
*   动态多态的函数地址晚绑定 - 运行结算确定函数地址 

早绑定代码:
```
    class Animal
    {
    public:
        void speak()
        {
            cout << "动物在说话" << endl;
        }
    };

    class Cat : public Animal
    {
    public:
        void speak()
        {
            cout << "哈基米在说话" << endl;
        }
    };
    void doSpeak(Animal &animal)
    {
        //现在函数的地址早绑定，在编译阶段确定函数地址
        animal.speak();
    }

    void test()
    {
        Cat cat;
        doSpeak(cat);
    }
```

output
```
    Joystick started.
    动物在说话
```

晚绑定，即将基类的函数定义为虚函数，满足动态多态

代码: 
```
    class Animal
    {
    public:
        virtual void speak()
        {
            cout << "动物在说话" << endl;
        }
    };

    class Cat : public Animal
    {
    public:
        void speak()
        {
            cout << "哈基米在说话" << endl;
        }
    };

    class Dog : public Animal
    {
    public:
        void speak()
        {
            cout << "汪汪在说话" << endl;
        }
    };

    void
    doSpeak(Animal &animal)
    {
        // 现在函数的地址早绑定，在编译阶段确定函数地址
        // 如果是想执行猫猫说话，那么就需要执行的函数晚绑定，即基类的函数变位虚函数
        animal.speak();
    }

    void test()
    {
        Cat cat;
        doSpeak(cat);
        Dog dog;
        doSpeak(dog);
    }
```

output

```
    Joystick started.
    哈基米在说话
    汪汪在说话
```

总结
多态的满足条件:
1.  有继承关系,基类定义虚函数
2.  子类完全重写父类的虚函数(*函数名、参数列表和返回值类型与虚函数定义的完全一致*)

动态多态的使用：
*   父类的指针或引用，执行子类对象的函数