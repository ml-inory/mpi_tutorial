# mpi_tutorial
Code for learning MPI

学习MPI的过程

## 安装MPI

Ubuntu:
```
sudo apt-get install mpich
```

输入```mpiexec --version```若无报错则表示安装成功


## 编译

```bash build.sh```
编译完成后的程序生成在install目录下


## 运行

```mpirun -n 进程数 程序```

  
进程数量设置太大的话可能会让系统崩溃

示例:
```
mpirun -n 4 ./install/hello_world

Hello world from processor DESKTOP-5LKI0VV, rank 0 out of 4 processors
Hello world from processor DESKTOP-5LKI0VV, rank 2 out of 4 processors
Hello world from processor DESKTOP-5LKI0VV, rank 1 out of 4 processors
Hello world from processor DESKTOP-5LKI0VV, rank 3 out of 4 processors
```
进程之间的打印顺序是任意的，因为我们的代码里并没有涉及到同步的操作


如果你有多个节点可以通过host文件来设置，host文件的格式为：
每行一个配置了免密码SSH登录的机器名称，如：
```
server1
server2
server3
server4
```

如果想让MPI在每个节点的多个核上生成进程，再去其他的奇迹，可以在节点后面加上冒号和处理器核数，如:
```
server1:2
server2:1
server3:4
server4:8
```

运行时通过-f参数指定host文件路径，或者通过MPI_HOSTS环境变量配置, 如:
```
mpirun -n 4 -f host_file ./install/hello_world
```

各个程序的运行方式在[RUN.md](/RUN.md)