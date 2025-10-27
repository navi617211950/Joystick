### 4.2.2 构造函数的分类及调用

* 两种分类方式:
    * 按参数分为：有参构造和无参构造
    * 按类型分为：普通构造和拷贝构造
* 调用方式：
    * 括号法
    * 显示法
    * 隐式转换法

注意: 调用默认构造函数不要在参数后边增加括号

```
    Person p1() 会被编译器认为是函数声明,而非是创建对象的声明
```

### 4.2.3 拷贝构造函数调用时机

* 使用一个已经创建完毕的对象来初始化一个新对象
* 值传递的方式给函数参数传值
* 以值方式返回局部对象

### 4.2.4 构造函数调用规则

调用规则：
* 如果用户定义了有参构造函数，C++不再提供默认无参构造函数，但是会提供默认拷贝构造
* 如果用户定义了拷贝构造函数，C++不再提供其他构造函数

### 4.2.5 深拷贝和浅拷贝

* 浅拷贝：简单的赋值拷贝操作
* 深拷贝：在堆区重新申请空间，进行拷贝操作

即：如果类中存在有堆区开辟的属性，需要自己提供拷贝构造函数，防止浅拷贝带来的问题

### 4.2.6 初始化列表

### 4.2.7 类对象作为类成员

C++类中的成员可以是另一个类的对象，对象成员

```
    // 如果类中存在成员对象，C++先创建成员属性，再构造自身，析构顺序相反
    class A {}
    class B
    {
        A a;
    }
```

### 4.2.8 静态成员

在类的成员变量和成员函数前加上*static*关键字，成为静态成员

静态成员分为:
* 静态成员变量
    * 所有对象共享同一份数据
    * 在编译阶段分配内存
    * 类内声明，类外初始化
* 静态成员函数
    * 所有对象共享同一个函数
    * 静态成员函数只能访问静态成员变量
    * 通过对象和类都可以访问静态成员函数(`p.func() `和`Person::func()`)
    * 静态成员函数也可以设置访问权限


## 4.3 C++对象模型和this指针

### 4.3.1 成员变量和成员函数分开存储

在C++中，类内的成员变量和成员函数是分开存储的
只有非静态成员变量才属于类的对象

空对象占用内存空间为1个字节，目的是为了区分空对象占内存的位置

### 4.3.2 this指针概念

this指针指向被调用的成员函数所属的对象

this指针是隐含每一个非静态成员函数的一种指针
this指针不需要定义，直接使用即可

用途：
* 当形参和成员变量同名时，可以通过this指针来区分
* 在类的非静态成员函数中返回对象自身，可使用`return *this`

### 4.3.3 空指针控制成员函数

C++中空指针也可以调用成员函数，但是也要注意有没有用到this指针

如果用到this指针，需要加判断保证代码的健壮性

```
    void showPersonAge()
    {
        // 这段代码用于增加健壮性，现注释掉仅做运行时错误演示
        // if(this == NULL){
        //     return;
        // }

        cout << "age=" << m_age << endl;
    }
```

### 4.3.4 const修饰成员函数

##### 常函数：

成员函数加const后我们称这个函数为常函数
常函数内不可以修改成员属性
成员属性声明增加关键字mutable后，在常函数数仍然可以修改

```
class ConstTestPerson
{
    int m_age;
    mutable int m_boll;

    public:
    //常量函数的实现是 this指针的本质是指针常量，指针的指向是不可以修改的
    // 在成员函数后加const，修饰的是this指针，让指针指向的值也不可修改
    void showPerson() const{
        //常量函数中不可以修改属性
        // this 相当于是 ConstTestPerson * const this
        //this->m_age = 100;
        // mutable修饰的成员变量在常函数中也可以修改
        m_boll = 200;
    }
};
```

##### 常对象：

声明对象前加const称该对象为常对象
常对象只能调用常函数

```
    const ConstTestPerson p;
    p.m_boll = 200;
    p.showPerson();
    // 常对象只能调用常函数，因为普通函数有可能会修改成员属性，
    //p.func();
```


## 4.4 友元

目的是让一个函数或者类访问另一个类的私有成员

友元的三种实现:
    
* 全局函数做友元
    ```
    #include <iostream>
    #include <string>

    using namespace std;

    class Building
    {
        /// @brief goodGay函数是Building的友元函数，可以访问building类的私有成员
        /// @param building 
        friend void goodGay(Building *building);

    public:
        Building()
        {
            m_bedRoom = "卧室";
            m_sittingRoom = "客厅";
        }

    public:
        string m_sittingRoom;

    private:
        string m_bedRoom;
    };

    /// @brief 全局函数，用来访问building的属性
    /// @param building 参数
    void goodGay(Building *building)
    {
        cout << "好基友全局函数,正在访问：" << building->m_sittingRoom << endl;
        cout << "好基友全局函数,正在访问：" << building->m_bedRoom << endl;
    }

    void test01()
    {
        Building building;
        goodGay(&building);
    }    
    ```

