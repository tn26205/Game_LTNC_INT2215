#include "Map.hpp"

Map::Map()
{
    grass = TextureManager::LoadTexture("Game Graphics/grass/2.png");

    LoadMap("Map/file_map.txt");

    src.x = src.y = 0;
    src.w = dest.w = 35;
    src.h = dest.h = 35;

    dest.x = dest.y = 0;
}

Map::~Map()
{
}

void Map::LoadMap(const char* filepath)
{
    std::ifstream file(filepath);
    if(!file.is_open()) return;

    for(int i=0;i<24;i++){
        for(int j=0;j<48;j++){
            file >> map[i][j];
        }
    }
    file.close();

}

void Map::DrawMap()
{
    int type;

    for(int i=0;i<24;i++){
        for(int j=0;j<48;j++){
           type=map[i][j];

           dest.x = j*32;
           dest.y = i*32;

           switch (type)
           {
               case 1:
                    TextureManager::Draw(grass, src, dest);
                   break;
               default:
                break;
           }
        }
    }
}
