#pragma once
#include<iostream>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include <vector>
#include "GameObject.hpp"
#include "GameNonogram.hpp"
#include "Map.hpp"

class Obj
{
public:
    static GameObject *background;
    static GameObject *startgame;
    static GameObject *ground;
    static GameObject *turtle;
    static GameObject *turtlerun;
    static GameObject *ogre;
    static GameObject *box;
    static GameObject *box1;
    static GameObject *box2;
    static GameObject *nonogram;
    static GameObject *color[ROW][COL];
    static GameObject *Collision;
    static GameObject *heart;
    static GameObject *bgrn;
    static GameObject *grid;
    static GameObject *lose;
    static GameObject *back_;
    static GameObject *box_locked;
    static GameObject *continue_;
    static GameObject *GameOver;

    int current[15][15]={0};
    int mapn[15][15];
    int clicked[15][15];
    vector<string> title;
    vector<GameObject*> Boxs = {
        new GameObject("Game Graphics/Box/Box.png", 100, 100, 148, 100),
        new GameObject("Game Graphics/Box/Box.png", 200, 150, 148, 100),
        new GameObject("Game Graphics/Box/Box.png", 300, 200, 148, 100),
        new GameObject("Game Graphics/Box/Box.png", 400, 250, 148, 100)
        };

    static Map *_map;

    static GameNgram *Ngram = new GameNgram();
    static GameNgram *sgNgram = new GameNgram();
    static GameNgram *Ngame = new GameNgram();


	static void LoadObj(renderer);
};


