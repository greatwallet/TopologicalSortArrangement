//
// Created by 郑欣阳 on 2020/10/21.
//

#ifndef TEST_SORT_FOUR_H
#define TEST_SORT_FOUR_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
using namespace std;

int factorial[10] = { 1,1,2,6,24,120,720,5040,40320,362880 }; //从0!到9!，预先计算好
void processOrder(vector<int>& k_compare, int n) {
    //适用于字典序和递增进位制序，处理中介数的后n项
    int length = k_compare.size() + 1;
    int SeqNumber = 0;
    for (int i = length - 1; i > 0; i--) {
        SeqNumber += k_compare[length - 1 - i] * factorial[i];
    }
    SeqNumber += n;
    //接下来开始计算新的中介数
    for (int i = length - 1; i > 0; i--) {
        k_compare[length - 1 - i] = SeqNumber / factorial[i];
        SeqNumber -= k_compare[length - 1 - i] * factorial[i];
    }
}
void check_lexicographical(vector<int>& data, int i) {
    bool finished;
    vector<bool> visted(i, false);
    do {
        finished = true;
        for (int j = 0; j < i; j++) {
            if (visted[j]==false && data[j] <= data[i]) {
                visted[j] = true;
                finished = false;
                data[i] += 1;
                break;
            }
        }
    } while (!finished);
}
int lexicographicalLast(vector<int>& data, int n) {
    for (int i = 1; i <= n; i++) {
        if (find(data.begin(), data.end(), i)==data.end()) {
            return i;
        }
    }
    return 0;
}
string lexicographicalOrder(string origin, int n) {
    //原始排列为origin e.g.: 83674321,序号为37313
    //想要得到它之后的第n个排列
    int length = origin.length();
    vector<int> data(length);
    for (int i = 0; i < length; i++) {
        data[i] = origin[i] - '0';
    }
    //计算中介数
    vector<int> k_compare(length - 1, 0);//中介数
    for (int i = 0; i < length-1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (data[j] < data[i]) {
                k_compare[i] += 1;
            }
        }
    }
    processOrder(k_compare, n);
    //然后由中介数复原回排列
    for (int i = 0; i < length - 1; i++) {
        data[i] = k_compare[i]+1;
        check_lexicographical(data, i);
    }
    data[length - 1] = 0;
    data[length - 1] = lexicographicalLast(data,length);
    for (int i = 0; i < length; i++) {
        origin[i] = data[i] + '0';
    }
    return origin;
}
string increaseOrder(string origin, int n) {
    //原始排列为origin e.g.: 83674321,递增进位制数为742221
    //想要得到它之后的第n个排列
    int length = origin.length();
    vector<int> data(length);
    for (int i = 0; i < length; i++) {
        data[i] = origin[i] - '0';
        //cout << data[i] << endl;
    }
    //计算中介数
    vector<int> k_compare(length - 1, 0);//中介数
    for (int i = 0; i < length - 1; i++) {
        int index = length - i;
        auto pos = find(data.begin(), data.end(), index);
        //增序的中介数的a_i指的是i右边有多少个比i小的数
        for (auto j = pos + 1; j < data.end(); j++) {
            if (*j < length - i) {
                k_compare[i] += 1;
            }
        }
    }
    processOrder(k_compare, n);
    //接下来要从中介数恢复序列
    vector<bool> visted(length, false);
    for (int i = 0; i < length - 1; i++) {
        int index = 0;
        int j;
        for (j = length - 1; index < k_compare[i]; j--) {
            if (!visted[j]) {
                index += 1;
            }
        }
        for (; visted[j]; j--);
        data[j] = length - i;
        visted[j] = true;

        for (int i = 0; i < length; i++) {
            if (!visted[i]) {
                data[i] = 1;
            }
        }}
    for (int i = 0; i < length; i++) {
        origin[i] = data[i] + '0';
    }
    return origin;
}
string decreaseOrder(string origin, int n) {
    int length = origin.length();
    vector<int> data(length);
    for (int i = 0; i < length; i++) {
        data[i] = origin[i] - '0';
        //cout << data[i] << endl;
    }
    //计算中介数
    vector<int> k_compare(length - 1, 0);//中介数
    for (int i = 0; i < length - 1; i++) {
        int index = length - i;
        auto pos = find(data.begin(), data.end(), index);
        //先计算a_i（i右边有多少个比i小的数）
        for (auto j = pos + 1; j < data.end(); j++) {
            if (*j < length - i) {
                k_compare[i] += 1;
            }
        }
    }
    reverse(k_compare.begin(), k_compare.end());
    int SeqNumber = k_compare[0];
    for (int i = 0; i <length - 2; i++) {
        SeqNumber = SeqNumber * (i + 3) + k_compare[i+1];
    }
    SeqNumber += n;
    //接下来开始计算新的中介数
    for (int i = length - 1; i > 0; i--) {
        int temp = SeqNumber / (i + 1);
        k_compare[i - 1] = SeqNumber - temp * (i + 1);
        SeqNumber = temp;
    }
    reverse(k_compare.begin(), k_compare.end());
    vector<bool> visted(length, false);
    for (int i = 0; i < length - 1; i++) {
        int index = 0;
        int j;
        for (j = length - 1; index < k_compare[i]; j--) {
            if (!visted[j]) {
                index += 1;
            }
        }
        for (; visted[j]; j--);
        data[j] = length - i;
        visted[j] = true;
    }
    for (int i = 0; i < length; i++) {
        if (!visted[i]) {
            data[i] = 1;
        }
    }
    for (int i = 0; i < length; i++) {
        origin[i] = data[i] + '0';
    }
    return origin;
}
string SJTOrder(string origin, int n) {
    //TODO: 邻位对换法的全排列生成
    int length = origin.length();
    vector<int> data(length);
    for (int i = 0; i < length; i++) {
        data[i] = origin[i] - '0';
    }
    vector<int> b(length - 1, 0);//中介数
    for (int i = 2; i <= length; i++) {
        auto pos = find(data.begin(), data.end(), i);
        //增序的中介数的a_i指的是i右边有多少个比i小的数
        if (i == 2) {
            //2的方向一定向左
            auto index = find(data.begin(), data.end(), 1);
            if (index < pos) {
                b[0] = 0;
            }
            else
            {
                b[0] = 1;
            }
        }
        else
        {
            if (i % 2 == 1) {
                //如果i为奇数，那么就考虑b_{i-1}
                if (b[i - 3] % 2 == 0) {
                    //偶向左
                    for (auto p = pos + 1; p < data.end(); p++) {
                        if (*p < i) {
                            b[i - 2] += 1;
                        }
                    }
                }
                if (b[i - 3] % 2 == 1) {
                    //奇向右
                    for (auto p = data.begin(); p < pos; p++) {
                        if (*p < i) {
                            b[i - 2] += 1;
                        }
                    }
                }
            }
            else
            {
                //偶看两位
                if ((b[i - 3] + b[i-4])% 2 == 0) {
                    //偶向左
                    for (auto p = pos + 1; p < data.end(); p++) {
                        if (*p < i) {
                            b[i - 2] += 1;
                        }
                    }
                }
                if ((b[i - 3] + b[i - 4]) % 2 == 1) {
                    //奇向右
                    for (auto p = data.begin(); p < pos; p++) {
                        if (*p < i) {
                            b[i - 2] += 1;
                        }
                    }
                }
            }
        }
    }
    int SeqNumber = b[0];
    for (int i = 0; i < length - 2; i++) {
        SeqNumber = SeqNumber * (i + 3) + b[i + 1];
    }
    SeqNumber += n;
    //接下来开始计算新的中介数
    for (int i = length - 1; i > 0; i--) {
        int temp = SeqNumber / (i + 1);
        b[i - 1] = SeqNumber - temp * (i + 1);
        SeqNumber = temp;
    }
    //接下来开始由中介数恢复序列
    vector<bool> visted(length, false);
    for (int i = length - 2; i >= 1; i--) {
        if (i % 2 == 0) {
            if ((b[i - 2] + b[i - 1]) % 2 == 0) {
                //偶向左
                int index = 0;
                int j;
                for (j = length - 1; index < b[i]; j--) {
                    if (!visted[j]) {
                        index += 1;
                    }
                }
                for (; visted[j]; j--);
                data[j] = i + 2;
                visted[j] = true;
            }
            else{
                //奇向右
                int index = 0;
                int j;
                for (j = 0; index < b[i]; j++) {
                    if (!visted[j]) {
                        index += 1;
                    }
                }
                for (; visted[j]; j++);
                data[j] = i + 2;
                visted[j] = true;
            }
        }
        if (i % 2 == 1) {
            if (b[i - 1] % 2 == 0) {
                //偶向左
                int index = 0;
                int j;
                for (j = length - 1; index < b[i]; j--) {
                    if (!visted[j]) {
                        index += 1;
                    }
                }
                for (; visted[j]; j--);
                data[j] = i + 2;
                visted[j] = true;
            }
            else {
                //奇向右
                int index = 0;
                int j;
                for (j = 0; index < b[i]; j++) {
                    if (!visted[j]) {
                        index += 1;
                    }
                }
                for (; visted[j]; j++);
                data[j] = i + 2;
                visted[j] = true;
            }
        }
    }
    //2一定向左
    int index = 0;
    int j;
    for (j = length - 1; index < b[0]; j--) {
        if (!visted[j]) {
            index += 1;
        }
    }
    for (; visted[j]; j--);
    data[j] = 2;
    visted[j] = true;
    //最后一个位置把1填上
    for (int i = 0; i < length; i++) {
        if (!visted[i]) {
            data[i] = 1;
        }
    }
    for (int i = 0; i < length; i++) {
        origin[i] = data[i] + '0';
    }
    return origin;
}


