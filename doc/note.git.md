## vscode 中git相关问题

#### 1. 打开VPN后，github.com可以正常访问，但是git指令报443错误

* 使用命令取消http代理设置后重试
```
git config --global --unset http.proxy
```

* 如果不行，则手动配置git走vpn代理

```
// 11107是shadowrocket的代理端口
git config --global http.proxy http://127.0.0.1:11107 
git config --global https.proxy http://127.0.0.1:11107
```