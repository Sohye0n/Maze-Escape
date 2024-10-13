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

//ũ�罺Į �˰��򿡼� ����� ���� ���� ���� Ŭ����
class connected {
public:
	int st, end, w;
	connected() {
		st = end = w = 0;
	}
};

//�ͽ��� ������ ����� �� ��� ��ǥ ���� Ŭ����
class ghostpath {
public:
	float x_st, x_end, y;

	ghostpath(float xs, float xe, float h) {
		x_st = xs;
		x_end = xe;
		y = h;
	}

};

//�̷ο� ���� ��� ������ ���� Ŭ����
class trimaze {
public:
	//������
	trimaze();
	//�� ��� ����
	int vertice_num;
	//�� ���� ����
	int edge_num;
	//�׷����� ����
	int level;
	//union find���� ���� ������ ���� �迭
	int* parent;
	//�� ������ ��� ���� ���� �迭
	int* nodes_in_level;

	//������ ����� ����
	vector<node> tree;
	//�ͽ� ������ ���� ghostpath�� ����� ����
	vector<ghostpath> ghostvertice;
	//ũ�罺Į �˰��򿡼� ����� �������� connected�� ���� ����
	vector<connected> edge;
	//prim �˰��򿡼� ����� ��尣 ���������� ���� ����ġ ������ ���� ����
	vector<vector<pair<int, int>>>e;

	//�ʱ� ��� ����
	void built_a_tree(int H, int q);
	//���� ��� ã��
	int union_find(int n);
	//�� ��� ���� ���� ��ġ�� 
	void union_combine(int r1, int r2);
	//ũ�罺Į�� MST����
	void kruskal();
	//�������� MST����
	void prim(int s);
	//��带 ���� �� MST���� ��������.(built_a_tree, prim/kruskal ȣ��)
	void build_a_maze(int k, int q);
	//�ͽ��� �̵� ������ �� Ž�� �� �ͽ� �߰�
	void gostpath_hor();
	//���� ���� �ʱ�ȭ
	void initialize();
	//������ ��� ������
	node* endnode;
	//�Ҹ���
	~trimaze();
};

#endif