# 代码说明


## 四种全排列算法的实现


主要代码在头文件sort_four.h中，该头文件主要包含5个函数，分别是

```c++
string lexicographicalOrder(string origin, int n);
```

返回字典序法下origin往后的第$n$个排列

```c++
string increaseOrder(string origin, int n);
```

返回递增进位制法下origin往后的第$n$个排列

```c++
string decreaseOrder(string origin, int n);
```

返回递减进位制法下origin往后的第$n$个排列

```c++
string SJTOrder(string origin, int n);
```

返回邻位对换法下origin往后的第$n$个排列

```c++
void test(const string& inputFile,const string& outputFile,string (*pfun)(string,int),int str_size = 7)
```

其中inputFile为输入文本文件（拓扑排序的约束），outputFile为输出文本文件（在某种全排列生成算法下满足拓扑排序的序列在整个序列中的分布）,pfun为选择的全排列生成算法（字典序法、递增进位制法、递减进位制法、邻位对换法），str_size为待排列的元素个数



result文件夹中，result_11.txt到result_14.txt分别为拓扑约束满足DAG-08.txt中的约束时满足拓扑排序的序列在整个排列中的分布，result_21.txt到result_24.txt分别为拓扑约束满足DAG-03.txt中的约束时满足拓扑排序的序列在整个排列中的分布。（1指字典序法，2指递增进位制法，3指递减进位制法，4指邻位对换法），result_11.png到result_24.png为可视化的结果


## 相邻交换法的实现

主要的实现在algo_v.h 和 algo_v.cpp的文件里。
```c++
#define FILE_NAME "DAG.txt"
```
定义了拓扑约束的输入，以文件形式存储。其中文件第一行表示全部元素数目，第二行以后表示约束，要求左边的数在排列中位于右边的数之前

```c++
void algo_v::all_topological_sorts_K();
```
算法的主要实现在类内的这个函数中




