//https://www.acmicpc.net/problem/5545
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int toppings;
    scanf("%d", &toppings);
    int dough_price, topping_price;
    scanf("%d %d", &dough_price, &topping_price);
    int dough_calorie;
    scanf("%d", &dough_calorie);

    vector<int> toppings_calorie(toppings);
    for(int i = 0; i < toppings; i++) {
        scanf("%d", &toppings_calorie[i]);
    }
    sort(toppings_calorie.begin(), toppings_calorie.end(), greater<int>());

    int price = dough_price;
    int calorie = dough_calorie;
    int calorie_1won = calorie / price;

    for(int i = 0; i < toppings; i++) {
        price += topping_price;
        calorie += toppings_calorie[i];
        int temp = calorie / price;

        if(calorie_1won > temp) {
            break;
        } else {
            calorie_1won = temp;
        }
    }

    printf("%d\n", calorie_1won);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
}