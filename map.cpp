#include "Map.hpp"

extern const int START_X_GRID;
extern const int START_X_GRID;
extern const int PUZZLE_SIZE;

Map::Map()
{
    grass = TextureManager::LoadTexture("Game Graphics/grass/1.png");

    LoadNgram("mapNgram.txt");

    LoadMap("file_map.txt");

    src.x = src.y = 0;
    src.w = dest.w = 36;
    src.h = dest.h = 34;

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

void Map::mapNgram()
{


    black = TextureManager::LoadTexture("Game Graphics/puzzle/black.png");
    red = TextureManager::LoadTexture("Game Graphics/puzzle/red.png");
    x_black = TextureManager::LoadTexture("Game Graphics/puzzle/x_black.png");
    x_red = TextureManager::LoadTexture("Game Graphics/puzzle/x_red.png");
    src_n.x = src_n.y = 0;
    src_n.w = dest_n.w = 35;
    src_n.h = dest_n.h = 35;

    dest_n.x = dest_n.y = 0;
}

void Map::LoadNgram(const char* filepath)
{
    std::ifstream file(filepath);
    if(!file.is_open()) return;

    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            file >> mapn[i][j];
        }
    }
    file.close();
}

void Map::DrawNgram(int digit,int pos_x, int pos_y)
{
    std::cout << "ok" << std::endl;
    /*for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
           //type=cur->current[i][j];*/


           dest_n.x = START_X_GRID + pos_y * PUZZLE_SIZE;
           dest_n.y = START_Y_GRID + pos_x * PUZZLE_SIZE;

           std::cout << dest_n.x << " " << dest_n.y << std::endl;
           switch (digit)
           {
               case 3:
                   TextureManager::Draw(x_red, src_n, dest_n);
                   break;
               case 0:
                   TextureManager::Draw(x_black, src_n, dest_n);
                   break;
               case 1:
                   TextureManager::Draw(black, src_n, dest_n);
                   break;
               case 2:
                   TextureManager::Draw(grass, src_n, dest_n);
                   break;
               default:
                break;
           }

                    SDL_RenderPresent(Game::renderer);
        //}
    //}
}
