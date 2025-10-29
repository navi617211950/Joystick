## vscode 中git相关问题

#### 1. 打开VPN后，github.com可以正常访问，但是git指令报443错误

* 使用命令取消http代理设置后重试
    ```
        git config --global --unset http.proxy
    ```