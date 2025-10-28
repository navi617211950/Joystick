#include <iostream>
#include <cstring>

using namespace std;

/// @brief 多态测试命名空间
namespace polymorphism
{
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
        Animal animal;
        doSpeak(animal);
        Cat cat;
        doSpeak(cat);
        Dog dog;
        doSpeak(dog);
    }

} // namespace polymorphism
