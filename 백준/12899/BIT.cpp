#include <bits/stdc++.h>
#define SIZE 2097152 // 2,000,000 보다 큰 2의 제곱수가 3
#define ll long long
#define pii pair<int, int>
using namespace std;
int bit[SIZE + 1];
int query(int x){ //x의 lower_bound의 Index(자연수)를 반환
    int begin = 0;
    if(x <= 0) return 0;
    for(int i = 20; i>=0;i--){
        int len = 1 << i;
        if(bit[len + begin] < x){
            x -= bit[begin += len];
        }
    }
    begin++;
    for(int i = begin; i<SIZE; i += i&-i){
        bit[i]--;
    }
    return begin;
}
void update(int i){ //i의 개수를 추가함
    for(;i<SIZE;i += i & -i){
        bit[i]++;
    }
}
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    //디버깅용
    //freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    while(n--){
        int a,b;
        cin >> a >> b;
        if(a == 1){ // a -> 1
            update(b);
        }
        else{ // a -> 2
            cout << query(b) << '\n';
        }
    }
    return 0;
}
