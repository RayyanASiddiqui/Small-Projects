#include <iostream>
#include <vector>
#include <cmath>
#include <raylib.h>

using namespace std;

class Laser{
    public:
    Vector2 initialPos;
    Vector2 endPos;
    Color laserColor;
    Laser(Vector2 posOne, Vector2 posTwo, Color color){
        this -> initialPos = posOne;
        this -> endPos = posTwo;
        this -> laserColor = color;
    }
    void drawLaser(){
        DrawLineV(initialPos, endPos, laserColor);
    }
    void moveLaser(int speed){
        initialPos.x -= speed;
        endPos.x -= speed;
    }
    Color returnColor(){
        return laserColor;
    }
};

class Player{
    public:
    Color ballColor;
    Vector2 ballPosition;
    float ballRadius;
    vector<Vector2> trail = {};
    Player(Color color, Vector2 pos, vector<Vector2>trailParticles, float radius){
        this -> ballColor = color;
        this -> ballPosition = pos;
        this -> trail = trailParticles;
        this -> ballRadius = radius;
    }
    void drawBall(){
        DrawCircleV(ballPosition, ballRadius, ballColor);
    }
    void drawTrail(){
        for (int i = 0; i < trail.size(); i++){
            float alpha = (float)i / 10; 
            Color color = Fade(ballColor, alpha);
            DrawCircleV(trail[i], ballRadius, color);
        }
    }
};

Color setBallColor(){
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) || IsKeyDown(KEY_C)){
        return PURPLE;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsKeyDown(KEY_X)){
        return RED;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_Z)){
        return BLUE;
    }
    else{
        return DARKGRAY;
    }
}

void laserSpeed(int level, int &speed){
    speed = 3 + 0.07 * pow(level, 1.1); // Could be optimised but works for now
}

bool allLasersOffScreen(vector<Laser> &lasers){
    for (int i = 0; i < lasers.size(); i++){
        if (lasers[i].initialPos.x > 0 || lasers[i].endPos.x > 0){
            return false;
        }
    }
    return true;
}

void spawnLasers(vector<Laser>& lasers, int &level){
    lasers.clear();
    for (int i = 0; i < level; i++){
        float x1 = 1200 + i * 100;
        float x2;

        int orientation = rand() % 2; // Makes random start and end points
        if (orientation == 0){
            x2 = x1 + rand() % 201;
        }
        else if (orientation == 1){
            x2 = x1 - rand() % 201;
        }

        Color laserColor; // Random color picked
        if (level < 10){
            int randIntForColor = rand() % 2;
            if (randIntForColor == 0){
                laserColor = BLUE;
            }
            else if (randIntForColor == 1){
                laserColor = RED;
            }
        }
        else if (level >= 10){ // Purple unlocked level 10
            int randIntForColor = rand() % 3;
            if (randIntForColor == 0){
                laserColor = BLUE;
            }
            else if (randIntForColor == 1){
                laserColor = RED;
            }
            else if (randIntForColor == 2){
                laserColor = PURPLE;
            }
        }

        lasers.push_back(Laser({x1, 0}, {x2, 300}, laserColor));
    }
}

bool CompareColors(Color colorOne, Color colorTwo){
    if (colorOne.r == colorTwo.r &&
        colorOne.g == colorTwo.g &&
        colorOne.b == colorTwo.b &&
        colorOne.a == colorTwo.a){
        return true;
    }
    else{
        return false;
    }
}

// Ignore the debugging terms lol, they're all memes or references, not relevant to code


bool checkCollision(Laser &laser, Player &ball, bool &pause, bool &invincibility, Sound slashWhoosh){
    if (invincibility == false){
        PlaySound(slashWhoosh);
        if (CompareColors(ball.ballColor, laser.laserColor)){
            cout << "Skibidi" << endl;
            return true;
        }
        else{
            cout << "Sadge" << endl;
            return false;
        }
    }
    else{
        return false;
    }
}

void pausePowerup(bool &pause, int &level, int &lastUsedOne, Sound effect){
    if (IsKeyPressed(KEY_Q) && level >= 5 && level >= lastUsedOne + 3){
        PlaySound(effect);
        cout << "Pause bruh" << endl;
        lastUsedOne = level;
        pause = true;
        WaitTime(3);
        pause = false;
    }
}

void invincibilityPowerup(bool &invincibility, int &level, int &lastUsedTwo, Sound effect){
    if (IsKeyPressed(KEY_W) && level >= 8 && level >= lastUsedTwo + 5){
        PlaySound(effect);
        cout << "Prepare for my arrival worm" << endl;
        lastUsedTwo = level;
        invincibility = true;
    }
    if (level != lastUsedTwo){
        invincibility = false;
    }
}

void endScreen(int score){
    BeginDrawing();
        DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), RED, BLUE);
        DrawText("Game Over", 500, 140, 30, WHITE);
        DrawText("Final Score:", 500, 180, 30, WHITE);
        DrawText(to_string(score).c_str(), 700, 180, 30, WHITE);
    EndDrawing();
}