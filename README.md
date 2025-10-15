#### C++项目创建及调试步骤
    1. 在资源管理器中创建项目文件夹
    2. 通过VSCode打开文件夹
    3. 创建项目目录结构
        > .vscode(系统生成c_cpp_properties.json时自动创建)
        > build
        > include
        > lib
        > src
        > test
        > readme.md
    4. Ctrl + Shift + P 或点击顶部搜索框 显示并运行命令 -> C/C++:编辑配置(UI)
    5. 编辑C/C++配置 增加包含路径(路径通过命令 g++ -v -E -x C++ - 打印), 增加 ${workspaceFolder}/include
    6. 在src下创建启动函数 main.cpp -> main方法
    7. 点击debug图标右侧齿轮图标, 项目在.vscode下自动生成launch.json
    8. 点击debud图标 调试C/C++文件, 首次选择"C/C++:g++.exe 构建和调试活动文件", 或点击"终端-配置默认生成任务", 系统自动生成tasks.json文件
    9. 编辑tasks.json,在args命令选项中 将 "${file}" 修改为 "${workspaceFolder}\\src\\*.cpp",
       "${fileDirname}\\${fileBasenameNoExtension}.exe" 修改为 "${workspaceFolder}\\build\\${workspaceFolderBasename}.exe",
       然后再数组最后添加"-I", "${workspaceFolder}\\include"

    ```
        "args": [
            "-fdiagnostics-color=always",
            "-g",
            "${workspaceFolder}\\src\\*.cpp",
            "-o",
            "${workspaceFolder}\\build\\${workspaceFolderBasename}.exe",
            "-I",
            "${workspaceFolder}\\include"
        ],
    ```
    
    10. 编辑launch.json 将 "program": "${fileDirname}\\${fileBasenameNoExtension}.exe" 指令 修改为  "program": "${workspaceFolder}\\build\\${workspaceFolderBasename}.exe",

    ```
        {
            "configurations": [

                {
                    "name": "C/C++: g++.exe 构建和调试活动文件",
                    "type": "cppdbg",
                    "request": "launch",
                    "program": "${workspaceFolder}\\build\\${workspaceFolderBasename}.exe",
                    "args": [],
                    "stopAtEntry": false,
                    "cwd": "D:/Coding/Qt/Tools/mingw810_32/bin",
                    "environment": [],
                    "externalConsole": false,
                    "MIMode": "gdb",
                    "miDebuggerPath": "D:\\Coding\\Qt\\Tools\\mingw810_32\\bin\\gdb.exe",
                    "setupCommands": [
                        {
                            "description": "为 gdb 启用整齐打印",
                            "text": "-enable-pretty-printing",
                            "ignoreFailures": true
                        },
                        {
                            "description": "将反汇编风格设置为 Intel",
                            "text": "-gdb-set disassembly-flavor intel",
                            "ignoreFailures": true
                        }
                    ],
                    "preLaunchTask": "C/C++: g++.exe 生成活动文件"
                }
            ],
            "version": "2.0.0"
        }

    ```
    11. 重新运行程序测试
