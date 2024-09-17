#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

typedef struct {
    float x, y;            // Position of the enemy
    float speed;           // Movement speed
    int health;            // Health points
    SDL_Texture *texture;  // Texture for rendering
} Enemy;

// Function declarations
void initEnemy(Enemy *enemy, SDL_Renderer *renderer, const char *texturePath, float x, float y);
void updateEnemy(Enemy *enemy, float playerX, float playerY);
void renderEnemy(SDL_Renderer *renderer, Enemy *enemy);
void freeEnemy(Enemy *enemy);

#endif // ENEMY_H
