#include "Box_Map_Image.hpp"
#include <cstdlib>
#include <ctime>

extern const char* image_title;
extern const char* map_title;
extern const int ROW;
extern const int COL;
extern mapn[15][15];

Box::Box() : boxObject(nullptr) {
    LoadNgram("Nonogram.txt");
    srand(time(0));
    index = rand() % MAP_IMAGE + 1;
    _image_title = "Game Graphics/Nonogram/" + title[index] + ".png";
    _map_title = "Map/" + title[index] + ".txt";
    image_title = _image_title.c_str();
    map_title = _map_title.c_str();
    image.push_back(new GameObject(image_title,300,225,525,525));
    LoadMapNgram(map_title);
    maps.push_back(mapn)
}

Box::~Box() {
    delete boxObject;

    for (GameObject* map : maps) {
        delete map;
    }
}

void Box::LoadNgram(const char* filepath)
{
    std::ifstream file(filepath);
    if(!file.is_open()) return;

    for(int i=0;i<title.size();i++){
        file >> title[i];
    }
    file.close();
}

void Box::LoadMapNgram(const char* filepath)
{
    std::ifstream file(filepath);
    if(!file.is_open()) return;

    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            file >> mapn[i][j];
        }
    }
    file.close();
}

void Box::loadGameObject(GameObject* gameObject) {
    if (boxObject != nullptr) {
        delete boxObject;
    }
    int index = rand() % maps.size();
    boxObject = new GameObject(*maps[index]);
}

GameObject* Box::getGameObject() const {
    return boxObject;
}
