# cpp_project

# 目标形态

拥有一条线路包含10个左右的站点，初始拥有5个左右车次（车次可以由管理员修改）
且使用Server/Client模式

该系统可以：

- 订票
- 退票
- 余票查询


# 设计思路

使用TCP来实现Server/Client模式
预计有站点、车次、车票这三个主要的类

站点应为：一个接着一个站点(将使用vector进行存储)，站点应包含id号（按id号排列的站点）、站点名、车站位置

车次使用vector进行存储，有车次id、发车方向、起始站、终点站、客容量、当前客容量、每个单位路程的价格、车次距离等级

车票使用vector进行存储，有车票id、车次id、始发站、终点站、价格

算法模型确定放票策略，通过对车次的始发站与终点站相差的站点数进行计算得出该车次的总距离，对应当需要放票时，确定放票的始发站与终点站相差的站点数，此时去除车次总距离小于放票相差的站数，按车次总距离从小到大对排序，依次判断直到找到符合其他项的车站。

# 模块划分

对订票、退票、余票查询的模块；
添加车次、编辑车次信息、删除车次的模块；
主要操作的UI界面模块；
TCP传输模块；

# 类派生结构

暂无需要派生的类

# 编译和使用说明

## 编译说明

本项目使用Server/Client 模式，在代码根目录打开terminal，使用sh build.sh进行编译

![image-20221213214456435](README.assets/image-20221213214456435.png)

## 使用说明

在根目录下生成out文件夹，接着分别使用两个terminal先后打开./server与./client

![image-20221213220101156](README.assets/image-20221213220101156.png)

在客户端输入用户id
便可以输入对应数字来进行操作

### 1. 订票

![image-20221213220130733](README.assets/image-20221213220130733.png)

输入数字1，然后分别输入出发站点id与到达站点（用空格隔开）

显示订票详细信息

### 2. 退票

![image-20221213220704445](README.assets/image-20221213220704445.png)

输入数字2，然后输入退票的id

<img src="README.assets/image-20221213220818051.png" alt="image-20221213220818051" style="zoom:67%;" />

已成功退票

### 3. 余票查询

![image-20221213220221267](README.assets/image-20221213220221267.png)

输入数字3，显示所有车次余票信息

### 4. 购票查询

![image-20221213220319226](README.assets/image-20221213220319226.png)

输入数字4，显示当前用户的所有购票信息

### 5. 站点查询

![image-20221213220941229](README.assets/image-20221213220941229.png)

输入数字5，显示所有站点信息

### 0. 退出客户端

注意最好使用此方法退出程序，否则可能出现端口占用，导致无法建立连接

若出现端口占用可修改server.cc与client.cc的的DEFINE MYPORT

![image-20221213223027116](README.assets/image-20221213223027116.png)![image-20221213223055743](编译和使用说明.assets/image-20221213223055743.png)

# 订票信息存储的数据结构和设计思路

## 订票信息存储的数据结构

存储在本地的ticket_data文件中

![image-20221213175544441](README.assets/image-20221213175544441.png)

第一行为当前放票id的计数
其余行每行为一张订票信息
依次为订票用户id, 车票id, 车次id, 出发站, 到达站, 车票价格

在程序中使用vector作为容器，类里的属性为：

```c++
private:
    int ticket_id; // 车票id
    int train_id; // 车次id
    int user_id; //用户id
    int ticket_start; // 车票起始站id
    int ticket_end; // 车票终点站id
    int ticket_price; // 车票价格
```

## 设计思路

车票id为当前放票id的计数，每增加一个车票，+1。
车次id为订票时通过放票策略选择的车次id
用户id为当前购票用户id
起始站id为用户购票输入的起始站
终点站id为用户购票输入的终点站
车票价格将根据输入的终点与起点，计算距离并乘上车次的价格/距离得出最终的车票价格

# 放票策略

通过对车次的始发站与终点站相差的站点数进行计算得出该车次的总距离，对应当需要放票时，确定放票的始发站与终点站相差的站点数，此时去除车次总距离小于放票相差的站数，按车次总距离从小到大对排序，依次判断直到找到符合其他项的车站。

# 验证策略效果截图

## 实验准备

### 车站配置

共10个车站

```c++
void init_station(std::vector<station>& stations) {
    stations.push_back(station(1, "A", 0));
    stations.push_back(station(2, "B", 10));
    stations.push_back(station(3, "C", 20));
    stations.push_back(station(4, "D", 30));
    stations.push_back(station(5, "E", 40));
    stations.push_back(station(6, "F", 50));
    stations.push_back(station(7, "G", 60));
    stations.push_back(station(8, "H", 70));
    stations.push_back(station(9, "I", 80));
    stations.push_back(station(10, "J", 90));
}
```

### 车次配置

共20个车次，每个车次均有3个载客量，起始站与终点站不一

```c++
void init_train(std::vector<train>& trains, std::vector<station>& stations) {
    trains.push_back(train(1, 1, 10, 3, 1));
    trains.push_back(train(2, 1, 7, 3, 1));
    trains.push_back(train(3, 2, 5, 3, 1));
    trains.push_back(train(4, 5, 8, 3, 1));
    trains.push_back(train(5, 8, 10, 3, 1));
}
```

### 测试起始站与终点站用例

```c++
int ticket_start_list[] = {8, 8, 8, 5, 5, 5, 2, 2, 2, 1, 1, 1, 1, 1, 1};
int ticket_end_list[] = {10, 10, 10, 8, 8, 8, 5, 5, 5, 7, 7, 7, 10, 10, 10};
```

为15个用例，若合理放票可以满足全部的用例

## 实验过程

分别对应优化的应用算法的测试与未优化的测试

```c++
for (int i = 0; i < 15; i++) {
        
        int ticket_start = ticket_start_list[i];
        // ticket_end 不能等于 ticket_start
        int ticket_end = ticket_end_list[i];
        addTicketNoOptimized(user_id, ticket_num_common, ticket_start, ticket_end, trains, tickets_common, stations);
        addTicket(user_id, ticket_num, ticket_start, ticket_end, trains_common, tickets, stations);
    }
```

## 实验结果

使用算法优化放票策略的上座率: 100%
不使用算法优化放票策略的上座率: 60%
