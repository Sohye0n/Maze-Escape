#pragma once
#ifndef tri_h
#define tri_h

#include <iostream>
#include <vector>
#include <algorithm>
#include "ofMain.h"
using namespace std;

class node {
public:
	//connection infos : up, down, left, right
	node* adj[4];
	//coordinate infos : head, left, right
	pair<int, int> p1, p2, p3;
	pair<float, float> mid;

	node() {
		for (int i = 0; i < 4; i++) adj[i] = nullptr;
		p1 = p2 = p3 = { 0,0 };
		mid = { 0.f,0.f };
	}
};

//크루스칼 알고리즘에서 사용할 간선 정보 저장 클래스
class connected {
public:
	int st, end, w;
	connected() {
		st = end = w = 0;
	}
};

//귀신이 움직일 경로의 양 경계 좌표 저장 클래스
class ghostpath {
public:
	float x_st, x_end, y;

	ghostpath(float xs, float xe, float h) {
		x_st = xs;
		x_end = xe;
		y = h;
	}

};

//미로에 대한 모든 정보를 담은 클래스
class trimaze {
public:
	//생성자
	trimaze();
	//총 노드 개수
	int vertice_num;
	//총 간선 개수
	int edge_num;
	//그래프의 높이
	int level;
	//union find에서 쓰일 조상노드 저장 배열
	int* parent;
	//각 레벨별 노드 개수 저장 배열
	int* nodes_in_level;

	//노드들이 저장된 벡터
	vector<node> tree;
	//귀신 정보를 담은 ghostpath가 저장된 벡터
	vector<ghostpath> ghostvertice;
	//크루스칼 알고리즘에서 사용할 간선정보 connected를 담은 벡터
	vector<connected> edge;
	//prim 알고리즘에서 사용할 노드간 연결정보와 간선 가중치 정보를 담은 벡터
	vector<vector<pair<int, int>>>e;

	//초기 노드 생성
	void built_a_tree(int H, int q);
	//조상 노드 찾기
	int union_find(int n);
	//두 노드 같은 조상 합치기 
	void union_combine(int r1, int r2);
	//크루스칼로 MST생성
	void kruskal();
	//프림으로 MST생성
	void prim(int s);
	//노드를 생성 후 MST까지 생성해줌.(built_a_tree, prim/kruskal 호출)
	void build_a_maze(int k, int q);
	//귀신이 이동 가능한 곳 탐색 및 귀신 추가
	void gostpath_hor();
	//각종 변수 초기화
	void initialize();
	//마지막 노드 포인터
	node* endnode;
	//소멸자
	~trimaze();
};

#endif