* 类做友元

    ```
        #include <iostream>
        #include <string>

        using namespace std;

        class Building;
        class GoodGay;

        class Building
        {
            friend class GoodGay;

        public:
            Building()
            {
                m_bedRoom = "卧室";
                m_sittingRoom = "客厅";
            }

        public:
            string m_sittingRoom;

        private:
            string m_bedRoom;
        };

        class GoodGay
        {
        public:
            Building *building = new Building;
            void visit()
            {
                cout << "好基友类正在访问" << building->m_bedRoom << endl;
            }
        };

        void test01()
        {
            GoodGay g;
            g.visit();
        }
    ```

* 成员函数做友元

    ```
        #include <iostream>
        #include <string>

        using namespace std;

        // 前置声明Building类（因为GoodGay中需要使用）
        class Building;

        // 先声明GoodGay类，并在类内声明visit()函数（无需实现）
        class GoodGay
        {
        public:
            Building* building; // 先声明指针，后续再初始化
            void visit(); // 声明visit()函数
        };

        // 定义Building类，此时可以正确声明GoodGay::visit()为友元
        class Building
        {
            // 此时GoodGay类已声明，且visit()函数已声明，友元声明有效
            friend void GoodGay::visit();

        public:
            Building()
            {
                m_bedRoom = "卧室";
                m_sittingRoom = "客厅";
            }

        public:
            string m_sittingRoom;

        private:
            string m_bedRoom;
        };

        // 实现GoodGay的visit()函数（此时Building类已完整定义，可访问其成员）
        void GoodGay::visit()
        {
            cout << "好基友类正在访问" << building->m_bedRoom << endl;
        }

        void test01()
        {
            GoodGay g;
            g.building = new Building; // 初始化building指针
            g.visit();
            delete g.building; // 记得释放内存，避免泄漏
        }
    ```

## 4.5 运算符重载

概念：对已有的运算符重新进行定义，赋予其另一种功能，已适应不同的数据类型

### 4.5.1 加号运算符重载

运算符重载可以通过成员函数和全局函数两种方式实现，如果同时存在，成员函数的优先级更高

```
    class OperatorOverloadPerson
    {
    public:
        string name;
        int m_age;
        float m_height;

        /// @brief 通过成员函数重载加号运算符
        /// @param p 被加数参数
        /// @return 相加结果
        OperatorOverloadPerson operator+(const OperatorOverloadPerson &p)
        {
            OperatorOverloadPerson temp;
            temp.name = "成员函数重载: " + this->name + p.name;
            temp.m_age = this->m_age + p.m_age;
            temp.m_height = this->m_height + p.m_height;
            return temp;
        }

        /// @brief 运算符重载也可以通过参数的不同进行函数重载
        /// @param addAge 增加的年龄
        /// @return 运算结果
        OperatorOverloadPerson operator+(const int addAge)
        {
            this->m_age += addAge;
            return *this;
        }
    };

    /// @brief 通过全局变量重载OperatorOverloadPerson相加运算
    /// @param p1 加数对象
    /// @param p2 被加数对象
    /// @return 相加结果
    OperatorOverloadPerson operator+(const OperatorOverloadPerson &p1, const OperatorOverloadPerson &p2)
    {
        OperatorOverloadPerson temp;
        temp.name = "全局函数重载: " + p1.name + p2.name;
        temp.m_age = p1.m_age + p2.m_age;
        temp.m_height = p1.m_height + p2.m_height;
        return temp;
    }

    void test02()
    {
        OperatorOverloadPerson p1;
        p1.name = "zhangsan";
        p1.m_age = 34;
        p1.m_height = 1.65;
        OperatorOverloadPerson p2;
        p2.name = "lisi";
        p2.m_age = 25;
        p2.m_height = 2.56;
        OperatorOverloadPerson p3 = p1 + p2;
        cout << p3.name << ": " << p3.m_age << ", " << p3.m_height << endl;

        OperatorOverloadPerson p4 = p1 + 50;
        cout << p1.name << ": " << p1.m_age << ", " << p1.m_height << endl;

    }
```

##### 总结:
    * 对于内置的数据类型的表达式的运算符是不可能改变的
    * 不要滥用运算符重载

### 4.5.2 左移运算符重载

