#include "Initialization.hpp"

GameObject* Obj::background;
GameObject* Obj::back_;
GameObject* Obj::bgrn;
GameObject* Obj::box1;
GameObject* Obj::box2;
GameObject* Obj::box;
GameObject* Obj::startgame;
GameObject* Obj::ground;
GameObject* Obj::turtle;
GameObject* Obj::heart;
GameObject* Obj::grid;
GameObject* Obj::lose;
GameObject* Obj::continue_;
GameObject* Obj::GameOver;
Map* Obj::_map;

void Obj::LoadObj(renderer)
{
    background = new GameObject("Game Graphics/newbackground1.png",0,0,1536,768);
    startgame = new GameObject("Game Graphics/playgame.png",620,380,200,90);

    ground = new GameObject("Game Graphics/ground.png",0,0,1536,768);

    turtle = new GameObject("Game Graphics/Character/turtle.png",0,100,64,52);
    box = new GameObject("Game Graphics/Box/Box.png",100,100,148,100);
    box1 = new GameObject("Game Graphics/Box/Box.png",350,100,148,100);
    box2 = new GameObject("Game Graphics/Box/Box.png",600,100,148,100);
    bgrn = new GameObject("Game Graphics/Asset 3.png",-3,-10,1572,794);
    heart = new GameObject("Game Graphics/heart.png",heartPosX , heartPosY, heartWidth,heartHeight);
    grid = new GameObject("Game Graphics/grid.png",300,225,525,525);
    lose = new GameObject("Game Graphics/lose.png",80,150,160,114);
    back_ = new GameObject("Game Graphics/back.png",70,90,145,50);
    continue_ = new GameObject("Game Graphics/continue.png",70,150,144,43);

    GameOver = new GameObject("Game Graphics/GameOver.png", 812, 91, 510, 568);

    _map = new Map();

}

