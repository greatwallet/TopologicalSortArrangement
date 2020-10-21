#include <fstream>
#include <vector>
#include "algo_v.h"

using namespace std;

algo_v::algo_v(const string& fname)
{
    ifstream fin(fname);
    int seq_len;
    fin >> seq_len;
    this->seq_len = seq_len;
    int left, right;
    while (fin >> left >> right)
    {
        tp con_{ left + 1, right + 1 };
        this->cons.push_back(con_);
    }
    fin.close();
    int a_len = this->seq_len + 1;
    vector<int> a(a_len, 0);
    for (int i = 0; i < a_len; i++) {
        a[i] = i;
    }
    this->a = a;
    vector<int> a_inv(a);
    this->a_inv = a_inv;
}


bool algo_v::in_tp(int _b, int _e) {

    for (unsigned int i = 0; i < this->cons.size(); i++) {
        int b_ = this->cons.at(i).b;
        int e_ = this->cons.at(i).e;
        if (b_ == _b && e_ == _e) return true;
    }
    return false;
}

void algo_v::print(vector<int> const& input) {
    for (unsigned int i = 0; i < input.size(); i++) {
		// change from 1-indexed to 0-indexed
        cout << input.at(i) - 1 << ' ';
    }
    cout << endl;
}

vector<int> algo_v::filter_out()
{
    vector<int> a_;
    for (unsigned int i = 0; i < this->a.size(); i++) {
        if (this->a.at(i) != 0) {
            a_.push_back(this->a.at(i));
        }
    }
    return a_;
}

bool algo_v::founded(vector<int> const& a_)
{
    for (unsigned int i = 0; i < this->all_top_sorts.size(); i++) {
        vector<int> a__ = this->all_top_sorts.at(i);
        if (a__ == a_) return true;
    }
    return false;
}

void algo_v::all_topological_sorts_K()
{

    // AlgorithmV
    // V1: initial
    int k = 0;
    int j = 0;
    int l = 0;

    bool flag = true;
    k = this->seq_len;
    int step = 0;
    while (flag) {
        // V3:
        j = this->a_inv.at(k);

        step += 1;
        if ((j < 1) or in_tp(this->a.at(j - 1), k)) {
            // V5:
            while (j < k) {
                l = this->a[j + 1];
                this->a[j] = l;
                this->a_inv[l] = j;
                j += 1;
            }
            this->a_inv[k] = k;
            this->a[k] = this->a_inv[k];
            k -= 1;
            if (k > 0) {
                // return to V3
                flag = true;
            }
            else {
                flag = false;
            }
        }
        else {
            l = this->a.at(j - 1);
            // V4:
            this->a[j - 1] = k;
            this->a[j] = l;
            this->a_inv[k] = j - 1;
            this->a_inv[l] = j;
            // return to V2
            k = this->seq_len;

            // add to sorts list
            vector<int> a_ = filter_out();
            
            if (!founded(a_)) {
                this->all_top_sorts.push_back(a_);
            }
        }
    }
}

void algo_v::show_result()
{
    cout << this->all_top_sorts.size() << " Result have been found:" << endl;
    for (unsigned int i = 0; i < this->all_top_sorts.size(); i++) {
        print(this->all_top_sorts.at(i));
    }
}
