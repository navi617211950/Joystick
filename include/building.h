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