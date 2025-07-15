#include "game.h"

// Global variables
Player kael = {120, 80, 0, -1}; // Start at center, neutral morality
GBA_STATE *state = (GBA_STATE *)0x03000000;
const char *choices[MAX_CHOICES] = {"Help survivors", "Ignore them", "Deceive them"};
int currentChoice = 0;
int inChoiceMenu = 0;

int main() {
    // Set video mode (Mode 3 for simplicity)
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    initGame();

    while (1) {
        VBlankIntrWait();
        handleInput();
        updateGame();
        drawGame();
    }

    return 0;
}

void initGame() {
    // Initialize Kael
    kael.gameState = 0; // Start in exploration
    m3_plot(kael.x, kael.y, RGB15(31, 0, 0));
}

void updateGame() {
    if (kael.gameState == 0) {
        // Exploration mode
        if (state->keys & KEY_LEFT) kael.x--;
        if (state->keys & KEY_RIGHT) kael.x++;
        if (state->keys & KEY_UP) kael.y--;
        if (state->keys & KEY_DOWN) kael.y++;
        // Trigger choice menu (e.g., when reaching survivors)
        if (state->keys & KEY_A) {
            kael.gameState = 1;
            inChoiceMenu = 1;
            currentChoice = 0;
        }
    } else if (kael.gameState == 1) {
        // Choice menu mode
        if (state->keys & KEY_UP && currentChoice > 0) currentChoice--;
        if (state->keys & KEY_DOWN && currentChoice < MAX_CHOICES - 1) currentChoice++;
        if (state->keys & KEY_A) {
            processChoice(currentChoice);
            kael.gameState = 0; // Return to exploration
            inChoiceMenu = 0;
        }
    }
}

void drawGame() {
    // Clear screen
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        ((u16 *)VRAM)[i] = RGB15(0, 0, 0);
    }
    // Draw Kael
    m3_plot(kael.x, kael.y, RGB15(31, 0, 0));
    // Draw choice menu
    if (inChoiceMenu) {
        showChoiceMenu(0);
    }
}

void handleInput() {
    state->keys = ~REG_KEYINPUT & KEY_ANY;
}

void showChoiceMenu(int choiceId) {
    // Placeholder: Draw text (requires font library or bitmap text)
    // For now, simulate text by drawing colored pixels
    for (int i = 0; i < MAX_CHOICES; i++) {
        int y = 50 + i * 20;
        // Highlight selected choice
        u16 color = (i == currentChoice) ? RGB15(31, 31, 31) : RGB15(15, 15, 15);
        for (int x = 20; x < 100; x++) {
            m3_plot(x, y, color);
        }
    }
}

void processChoice(int choice) {
    switch (choice) {
        case CHOICE_HELP:
            kael.morality += 10; // Increase Hope
            break;
        case CHOICE_IGNORE:
            kael.morality += 0; // Neutral
            break;
        case CHOICE_DECEIVE:
            kael.morality -= 10; // Increase Despair
            break;
    }
}
 divisio