#include "maze.h"
#include "enemy.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

/* Define a structure to hold game state variables */
typedef struct Game
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];
	point_t pos;
	point_t dir;
	point_t plane;
	double time;
	Enemy enemy;
} Game;

/* Initialize game variables */
void initGame(Game *game)
{
	game->pos.x = 1;
	game->pos.y = 12;
	game->dir.x = 1;
	game->dir.y = -0.66;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->time = 0;
}

/* Initialize the enemy */
void initEnemy(Game *game)
{
	game->enemy.x = 5.0;
	game->enemy.y = 5.0;
	game->enemy.speed = 0.05;
	game->enemy.health = 100;
	game->enemy.texture = IMG_LoadTexture(game->renderer, "textures/enemy.png");
	if (game->enemy.texture == NULL)
	{
		fprintf(stderr, "Failed to load enemy texture\n");
	}
}

/* Main function */
int main(int argc, char *argv[])
{
	Game game;  /* Declare the game state */
	int *maze;  /* 2D array defining maze map */
	char *mapName;
	bool textured;

	/* Initialize the game state */
	initGame(&game);

	/* Check user arguments and set options */
	mapName = "\0";
	textured = true;
	if (argc == 3)
	{
		if (strcmp(argv[2], "no_tex") == 0)
		textured = false;
		mapName = argv[1];
	} else if (argc == 2)
	{
		if (strcmp(argv[1], "no_tex") == 0)
		{
			mapName = "maps/map_0";
			textured = false;
	} else
		mapName = argv[1];
	} else if (argc == 1)
		mapName = "maps/map_0";

	/* Start SDL and create window and renderer */
	printf("Initializing SDL...\n");
	if (!initSDL())
	{
		fprintf(stderr, "Failed to initialize SDL\n");
		return (1);
	}
	printf("SDL initialized successfully\n");

	/* Parse maze file */
	printf("Parsing maze map...\n");
	maze = NULL;
	maze = parseMap(mapName, maze);
	if (maze == NULL)
	{
		fprintf(stderr, "Failed to parse maze map\n");
		return (1);
	}
	printf("Maze map parsed successfully\n");

	/* Initialize the enemy */
	initEnemy(&game);

	if (textured)
	{
		printf("Loading textures...\n");
		loadTextures(mapName);
	printf("Textures loaded successfully\n");
	}

	/* Game loop */
	while (!quit())
	{
		/* Clear the buffer */
		clearBuffer();

		if (!textured)
		renderBGFlat();  /* Render background if no textures */

		/* Draw walls, textured floor, and textured ceiling */
		raycaster(maze, textured);

		/* Update and render the enemy */
		updateEnemy(&game);
		renderEnemy(&game);

		/* Handle user input */
		input(maze, &game);

		/* Present the rendered frame */
		SDL_RenderPresent(game.renderer);
	}

	/* Close SDL, renderer, and window */
	printf("Closing SDL...\n");
	closeSDL(&game);
	free(maze);
	freeEnemy(&game);  /* Free enemy resources */
	printf("SDL closed successfully\n");
	return (0);
}
