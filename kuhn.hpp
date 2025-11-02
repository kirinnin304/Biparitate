#ifndef KUHN_HPP
#define KUHN_HPP

#include <vector>
#include <map>
#include <utility>

std::map<int, std::vector<int>> buildSearchGraph(const std::vector<std::pair<int, int>>& edges);

bool tryKuhn(
    int a,
    const std::map<int, std::vector<int>>& adj,
    std::map<int, bool>& used,
    std::map<int, int>& matchB);

std::vector<std::pair<int, int>> kuhn(
    const std::vector<int>& sideA,
    const std::vector<int>& sideB,
    std::vector<std::pair<int, int>>& edges);

#endif 
