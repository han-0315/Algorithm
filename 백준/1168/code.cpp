#include <bits/stdc++.h>
#define SIZE 100000
#define ll long long
#define pii pair<int, int>
using namespace std;
int seg[400005];
void init(int n){
    int len = 1;
    while((len <<= 1) < n);
    for(int i = 0; i<n;i++) seg[len + i] = 1;
    for(int i = len-1; i>0; i--) seg[i] = seg[i << 1] + seg[i << 1 | 1];
}
// int init(int node, int s, int e) {
//     if (s == e) return seg[node] = 1;
//     int mid = (s + e) >> 1;
//     return seg[node] = init(2 * node, s, mid) + init(2 * node + 1, mid + 1, e);
// }
// init(1,1,n)
int qeury(int node, int s, int e, int num){
    seg[node]--;
    int m = (s + e)/2;
    if(s==e) return s;

    if(seg[node << 1] >= num) return qeury(node << 1, s, m, num);
    else return qeury(node << 1 | 1, m+1, e, num - seg[node << 1]);
}
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    //디버깅용
    freopen("input.txt", "r", stdin);
    int n,k;
    cin >> n >> k;
    init(n);
    int x = k;
    cout << "<";
    for(int i = 0; i< n - 1;i++){
        cout << qeury(1,1,n,x) << ", ";
        x += k - 1;
        if (x % seg[1] == 0) x = seg[1];
        else x %= seg[1]; 
    }
    cout << qeury(1,1,n,x) << '>';



    return 0;
}
