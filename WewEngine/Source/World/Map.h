#pragma once

#include <vector>

#include "Tile.h"

class Map
{
private:
    std::vector<std::vector<Tile>> m_tiles;
    static constexpr int kTileWidth = 100;
    static constexpr int kTileHeight = 100;

public:
    Map();
    ~Map();

    void Draw(Renderer* pRenderer);
    bool Load(const FilePath& filePath);

    Tile* GetTile(const Point& position);
};

