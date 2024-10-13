#pragma once
#ifndef triheap_h
#define triheap_h

#include <iostream>
#include <vector>
using namespace std;

class heap {
public:
	vector<pair<int, int>> A;
	heap(vector<pair<int, int>>arr);
	~heap();
	//�� ���� ����
	int size;
	//�θ� �ڽ� �ε��� ����
	int parent(int idx);
	//���� �ڽ� �ε��� ����
	int left(int idx);
	//������ �ڽ� �ε��� ����
	int right(int idx);
	//i��° �ε��� �Ʒ��� �ּ���ȭ
	void Min_Heapify(int i);
	//�ּ��� �����
	void Build_min_heap();
	//�ּҰ� ����
	int Extract_Min();
	//�� ���� ����
	void Insert(pair<int, int>);
};

#endif