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
        ofs << "Hi from Joystick in the VScode" << endl;
        // 5. 关闭流对象
        ofs.close();
    }

    void test02()
    {
        ifstream ifs;
        ifs.open("test.txt", ios::in);
        if (ifs.is_open())
        {
            // 1. 第一种读取方式
            // char buf[1024] = {0};
            // while(ifs >> buf)
            // {
            //     cout << buf << endl;
            // }

            // 2. 第二种 使用流对象的getline函数读取
            // char buf[1024] = {0};
            // while(ifs.getline(buf, sizeof(buf)))
            // {
            //     cout << buf << endl;
            // }

            // 3.通过cstring的getline全局函数读取数据
            string buf;
            while (getline(ifs, buf))
            {
                cout << buf << endl;
            }

            // 4. 通过字符读取数据，不推荐
            // char c;
            // while((c = ifs.get()) != EOF) //EOF: END OF FILE;
            // {
            //     cout << c;
            // }
        }
        ifs.close();
    }

    class Person
    {
    public:
        char m_name[64];
        int m_age;
    };

    void writeBinaryFile()
    {
        //1. 包含头文件
        Person p = {"张三", 18};
        //2. 创建流对象
        //3. 打开文件
        ofstream ofs("person.dat", ios::out | ios::binary);
        //ofs.open("person.txt", ios::out | ios::binary);
        //4. 写数据
        ofs.write((const char *)&p, sizeof(p));
        //5. 关闭流对象
        ofs.close();
    }

    void readBinaryFile()
    {
        ifstream ifs;
        ifs.open("person.dat", ios::in | ios::binary);
        if(ifs.is_open())
        {
            // 推荐在栈区声明一个Person对象，然后在read函数中传p的地址; 直接传指针对象不安全
            Person p;
            ifs.read((char *)&p, sizeof(Person));
            cout << p.m_name << endl;
            cout << p.m_age << endl;
            ifs.close();
            
        }
        else
        {
            cout << "Error: 文件打开失败" << endl;
            return;
        }
    }

    void testFile()
    {
        // cout << __FILE__ << endl;
        // cout << __BASE_FILE__ << endl;
        // test01();
        // test02();
        writeBinaryFile();
        readBinaryFile();
    }
} // namespace testfile
