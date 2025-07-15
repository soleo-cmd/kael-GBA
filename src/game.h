#ifndef GAME_H
#define GAME_H

#include <gba.h>

// Constants
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160
#define MAX_CHOICES 3
#define CHOICE_HELP 0
#define CHOICE_IGNORE 1
#define CHOICE_DECEIVE 2

// Game state
typedef struct {
    int x, y; // Kael's sprite position
    int morality; // Hope (positive) vs. Despair (negative)
    int choice; // Current player choice
    int gameState; // 0 = exploration, 1 = choice menu
} Player;

// Function declarations
void initGame();
void updateGame();
void drawGame();
void handleInput();
void showChoiceMenu(int choiceId);
void processChoice(int choice);

#endif