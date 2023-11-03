#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory.h>
#include <string>
#include <tuple>
#include <deque>
#include <stack>
#include <queue> // 여기에 priority queue 존재
using namespace std;

pair<int, int>
	/*
	가능한 보드는 분리하는 것이 좋아보임(타입 별로)
	int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int dy[8] = {0, 1, 1, 1, 0, -1,-1, -1};
	struct boss{
		int dir;
		int 시체수명; // <= 2, ==0이면 제거
	}
	Boss board[][] = 1 알, 2 몬스터,-1 시체


	for(;;)
		for(;;)
			if(몬스터가 있으면){
				복제시도: 보드에 바로 업데이트
				몬스터이동()
			}

	몬스터 이동(){
		가능한 경로 탐색
		int dir = 몬스터.dir
		for(;8번 반복;){
			dir = (dir + 1) % 8;
			if(가능?){
				이동 후 break;
			}
		}
	}
	팩맥 이동(){
		BFS를 통해 현재 이동하면서,
		attacker[][] += 이전꺼 + 현재 위치 몬스터의 수
		이런식으로 구하고, 해당 map의 좌표를 저장해둠
	}



	*/