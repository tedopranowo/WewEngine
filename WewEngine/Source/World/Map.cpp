#include "Map.h"

#include <Logger.h>

#include "..\WDataLoader\WDataLoader.h"

Map::Map()
{
}


Map::~Map()
{
}

void Map::Draw(Renderer * pRenderer)
{
    for (auto& row : m_tiles)
    {
        for (auto& tile : row)
        {
            tile.Draw(pRenderer);
        }
    }
}

bool Map::Load(const FilePath & filePath)
{
    //Load the file
    WDataLoader fileLoader(filePath);
    if (!fileLoader.Load())
        return false;

    //Make sure the file type is correct
    if (fileLoader.GetObjectType() != "Map")
    {
        LOG(Error, "%s does not contain \"World\" type object", filePath.GetFileName().c_str());
        return false;
    }

    //Get the map
    std::string map = fileLoader["Map"];
    std::vector<Tile> row;
    unsigned int index = 0;

    //Ignore enter and whitespace until the first real data
    while (isspace(map[index]) || map[index] == '\n')
        ++index;

    //Iterate through the map data
    for (; index < map.length(); ++index)
    {
        char terrainChar = map[index];

        //If it is the end of line, start a new row
        if (terrainChar == '\n')
        {
            m_tiles.push_back(std::move(row));
            continue;
        }

        //If it is not the end of the line, push the terrainChar into row
        std::string terrainKey;
        terrainKey += terrainChar;

        FilePath terrainFilePath(filePath);
        terrainFilePath.ChangePath(fileLoader[terrainKey]);
        
        int x = static_cast<int>(row.size());
        int y = static_cast<int>(m_tiles.size());
        row.push_back(Tile(terrainFilePath, Rect(x * kTileWidth, y * kTileHeight, kTileWidth, kTileHeight)));
    }

    return true;
}

Tile * Map::GetTile(const Point & position)
{
    if (position.y < static_cast<int>(m_tiles.size()) && position.y >= 0)
    {
        if (position.x < static_cast<int>(m_tiles[position.y].size()) && position.x >= 0)
        {
            return &m_tiles[position.y][position.x];
        }
    }
    return nullptr;
}
