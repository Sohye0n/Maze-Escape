#include <iostream>
#include <time.h>
#include "tri.h"
#include "triheap.h"
using namespace std;

///ũ�罺Į �˰��� ���� connected �迭 sort�� �� ����
bool cmp(connected p1, connected p2) {
	if (p1.w < p2.w) return true;
	else if (p1.w == p2.w) return false;
	else return false;
}

//��� �����ϴ� �Լ�
void trimaze::built_a_tree(int H, int q) {

	//Ʈ�� �ʱ�ȭ
	for (int i = 0; i < vertice_num; i++){
		node tmp;
		tree.push_back(tmp);
	}

	//���� �����Ǵ� ����� ��ȣ
	int order = 0;

	//q==1�̸� ����. �ش��ϴ� ũ���� ���� �Ҵ�.
	if (q) {
		vector<vector<pair<int, int>>>de(3*vertice_num);
		de.swap(e);
	}

	//�� ������ ���Ͽ�
	for (int level = 0; level < H; level++) {
		//�� ������ ��� ������ ���Ͽ�
		int num_of_nodes = nodes_in_level[level];
		for (int i = 0; i < num_of_nodes; i++) {

			//������ ��ǥ ���

			if (i % 2 == 0) {
				//p1�� �� ��
				tree[order].p1.first = (i - num_of_nodes / 2) * 3 + 3 * H;
				tree[order].p1.second = level * 5;

				//p2 ���� �Ʒ�
				tree[order].p2.first = tree[order].p1.first - 3;
				tree[order].p2.second = (level + 1) * 5;

				//p3 ������ �Ʒ�
				tree[order].p3.first = tree[order].p1.first + 3;
				tree[order].p3.second = (level + 1) * 5;
			}

			else {
				//p1 �� ��
				tree[order].p1.first = (i - num_of_nodes / 2) * 3 + 3 * H;
				tree[order].p1.second = (level + 1) * 5;

				//p2 ���� ��
				tree[order].p2.first = tree[order].p1.first - 3;
				tree[order].p2.second = level * 5;

				//p3 ������ ��
				tree[order].p3.first = tree[order].p1.first + 3;
				tree[order].p3.second = level * 5;
			}

			//���Ʒ� ������� �߰�
			//�� ���� ������ ¦����ȣ ����̰� ���� �Ʒ� ���� ��尡 �ƴϸ�(¦����ȣ���� �Ʒ� ���� �����)
			if (i % 2 == 0 && level != H - 1) {

				//�ڽ�(�Ʒ� ���)�� ��ȣ
				int child_order = 0;
				for (int t = 0; t <= level; t++) child_order += nodes_in_level[t];

				//�ڽ��� �� ĭ�� �и�
				child_order = child_order + (i + 1);

				//�� ������ �����ϴ� ���� ���� ����
				int st, end, w;
				st = order;
				end = child_order;
				w = rand() % vertice_num;

				//q=1 : prim
				if (q) {
					e[st].push_back({ end,w });
					e[end].push_back({ st,w });
				}
				//q=0 : kruskal
				else {
					connected tmp;
					tmp.st = st;
					tmp.end = end;
					tmp.w = w;
					edge.push_back(tmp);
				}
				edge_num++;
			}

			//�� �� ������� �߰�
			if (i != 0) {
				//�� ������ �����ϴ� ���� ���� ����
				int st, end, w;
				st = order-1;
				end = order;
				w = rand() % vertice_num;

				//�̸� ���� �迭�� �߰�

				//q=1: prim
				if (q) {
					e[order - 1].push_back({ order,w });
					e[order].push_back({ order - 1,w });
				}

				//q=0 : krukal
				else {
					connected tmp;
					tmp.st = st;
					tmp.end = end;
					tmp.w = w;
					edge.push_back(tmp);
				}
				edge_num++;
			}
			//mid�� �����߽�
			tree[order].mid.first = (tree[order].p2.first + tree[order].p3.first) / 2.0f;
			tree[order].mid.second = (tree[order].p1.second + tree[order].p2.second) / 2.0f;
			order++;
		}
	}

	//������ ǥ��
	endnode = &tree[order - 1];

}

