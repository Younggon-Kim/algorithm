// https://www.geeksforgeeks.org/gcd-two-array-numbers/
// https://www.geeksforgeeks.org/lcm-of-given-array-elements/
// https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/

#include <iostream>
#include <vector>

using namespace std;

int get_gcd(int a, int b) {
    if(a == 0) {
        return b;
    }
    return get_gcd(b % a, a);
}

int get_gcd_arr(vector<int> &arr) {
    int gcd = 0;
    for(auto n : arr) {
        gcd = get_gcd(gcd, n);
    }
    return gcd;
}

// a x b = LCM(a, b) * GCD (a, b)
// LCM(a, b) = (a x b) / GCD(a, b)
int get_lcm(int a, int b) {
    return (a / get_gcd(a, b)) * b;
}

int get_lcm_arr(vector<int> &arr) {
    int lcm = arr[0];

    for(int i = 1; i < arr.size(); i++) {
        int a = lcm;
        int b = arr[i];
        int gcd = get_gcd(a, b);
        lcm = (lcm * b) / gcd;
    }

    return lcm;
}

int main() {
    cout << get_gcd(3, 9) << endl;

    vector<int> arr = {2, 4, 6};
    cout << get_gcd_arr(arr) << endl;

    cout << get_lcm(3, 7) << endl;

    arr = {3, 5, 7};
    cout << get_lcm_arr(arr) << endl;
}