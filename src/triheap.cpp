#include "triheap.h"
using namespace std;

//힙 생성
heap::heap(vector<pair<int, int>>arr) {
	size = arr.size();
	A.push_back({ 0,0 });
	for (int i = 0; i < size; i++) A.push_back(arr[i]);
	Build_min_heap();
}

//왼쪽 자식 인덱스
int heap::left(int i) {
	return 2 * i;
}

//오른쪽 자식 인덱스
int heap::right(int i) {
	return 2 * i + 1;
}

//부모 인덱스
int heap::parent(int i) {
	return i / 2;
}

//최소힙 생성
void heap::Build_min_heap() {
	for (int i = size / 2; i >= 0; i--) Min_Heapify(i);
}

//i번째 노드 밑으로 다 최소힙으로 
void heap::Min_Heapify(int i) {
	int l = left(i);
	int r = right(i);
	int smallest;

	//i 이하 가장 작은 원소 찾기
	if (r <= size && A[r].second < A[i].second) smallest = r;
	else smallest = i;
	if (l <= size && A[l].second < A[smallest].second) smallest = l;

	//i가 최소가 아니면 이와 i를 바꾸고 다시 min_heapify
	if (smallest != i) {
		pair<int, int> tmp = A[smallest];
		A[smallest] = A[i];
		A[i] = tmp;
		Min_Heapify(smallest);
	}
}

//최솟값 추출
int heap::Extract_Min() {
	if (size < 1) {
		cout << "heap underflow" << endl;
		return 0;
	}

	pair<int, int>min = A[1];
	A[1] = A[size];
	A.pop_back();
	size -= 1;
	//힙이 변경되었으므로 다시 min_heapify
	Min_Heapify(1);
	//return node number
	return min.first;
}

//원소 추가
void heap::Insert(pair<int, int>newnode) {
	size++;
	int i = size;
	A.push_back(newnode);
	//적절한 위치 찾아 삽입
	while (i > 1 && A[parent(i)].second > A[i].second) {
		pair<int, int>tmp = A[i];
		A[i] = A[parent(i)];
		A[parent(i)] = tmp;
	}

}

//소멸자
heap::~heap() {
	A.clear();
}