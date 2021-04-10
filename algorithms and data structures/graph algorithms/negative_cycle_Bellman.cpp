#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
const long long INF = 1000000000000;
vector<long long> shorted_dist, parent, path;
 
class Edge {
public:
    long long start, end, weight;
 
    inline Edge() = default;
 
    inline ~Edge() = default;
 
    inline explicit Edge(const long long start_, const long long end_, const long long weight_) : start(start_), end(end_), weight(weight_) {};
};
 
void fill_graph(vector<Edge> &graph, const long long &vert_count) {
    long long weight;
    for (auto i = 0; i < vert_count; ++i)
        for (auto j = 0; j < vert_count; ++j) {
            cin >> weight;
            graph.emplace_back(Edge(i, j, weight));
        }
 
    parent.resize(vert_count, -1);
    shorted_dist.resize(vert_count, INF);
}
 
void bellman_algo(vector<Edge> &graph, const long long &vert_count) {
    shorted_dist[0] = 0;
    long long start;
    for (auto i = 0; i < vert_count; ++i) {
        start = -1;
        for (auto const &elem : graph)
            if (shorted_dist[elem.end] > shorted_dist[elem.start] + elem.weight) {
                shorted_dist[elem.end] = max(shorted_dist[elem.start] + elem.weight, -INF);
                parent[elem.end] = elem.start;
                start = elem.end;
            }
    }
 
    if (start == -1) {
        cout << "NO"; exit(0);
    } else {
        long long end = start;
        for (auto i = 0; i < vert_count; ++i)
            end = parent[end];
 
        for (auto cur = end; ; cur = parent[cur]) {
            path.emplace_back(cur);
            if (cur == end && path.size() > 1) break;
        }
        reverse(path.begin(), path.end());
 
        cout << "YES\n" << path.size() << "\n";
        for (auto const &elem : path)
            cout << elem + 1 << ' ';
    }
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);
    long long vert_count; cin >> vert_count;
    vector<Edge> graph;
 
    fill_graph(graph, vert_count);
    bellman_algo(graph, vert_count);
 
    return 0;
}
