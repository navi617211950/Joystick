#include <iostream>
#include <windows.h>
#include "box.h"
#include "point.h"
#include "circle.h"
#include "person.h"
#include "building.h"
#include "color.h"
#include "nvtest.h"

using namespace std;

int main(int argc, char const *argv[])
{
    //设置文本颜色为红色
    navis::setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "Joystick started." << endl;
    // // Box *b = new Box;
    // // b->setName("BBox");
    // // b->sayHi();
    // /// 括号法调用point类的有参构造函数
    // Point p(4,0);
    // /// 使用括号法调用Point类的拷贝构造函数
    // Point c(p);
    // Circle cir;
    // cir.setCenter(c);
    // cir.setMRange(3);
    // isInCircle(p, cir);

    // Person p1 = Person();
    // /**
    //  * 显示调用构造函数, Person(10) 相当于是一个匿名对象
    //  * 当前行执行结束后，系统会自动回收掉匿名对象
    //  */
    // Person p2 = Person("zhangsi", 12);

    // //拷贝构造函数
    // Person p3 = Person(p2);

    // //注: 不要利用拷贝构造函数初始化匿名对象 Person(p3) 等价于 Person p3
    // // Person(Person("lisi")) 语法校验通过，但是没有意义
    // //Person(p3)
    
    // //隐式转换法 但是Person p4 = "张三"语法校验不通过，"张三"会被理解为const char[]类型，找不到对应的构造函数
    // // 隐式转换法中的拷贝构造直接通 过等号赋值即可
    // Person p4 = {"zhangsan", 12};

    //空指针调用成员函数的注意事项
    // NullTestPerson *n = NULL;
    // n-> showClassName();
    // // 調用第二個方法錯誤，因为此方法中调用了对象中的属性，无法在空指针的情况下调用
    // n->showPersonAge();


    // const ConstTestPerson p;
    // p.m_boll = 200;
    // p.showPerson();
    // // 常对象只能调用常函数，因为普通函数有可能会修改成员属性，
    // //p.func();
    //设置文本颜色为绿色
    navis::setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    test05();
    //恢复文本颜色
    navis::setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

    //测试字符串
    navis::test();
    return 0;
}


