#include <iostream>
#include <cstring>

using namespace std;

/// @brief 多态测试命名空间
namespace polymorphism
{
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

} // namespace polymorphism
