#include "triheap.h"
using namespace std;

//�� ����
heap::heap(vector<pair<int, int>>arr) {
	size = arr.size();
	A.push_back({ 0,0 });
	for (int i = 0; i < size; i++) A.push_back(arr[i]);
	Build_min_heap();
}

//���� �ڽ� �ε���
int heap::left(int i) {
	return 2 * i;
}

//������ �ڽ� �ε���
int heap::right(int i) {
	return 2 * i + 1;
}

//�θ� �ε���
int heap::parent(int i) {
	return i / 2;
}

//�ּ��� ����
void heap::Build_min_heap() {
	for (int i = size / 2; i >= 0; i--) Min_Heapify(i);
}

//i��° ��� ������ �� �ּ������� 
void heap::Min_Heapify(int i) {
	int l = left(i);
	int r = right(i);
	int smallest;

	//i ���� ���� ���� ���� ã��
	if (r <= size && A[r].second < A[i].second) smallest = r;
	else smallest = i;
	if (l <= size && A[l].second < A[smallest].second) smallest = l;

	//i�� �ּҰ� �ƴϸ� �̿� i�� �ٲٰ� �ٽ� min_heapify
	if (smallest != i) {
		pair<int, int> tmp = A[smallest];
		A[smallest] = A[i];
		A[i] = tmp;
		Min_Heapify(smallest);
	}
}

//�ּڰ� ����
int heap::Extract_Min() {
	if (size < 1) {
		cout << "heap underflow" << endl;
		return 0;
	}

	pair<int, int>min = A[1];
	A[1] = A[size];
	A.pop_back();
	size -= 1;
	//���� ����Ǿ����Ƿ� �ٽ� min_heapify
	Min_Heapify(1);
	//return node number
	return min.first;
}

//���� �߰�
void heap::Insert(pair<int, int>newnode) {
	size++;
	int i = size;
	A.push_back(newnode);
	//������ ��ġ ã�� ����
	while (i > 1 && A[parent(i)].second > A[i].second) {
		pair<int, int>tmp = A[i];
		A[i] = A[parent(i)];
		A[parent(i)] = tmp;
	}

}

//�Ҹ���
heap::~heap() {
	A.clear();
}