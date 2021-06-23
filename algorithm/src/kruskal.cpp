#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

typedef struct kruskal {
    int from;
    int to;
    int val;
}KS;

vector<KS> edge;

int parent[10002];
int res; // result
bool chk; // check

bool comp(KS d1, KS d2)
{
    return d1.val < d2.val;
}

// 파인드
int find(int u)
{
    if (u == parent[u])
        return u;

    return parent[u] = find(parent[u]);
}

// 유니온
void merge(int u, int v) // u: 정점, v: 정점'
{
    chk = false;
    u = find(u);
    v = find(v);

    // 사이클 존재 여부 확인 코드
    if (u == v)
        return;

    parent[u] = v;
    chk = true;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 99);

    int V, E;

    V = 6;
    E = 12;

    // 부모를 자기 자신으로 초기화
    for (int i = 1; i <= V; i++)
        parent[i] = i;

    // 그래프 형성
    for (int i = 0; i < E; i++)
    {
        KS ks;
        std::cin >> ks.from >> ks.to;
        ks.val = dis(gen);
        std::cout << ks.val << "\n";
        edge.push_back(ks);
    }

    // 크루스칼 알고리즘에 의해 간선을 오름차순 정렬
    sort(edge.begin(), edge.end(), comp);

    // 간선 union, 사이클이 존재하지 않도록
    for (int i = 0; i < E; i++)
    {
        merge(edge[i].from, edge[i].to);

        if (chk)
            res += edge[i].val;
    }

    std::cin.ignore();
    if (std::cin.get() == '\n') {
		printf("%d", res);
    }

    return 0;
}
