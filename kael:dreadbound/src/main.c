#include "game.h"
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_input.h>
Player kael = {120, 80, 0, -1};
u16 *videoBuffer = (u16 *)0x06000000; // VRAM for Mode 3
const char *choices[MAX_CHOICES] = {"Help survivors", "Ignore them", "Deceive them"};
int currentChoice = 0;
int inChoiceMenu = 0;
int main() {
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    initGame();
    while (1) {
        VBlankIntrWait(); // libgba VBlank
        scanKeys(); // Update input
        updateGame();
        drawGame();
    }
    return 0;
}
void initGame() {
    kael.gameState = 0;
    videoBuffer[kael.y * SCREEN_WIDTH + kael.x] = RGB15(31, 0, 0); // Red pixel
}
void updateGame() {
    u16 keys = keysDown(); // libgba input
    if (kael.gameState == 0) {
        if (keys & KEY_LEFT) kael.x--;
        if (keys & KEY_RIGHT) kael.x++;
        if (keys & KEY_UP) kael.y--;
        if (keys & KEY_DOWN) kael.y++;
        if (keys & KEY_A) { kael.gameState = 1; inChoiceMenu = 1; currentChoice = 0; }
    } else if (kael.gameState == 1) {
        if (keys & KEY_UP && currentChoice > 0) currentChoice--;
        if (keys & KEY_DOWN && currentChoice < MAX_CHOICES - 1) currentChoice++;
        if (keys & KEY_A) { processChoice(currentChoice); kael.gameState = 0; inChoiceMenu = 0; }
    }
}
void drawGame() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        videoBuffer[i] = RGB15(0, 0, 0); // Clear screen
    }
    videoBuffer[kael.y * SCREEN_WIDTH + kael.x] = RGB15(31, 0, 0); // Draw Kael
    if (inChoiceMenu) showChoiceMenu(0);
}
void handleInput() {
    // Handled in updateGame
}
void showChoiceMenu(int choiceId) {
    // Simplified: Draw boxes (text needs libtonc)
    for (int i = 0; i < MAX_CHOICES; i++) {
        int y = 50 + i * 20;
        u16 color = (i == currentChoice) ? RGB15(31, 31, 31) : RGB15(15, 15, 15);
        for (int x = 20; x < 100; x++) {
            videoBuffer[y * SCREEN_WIDTH + x] = color;
        }
    }
}
void processChoice(int choice) {
    switch (choice) {
        case CHOICE_HELP: kael.morality += 10; break;
        case CHOICE_IGNORE: kael.morality += 0; break;
        case CHOICE_DECEIVE: kael.morality -= 10; break;
    }
}