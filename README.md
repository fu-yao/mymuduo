### 项目介绍

​	本项目是通过学习chenshuo的开源网络库muduo，自己仿写的mymuduo网络库。由于muduo库比较大，此处只是实现了核心的网络部分，目的是实现一个轻量级的网络库，因此mymuduo去除了boost库的依赖，而改用C++11中提供的语法实现(bind，实际上也是从boost库中来)，然后针对Linux多线程api，则改用了thread去实现。

​	特别感谢《Linux多线程服务端编程》(陈硕著)该书籍对muduo网络库的设计理念及实现的介绍。

​	
