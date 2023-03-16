/*
    몇번의 swap이 일어났는가? -> 처음원소기준으로 자신의 앞에 자신보다 작은 원소가 몇개 있는가?
    먼저, 병합정렬로 풀이하는 것을 간단히 설명
    큰 틀은 병합정렬과정 그대로 진행함. merge 과정에서, 왼쪽과 오른쪽의 집합을 합치는 과정에서 swap을 계산하면 됨
    먼저 왼쪽에 있는 집합이 오른쪽으로 이동해야하면, 현재 오른쪽에 있는 원소 개수를 더함 반대로 오른쪽에 있는 원소가 왼쪽으로 이동해야하면
    왼쪽에 있는 집합 개수를 더하면서 정렬시킴 -> 이를 전체가 정렬될 때까지 반복.

    ### 2. 세그먼트 트리 이용
    ex) idx 0 1 2 3 4 5
        val 6 4 3 5 2 1
    큰 틀은 해당 원소를 정렬시킨 뒤, 인덱스를 통해 추적하는 것임
    버블정렬을 (오름차순) 왼쪽에서 오른쪽 방향으로 진행한다 가정하면, 가장 작은 원소 1의 이동 횟수는 당연히 0임
    2의 이동횟수는 내 앞에 1이 있느냐가 중요하고, 3 또한 앞에 1,2가 있는가에 의해 swap이 일어남.
    그렇다면, 이를 추적하는 방법은 배열을 (val, idx)로 저장한 뒤, val 을 기준으로 정렬을 시킴
    배열은 오름차순으로 정렬되고, 이제 우리는 1부터 index를 통해 확인하면 됨 1의 앞에는 존재하는 원소가 없음 -> 원래 위치인 5로 이동
    다음 2는 index가 4임 그러므로 4~5사이의 존재하는 원소의 누적합 -> +1, 3 또한 같은 과정으로 2~5사이의 누적합 -> 2
    4도 같은 과정으로 1~5사이의 누적합 +3, 5는 3~5사이의 누적합 2 이런식으로 구함
*/

#include <bits/stdc++.h>
#include <unordered_map>
#include <cmath>
#define SIZE 500000
#define pii pair<int, int>
#define INF 987654321
using namespace std;
typedef long long ll;
int n;
int arr[SIZE + 1];
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    //디버깅용
    freopen("input.txt", "r", stdin);
    cin >> n;
    for(int i = 0; i<n;i++) cin >> arr[i];
    

    return 0;
}
