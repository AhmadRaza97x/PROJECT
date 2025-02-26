#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

// Game board dimensions
int width = 40, height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLength;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

// Function to hide the blinking cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 10;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Function to move the cursor to the top-left (for smooth rendering)
void moveCursorToTop() {
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void setup() {
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tailLength = 0;
}

void draw() {
    moveCursorToTop();  // Move cursor to the top instead of clearing the screen

    for (int i = 0; i <= width/2; i++) printf("# ");
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) printf("#");
            
            if (i == y && j == x)
                printf("O"); // Snake head
            else if (i == fruitY && j == fruitX)
                printf("F"); // Fruit
            else {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        isTail = 1;
                        break;
                    }
                }
                if (!isTail) printf(" ");
            }

            if (j == width - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i <= width/2 ; i++) printf("# ");
    printf("\n");

    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if ((key == 'a' && dir != RIGHT) ||
            (key == 'd' && dir != LEFT) ||
            (key == 'w' && dir != DOWN) ||
            (key == 's' && dir != UP)) {
            switch (key) {
                case 'a': dir = LEFT; break;
                case 'd': dir = RIGHT; break;
                case 'w': dir = UP; break;
                case 's': dir = DOWN; break;
            }
        }
        if (key == 'x') exit(0); // Exit game
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    // Screen wrapping logic
    if (x >= width) x = 0; 
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0; 
    else if (y < 0) y = height - 1;

    // Check for collision with tail
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            printf("Game Over!\n");
            system("pause"); // Wait for user input before exiting
            exit(0);
        }
    }

    // Eating the fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLength++;
    }
}

int main() {
    hideCursor();
    setup();

    while (1) {
        draw();
        input();
        logic();
        Sleep(50); // Adjust speed
    }
    
    return 0;
}
