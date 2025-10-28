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

### 4.7.2 多态的底层原理

1. 首先不声明虚函数的前提下，下方的空函数的类的sizeof大小为1，
代码: 
```
    class Animal
    {
    public:
        void speak()
        {
            cout << "动物在说话" << endl;
        }
    };  
```

2. 当函数声明成虚函数的时候，该类sizeof的大小则变为4(64位系统结果为8)

    Animal类的内部结构存储的是一个vfptr(虚函数(表)指针)，该指针指向vftable，表的内部记录一个虚函数的地址(&Animal::speak())
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
```

3. 如果类Cat直接继承Animal，不重写虚函数，则类内存储的vfptr也指向Animal的虚函数(&Animal::speak());如果Cat类内重写了父类的虚函数，则类内存储的vfptr会修改指向vftable中另外的一个虚函数地址(&Cat::speak())。
    
    当 执行` Animal &animal = cat; cat.speak();`代码时, 系统动态绑定Cat::speak()方法。

代码: 
```
    class Cat : public Animal
    {
    public:
        void speak()
        {
            cout << "哈基米在说话" << endl;
        }
    };
```

### 4.7.2 多态实例-计算器类

* 多态的优点:
    * 代码组织结构清晰
    * 可读性强
    * 有利于前期和后期的扩展和维护

普通实现的计算器类

代码:

```
    const int OPER_ADD = 0;
    const int OPER_MINUS = 1;
    const int OPER_MULTIPLY = 2;
    const int OPER_DEVIDE = 3;

    /// @brief 普通实现计算器
    class Calculator
    {
    public:
        int m_Num1;
        int m_Num2;

    public:
        Calculator() {}
        Calculator(int num1, int num2)
        {
            m_Num1 = num1;
            m_Num2 = num2;
        }
        int getResult(int oper)
        {
            int result = 0;
            switch (oper)
            {
            case OPER_ADD:
                result = m_Num1 + m_Num2;
                break;
            case OPER_MINUS:
                result = m_Num1 - m_Num2;
                break;
            case OPER_MULTIPLY:
                result = m_Num1 * m_Num2;
                break;
            case OPER_DEVIDE:
                if (m_Num2 == 0)
                {
                    cout << "错误: 除数不能为0" << endl;
                }
                else
                {
                    result = m_Num1 / m_Num2;
                }
                break;
            default:
                break;
            }
            return result;
        }
    };

    void test()
    {
        Calculator c(2, 3);
        cout << "2 + 3 = " << c.getResult(OPER_ADD) << endl;
        cout << "2 - 3 = " << c.getResult(OPER_MINUS) << endl;
    }
```

上述代码如果想扩展新的功能，需要修改源码，非常的不方便

在真实开发环境中，提倡开闭原则(对扩展进行开发，对修改进行关闭)

通过重构计算器类代码

```
    /// @brief 抽象计算器基类
    class AbstractCalculator
    {
    public:
        int m_num1;
        int m_num2;

    public:
        /// @brief 仅定义一个虚函数
        /// @return 返回值
        virtual int getResult()
        {
            return 0;
        }
    };

    /// @brief 加法计算器子类
    class AddCalcutor : public AbstractCalculator
    {
    public:
        virtual int getResult()
        {
            return m_num1 + m_num2;
        }
    };

    /// @brief 减法计算器子类
    class SubCalcutor : public AbstractCalculator
    {
    public:
        virtual int getResult()
        {
            return m_num1 - m_num2;
        }
    };

    /// @brief 乘法计算器子类
    class MultiplyCalcutor : public AbstractCalculator
    {
    public:
        virtual int getResult()
        {
            return m_num1 * m_num2;
        }
    };

    /// @brief 除法计算器子类
    class DevideCalcutor : public AbstractCalculator
    {
    public:
        virtual int getResult()
        {
            if (m_num2 == 0)
            {
                cout << "错误: 除数不能为0" << endl;
                return -1;
            }
            else
            {
                return m_num1 / m_num2;
            }
        }
    };

    void test()
    {
        AbstractCalculator *calc = new AddCalcutor;
        calc->m_num1 = 3;
        calc->m_num2 = 5;
        cout << "2 + 3 = " << calc->getResult() << endl;
        delete calc;
        calc = new DevideCalcutor;
        calc->m_num2 = 0;
        cout << "2 / 0 = " << calc->getResult() << endl;
        delete calc;
        calc = NULL;
    }
