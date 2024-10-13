#include <iostream>
#include <time.h>
#include "tri.h"
#include "triheap.h"
using namespace std;

///크루스칼 알고리즘 사용시 connected 배열 sort할 때 인자
bool cmp(connected p1, connected p2) {
	if (p1.w < p2.w) return true;
	else if (p1.w == p2.w) return false;
	else return false;
}

//노드 생성하는 함수
void trimaze::built_a_tree(int H, int q) {

	//트리 초기화
	for (int i = 0; i < vertice_num; i++){
		node tmp;
		tree.push_back(tmp);
	}

	//지금 생성되는 노드의 번호
	int order = 0;

	//q==1이면 프림. 해당하는 크기의 벡터 할당.
	if (q) {
		vector<vector<pair<int, int>>>de(3*vertice_num);
		de.swap(e);
	}

	//각 레벨에 대하여
	for (int level = 0; level < H; level++) {
		//각 레벨별 노드 개수에 대하여
		int num_of_nodes = nodes_in_level[level];
		for (int i = 0; i < num_of_nodes; i++) {

			//꼭짓점 좌표 계산

			if (i % 2 == 0) {
				//p1이 젤 위
				tree[order].p1.first = (i - num_of_nodes / 2) * 3 + 3 * H;
				tree[order].p1.second = level * 5;

				//p2 왼쪽 아래
				tree[order].p2.first = tree[order].p1.first - 3;
				tree[order].p2.second = (level + 1) * 5;

				//p3 오른쪽 아래
				tree[order].p3.first = tree[order].p1.first + 3;
				tree[order].p3.second = (level + 1) * 5;
			}

			else {
				//p1 젤 밑
				tree[order].p1.first = (i - num_of_nodes / 2) * 3 + 3 * H;
				tree[order].p1.second = (level + 1) * 5;

				//p2 왼쪽 위
				tree[order].p2.first = tree[order].p1.first - 3;
				tree[order].p2.second = level * 5;

				//p3 오른쪽 위
				tree[order].p3.first = tree[order].p1.first + 3;
				tree[order].p3.second = level * 5;
			}

			//위아래 연결관계 추가
			//현 레벨 내에서 짝수번호 노드이고 가장 아래 레벨 노드가 아니면(짝수번호여야 아래 노드와 연결됨)
			if (i % 2 == 0 && level != H - 1) {

				//자식(아래 노드)의 번호
				int child_order = 0;
				for (int t = 0; t <= level; t++) child_order += nodes_in_level[t];

				//자식은 한 칸씩 밀림
				child_order = child_order + (i + 1);

				//두 정점을 연결하는 간선 정보 저장
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

			//양 옆 연결관계 추가
			if (i != 0) {
				//두 정점을 연결하는 간선 정보 저장
				int st, end, w;
				st = order-1;
				end = order;
				w = rand() % vertice_num;

				//이를 간선 배열에 추가

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
			//mid는 무게중심
			tree[order].mid.first = (tree[order].p2.first + tree[order].p3.first) / 2.0f;
			tree[order].mid.second = (tree[order].p1.second + tree[order].p2.second) / 2.0f;
			order++;
		}
	}

	//도착점 표시
	endnode = &tree[order - 1];

}

//크루스칼 알고리즘에서 사용. 집합 찾기
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

//크루스칼 알고리즘에서 사용. 집합 합치기
void trimaze::union_combine(int r1, int r2) {
	if (r1 > r2) parent[r1] = r2;
	else parent[r2] = r1;
}

void trimaze::kruskal() {

	sort(edge.begin(), edge.end(), cmp);

	//since all edge's weight is equal, we have to randomly choose the edges
	int r1, r2;

	//아무 간선도 선택되지 않은 상태이므로 조상을 다 -1로 초기화한다.
	for (int i = 0; i < vertice_num; i++) parent[i] = -1;
	for (int i = 0; i < edge_num; i++) {
		//두 노드가 사이클을 형성하는지 체크
		r1 = union_find(edge[i].st); r2 = union_find(edge[i].end);

		//사이클을 형성하지 않으면 이 간선을 선택하면 된다
		if (r1 != r2) {
			//두 노드 연결되었으므로 조상을 합쳐준다.
			union_combine(r1, r2);

			//두 노드가 상하 연결인지, 좌우 연결인지 체크하여 각자의 연결노드 배열에 추가한다.
			//항상 st에 더 작은 값을 저장했기 때문에 tmp는 양수이다.
			int tmp = -edge[i].st + edge[i].end;
			//같은 레벨이면 1만큼 차이난다.
			if (tmp == 1) {
				tree[edge[i].st].adj[3] = &tree[edge[i].end];
				tree[edge[i].end].adj[2] = &tree[edge[i].st];
			}
			//1이상 차이나면 상하 관계이다. 더 작은 st가 위 레벨, 더 큰 end가 아래 레벨이다.
			else {
				tree[edge[i].st].adj[1] = &tree[edge[i].end];
				tree[edge[i].end].adj[0] = &tree[edge[i].st];
			}
		}

	}
}

void trimaze::prim(int s) {
	//dist는 s에서 각 노드까지 떨어진 거리. {노드 번호, 거리} 꼴로 저장.
	//노드 번호 부여, 거리 모두 9999로 초기화
	vector<pair<int, int>>dist(vertice_num, { 1,9999 });
	for (int i = 0; i < vertice_num; i++) dist[i].first = i;

	//방문여부 체크 배열
	vector<int>visited(vertice_num, 0);
	//부모 노드 표시 배열
	vector<int>parent(vertice_num, -1);
 
	int v = 0,u=-1;
	visited[v] = 1;

	//힙으로 만들 벡터 t
	vector<pair<int, int>>t;
	//t에 시작점인 s 추가. (s에서 s로는 0이므로 w=0)
	t.push_back({ s,0 });
	//힙으로 만듬
	heap Q(t);

	//힙이 차있을 동안
	while (Q.size) {
		//가장 작은 dist를 갖는 노드 선택
		int u = Q.Extract_Min();
		//u의 부모 찾아오기
		v = parent[u];
		//u는 방문되지 않았고 v도 정상값이면 u와 v를 잇는 간선을 트리에 추가.
		if (!visited[u] && parent[u]) {

			//수평 관계(u가 더 왼쪽 노드)
			if (u - v == 1) {
				tree[u].adj[2] = &tree[v];
				tree[v].adj[3] = &tree[u];
			}

			//수평 관계(u가 더 오른쪽 노드)
			else if (u - v == -1) {
				tree[u].adj[3] = &tree[v];
				tree[v].adj[2] = &tree[u];
			}

			//상하 관계
			else {
				//u가 자식
				if ((u - v) > 0) {
					tree[u].adj[0] = &tree[v];
					tree[v].adj[1] = &tree[u];
				}
				//u가 부모
				else if ((u - v) < 0) {
					tree[u].adj[1] = &tree[v];
					tree[v].adj[0] = &tree[u];
				}
			}
		}
		//u의 방문 표시
		visited[u] = 1;

		//u가 추가되었으므로 u와 연결된 노드들의 dist값 업데이트
		for (int i = 0; i < e[u].size(); i++) {
			//연결된 노드 중 이미 방문한(선택된) 노드는 업데이트할 필요 없음.
			//방문하지 않은 노드의 dist보다 u를 통해 방문했을 때 dist가 더 작으면 업데이트
			if (!visited[e[u][i].first] && dist[e[u][i].first].second > e[u][i].second) {
				dist[e[u][i].first].second = e[u][i].second;

				//업데이트가 되었다면 u를 통해 오는 경로가 최단경로라는 것. 따라서 얘의 부모를 u로. 그리고 힙에 넣어준다.
				parent[e[u][i].first] = u;
				Q.Insert({ e[u][i].first, e[u][i].second });
			}
		}
	}
}

void trimaze::gostpath_hor() {
	//i는 현재 보고 있는 노드 번호
	//cnt는 귀신 개수
	int i = 5, cnt=0;
	
	while(i<vertice_num) {
		int length = 0;
		//수평으로 4개 이상의 노드가 연결된 경우에만 귀신이 돌아다닐 수 있는 경로로 취급할 것임.
		//tmp: 귀신 경로의 시작점을 나타내는 노드
		//이중포인터 ttmp를 통해 tmp의 오른쪽으로 몇개의 노드가 연결되어 있는지 체크함. -> 개수를 length에 저장.
		node* tmp = &tree[i];
		node** ttmp = &tmp;

		//오른쪽으로 몇개나 연결되었는지 체크
		while ((*ttmp)->adj[3]) {
			length++;
			ttmp = &((*ttmp)->adj[3]);
		}

		//4개 이상이면 경로로 채택.
		if (length >= 4) {
			ghostpath newghost(tree[i].mid.first, tree[i + length].mid.first, tree[i].mid.second);
			ghostvertice.push_back(newghost);
			cnt++;
		}
		//중복 경로를 찾으면 안되므로 다음 탐색은 현 경로의 끝 노드의 다음 노드부터 시작. 따라서 i=i+length+1
		i = i + length + 1;
		//경로 10개 넘으면 그만둠
		if (cnt >= 10) break;
	}
}

void trimaze::build_a_maze(int k, int q) {
	vertice_num = edge_num=0;
	//각 레벨별 노드 수 계산
	nodes_in_level = new int[k];
	for (int level = 0; level < k; level++) {
		nodes_in_level[level] = 2 * level + 1;
		vertice_num += (2 * level + 1);
	}
	
	parent = new int[vertice_num];
	//random seed
	srand(time(NULL));

	//노드 생성
	built_a_tree(k,q);
	//노말모드-크루스칼
	if (q == 0) {
		cout << "normal mode selected. kruskal algorithm is running" << endl;
		kruskal();
	}
	//하드모드-프림
	else {
		cout << "hard mode selected. Prim algorithm is running" << endl;
		prim(0);
		tree[0].adj[1] = &tree[2];
		tree[2].adj[0] = &tree[0];
	}
	//탈출점 표시
	endnode = &tree[vertice_num-1];
	//귀신 경로 저장
	gostpath_hor();
	cout << "end" << endl;
}

//모든 정보를 초기화. 벡터들도 swqp을 통해 메모리 정리해줌.
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

//생성자
trimaze::trimaze() {
	nodes_in_level=nullptr;
	parent=nullptr;
	endnode = nullptr;
}

//소멸자. 동적할당된 배열과 벡터들 메모리 정리.
trimaze::~trimaze() {
	delete nodes_in_level;
	delete parent;
	vector<node>().swap(tree);
	vector<ghostpath>().swap(ghostvertice);
	vector<connected>().swap(edge);
}