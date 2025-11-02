#include <vector>
#include <map>
#include <utility>

std::map<int, std::vector<int>> buildSearchGraph(const std::vector<std::pair<int, int>>& edges) {
    std::map<int, std::vector<int>> adj;
    for (const auto& [u, v] : edges) {
        adj[u].push_back(v); // from A → B
    }
    return adj;
}

// Recursive Kuhn DFS
bool tryKuhn(int a,
    const std::map<int, std::vector<int>>& adj,
    std::map<int, bool>& used,
    std::map<int, int>& matchB)
{
    if (used[a]) return false;
    used[a] = true;

    auto it = adj.find(a);
    if (it == adj.end()) return false;

    for (int b : it->second) {
        if (matchB[b] == -1 || tryKuhn(matchB[b], adj, used, matchB)) {
            matchB[b] = a;
            return true;
        }
    }
    return false;
}

//matching
std::vector<std::pair<int, int>> kuhn(
    const std::vector<int>& sideA,
    const std::vector<int>& sideB,
    std::vector<std::pair<int, int>>& edges)
{
    auto adj = buildSearchGraph(edges);

    std::map<int, int> matchB;
    for (int b : sideB) matchB[b] = -1;

    for (int a : sideA) {
        std::map<int, bool> used;
        tryKuhn(a, adj, used, matchB);
    }

    std::vector<std::pair<int, int>> result;
    for (const auto& [b, a] : matchB) {
        if (a != -1) {
            result.emplace_back(a, b);
        }
    }

    return result;
}