```

### 4.7.3 纯虚函数和抽象类

在多态中，通常父类中的虚函数实现是无意义的，主要都是调用子类重写的内容

因此可以将父类的虚函数定义为纯虚函数，其语法是 ` virtual 返回值类型 函数名(参数列表) = 0;`

当类中有了纯虚函数，这个类也称之为抽象类

抽象类特点:
* 无法实例化对象
* 子类必须重写抽象类中的纯虚函数, 否则也属于抽象类

### 4.7.4 抽象类下的饮品代码实例

```
    class AbstractDrinking
    {
        virtual void boil() = 0;
        virtual void brew() = 0;
        virtual void cup() = 0;
        virtual void insert() = 0;

    public:
        void makeDrink()
        {
            boil();
            brew();
            cup();
            insert();
        }
    };

    class Coffee : public AbstractDrinking
    {
        virtual void boil()
        {
            cout << "煮水" << endl;
        }
        virtual void brew()
        {
            cout << "冲泡咖啡" << endl;
        }
        virtual void cup()
        {
            cout << "倒入咖啡杯" << endl;
        }
        virtual void insert()
        {
            cout << "加入糖和牛奶" << endl;
        }
    };

    class Tea : public AbstractDrinking
    {
        virtual void boil()
        {
            cout << "煮水" << endl;
        }
        virtual void brew()
        {
            cout << "冲泡茶叶" << endl;
        }
        virtual void cup()
        {
            cout << "倒入茶杯" << endl;
        }
        virtual void insert()
        {
            cout << "加入柠檬片" << endl;
        }
    };

    void doWork(AbstractDrinking *abs)
    {
        abs->makeDrink();
        delete abs;
    }

    void test()
    {
        doWork(new Tea);
        cout << "------------" << endl;
        doWork(new Coffee);
    }
```

### 4.7.5 虚析构和纯虚析构

多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码

解决方法: 将父类的析构函数改成虚析构或者纯虚析构

虚析构和纯虚析构共性:
* 可以解决父类指针释放子类对象
* 都需要具体的函数实现

虚析构和纯虚析构的区别:
* 如果是纯虚析构, 该类属于抽象类，无法实例化对象

虚析构语法:
    ` virtual ~类名(){}`

纯虚析构语法:
    ` virtual ~类名() = 0;`


普通析构函数无法被父类指针调用，子类的堆区属性无法被释放

```
    class Animal
    {
    public:
        Animal()
        {
            cout << "动物构造函数被调用" << endl;
        }
        ~Animal()
        {
            cout << "动物析构函数被调用" << endl;
        }
        virtual void speak() = 0;
    };

    class Cat : public Animal
    {
    private:
        string *m_name;

    public:
        Cat(string name)
        {
            m_name = new string(name);
            cout << "猫猫构造函数被调用" << endl;
        }
        ~Cat()
        {
            if (m_name != NULL)
            {
                cout << "猫猫析构函数被调用" << endl;
                delete m_name;
                m_name = NULL;
            }
        }
        virtual void speak()
        {
            cout << "哈基米" << *m_name << "在说话" << endl;
        }
    };

    void test()
    {
        Animal *animal = new Cat("Tom");
        animal->speak();
        delete animal;
    }
```

output
```
    Joystick started.
    动物构造函数被调用
    猫猫构造函数被调用
    哈基米Tom在说话
    //Cat 析构函数未被调用, 会造成内存泄漏
    动物析构函数被调用
```

将父类的析构函数设置成虚析构或者纯虚析构，子类的析构函数会被正确调用
    父类的纯虚析构在声明后，需要有实现，否则系统报错父类的指针无法实例化

```
    class Animal
    {
    public:
        Animal()
        {
            cout << "动物构造函数被调用" << endl;
        }

        /// @brief 纯虚析构函数有声明，也必须有实现，否则无法实例化
        virtual ~Animal() = 0;
        virtual void speak() = 0;
    };

    /// @brief 纯虚析构函数有声明，也必须有实现，否则无法实例化
    Animal::~Animal() 
    {
        cout << "动物析构函数被调用" << endl;
    }

    class Cat : public Animal
    {
    private:
        string *m_name;

    public:
        Cat(string name)
        {
            m_name = new string(name);
            cout << "猫猫构造函数被调用" << endl;
        }
        ~Cat()
        {
            if (m_name != NULL)
            {
                cout << "猫猫析构函数被调用" << endl;
                delete m_name;
                m_name = NULL;
            }
        }
        virtual void speak()
        {
            cout << "哈基米" << *m_name << "在说话" << endl;
        }
    };

    void test()
    {
        Animal *animal = new Cat("Tom");
        animal->speak();
        delete animal;
    }
```

总结:
1. 虚析构或者纯虚析构就是用来解决父类指针释放子类对象堆区资源的问题
2. 如果子类没有堆区数据，可以不写虚析构或纯虚析构
3. 拥有纯虚析构函数的类也是抽象类