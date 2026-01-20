#include "colourswipeheader.hpp"

int main(){

    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 300;
    srand(time(0));
    InitAudioDevice();

    // Variables for da ball
    Color ballColor;
    Vector2 ballPosition;
    vector<Vector2> trail;
    float radius = 10;
    Player ball(ballColor, ballPosition, trail, radius);

    // Level Counter, Speed, and other things i guess
    int level = 1;
    int speed;
    bool gameOver = false;

    // Powerup stuff
    bool pause = false;
    bool invincible = false;
    int lastUsedPause = 0;
    int lastUsedInvincibility = 0;

    // Music and Audio
    bool gameOverSFXPlayed = false;
    bool purpleLaserUnlockSoundPlayed = false;
    bool upgradeSoundPlayedOne = false;
    bool upgradeSoundPlayedTwo = false;
    Music bgm = LoadMusicStream("Audio/bgmusic.mp3");
    PlayMusicStream(bgm);
    Sound laserSwoosh = LoadSound("Audio/slash.mp3");
    Sound gameOverDunDunDun = LoadSound("Audio/GAMEOVER.mp3");
    Sound upgradeUnlock = LoadSound("Audio/Unlock.mp3");
    Sound ggez = LoadSound("Audio/ggbro.mp3");
    Sound pauselol = LoadSound("Audio/pause.mp3");
    Sound INVINCIBLEYEA = LoadSound("Audio/invinc.mp3");


    // Laser Vector
    vector<Laser> lasers = {Laser({1100, 0}, {1200, 300}, RED)}; // Needs a default to start, then it generates itself

    // Only variables should be above this, otherwise it won't work I think
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Colour Swipe");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){

        UpdateMusicStream(bgm);
        if (IsMusicStreamPlaying(bgm) == false){
            PlayMusicStream(bgm);
        }

        if (gameOver != true){

            // Setup
            HideCursor();
            ball.ballPosition = GetMousePosition();
            ball.ballColor = setBallColor();
            ClearBackground(WHITE);
            laserSpeed(level, speed);
            
            // Mouse Trail
            ball.trail.push_back(ball.ballPosition);
            if (ball.trail.size() > 10) {
                ball.trail.erase(ball.trail.begin());
            }

            // Laser Spawning
            for (int i = 0; i < lasers.size(); i++){
                lasers[i].moveLaser(speed);
            }
            if (allLasersOffScreen(lasers)){
                level++;
                spawnLasers(lasers, level);
            }

            BeginDrawing();
        
                // Instructions, at the end so they render above the ball and lasers, nvm it covers too much
                DrawText("Match the colours to pass through!", 15, 15, 20, BLACK);
                DrawText("(Left/Z) Blue, (Right/X) Red ", 15, 35, 20, BLACK);
                DrawText("Current Level:", 15, 55, 20, BLACK);
                DrawText(to_string(level).c_str(), 200, 55, 20, BLACK);

                // Powerup Unlocks
                if (level < 5){
                    DrawText("Pause (Q): Unlocks at level 5" , 15, 250, 20, ORANGE);
                }
                else{
                    DrawText("Pause (Q) unlocked! - 3 second pause. Cooldown: 3L" , 15, 250 , 20, ORANGE);
                    if (upgradeSoundPlayedOne != true){
                        PlaySound(upgradeUnlock);
                        upgradeSoundPlayedOne = true;
                    }
                }
                if (level < 8){
                    DrawText("Invincibility (W): Unlocks at level 8" , 15, 270, 20, LIME);
                }
                else{
                    DrawText("Invincibility (W) unlocked! - 1 level. Cooldown: 5L" , 15, 270, 20, LIME);
                    if (upgradeSoundPlayedTwo != true){
                        PlaySound(upgradeUnlock);
                        upgradeSoundPlayedTwo = true;
                    }
                }
                if (level >= 10){
                    if (purpleLaserUnlockSoundPlayed != true){
                        PlaySound(upgradeUnlock);
                        purpleLaserUnlockSoundPlayed = true;
                    }
                    DrawText("Purple Lasers Unlocked! (Scroll Wheel/C) Purple" , 15, 75, 20, PURPLE);
                }

                // Ball Movement & Trail Fade
                ball.drawBall();
                ball.drawTrail();

                // Draw Lasers
                for (int i = 0; i < lasers.size(); i++){
                    lasers[i].drawLaser();
                }

                // Power Up Checks
                pausePowerup(pause , level, lastUsedPause, pauselol);
                invincibilityPowerup(invincible, level, lastUsedInvincibility, INVINCIBLEYEA);

                // Collision Stuff, works with function, for some reason can't get it to work all in that
                for (int i = 0; i < lasers.size(); i++){
                    if (CheckCollisionCircleLine(ball.ballPosition, ball.ballRadius, lasers[i].initialPos, lasers[i].endPos)){
                        if (checkCollision(lasers[i], ball, pause, invincible, laserSwoosh) == false && invincible == false){
                            gameOver = true;
                        }
                    }
                }

            EndDrawing();
        } 
        else{

            // Game Over Screen
            ShowCursor();
            StopMusicStream(bgm);
            endScreen(level);
            if (gameOverSFXPlayed != true){
                PlaySound(gameOverDunDunDun);
                SetSoundVolume(ggez, .4);
                PlaySound(ggez);
                gameOverSFXPlayed = true;
            }
        }
    }

    UnloadMusicStream(bgm);
    UnloadSound(gameOverDunDunDun);
    UnloadSound(laserSwoosh);
    UnloadSound(upgradeUnlock);
    UnloadSound(ggez);
    UnloadSound(INVINCIBLEYEA);
    UnloadSound(pauselol);
    CloseAudioDevice();

    CloseWindow();
}