#include "map_loader.h"
#include <sstream>

bool MapLoader::loadTiledMap(const std::string& jsonPath, Map* map) {
    std::string jsonContent = readFile(jsonPath);
    if (jsonContent.empty()) {
        std::cerr << "Failed to read map file: " << jsonPath << std::endl;
        return false;
    }
    
    // Parse basic map properties
    int mapWidth = findValue(jsonContent, "\"width\"");
    int mapHeight = findValue(jsonContent, "\"height\"");
    int tileWidth = findValue(jsonContent, "\"tilewidth\"");
    int tileHeight = findValue(jsonContent, "\"tileheight\"");
    
    if (mapWidth <= 0 || mapHeight <= 0) {
        std::cerr << "Invalid map dimensions" << std::endl;
        return false;
    }
    
    // Parse tile data array
    std::vector<int> tileData = parseDataArray(jsonContent);
    if (tileData.size() != mapWidth * mapHeight) {
        std::cerr << "Tile data size mismatch. Expected: " << (mapWidth * mapHeight) 
                  << ", Got: " << tileData.size() << std::endl;
        return false;
    }
    
    // Update map dimensions
    map->width = mapWidth;
    map->height = mapHeight;
    map->tileSize = 48; // Keep your current tile size for rendering
    
    // Resize and populate tile array
    map->tiles.clear();
    map->tiles.resize(mapHeight);
    for (int y = 0; y < mapHeight; y++) {
        map->tiles[y].resize(mapWidth);
        for (int x = 0; x < mapWidth; x++) {
            int tileId = tileData[y * mapWidth + x];
            map->tiles[y][x] = getTileTypeFromId(tileId);
        }
    }
    
    return true;
}

std::vector<int> MapLoader::parseDataArray(const std::string& jsonContent) {
    std::vector<int> data;
    
    // Find the data array
    size_t dataStart = jsonContent.find("\"data\":[");
    if (dataStart == std::string::npos) {
        std::cerr << "Could not find data array in JSON" << std::endl;
        return data;
    }
    
    dataStart += 8; // Skip "data":["
    size_t dataEnd = jsonContent.find(']', dataStart);
    if (dataEnd == std::string::npos) {
        std::cerr << "Could not find end of data array" << std::endl;
        return data;
    }
    
    std::string dataStr = jsonContent.substr(dataStart, dataEnd - dataStart);
    
    // Parse comma-separated integers
    std::stringstream ss(dataStr);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        // Remove whitespace
        token.erase(0, token.find_first_not_of(" \t\n\r"));
        token.erase(token.find_last_not_of(" \t\n\r") + 1);
        
        if (!token.empty()) {
            try {
                int value = std::stoi(token);
                data.push_back(value);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing tile ID: " << token << std::endl;
            }
        }
    }
    
    return data;
}

int MapLoader::findValue(const std::string& jsonContent, const std::string& key) {
    size_t pos = jsonContent.find(key + ":");
    if (pos == std::string::npos) {
        return -1;
    }
    
    pos += key.length() + 1;
    size_t numStart = jsonContent.find_first_of("0123456789", pos);
    if (numStart == std::string::npos) {
        return -1;
    }
    
    size_t numEnd = jsonContent.find_first_not_of("0123456789", numStart);
    if (numEnd == std::string::npos) {
        numEnd = jsonContent.length();
    }
    
    std::string numStr = jsonContent.substr(numStart, numEnd - numStart);
    try {
        return std::stoi(numStr);
    } catch (const std::exception& e) {
        return -1;
    }
}

std::string MapLoader::findStringValue(const std::string& jsonContent, const std::string& key) {
    size_t pos = jsonContent.find(key + ":");
    if (pos == std::string::npos) {
        return "";
    }
    
    pos = jsonContent.find('"', pos + key.length() + 1);
    if (pos == std::string::npos) {
        return "";
    }
    
    pos++; // Skip opening quote
    size_t endPos = jsonContent.find('"', pos);
    if (endPos == std::string::npos) {
        return "";
    }
    
    return jsonContent.substr(pos, endPos - pos);
}

std::string MapLoader::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << path << std::endl;
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

TileType MapLoader::getTileTypeFromId(int tileId) {
    // Dựa vào tile ID từ Tiled map, quy định loại tile
    // Bạn cần điều chỉnh theo tileset của mình
    
    if (tileId == 0) {
        return TILE_BLOCK; // Empty tile
    }
    
    // Path tiles (đường đi - thường là các tile có ID cụ thể)
    if (tileId == 2 || tileId == 3 || tileId == 26 || tileId == 31 || tileId == 32) {
        return TILE_PATH;
    }
    
    // Blocked tiles (obstacles like trees, rocks)
    if (tileId == 63 || tileId == 64 || tileId == 65 || tileId == 66 || tileId == 67 || 
        tileId == 78 || tileId == 79 || tileId == 90 || tileId == 91 || 
        tileId == 102 || tileId == 103 || tileId == 104) {
        return TILE_BLOCK;
    }
    
    // Default: buildable grass tiles
    return TILE_BUILDABLE;
}