作用：可以输出自定义数据类型
    注：一般不用通过成员函数实现左移运算符重载，因为无法实现cout在左侧

    ```
        /// @brief 使用全局函数进行左移运算符重载，实现标准输出
        /// 如果成员属性是私有的，可以把重载函数设置成类的友元函数
        /// @param cout 标准输出对象
        /// @param p 输出对象
        /// @return 标准输出对象，方便进行链式访问
        ostream & operator<<(ostream &cout , OperatorOverloadPerson &p)
        {
            cout << "OperatorOverloadPerson: name=" + p.name +", age=" << p.m_age << ", height=" << p.m_height;
            return cout;
        }
    ```

    ##### 总结
        * 重载左移运算符配合友元函数可以实现输出自定义数据类型

### 4.5.3 递增运算符重载

递增运算符重载分为前置和后置两种情况

    ```
        class SelfInteger
        {
            friend ostream & operator<<(ostream &out, SelfInteger self);
        private:
            int num;

        public:
            SelfInteger(int num)
            {
                this->num = num;
            }

            /// @brief 前置自增运算符重载，无参数
            /// @return 自增后对象(引用)
            SelfInteger & operator++()
            {
                this->num++;
                return *this;
            }

            /// @brief 后置自增运算符重载，参数仅通过数据类型占位
            /// @param  数据类型占位参数，用于区分前置、后置
            /// @return 自增前对象
            SelfInteger operator++(int)
            {
                SelfInteger temp = *this;
                this->num++;
                return temp;
            }
        };

        ostream & operator<<(ostream &out, const SelfInteger self)
        {
            cout << self.num;
            return out;
        }

        void test03()
        {
            SelfInteger s(20);
            ++s;
            cout << s << endl;
        }
    ```

### 4.5.4 赋值运算符重载

C++编译器至少给一个类添加了4个函数
1. 默认构造函数(无参, 函数体为空)
2. 默认析构函数(无参, 函数体为空)
3. 默认拷贝构造函数, 对属性进行值拷贝
4. 赋值运算符operator=，对属性进行值拷贝

如果类中有属性指向堆区, 做赋值操作时也会出现深潜拷贝的问题

```
    class EqualOverloadPerson
    {

    public:
        int *m_age;
        EqualOverloadPerson(int age)
        {
            m_age = new int(age);
        }

        ~EqualOverloadPerson()
        {
            if (m_age != NULL)
            {
                delete m_age;
                m_age = NULL;
            }
        }

        EqualOverloadPerson &operator=(EqualOverloadPerson &p)
        {
            this->m_age = new int(*p.m_age);
            return *this;
        }
    };

    void test04()
    {
        EqualOverloadPerson p(20);
        EqualOverloadPerson p2(30);
        EqualOverloadPerson p3(40);
        p3 = p2 = p;
        cout << "P1:" << *p.m_age << endl;
        cout << "P2:" << *p2.m_age << endl;
        cout << "P3:" << *p2.m_age << endl;
    }
```

### 4.5.5 关系运算符重载

作用: 重载关系运算符，可以让两个自定义对象进行对比操作

```
    class EqualOverloadPerson
    {

    public:
        int *m_age;
        EqualOverloadPerson(int age)
        {
            m_age = new int(age);
        }

        ~EqualOverloadPerson()
        {
            if (m_age != NULL)
            {
                delete m_age;
                m_age = NULL;
            }
        }

        EqualOverloadPerson &operator=(EqualOverloadPerson &p)
        {
            this->m_age = new int(*p.m_age);
            return *this;
        }

        bool operator==(const EqualOverloadPerson &p){
            return *this->m_age == *p.m_age;
        }

        bool operator!=(const EqualOverloadPerson &p)
        {
            return *this->m_age != *p.m_age;
        }

    };
```

### 4.5.6 函数调用运算符重载

函数调用运算符()也可以重载
由于重载后使用的方式非常像函数的调用，因此称之为仿函数
仿函数没有固定写法，非常灵活

```
    /// 实现 1
    class SelfPrint
    {
        public:
        void operator()(string text)
        {
            std::cout << "自定义输出: " << text << std::endl;
        }
    };

    void test05()
    {
        SelfPrint print;
        print("Hi");
    }
```

```
    /// @brief 函数调用运算符重载第二种实现
    class SelfAdd
    {
        public:
        /// @brief 仿函数
        /// @param n1 形参1
        /// @param n2 形参2
        /// @return 返回结果
        int operator()(int n1, int n2)
        {
            return n1 + n2;
        }
    };

    void test06()
    {
        /// SelfAdd() 相当于是创建一个匿名对象，使用完立即注销
        cout << SelfAdd()(4,5) << endl;
    }
```

