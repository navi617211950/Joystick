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
