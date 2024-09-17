#include "maze.h"

/* Function Prototypes */
void cast_ray(SDL_Point *map, point_t *rayPos, point_t *rayDir, int *hit, int *side, int *maze);
double calculate_distance(SDL_Point map, point_t rayPos, point_t rayDir, int side);
void render_and_update(int *maze, SDL_Point map, point_t rayPos, point_t rayDir, double distToWall, int x, int side, bool textured);

/**
 * raycaster - casts rays and renders walls, floor, and ceiling
 * @maze: 2D array defining maze map
 * @textured: True if user enabled textures, otherwise False
 * Return: void
 */
void raycaster(int *maze, bool textured)
{
    int x;
    SDL_Point map;
    point_t rayPos, rayDir;
    int hit, side;
    double distToWall;

    for (x = 0; x < SCREEN_WIDTH; x++)
    {
        /* Calculate ray position and direction */
        double cameraX = 2 * x / (double)(SCREEN_WIDTH) - 1;
        rayPos.x = pos.x;
        rayPos.y = pos.y;
        rayDir.x = dir.x + plane.x * cameraX;
        rayDir.y = dir.y + plane.y * cameraX;

        /* Cast ray and detect hit */
        cast_ray(&map, &rayPos, &rayDir, &hit, &side, maze);

        /* Calculate distance to wall */
        distToWall = calculate_distance(map, rayPos, rayDir, side);

        /* Render walls and update buffer */
        render_and_update(maze, map, rayPos, rayDir, distToWall, x, side, textured);
    }

    updateRenderer(textured); /* Draw updated buffer */
}

/**
 * cast_ray - Cast a ray and determine if it hits a wall
 * @map: The position on the maze grid
 * @rayPos: Position of the ray
 * @rayDir: Direction of the ray
 * @hit: Whether the ray hits a wall
 * @side: The side of the wall that was hit
 * @maze: The maze array
 */
void cast_ray(SDL_Point *map, point_t *rayPos, point_t *rayDir, int *hit, int *side, int *maze)
{
    point_t posToNext, distToNext;
    SDL_Point step;

    map->x = (int)(rayPos->x);
    map->y = (int)(rayPos->y);

    /* Calculate distance to next X or Y intersection */
    distToNext.x = sqrt(1 + (pow(rayDir->y, 2)) / pow(rayDir->x, 2));
    distToNext.y = sqrt(1 + (pow(rayDir->x, 2)) / pow(rayDir->y, 2));

    /* Determine step and initial distance to next intersection */
    if (rayDir->x < 0)
    {
        step.x = -1;
        posToNext.x = (rayPos->x - map->x) * distToNext.x;
    }
    else
    {
        step.x = 1;
        posToNext.x = (map->x + 1.0 - rayPos->x) * distToNext.x;
    }

    if (rayDir->y < 0)
    {
        step.y = -1;
        posToNext.y = (rayPos->y - map->y) * distToNext.y;
    }
    else
    {
        step.y = 1;
        posToNext.y = (map->y + 1.0 - rayPos->y) * distToNext.y;
    }

    *hit = 0;
    while (*hit == 0)
    {
        if (posToNext.x < posToNext.y)
        {
            posToNext.x += distToNext.x;
            map->x += step.x;
            *side = 0;
        }
        else
        {
            posToNext.y += distToNext.y;
            map->y += step.y;
            *side = 1;
        }

        /* Check if ray hit a wall */
        if (*((int *)maze + map->x * MAP_WIDTH + map->y) > 0)
            *hit = 1;
    }
}

/**
 * calculate_distance - Calculate distance to the wall
 * @map: The position on the maze grid
 * @rayPos: Position of the ray
 * @rayDir: Direction of the ray
 * @side: The side of the wall that was hit
 * 
 * Return: Distance to the wall
 */
double calculate_distance(SDL_Point map, point_t rayPos, point_t rayDir, int side)
{
    double distToWall;

    if (side == 0)
        distToWall = (map.x - rayPos.x + (1 - step.x) / 2) / rayDir.x;
    else
        distToWall = (map.y - rayPos.y + (1 - step.y) / 2) / rayDir.y;

    return distToWall;
}

/**
 * render_and_update - Render walls and update the buffer
 * @maze: The maze array
 * @map: The position on the maze grid
 * @rayPos: Position of the ray
 * @rayDir: Direction of the ray
 * @distToWall: Distance to the wall
 * @x: X position on screen
 * @side: The side of the wall that was hit
 * @textured: Whether textures are enabled
 */
void render_and_update(int *maze, SDL_Point map, point_t rayPos, point_t rayDir, double distToWall, int x, int side, bool textured)
{
    renderWalls(maze, map, rayPos, rayDir, distToWall, x, side, textured);
}
