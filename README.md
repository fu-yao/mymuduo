### 项目介绍

​	本项目是通过学习chenshuo的开源网络库muduo，自己仿写的mymuduo网络库。由于muduo库比较大，此处只是实现了核心的网络部分，目的是实现一个轻量级的网络库，因此mymuduo去除了boost库的依赖，而改用C++11中提供的语法实现(bind，实际上也是从boost库中来)，然后针对Linux多线程api，则改用了thread去实现。




### 项目参考

[陈硕老师的Blog](http://www.cppblog.com/solstice/)

[Muduo源码分析](https://youjiali1995.github.io/network/muduo/)

[Reactor时间驱动的两种实现：面系对象VS函数式编程](https://www.cnblogs.com/me115/p/5088914.html)

[muduo源码剖析 - cyhone的文章 - 知乎](https://zhuanlan.zhihu.com/p/85101271)

[有什么适合提高C/C++网络编程能力的开源项目推荐？ - Variation的回答 - 知乎](https://www.zhihu.com/question/20124494/answer/733016078)

​	特别感谢《Linux多线程服务端编程》(陈硕著)该书籍对muduo网络库的设计理念及实现的介绍。
