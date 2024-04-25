#pragma once
#include "GameObject.hpp"
#include <vector>
#include <string>

const int MAP_IMAGE = 21;

class Box {
private:
    std::vector<GameObject*> maps;
    std::vector<GameObject*> image;
    GameObject* boxObject;

    vector<string> title;

public:
    Box();
    ~Box();

    void loadGameObject(GameObject* gameObject);
    void LoadNgram(const char* filepath);
    void LoadMapNgram(const char* filepath);

    GameObject* getGameObject() const;

    string _image_title;
    string _map_title;
    int index;
};

