#include <iostream>
#include <vector>
 
using namespace std;
 
const long long INF = 1000000000000000;
static vector<long long> shorted_dist;
 
void fill_graph(vector<vector<long long>> &graph) {
    long long num;
    for (long long i = 0; i < graph.size(); ++i)
        for (long long j = 0; j < graph.size(); ++j) {
            cin >> num;
            (num >= 0) ? graph[i][j] = num : graph[i][j] = INF;
        }
}
 
void dijkstra_algo(vector<vector<long long>> &graph, long long start) {
    shorted_dist[start] = 0;
    vector<bool> used(graph.size());
    for (long long i = 0; i < graph.size(); ++i) {
        long long cur = -1;
        for (long long j = 0; j < graph.size(); ++j)
            if (!used[j] && (cur == -1 || shorted_dist[j] < shorted_dist[cur]))
                cur = j;
 
        if (shorted_dist[cur] == INF)
            break;
        used[cur] = true;
 
        for (long long to = 0; to < graph[cur].size(); ++to)
            shorted_dist[to] = min(shorted_dist[to], shorted_dist[cur] + graph[cur][to]);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);
    long long count_vert, start, end;
    cin >> count_vert >> start >> end;
    vector<vector<long long>> graph(count_vert, vector<long long>(count_vert, INF));
    shorted_dist.resize(graph.size(), INF);
 
    fill_graph(graph);
    dijkstra_algo(graph, start - 1);
 
    (shorted_dist[end - 1] != INF) ? cout << shorted_dist[end - 1] : cout << -1;
 
    return 0;
}
