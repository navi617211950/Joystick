#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>

using namespace std;

namespace testfile
{

    void test01()
    {
        // 1. 包含ftream头文件
        // 2. 创建写流对象
        ofstream ofs;
        // 3. 打开写的文件
        ofs.open("test.txt", ios::out);
        // 4. 写数据
        ofs << "Hi from VScode" << endl;
        // 5. 关闭流对象
        ofs.close();
    }

    void testFile()
    {
         cout << __FILE__ << endl;
         cout << __BASE_FILE__ << endl;
         test01();
    }
} // namespace testfile
