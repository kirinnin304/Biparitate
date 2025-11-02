#ifndef KUHN_HPP
#define KUHN_HPP

#include <vector>
#include <utility>

class KuhnMatching {
public:
    static std::vector<std::pair<int, int>> matching(
        const std::vector<int>& sideA,
        const std::vector<int>& sideB,
        const std::vector<std::vector<int>>& edges);
};

#endif // KUHN_HPP
