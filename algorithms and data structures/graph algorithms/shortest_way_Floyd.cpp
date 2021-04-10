#include <vector>
#include <iostream>
 
using namespace std;
 
void fill_graph(vector<vector<long long>> &graph, long long &count_edge) {
    int start_vert, end_vert, cost;
 
    for (long long i = 0; i < count_edge; ++i) {
        cin >> start_vert >> end_vert >> cost;
        graph[start_vert - 1][end_vert - 1] = cost;
    }
 
    for (long long i = 0; i < graph.size(); ++i)
        graph[i][i] = 0;
}
 
void Floyd_algo(vector<vector<long long>> &graph) {
    for (long long k = 0; k < graph.size(); ++k)
        for (long long i = 0; i < graph.size(); ++i)
            for (long long j = 0; j < graph.size(); ++j)
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}
 
void print_graph(vector<vector<long long>> &graph) {
    for (long long i = 0; i < graph.size(); ++i) {
        for (long long j = 0; j < graph.size(); ++j) {
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    freopen("pathsg.in", "r", stdin);
    freopen("pathsg.out", "w", stdout);
    long long count_vert, count_edge;
    cin >> count_vert >> count_edge;
    vector<vector<long long>> graph(count_vert, vector<long long>(count_vert, INT_MAX));
 
    fill_graph(graph, count_edge);
    Floyd_algo(graph);
    print_graph(graph);
 
    return 0;
}