bool checkOrder(std::vector<std::pair<int, int>>& compare,const std::string& str) {
    //特别注意：文件中的输入从0开始
    vector<int> data(str.size(), 0);
    for (auto i = 0; i < data.size(); i++) {
        data[i] = str[i]  - '0' ;
    }
    bool succ = true;
    for (auto i = 0; i < compare.size(); i++) {
        auto test = compare[i];
        int index_1 = 0;
        int index_2 = 0;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == test.first) {
                index_1 = i;
            }
            if (data[i] == test.second) {
                index_2 = i;
            }
        }
        if (index_1 > index_2) {
            succ = false;
            break;
        }
    }
    return succ;
}

void test(const string& inputFile,const string& outputFile,string (*pfun)(string,int),int str_size = 7)
{
    //cout << INT32_MAX << endl;
    //实际上用int 的长度就足够了
    std::ifstream input(inputFile);
    std::vector<std::pair<int, int>> compare;
    std::string temp, word1,word2;
    int i = 0;
    while (std::getline(input, temp)) {
        std::istringstream iss(temp);
        iss >> word1;
        iss >> word2;
        int less_one = std::atoi(word1.c_str()) + 1;
        int big_one = std::atoi(word2.c_str()) + 1;
        //cout << less_one <<" "<<big_one << endl;
        compare.push_back(pair<int, int>(less_one, big_one));
        //compare.emplace_back(less_one, big_one);
    }
    int length = str_size;
    string initial_str(length, '0');
    for (int i = 0; i < length; i++) {
        initial_str[i] = i + '1';
    }
    string str;

    int count = 0;
    vector<int> succ(factorial[length], 0);
    for (int i = 0; i < factorial[length]; i++) {
        str = pfun(initial_str, i);
        //cout<<str<<endl;
        if (checkOrder(compare, str)) {
            succ[i] = 1;
            count++;
        }
    }


    std::ofstream out;
    out.open(outputFile);
    for (int i = 0; i < factorial[length]; i++) {
        if (succ[i] == 1) {
            out << i + 1<< endl;
        }
    }
    out.close();
    /*string str =lexicographicalOrder("83674521", -2020);
    cout << str << endl;
    str = increaseOrder("83674521", -2020);
    cout << str << endl;
    str = decreaseOrder("83674521", -2020);
    cout << str << endl;
    str = SJTOrder("83674521", -2020);
    cout << str << endl;*/
}

#endif //TEST_SORT_FOUR_H
