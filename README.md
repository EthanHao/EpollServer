# TCP Server
A high efficient Tcp server based on Epoll, Using reactor and producer consumer threadpool pattern. And use memory pool to improve the efficiency. prefer to use binary protocol to support some financial trading.  


Instruction  
###  1. Simply introduce the Reactor pattern.   
Usually the reactor pattern use one process and one thread. The main goal of Reactor pattern is to seperate the application sepecific code. 

![reactor](./Portal/reactor.png)

### 2. Reactor pattern with threadpool

  ![Open Device](./Portal/reactorWithPool.png)

### 3.The detail of worker

  ![Open](./Portal/ReactorMoreDetail.png)


  
