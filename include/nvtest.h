#include <iostream>
#include <cstring>

using namespace std;

namespace navis
{
    namespace str
    {
    }

    namespace dycast
    {
        /// @brief 基类
        class Base
        {
        public:
            virtual ~Base() = default;
        };

        /// @brief 子类
        class Derived : public Base
        {
        public:
            void show()
            {
                std::cout << "Derived class method" << std::endl;
            }
        };
    }

    /// @brief 测试方法
    void test()
    {
        dycast::Base *ptr_base = new dycast::Derived;
        dycast::Derived *ptr_derived = dynamic_cast<dycast::Derived *>(ptr_base);
        if (ptr_derived)
        {
            ptr_derived->show();
        }
        else
        {
            std::cout << "Dynamic cast failed" << std::endl;
        }
    }
}