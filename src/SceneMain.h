#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H
#include "Scene.h"
#include"Object.h"
#include <list>
class Game;

class SceneMain : public Scene
{
public:
    SceneMain();
    ~SceneMain();
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void clean() override;
    void handleEvent(SDL_Event* event) override;
    
    void keyboardControl(float deltaTime);
    void shootPlayer();
    void updatePlayerProjectiles(float deltaTime);
    void renderPlayerProjectiles();

private:
    Game &game;
    player player;
    //创建每个物体的模板
    ProjectilePlayer projectilePlayerTemplate;


    std::list<ProjectilePlayer*> projectilesPlayer;//子弹很多，别用栈
    

};
#endif