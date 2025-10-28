
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
        Sub::Base::func();
    }
} // namespace testfathor

namespace doublefather
{

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
} // namespace doublefather

namespace damianl
{
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

    /// @brief 由于Sheep和Camel都是虚继承，共享一个Animal虚基类，age属性不再具有二义性，根据就近原则Alpaca.age等于最后一次age赋值
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
        cout << "al.sheep.age=" << al.Sheep::age << endl;
        cout << "al.camel.age=" << al.Camel::age << endl;
        cout << "al.age = " << al.age << endl;
    }
} // namespace damianl