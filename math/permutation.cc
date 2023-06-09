#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

using namespace std;

chrono::high_resolution_clock::time_point st;
chrono::high_resolution_clock::time_point et;

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

template<typename T>
void permutation_swap(vector<T> &data, int n, int r, int depth) {
    if(depth == r) {
        // print_data(data, r); //debugging
        return;
    }

    for(int i = depth; i < n; i++) {
        swap(data[depth], data[i]);
        permutation_swap(data, n, r, depth + 1);
        swap(data[depth], data[i]);
    }
}

template<typename T>
void permutation_visit(vector<T> &data, int n, int r, vector<T> &out, vector<bool> &visit) {
    if(out.size() == r) {
        // print_data(out, r); //debugging
        return;
    }

    for(int i = 0; i < n; i++) {
        if(visit[i]) continue;

        out.push_back(data[i]);
        visit[i] = true;
        permutation_visit(data, n, r, out, visit);
        visit[i] = false;
        out.pop_back();
    }
}

int main() {
    vector<char> data = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'}; //10개

    measure_start("permutation swap");
    permutation_swap(data, data.size(), data.size(), 0);
    measure_end("permutation swap");

    measure_start("permutation visit");
    vector<bool> visit(data.size(), false);
    vector<char> out;
    permutation_visit(data, data.size(), data.size(), out, visit);
    measure_end("permutation visit");

    measure_start("permutation STL");
    do {
        // print_data<char>(data, data.size()); //debugging
    } while(next_permutation(data.begin(), data.end()));
    measure_end("permutation STL");
}

// permutation swap is measuring...
// permutation swap : 0.28354 seconds
// permutation visit is measuring...
// permutation visit : 1.94415 seconds
// permutation STL is measuring...
// permutation STL : 0.382837 seconds