#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;

chrono::high_resolution_clock::time_point st;
chrono::high_resolution_clock::time_point et;

long long cnt = 0; //debugging

void measure_start(string message) {
    cout << message << " is measuring..." << endl;
    st = chrono::high_resolution_clock::now();
}

void measure_end(string message) {
    et = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(et - st);
    cout << message << " : " << time_span.count() << " seconds" << endl;;
}

template<typename T>
void print_data(vector<T> &data, int r) {
    for(int i = 0; i < r; i++) {
            cout << data[i] << " ";
        }
    cout << endl;
}


//nCr = C(n, r) = n! / (r! * (n - r)!)
template<typename T>
void _combination_recursion(vector<T> &data, int n, int r, int index, vector<T> &out) {
    if(out.size() == r) {
        // print_data(out, r);
        ++cnt;
        return;
    }

    for(int i = index; i < n; i++) {
        out.push_back(data[i]);
        _combination_recursion(data, n, r, i + 1, out);
        out.pop_back();
    }
}

template<typename T>
void combination_recursion(vector<T> &data, int n, int r) {
    cnt = 0;
    vector<char> out;
    _combination_recursion(data, data.size(), data.size() / 2, 0, out);
    printf("combination recursion, n = %d, r = %d, cnt = %lld\n", n, r, cnt);
}

//nCr = C(n, r) = n! / (r! * (n - r)!)
template<typename T>
void combination_stl(vector<T> &data, int n, int r) {
    cnt = 0;
    vector<bool> visit(n, true);
    for(int i = 0; i < r; i++) {
        visit[i] = false;
    }
    do {
        ++cnt;
    } while(next_permutation(visit.begin(), visit.end()));
    printf("combination STL, n = %d, r = %d, cnt = %lld\n", n, r, cnt);
}

int main() {
    vector<char> data = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'}; //10개
    int n = data.size();
    int r = data.size() / 2;

    measure_start("combination recursion");
    combination_recursion(data, n, r);
    measure_end("combination recursion");

    measure_start("combination STL");
    combination_stl(data, n, r);
    measure_end("combination STL");
}

// combination recursion is measuring...
// combination recursion, n = 10, r = 5, cnt = 252
// combination recursion : 0.000071942 seconds
// combination STL is measuring...
// combination STL, n = 10, r = 5, cnt = 252
// combination STL : 0.000166946 seconds