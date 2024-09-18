#include "enemy.h"
#include <SDL2/SDL_image.h>
#include <math.h>

void initEnemy(Enemy *enemy, SDL_Renderer *renderer, const char *texturePath, float x, float y) {
    enemy->x = x;
    enemy->y = y;
    enemy->speed = 0.05f;  // Example speed, adjust as needed
    enemy->health = 100;   // Example health, adjust as needed
    enemy->texture = IMG_LoadTexture(renderer, texturePath);  // Load enemy texture
}

void updateEnemy(Enemy *enemy, float playerX, float playerY) {
    // Example update logic: move towards the player
    float dx = playerX - enemy->x;
    float dy = playerY - enemy->y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > 0) {
        // Normalize direction
        dx /= distance;
        dy /= distance;

        // Move towards the player
        enemy->x += dx * enemy->speed;
        enemy->y += dy * enemy->speed;
    }
}

void renderEnemy(SDL_Renderer *renderer, Enemy *enemy) {
    // Render the enemy at its current position
    SDL_Rect destRect = {(int)enemy->x, (int)enemy->y, 32, 32};  // Adjust size as needed
    SDL_RenderCopy(renderer, enemy->texture, NULL, &destRect);
}

void freeEnemy(Enemy *enemy) {
    // Free resources
    SDL_DestroyTexture(enemy->texture);
    enemy->texture = NULL;
}