//ũ�罺Į �˰��򿡼� ���. ���� ã��
int trimaze::union_find(int n1) {
	int r1;

	//search n1's set
	if (parent[n1] == -1) r1 = n1;
	else {
		while (parent[n1] != -1) n1 = parent[n1];
		r1 = n1;
	}
	return r1;
}

//ũ�罺Į �˰��򿡼� ���. ���� ��ġ��
void trimaze::union_combine(int r1, int r2) {
	if (r1 > r2) parent[r1] = r2;
	else parent[r2] = r1;
}

void trimaze::kruskal() {

	sort(edge.begin(), edge.end(), cmp);

	//since all edge's weight is equal, we have to randomly choose the edges
	int r1, r2;

	//�ƹ� ������ ���õ��� ���� �����̹Ƿ� ������ �� -1�� �ʱ�ȭ�Ѵ�.
	for (int i = 0; i < vertice_num; i++) parent[i] = -1;
	for (int i = 0; i < edge_num; i++) {
		//�� ��尡 ����Ŭ�� �����ϴ��� üũ
		r1 = union_find(edge[i].st); r2 = union_find(edge[i].end);

		//����Ŭ�� �������� ������ �� ������ �����ϸ� �ȴ�
		if (r1 != r2) {
			//�� ��� ����Ǿ����Ƿ� ������ �����ش�.
			union_combine(r1, r2);

			//�� ��尡 ���� ��������, �¿� �������� üũ�Ͽ� ������ ������ �迭�� �߰��Ѵ�.
			//�׻� st�� �� ���� ���� �����߱� ������ tmp�� ����̴�.
			int tmp = -edge[i].st + edge[i].end;
			//���� �����̸� 1��ŭ ���̳���.
			if (tmp == 1) {
				tree[edge[i].st].adj[3] = &tree[edge[i].end];
				tree[edge[i].end].adj[2] = &tree[edge[i].st];
			}
			//1�̻� ���̳��� ���� �����̴�. �� ���� st�� �� ����, �� ū end�� �Ʒ� �����̴�.
			else {
				tree[edge[i].st].adj[1] = &tree[edge[i].end];
				tree[edge[i].end].adj[0] = &tree[edge[i].st];
			}
		}

	}
}

void trimaze::prim(int s) {
	//dist�� s���� �� ������ ������ �Ÿ�. {��� ��ȣ, �Ÿ�} �÷� ����.
	//��� ��ȣ �ο�, �Ÿ� ��� 9999�� �ʱ�ȭ
	vector<pair<int, int>>dist(vertice_num, { 1,9999 });
	for (int i = 0; i < vertice_num; i++) dist[i].first = i;

	//�湮���� üũ �迭
	vector<int>visited(vertice_num, 0);
	//�θ� ��� ǥ�� �迭
	vector<int>parent(vertice_num, -1);
 
	int v = 0,u=-1;
	visited[v] = 1;

	//������ ���� ���� t
	vector<pair<int, int>>t;
	//t�� �������� s �߰�. (s���� s�δ� 0�̹Ƿ� w=0)
	t.push_back({ s,0 });
	//������ ����
	heap Q(t);

	//���� ������ ����
	while (Q.size) {
		//���� ���� dist�� ���� ��� ����
		int u = Q.Extract_Min();
		//u�� �θ� ã�ƿ���
		v = parent[u];
		//u�� �湮���� �ʾҰ� v�� �����̸� u�� v�� �մ� ������ Ʈ���� �߰�.
		if (!visited[u] && parent[u]) {

			//���� ����(u�� �� ���� ���)
			if (u - v == 1) {
				tree[u].adj[2] = &tree[v];
				tree[v].adj[3] = &tree[u];
			}

			//���� ����(u�� �� ������ ���)
			else if (u - v == -1) {
				tree[u].adj[3] = &tree[v];
				tree[v].adj[2] = &tree[u];
			}

			//���� ����
			else {
				//u�� �ڽ�
				if ((u - v) > 0) {
					tree[u].adj[0] = &tree[v];
					tree[v].adj[1] = &tree[u];
				}
				//u�� �θ�
				else if ((u - v) < 0) {
					tree[u].adj[1] = &tree[v];
					tree[v].adj[0] = &tree[u];
				}
			}
		}
		//u�� �湮 ǥ��
		visited[u] = 1;

		//u�� �߰��Ǿ����Ƿ� u�� ����� ������ dist�� ������Ʈ
		for (int i = 0; i < e[u].size(); i++) {
			//����� ��� �� �̹� �湮��(���õ�) ���� ������Ʈ�� �ʿ� ����.
			//�湮���� ���� ����� dist���� u�� ���� �湮���� �� dist�� �� ������ ������Ʈ
			if (!visited[e[u][i].first] && dist[e[u][i].first].second > e[u][i].second) {
				dist[e[u][i].first].second = e[u][i].second;

				//������Ʈ�� �Ǿ��ٸ� u�� ���� ���� ��ΰ� �ִܰ�ζ�� ��. ���� ���� �θ� u��. �׸��� ���� �־��ش�.
				parent[e[u][i].first] = u;
				Q.Insert({ e[u][i].first, e[u][i].second });
			}
		}
	}
}

