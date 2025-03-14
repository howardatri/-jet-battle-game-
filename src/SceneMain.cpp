#include "SceneMain.h"
#include <SDL_image.h>
#include <SDL.h>
#include "Game.h"

SceneMain::SceneMain():game(Game::getInstance())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::init()
{
    player.texture=IMG_LoadTexture(game.getRenderer(),"assets/image/SpaceShip.png");
    SDL_QueryTexture(player.texture,nullptr,nullptr,&player.width,&player.height);
    player.width/=4;
    player.height/=4;
    player.position.x=game.getWindowWidth()/2-player.width/2;
    player.position.y=game.getWindowHeight()-player.height;

    //初始化模板
    projectilePlayerTemplate.texture=IMG_LoadTexture(game.getRenderer(),"assets/image/laser-1.png");
    SDL_QueryTexture(projectilePlayerTemplate.texture,nullptr,nullptr,&projectilePlayerTemplate.width,&projectilePlayerTemplate.height);
    projectilePlayerTemplate.width/=4;
    projectilePlayerTemplate.height/=4;


}


void SceneMain::update(float deltaTime)
{
    keyboardControl(deltaTime);
    updatePlayerProjectiles(deltaTime);
}

void SceneMain::render()
{
    //渲染玩家子弹
    renderPlayerProjectiles();
    //渲染玩家
    SDL_Rect PlayerRect={static_cast<int>(player.position.x),static_cast<int>(player.position.y),player.width,player.height};
    SDL_RenderCopy(game.getRenderer(),player.texture,nullptr,&PlayerRect);

}

void SceneMain::clean()
{
    //清理容器
    for(auto &projectile:projectilesPlayer){
        delete projectile;
    }
    projectilesPlayer.clear();
    //清理模板
    if(player.texture!=nullptr){
        SDL_DestroyTexture(player.texture);
    }
    if(projectilePlayerTemplate.texture!=nullptr){
        SDL_DestroyTexture(projectilePlayerTemplate.texture);
    }
}

void SceneMain::handleEvent(SDL_Event *event)
{
}

void SceneMain::keyboardControl(float deltaTime)
{
    auto keyboardState=SDL_GetKeyboardState(NULL);
    if(keyboardState[SDL_SCANCODE_W]){
        player.position.y-=deltaTime*player.speed;
    }
    if(keyboardState[SDL_SCANCODE_S]){
        player.position.y+=deltaTime*player.speed;
    }
    if(keyboardState[SDL_SCANCODE_A]){
        player.position.x-=deltaTime*player.speed;
    }
    if(keyboardState[SDL_SCANCODE_D]){
        player.position.x+=deltaTime*player.speed;
    }
    //限制飞船的移动范围
    if(player.position.x<0){
        player.position.x=0;
    }
    if(player.position.x>game.getWindowWidth()-player.width){
        player.position.x=game.getWindowWidth()-player.width;
    }
    if(player.position.y<0){
        player.position.y=0;
    }
    if(player.position.y>game.getWindowHeight()-player.height){
        player.position.y=game.getWindowHeight()-player.height;
    }

    //控制子弹发射
    if(keyboardState[SDL_SCANCODE_J]){
        auto currentTime=SDL_GetTicks();
        if(currentTime-player.lastShootTime>player.coolDown){
            shootPlayer();
            player.lastShootTime=currentTime;
            
        }
    }
}

void SceneMain::shootPlayer()
{
    //实现发射子弹逻辑
    auto projectile=new ProjectilePlayer(projectilePlayerTemplate);
    projectile->position.x=player.position.x+player.width/2-projectile->width/2;
    projectile->position.y=player.position.y-projectile->height;
    projectilesPlayer.push_back(projectile);
}

void SceneMain::updatePlayerProjectiles(float deltaTime)
{
    for(auto it=projectilesPlayer.begin();it!=projectilesPlayer.end();){
        auto projectile=*it;
        projectile->position.y-=deltaTime*projectile->speed;
        //检查子弹是否超出屏幕
        ++it;
        
    }

}

void SceneMain::renderPlayerProjectiles()
{
    for(auto projectile:projectilesPlayer){
        SDL_Rect projectileRect={static_cast<int>(projectile->position.x),static_cast<int>(projectile->position.y),projectile->width,projectile->height};
        SDL_RenderCopy(game.getRenderer(),projectile->texture,nullptr,&projectileRect);
    }

}
