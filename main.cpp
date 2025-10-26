#include "kuhn.hpp"
#include <functional>
#include <algorithm>

    std::vector<std::pair<int, int>> KuhnMatching::matching(
        const std::vector<int>& sideA,
        const std::vector<int>& sideB,
        const std::vector<std::vector<int>>& edges)
    {
		const auto sizeA = sideA.size(); // Number of vertices in side A
		const auto sizeB = sideB.size(); // Number of vertices in side B

        std::vector<int> matchB(sizeB, -1);
        std::vector<char> visited(sizeA, false);

		// DFS function to find augmenting paths
        std::function<bool(int)> dfs = [&](int a) -> bool {
            if (visited[a]) return false;
            visited[a] = true;

            for (int b : edges[a]) {
                if (matchB[b] == -1 || dfs(matchB[b])) {
                    matchB[b] = a;
                    return true;
                }
            }
            return false;
            };
		// for each vertex in sideA
        for (int a = 0; a < sizeA; ++a) {
            std::fill(visited.begin(), visited.end(), false);
            dfs(a);
        }
		// Collecting the matched pairs
        std::vector<std::pair<int, int>> matches;
        for (int b = 0; b < sizeB; ++b)
            if (matchB[b] != -1)
                matches.push_back({ sideA[matchB[b]], sideB[b] });

        return matches;
    }
