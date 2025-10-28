## 4.6 继承

继承是面向对象的三大特性之一。
    定义这些类时，下级别的成员除了拥有上一级的共性，还有自己的特性

**好处**：减少重复代码，提高代码质量



` class A: public B ` A类成为子类，B类成为父类
子类也称之为派生类，父类也称为基类

派生类中的成员，包含两大部分：
    一类是从基类继承过来的，一类是自己增加的成员
    从基类继承过来的表现其共性，新增成员体现其个性

#### 分类
* 公共继承(` class A: public B `): 全面继承父类的成员访问修饰符封装权限
* 保护继承(` class B: protected B `): 分类的public访问修饰符成员收紧为protected类型，其他类型不变(如：` public int a => protected int a `)
* 私有继承(` class A: private B `): 所有的父类成员访问均收紧为private权限，只能被子类访问，无法被子类的派生类或其他类访问(` public|protected int i => private int i`)


#### 继承中的对象模型

父类中的所有非静态成员都会被子类继承,但是父类中的私有属性被编译器隐藏，子类访问不到
```
class Base
    {
    private:
        int m_a;

    protected:
        int m_b;

    public:
        int m_c;
    };

    class Son : public Base
    {
    public:
        int m_d;
    };

    void test()
    {
        cout << "Son size: " << sizeof(Son) << endl;
    }

    //output: Son size: 16
```

#### 继承中构造和析构的顺序

在继承中，编译器会从上往下首先调用父类构造函数，然后在调用子类构造函数，对象销毁调用析构函数则相反，从下往上先析构子类，然后再析构父类

代码
```
    class Base
    {
    private:
        int m_a;

    protected:
        int m_b;

    public:
        int m_c;

    public:
        Base()
        {
            cout << "Base 构造函数" << endl;
        }
        ~Base()
        {
            cout << "Base 析构函数" << endl;
        }
    };

    class Son : public Base
    {
    public:
        int m_d;

    public:
        Son()
        {
            cout << "Son 构造函数" << endl;
        }
        ~Son()
        {
            cout << "Son 析构造函数" << endl;
        }
    };

    void test()
    {
        cout << "Son size: " << sizeof(Son) << endl;
        Son son;
    }
```
打印结果
```
    Son size: 20
    Base 构造函数
    Son 构造函数
    GrandSon 构造函数
    GrandSon 析构函数
    Son 析构函数
    Base 析构函数
```


### 4.6.5 继承中父子成员重名的处理方式

* 访问子类同名成员，直接访问即可
* 访问父类同名成员，需要加作用域` 父类名::成员属性`
* 调用父类同名函数，在对象变量和函数之间添加` 父类名::`作用域 (` grandSon.Son::func()`)<br>
    *注: 当子类中出现和父类中同名的函数时，会自动隐藏所有父类的同名函数，包括不同的函数重载，需要通过作用域显示调用*
* 调用父类的父类的同名函数，则在调用操作符后添加对应类的作用域(` grandSon.Fathor::func()` 或` grandSon.Son::Fathor::func()`)

代码
```
    class Son : public Base
    {
    public:
        int m_c;

    public:
        Son()
        {
            m_c = 566;
            Base::m_c = 200;
            cout << "Son 构造函数" << endl;
        }
        ~Son()
        {
            cout << "Son 析构函数" << endl;
        }
    };
```

父类或爷爷类的同名函数调用代码
```
    #include <iostream>
    #include <cstring>

    using namespace std;

    namespace testfathor
    {
        class Fathor
        {
        public:
            void hi()
            {
                cout << "Say hi from base" << endl;
            }
        };

        class Son : public Fathor
        {
        public:
            void hi()
            {
                cout << "Say hi from son" << endl;
            }
        };

        class GrandSon : public Son
        {
        public:
            void hi()
            {
                cout << "Say hi from grandson" << endl;
            }
        };

        void test()
        {
            cout << "Son size: " << sizeof(GrandSon) << endl;
            GrandSon grandSon;
            grandSon.Son::hi();
            grandSon.Fathor::hi();
        }
    } // namespace testfathor
```

### 4.6.6 继承同名静态成员处理方式

静态成员和非静态成员出现同名，处理方式一致
* 访问子类同名成员，直接访问即可
* 访问父类同名成员，需要加作用域

静态成员属性访问代码
```
    class Base
    {
        public:
        static int m_a;
    };

    class Sub: public Base{
        public:
        static int m_a;
    };

    int Base::m_a = 100;

    int Sub::m_a = 200;

    void test()
    {
        cout << "通过对象访问: " << endl;
        cout << Sub().m_a << endl;
        cout << Sub().Base::m_a << endl;
        
        cout << "通过类名访问" << endl;
        cout << Sub::m_a << endl;
        //第一个双冒号代表通过类名方式访问，第二个::代表访问父类作用域下成员属性
        cout << Sub::Base::m_a << endl;
    }
```

