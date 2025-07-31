#pragma once

#include "map.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class MapLoader {
public:
    static bool loadTiledMap(const std::string& jsonPath, Map* map);
    
private:
    static std::vector<int> parseDataArray(const std::string& jsonContent);
    static int findValue(const std::string& jsonContent, const std::string& key);
    static std::string findStringValue(const std::string& jsonContent, const std::string& key);
    static std::string readFile(const std::string& path);
    static TileType getTileTypeFromId(int tileId);
};