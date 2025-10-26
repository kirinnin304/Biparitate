#ifndef KUHN_HPP
#define KUHN_HPP

#include <vector>
#include <utility>

class KuhnMatching {
public:
    /**
        * Computes the maximum bipartite matching using Kuhn's algorithm.
        *
        * @param sideA vertices of the left partition 
        * @param sideB vertices of the right partition
        * @param edges adjacency list: edges[a] contains indices of sideB vertices connected to sideA[a]
        * @return vector of matched pairs (A[i], B[j])
        */
    static std::vector<std::pair<int, int>> matching(
        const std::vector<int>& sideA,
        const std::vector<int>& sideB,
        const std::vector<std::vector<int>>& edges);
};

#endif // KUHN_HPP