#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

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

// nPr = P(n, r) = n! / (n - r)!
template<typename T>
void _permutation_swap(vector<T> &data, int n, int r, int depth) {
    if(depth == r) {
        // print_data(data, r); //debugging
        ++cnt; //debugging
        return;
    }

    for(int i = depth; i < n; i++) {
        swap(data[depth], data[i]);
        _permutation_swap(data, n, r, depth + 1);
        swap(data[depth], data[i]);
    }
}

template<typename T>
void permutation_swap(vector<T> &data, int n, int r) {
    cnt = 0;
    _permutation_swap(data, n, r, 0);
    printf("permutation swap, n = %d, r = %d, cnt = %lld\n", n, r, cnt);
}

// nPr = P(n, r) = n! / (n - r)!
template<typename T>
void _permutation_recursion(vector<T> &data, int n, int r, vector<T> &out, vector<bool> &visit) {
    if(out.size() == r) {
        // print_data(out, r); //debugging
        ++cnt; //debugging
        return;
    }

    for(int i = 0; i < n; i++) {
        if(visit[i]) continue;

        out.push_back(data[i]);
        visit[i] = true;
        _permutation_recursion(data, n, r, out, visit);
        visit[i] = false;
        out.pop_back();
    }
}

template<typename T>
void permutation_recursion(vector<T> &data, int n, int r) {
    cnt = 0;
    vector<bool> visit(n, false);
    vector<T> out;
    _permutation_recursion(data, n, r, out, visit);
    printf("permutation visit, n = %d, r = %d, cnt = %lld\n", n, r, cnt);
}

template<typename T>
void permutation_stl(vector<T> &data, int n, int r) {
    cnt = 0;
    do {
        // print_data<char>(data, r); //debugging
        reverse(data.begin() + r, data.end());
        ++cnt; //debugging
    } while(next_permutation(data.begin(), data.end()));
    printf("permutation STL, n = %d, r = %d, cnt = %lld\n", n, r, cnt);
}

int main() {
    vector<char> data = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'}; //10개
    int n = data.size();
    int r = data.size() / 2;

    measure_start("permutation swap");
    permutation_swap(data, n, r);
    measure_end("permutation swap");

    measure_start("permutation recursion");
    permutation_recursion(data, n, r);
    measure_end("permutation recursion");

    measure_start("permutation STL");
    permutation_stl(data, n, r);
    measure_end("permutation STL");
}

// permutation swap is measuring...
// permutation swap : 0.28354 seconds
// permutation visit is measuring...
// permutation visit : 1.94415 seconds
// permutation STL is measuring...
// permutation STL : 0.382837 seconds