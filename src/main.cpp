#include <iostream>
#include "box.h"
#include "point.h"
#include "circle.h"
#include "person.h"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "Joystick started." << endl;
    // Box *b = new Box;
    // b->setName("BBox");
    // b->sayHi();
    /// 括号法调用point类的有参构造函数
    Point p(4,0);
    /// 使用括号法调用Point类的拷贝构造函数
    Point c(p);
    Circle cir;
    cir.setCenter(c);
    cir.setMRange(3);
    isInCircle(p, cir);

    Person p1 = Person();
    /**
     * 显示调用构造函数, Person(10) 相当于是一个匿名对象
     * 当前行执行结束后，系统会自动回收掉匿名对象
     */
    Person p2 = Person("zhangsi");

    //拷贝构造函数
    Person p3 = Person(p2);

    //注: 不要利用拷贝构造函数初始化匿名对象 Person(p3) 等价于 Person p3
    // Person(Person("lisi")) 语法校验通过，但是没有意义
    //Person(p3)
    
    //隐式转换法 但是Person p4 = "张三"语法校验不通过，"张三"会被理解为const char[]类型，找不到对应的构造函数
    string name =  "zhangsan";
    Person p4 =name;
    
    return 0;
}
