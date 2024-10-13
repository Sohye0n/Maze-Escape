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
	//힙 원소 개수
	int size;
	//부모 자식 인덱스 리턴
	int parent(int idx);
	//왼쪽 자식 인덱스 리턴
	int left(int idx);
	//오른쪽 자식 인덱스 리턴
	int right(int idx);
	//i번째 인덱스 아래로 최소힙화
	void Min_Heapify(int i);
	//최소힙 만들기
	void Build_min_heap();
	//최소값 리턴
	int Extract_Min();
	//새 원소 삽입
	void Insert(pair<int, int>);
};

#endif