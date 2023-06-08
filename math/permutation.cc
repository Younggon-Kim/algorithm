#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

std::chrono::high_resolution_clock::time_point st;
std::chrono::high_resolution_clock::time_point et;

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


    cout << "----- permutation swap -----" << endl;
    st = std::chrono::high_resolution_clock::now();

    permutation_swap(data, data.size(), data.size(), 0);

    et = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(et - st);
    std::cout << "permutation swap execution time : " << time_span.count() << " seconds." << std::endl;;



    cout << "----- permutation visit -----" << endl;
    st = std::chrono::high_resolution_clock::now();

    vector<bool> visit(data.size(), false);
    vector<char> out;
    permutation_visit(data, data.size(), data.size(), out, visit);

    et = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(et - st);
    std::cout << "permutation visit execution time : " << time_span.count() << " seconds." << std::endl;;



    cout << "----- permutation (STL) -----" << endl;
    st = std::chrono::high_resolution_clock::now();

    do {
        // print_data<char>(data, data.size()); //debugging
    } while(next_permutation(data.begin(), data.end()));

    et = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(et - st);
    std::cout << "permutation STL execution time : " << time_span.count() << " seconds." << std::endl;;
}

// ----- permutation swap -----
// permutation swap execution time : 0.15964 seconds.
// ----- permutation visit -----
// permutation visit execution time : 1.96749 seconds.
// ----- permutation (STL) -----
// permutation STL execution time : 0.212547 seconds.