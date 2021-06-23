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

// ���ε�
int find(int u)
{
    if (u == parent[u])
        return u;

    return parent[u] = find(parent[u]);
}

// ���Ͽ�
void merge(int u, int v) // u: ����, v: ����'
{
    chk = false;
    u = find(u);
    v = find(v);

    // ����Ŭ ���� ���� Ȯ�� �ڵ�
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

    // �θ� �ڱ� �ڽ����� �ʱ�ȭ
    for (int i = 1; i <= V; i++)
        parent[i] = i;

    // �׷��� ����
    for (int i = 0; i < E; i++)
    {
        KS ks;
        std::cin >> ks.from >> ks.to;
        ks.val = dis(gen);
        std::cout << ks.val << "\n";
        edge.push_back(ks);
    }

    // ũ�罺Į �˰��� ���� ������ �������� ����
    sort(edge.begin(), edge.end(), comp);

    // ���� union, ����Ŭ�� �������� �ʵ���
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
