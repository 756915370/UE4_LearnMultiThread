# UE4_LearnMultiThread
 这个工程展示了使用ue4里的各种多线程的方式。有三个场景和三个蓝图。
 ![在这里插入图片描述](https://img-blog.csdnimg.cn/93440312c5e3415eaa89fc4ef7ad2c1b.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5rC05puc5pel6bih,size_15,color_FFFFFF,t_70,g_se,x_16#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/dd05be9f0b0c43f79b01426dc71ed86a.png#pic_center)

具体讲解文章：[【UE·引擎篇】Runnable、TaskGraph、AsyncTask、Async多线程开发指南](https://zhuanlan.zhihu.com/p/463272214)

### Runnable
**Bp_Tast_Runnable**的功能为：
- 从自定义Actor子类**ATestRunnableActor**里获取一个数字，然后在多线程里实现一个计数器，当计数器大于这个数字时，线程退出。

**FRunnable（线程执行体）和FRunnableThread（线程类）**是最简单的实现多线程方式，它只有**创建、暂停、销毁、等待完成**等基础功能。在实战中也较少用到。
### TaskGraph
我们以游戏开发中工作流为例：
- 首先是策划提出需求案子
- 然后美术设计概念图
	- 模型师根据概念图建模
	- 动画师等建模完成后制作动画
- 程序在案子提出后开发特性
- 等上面全部完成后策划进行验收

而程序特性比较复杂，将分给三个程序员分别开发（**即子任务**）。
![在这里插入图片描述](https://img-blog.csdnimg.cn/5d6d7f6feafa41728e8780d18e9a86fa.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5rC05puc5pel6bih,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)
同时这个需求非常重要，老板很关心开发进度，上面的每一步做完之后都要跟他汇报才算真正完成。这个需要使用**TaskGraph的DontCompleteUntil**功能。

具体查看**Bp_TestTaskGraph**蓝图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/4bae292bbbc4424daad9dc858ac4deb7.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5rC05puc5pel6bih,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)
TaskGraph适合有依赖关系的多线程任务。**指定使用哪个线程的时候要注意一些逻辑只能在GameThread上调用**。如
- 创建、消耗Actor
- Debug绘制函数
- 定时器 TimerManager

### Async和AsyncTask
我们将计算一个1到1000w的开根号，并求和，最后除以1000w的简单逻辑。并且计算主线程执行时长和逻辑计算总时长，来比较不同方法之间的差距。
- **主线程执行时长**的计算方式是创建多线程之前记录时间点，然后创建完之后记录时间点，两者相减。
- **逻辑计算总时长**是多线程里计算出结果以后的时间点减去创建多线程之前的时间点。

**Bp_TestAsync**包含使用AsyncTask类，使用AsyncTask全局方法和使用Async全局方法的不同测试方法。
![在这里插入图片描述](https://img-blog.csdnimg.cn/30015044e6cf4941b398dcd0e73da095.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5rC05puc5pel6bih,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

AsyncTask系统实现的多线程与你自己字节继承FRunnable实现的原理相似，还可以利用UE4提供的线程池。当使用多线程不满意时也可以调用**StartSynchronousTask改成主线程执行**。

**AsyncTask方法是TaskGraph的简单版本。需要有返回值和回调函数的时候使用Async方法。Async性能较差没事不用它**。

***
### 学习资料
- [《Exploring in UE4》多线程机制详解[原理分析]](https://zhuanlan.zhihu.com/p/38881269)  
- [UE4/UE5的TaskGraph](https://cloud.tencent.com/developer/article/1897046)  
- [b站：【合集】UE4 C++进阶[进行中]](https://www.bilibili.com/video/BV14p4y1a7nj?p=7)  
- [C++ decltype类型推导完全攻略](http://c.biancheng.net/view/7151.html)  
- [C++11完美转发及实现方法详解](http://c.biancheng.net/view/7868.html)  
- [2w字 + 40张图带你参透并发编程！ ](https://www.cnblogs.com/cxuanBlog/p/13523033.html)  
***
关于作者
- 我是**水曜日鸡**，喜欢ACG的游戏程序员。曾参与索尼中国之星项目《硬核机甲》的开发。 目前在某大厂做UE4项目。

CSDN博客：[https://blog.csdn.net/j756915370](https://blog.csdn.net/j756915370)  
知乎专栏：[https://zhuanlan.zhihu.com/c_1241442143220363264](https://zhuanlan.zhihu.com/c_1241442143220363264)  
游戏同行聊天群：891809847
