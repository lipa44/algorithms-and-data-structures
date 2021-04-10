#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cfloat>
 
#define edge pair<double, double>
 
using namespace std;
 
class Vertex {
public:
    int id;
    double x, y;
    bool used = false;
    vector<double> distances;
 
    inline Vertex(const double &x_, const double &y_, const int &id_) : x(x_), y(y_), id(id_) {};
 
    inline Vertex() = default;
 
    inline ~Vertex() = default;
};
 
inline double setDist(const edge &a, const edge &b) {
    return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}
 
void prim_algo(vector<Vertex> &graph, vector<double> &min_dist, vector<double> &included, double &weight) {
    min_dist[0] = 0;
 
    for (int i = 0; i < graph.size(); ++i) {
        Vertex *cur = nullptr;
        for (auto &elem : graph)
            // если точка не использована и ребро до неё кротчайшее
            if (!elem.used && (cur == nullptr || min_dist[elem.id] < min_dist[cur->id]))
                cur = &elem;
        cur->used = true;
 
        // если точка (ребро с ней) уже в остовном дереве
        if (included[cur->id] != -1)
            weight += graph[cur->id].distances[included[cur->id]];
 
        for (auto &elem : graph)
            // если нашлось ребро с данной точкой короче
            if (cur->distances[elem.id] < min_dist[elem.id]) {
                min_dist[elem.id] = cur->distances[elem.id];
                included[elem.id] = cur->id;
            }
    }
 
    cout << setprecision(10) << weight;
}
 
inline void set_distances(vector<Vertex> &graph) {
    for (auto &elem : graph)
        for (auto &second_elem : graph)
            elem.distances.push_back(setDist(edge(elem.x, elem.y), edge(second_elem.x, second_elem.y)));
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);
    int count_vertex; cin >> count_vertex;
    double x_coord, y_coord, weight = 0;
    vector<Vertex> graph(count_vertex);
    vector<double> min_dist(count_vertex, FLT_MAX), included(count_vertex, -1);
 
    for (int i = 0; i < count_vertex; ++i) {
        cin >> x_coord >> y_coord;
        graph[i] = Vertex(x_coord, y_coord, i);
    }
 
    set_distances(graph);
    prim_algo(graph, min_dist, included, weight);
 
    return 0;
}
