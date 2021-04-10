#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
 
using namespace std;
 
static vector<long long> tree_id;
 
class Vertex {
public:
    long long value;
 
    inline explicit Vertex(const long long &value_) : value(value_) {};
 
    inline Vertex() = default;
 
    inline ~Vertex() = default;
};
 
class Edge {
public:
    long long weight;
    Vertex first_vert, second_vert;
 
    inline long long first_value() const {
        return this->first_vert.value;
    }
 
    inline long long second_value() const {
        return this->second_vert.value;
    }
 
    inline explicit Edge(const Vertex &a, const Vertex &b, const long long &weight_) : first_vert(a), second_vert(b), weight(weight_) {};
 
    inline Edge() = default;
 
    inline ~Edge() = default;
 
    inline bool operator()(const Edge &a, const Edge &b) const {
        return (a.weight < b.weight);
    }
};
 
inline long long find_set(const long long &id) {
    if (id == tree_id[id])
        return id;
    return tree_id[id] = find_set(tree_id[id]);
}
 
inline void union_set(const long long &start, const long long &end) {
    if (start != end)
        tree_id[end] = start;
}
 
inline void fill_tree_id(const long long &end) {
    for (long long i = 0; i < end; ++i)
        tree_id.emplace_back(i);
}
 
void kruskal_algo(const vector<Edge> &graph, long long &weight) {
    for (auto &elem : graph)
        if (find_set(tree_id[elem.first_value()]) != find_set(tree_id[elem.second_value()])) {
            weight += elem.weight;
            union_set(find_set(tree_id[elem.first_value()]), find_set(tree_id[elem.second_value()]));
        }
 
    cout << setprecision(10) << weight;
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    freopen("spantree3.in", "r", stdin);
    freopen("spantree3.out", "w", stdout);
    long long vert_count, edge_count, first_vert, second_vert, cost, weight = 0;
    cin >> vert_count >> edge_count;
    vector<Edge> graph(edge_count);
 
    for (long long i = 0; i < edge_count; ++i) {
        cin >> first_vert >> second_vert >> cost;
        graph.at(i) = Edge(Vertex(first_vert - 1), Vertex(second_vert - 1), cost);
    }
 
    fill_tree_id(vert_count);
    sort(graph.begin(), graph.end(), Edge());
    kruskal_algo(graph, weight);
 
    return 0;
}
