#include <vector>
#include <map>
#include <iostream>
#include "Hopkroft.hpp"

void setSearch(std::vector<std::map<int, std::vector<int>>>& graph, int& layer) {
    if ((int)graph.size() <= layer) {
        graph.push_back({});
    }
    else {
        graph[layer].clear();
    }
}

std::map<int, std::vector<int>> buildSearchGraph(std::vector<std::pair<int, int>> graph) {
    std::map<int, std::vector<int>> out;
    int s = graph.size();
    for (int i = 0; i < s; i++) {
        out[graph[i].first].push_back(graph[i].second);
        out[graph[i].second].push_back(graph[i].first);
    }
    return out;
}

std::vector<std::pair<int, int>> fish(const std::vector<int> sideA, const std::vector<int> sideB, std::vector<std::pair<int, int>>& edges) {
    std::cout << "start";
    std::map<int, std::vector<int>> search = buildSearchGraph(edges);

    int aSize = sideA.size();
    int bSize = sideB.size();

    std::map<int, std::pair<int, int>> matchings;
    for (int i = 0; i < aSize + bSize; i++) {
        matchings[i] = { -1, 0 };
    }

    std::vector<std::map<int, std::vector<int>>> searchG;
    std::vector<int> L1;
    std::vector<int> L2;
    std::vector<int>* currentLayer = &L1;
    std::vector<int>* newLayer = &L2;
    int layer;
    bool aFlag;
    int aLoops = 1;
    std::vector<int> ends;

    for (int i = 0; i < aSize; i++) {
        L1.push_back(sideA[i]);
    }
    while (true) {
        layer = 0;
        aFlag = true;
        bool bFlag = false;
        ends.clear();
        while (true) {
            setSearch(searchG, layer);
            int cSize = (*currentLayer).size();
            if (cSize == 0) {
                std::vector<std::pair<int, int>> out;
                for (int i = 0; i < sideA.size(); i++) {
                    if (matchings[sideA[i]].first != -1) {
                        out.push_back({sideA[i], matchings[sideA[i]].first });
                    }
                }
                return out;
            }

            for (int i = 0; i < cSize; i++) {
                int node = (*currentLayer)[i];
                if (aFlag) {
                    for (int j = 0; j < search[node].size(); j++) {
                        int t = search[node][j];
                        searchG[layer][t].push_back(node);
                        newLayer->push_back(t);
                        if (matchings[t].first < 0) {
                            ends.push_back(t);
                            bFlag = true;
                        }
                    }
                }
                else {
                    if (matchings[(*currentLayer)[i]].second < aLoops) {
                        matchings[(*currentLayer)[i]].second = aLoops;
                        int t = matchings[(*currentLayer)[i]].first;
                        searchG[layer][t].push_back(node);
                        newLayer->push_back(t);
                    }
                }
            }

            if (bFlag) { break; }
            std::swap(L1, L2);
            (*newLayer).clear();
            aFlag = !aFlag;
            layer++;
        }

        std::vector<int> line;
        std::vector<int> mem;
        for (int j = 0; j < ends.size(); j++) {
            line.clear();
            line.push_back(ends[j]);
            for (int i = searchG.size() - 1; i >= 0; i--) {
                std::vector<int> temp = (searchG[i])[line[line.size() - 1]];

                bool memFlag = false;
                for (int k = 0; k < (int)temp.size(); k++) {
                    if (std::find(mem.begin(), mem.end(), temp[k]) != mem.end()) {
                        continue;
                    }
                    line.push_back(temp[k]);
                    memFlag = true;
                    break;
                }
                if (!memFlag) {
                    break;
                }
            }
            if (line.size() - 1 == searchG.size()) {
                mem.push_back(line[line.size() - 1]);
                for (int i = searchG.size() - 1; i >= 0; i--) {
                    int ls = line.size();
                    if (matchings[line[ls - 1]].first != -1) {
                        matchings[matchings[line[ls - 1]].first].first = -1;
                        matchings[line[ls - 1]].first = -1;
                    }
                    if (matchings[line[ls - 2]].first != -1) {
                        matchings[matchings[line[ls - 2]].first].first = -1;
                        matchings[line[ls - 2]].first = -1;
                    }
                    matchings[line[ls - 1]].first = line[ls - 2];
                    matchings[line[ls - 2]].first = line[ls - 1];
                    mem.push_back(line[ls - 2]);
                    line.erase(line.end() - 1);
                }
            }
        }
        currentLayer->clear();
        for (int i = 0; i < (int)sideA.size(); i++) {
            if (matchings[sideA[i]].first == -1) {
                (*currentLayer).push_back(sideA[i]);
            }
        }
    }
}