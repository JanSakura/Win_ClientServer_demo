# Win_ClientServer_demo
message.hpp是封装的互相通信的消息结构体，为Client和Server共用的

使用类进行封装基本的server和client网络通信步骤。

并用struct发送，进行判断，节省网络IO

使用双缓冲区，解决粘包问题；

使用多线程提高性能

解决线程数据一致性、保护问题
