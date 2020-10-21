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