void trimaze::gostpath_hor() {
	//i�� ���� ���� �ִ� ��� ��ȣ
	//cnt�� �ͽ� ����
	int i = 5, cnt=0;
	
	while(i<vertice_num) {
		int length = 0;
		//�������� 4�� �̻��� ��尡 ����� ��쿡�� �ͽ��� ���ƴٴ� �� �ִ� ��η� ����� ����.
		//tmp: �ͽ� ����� �������� ��Ÿ���� ���
		//���������� ttmp�� ���� tmp�� ���������� ��� ��尡 ����Ǿ� �ִ��� üũ��. -> ������ length�� ����.
		node* tmp = &tree[i];
		node** ttmp = &tmp;

		//���������� ��� ����Ǿ����� üũ
		while ((*ttmp)->adj[3]) {
			length++;
			ttmp = &((*ttmp)->adj[3]);
		}

		//4�� �̻��̸� ��η� ä��.
		if (length >= 4) {
			ghostpath newghost(tree[i].mid.first, tree[i + length].mid.first, tree[i].mid.second);
			ghostvertice.push_back(newghost);
			cnt++;
		}
		//�ߺ� ��θ� ã���� �ȵǹǷ� ���� Ž���� �� ����� �� ����� ���� ������ ����. ���� i=i+length+1
		i = i + length + 1;
		//��� 10�� ������ �׸���
		if (cnt >= 10) break;
	}
}

void trimaze::build_a_maze(int k, int q) {
	vertice_num = edge_num=0;
	//�� ������ ��� �� ���
	nodes_in_level = new int[k];
	for (int level = 0; level < k; level++) {
		nodes_in_level[level] = 2 * level + 1;
		vertice_num += (2 * level + 1);
	}
	
	parent = new int[vertice_num];
	//random seed
	srand(time(NULL));

	//��� ����
	built_a_tree(k,q);
	//�븻���-ũ�罺Į
	if (q == 0) {
		cout << "normal mode selected. kruskal algorithm is running" << endl;
		kruskal();
	}
	//�ϵ���-����
	else {
		cout << "hard mode selected. Prim algorithm is running" << endl;
		prim(0);
		tree[0].adj[1] = &tree[2];
		tree[2].adj[0] = &tree[0];
	}
	//Ż���� ǥ��
	endnode = &tree[vertice_num-1];
	//�ͽ� ��� ����
	gostpath_hor();
	cout << "end" << endl;
}

//��� ������ �ʱ�ȭ. ���͵鵵 swqp�� ���� �޸� ��������.
void trimaze::initialize() {
	vertice_num=0;
	edge_num=0;
	level=0;
	nodes_in_level=0;
	parent=0;
	if (nodes_in_level) delete(nodes_in_level);
	if (parent) delete(parent);
	vector<node>().swap(tree);
	vector<ghostpath>().swap(ghostvertice);
	vector<connected>().swap(edge);
}

//������
trimaze::trimaze() {
	nodes_in_level=nullptr;
	parent=nullptr;
	endnode = nullptr;
}

//�Ҹ���. �����Ҵ�� �迭�� ���͵� �޸� ����.
trimaze::~trimaze() {
	delete nodes_in_level;
	delete parent;
	vector<node>().swap(tree);
	vector<ghostpath>().swap(ghostvertice);
	vector<connected>().swap(edge);
}