静态成员函数访问代码
```
    class Base
    {
    public:
        static int m_a;
        static void func()
        {
            cout << "Base - static - func()" << endl;
        }
    };

    class Sub : public Base
    {
    public:
        static int m_a;
        static void func()
        {
            cout << "Sub - static - func()" << endl;
        }
    };

    int Base::m_a = 100;

    int Sub::m_a = 200;

    void test()
    {
        cout << "通过对象访问: " << endl;
        Sub sub;
        sub.func();
        sub.Base::func();

        cout << "通过类名访问" << endl;
        Sub::func();
        // 注: 当子类中出现和父类中同名的函数时，会自动隐藏所有父类的同名函数，包括不同的函数重载，需要通过作用域显示调用
        Sub::Base::func();
    }
```

总结: 同名静态成员变量处理方式和非静态处理方式一样，只不过有两种访问方式(通过对象和通过类名)

### 4.6.7 多继承语法

C++允许一个继承多个父类

```
    class 子类: 继承方式 父类1, 继承方式 父类2...
```

多继承可能会引发父类中有同名成员出现，需要加作用域区分

**C++实际开发中不建议使用多继承**

```
    class Base1
    {
    public:
        int m_a;
    };

    class Base2
    {
    public:
        int m_a;
        int m_b;
    };

    class Son : public Base1, public Base2
    {
    public:
        int m_c;
        int m_d;

    public:
        Son()
        {
            Base1::m_a = 20;
            m_b = 50;
            m_c = 44;
            m_d = 33;
        }
    };

    void test()
    {
        cout << "size of Son=" << sizeof(Son) << endl;
        Son s;
        cout << "Base1 m_a = " << s.Base1::m_a << endl;
    }
```

### 4.6.8 菱形继承(钻石继承)

#### 概念:
    两个派生类继承同一个基类
    又有某个类同时继承这两个派生类
    这种继承称之为菱形继承，或者钻石继承

    ```
        // B继承自A
        class B: public A
        // C继承自A
        class C: public A
        // D继承自B和C
        class D: public B,public C
    ```

#### 菱形继承的问题：
    1. B继承了A的成员，C也继承了A的成员，当D继承B和C后，使用数据时会产生二义性。
    2. D继承了A的数据有两份，产生了重复数据浪费资源

#### 虚继承

解决菱形继承中数据二义性和重复资源的问题

代码
```
    class Animal
    {
    public:
        int age;
    };

    /// @brief 添加Virtual 进行虚继承，Animal变成虚基类
    class Sheep : virtual public Animal
    {
        // 编译器自动添加 vbptr (8字节)
    };

    class Camel : virtual public Animal
    {
        // 编译器自动添加 vbptr (8字节)
    };

    class Alpaca: public Sheep, public Camel
    {
    };

    ostream & operator<<(ostream &out, Alpaca &a)
    {
        cout << sizeof(a);
        return out;
    }

    void test()
    {
        Alpaca al;
        /**
         * @brief Alpaca类的sizeof结果为24字节，这主要源于虚继承引入的虚基类指针和编译器为内存对齐所做的填充。
         * 在虚继承机制下，Sheep和Camel类内部会各包含一个指向虚基类表（vbtable）的虚基类指针（vbptr）。
         * 每个虚基类指针在64位系统中通常占用8字节。Animal类中的int age成员占4字节。
         * 因此，Alpaca对象的基础内存构成为：Sheep的vbptr（8字节） + Camel的vbptr（8字节） + Animal::age（4字节），总计20字节。
         * 编译器为了优化内存访问效率，会进行内存对齐。在64位系统中，常见的对齐边界是8字节。
         * 当前的20字节数据如果直接存放，可能导致后续数据或对象本身起始地址未对齐。
         * 因此，编译器在末尾填充了4字节，使得总大小达到24字节，以满足对齐要求。
         */
        cout << "size of Alpaca = " << al << endl;
        al.Sheep::age = 25;
        al.Camel::age = 30;
        /// @brief 由于Sheep和Camel都是虚继承，共享一个Animal虚基类，age属性不再具有二义性，根据就近原则Alpaca.age等于最后一次age赋值
        // 所以sheep.age 和 camel.age 及al.age的值都为30
        cout << "al.sheep.age=" << al.Sheep::age << endl;
        cout << "al.camel.age=" << al.Camel::age << endl;
        cout << "al.age = " << al.age << endl;
    }
```

output
```
    Alpaca的大小为24，其中animal占4个字节，
    size of Alpaca = 24
    al.sheep.age=30
    al.camel.age=30
    al.age = 30
```






