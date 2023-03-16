# Win_ClientServer_demo
方便debug可以定义宏
```
#define DEBUG 1
#if DEBUG 
#define Print(fmt,...) \
printf("File:%s ,Func:%s ,Line:%d ;" fmt,__FILE__,__FUNCDNAME__,__LINE__,__VA_ARGS__)
#else
#define Print(fmr,...)
#endif
```


message.hpp是封装的互相通信的消息结构体，为Client和Server共用的

使用类进行封装基本的server和client网络通信步骤。

并用struct发送，进行判断，节省网络IO

使用双缓冲区，解决粘包问题；

使用多线程提高性能

解决线程数据一致性、保护问题
内存池，解决内存碎片化问题
