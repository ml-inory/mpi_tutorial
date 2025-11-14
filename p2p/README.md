# MPI P2P通信

主要通过Send和Recv两个API完成，在MPI中是同步（或阻塞的）

## MPI的发送和接收简介

MPI 的发送和接收方法是按以下方式进行的：开始的时候，A 进程决定要发送一些消息给 B 进程。A进程就会把需要发送给B进程的所有数据打包好，放到一个缓存里面。因为所有数据会被打包到一个大的信息里面，因此缓存常常会被比作信封（就像我们把好多信纸打包到一个信封里面然后再寄去邮局）。数据打包进缓存之后，通信设备（communicator, 通常是网络）就需要负责把信息传递到正确的地方。这个正确的地方也就是根据特定秩确定的那个进程。

尽管数据已经被送达到 B 了，但是进程 B 依然需要确认它想要接收 A 的数据。一旦它确定了这点，数据就被传输成功了。进程 A 会接收到数据传递成功的信息，然后去干其他事情。

有时候 A 需要传递很多不同的消息给 B。为了让 B 能比较方便地区分不同的消息，MPI 运行发送者和接受者额外地指定一些信息 ID (正式名称是标签, tags)。当 B 只要求接收某种特定标签的信息的时候，其他的不是这个标签的信息会先被缓存起来，等到 B 需要的时候才会给 B。


**发送API**
```
MPI_Send(
    void* data,
    int count,
    MPI_Datatype datatype,
    int destination,
    int tag,
    MPI_Comm communicator)
```

MPI_Send会通过communicator发送count个datatype类型的打了tag的data到destination

**接收API**
```
MPI_Recv(
    void* data,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm communicator,
    MPI_Status* status)
```

MPI_Recv通过communicator从source最多会接收count个标签为tag的datatype类型的data，status提供了接收到的数据的状态。

MPI提供了基础数据类型作为datatype参数，它们与C语言对应如下:

| MPI datatype | C equivalent |
| ---- | ---- |
| MPI_SHORT | short int |
| MPI_INT | int |
| MPI_LONG | long int |
| MPI_LONG_LONG | long long int |
| MPI_UNSIGNED_CHAR | unsigned char |
| MPI_UNSIGNED_SHORT | unsigned short int |
| MPI_UNSIGNED | unsigned int |
| MPI_UNSIGNED_LONG | unsigned long int |
| MPI_UNSIGNED_LONG_LONG | unsigned long long int |
| MPI_FLOAT | float |
| MPI_DOUBLE | double |
| MPI_LONG_DOUBLE | long double |
| MPI_BYTE | char |

还可以创建自己的MPI数据类型来构建更复杂的消息类型
