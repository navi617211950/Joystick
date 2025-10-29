# 5 C++文件读写操作

通过文件读写将数据持久化

C++对文件操作需要包含头文件`<fstream>`

文件类型分为两种:
* 文本文件: 文件以文本的ASCII码形式存储在计算机中
* 二进制文件: 文件以文本的二进制形式存储在计算机中，用户一般不能直接读懂它们

操作文件的三大类:
* ofstream: 写操作
* ifstream: 读操作
* ftream: 读写操作

## 5.1 文本文件

### 5.1.1 写文件

#### 写文件的步骤:
1. 包含头文件 `#include <fstream>`
2. 创建流对象 `ofstream ofs`
3. 打开文件 `ofs.open("文件路径", 打开方式);`
4. 写数据 `ofs << "写入的数据";`
5. 关闭流 `ofs.close();`

##### 附: 文件打开方式:
* `ios::in`   为读文件而打开文件
* `ios::out`    为写文件而打开文件
* `ios::ate`    初始位置: 文件尾
* `ios::app`    追加方式写文件
* `ios::trunc`   如果文件存在,先删除再创建
* `ios::binary`   二进制形式
* 文件打开方式配合使用，利用 ` | `操作符号
* 例如用二进制写文件 ` ios::out | ios::binary`


#### 总结:
* 文件操作必须包含头文件`fstream`
* 写文件可以利用`ofstream`，或者`fstream`类
* 打开文件需要指定操作文件的路径，以及打开方式
* 利用`<<`可以向文件中写数据
* 操作完毕，要关闭文件和流对象

### 5.1.2 读文件

读文件与写文件步骤相似, 但是读取方式相对于比较多

#### 读文件步骤:
1. 包含头文件 ` #include <ftream>`
2. 创建流对象` ifstream ifs`
3. 打开文件并判断文件是否打开成功` ifs.open("文件路径", 打开方式)`
4. 读取数据(四种)
5. 关闭流对象` ifs.close()`

#### 四种读取方式

```
    void test02()
    {
        ifstream ifs;
        ifs.open("test.txt", ios::in);
        if(ifs.is_open())
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
            while(getline(ifs, buf))
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
```

#### 总结
* 读文件可以利用`ifstream`，或者`fstream`类
* 利用`ifs.is_open()`函数可以判断文件是否打开成功
* `ifs.close()`函数关闭流对象


## 5.2 二进制文件读写

以二进制方式对文件读写操作
打开方式要制定 `ios::binary`

### 5.2.1 写文件

* 二进制方式写文件主要利用流对象调用成员函数`write`
* 函数原型: `ostream & write(const char * buffer, int len);`
* 参数解释: 字符指针buffer指向内存中的一段存储空间, len是读写的字节数

代码:

```
void writeBinaryFile()
{
    //1. 包含头文件
    Person p = {"张三", 18};
    //2. 创建流对象
    //3. 打开文件
    ofstream ofs("person.txt", ios::out | ios::binary);
    //ofs.open("person.txt", ios::out | ios::binary);
    //4. 写数据
    ofs.write((const char *)&p, sizeof(p));
    //5. 关闭流对象
    ofs.close();
}
```

### 5.2.2 读文件

* 二进制方式读文件主要利用流对象调用成员函数`read`
* 函数原型: `istream& read(char *buffer, int len);`
* 参数解释: 字符指针buffer指向内存中的一段存储空间, len是读写的字节数

代码:

```
void readBinaryFile()
{
    ifstream ifs;
    ifs.open("person.txt", ios::in | ios::binary);
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
```