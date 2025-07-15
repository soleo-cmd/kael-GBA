#include "game.h"

// Global variables
Player kael = {120, 80, 0, -1}; // Start Kael at screen center, neutral morality
GBA_STATE *state = (GBA_STATE *)0x03000000; // GBA input state

int main() {
    // Set video mode (Mode 3: 240x160, 16-bit color bitmap)
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    initGame();

    while (1) {
        // Wait for VBlank to avoid screen tearing
        VBlankIntrWait();
        handleInput();
        updateGame();
        drawGame();
    }

    return 0;
}

void initGame() {
    // Initialize Kael’s sprite (placeholder: draw a red pixel for now)
    m3_plot(kael.x, kael.y, RGB15(31, 0, 0)); // Red pixel in Mode 3
}

void updateGame() {
    // Update game state (e.g., move Kael based on input)
    if (state->keys & KEY_LEFT) kael.x--;
    if (state->keys & KEY_RIGHT) kael.x++;
    if (state->keys & KEY_UP) kael.y--;
    if (state->keys & KEY_DOWN) kael.y++;
}

void drawGame() {
    // Clear previous frame (black background)
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        ((u16 *)VRAM)[i] = RGB15(0, 0, 0); // Black
    }
    // Draw Kael (placeholder: red pixel)
    m3_plot(kael.x, kael.y, RGB15(31, 0, 0));
}

void handleInput() {
    // Read input state
    state->keys = ~REG_KEYINPUT & KEY_ANY;
}