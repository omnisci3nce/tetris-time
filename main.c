#include "raylib.h"
#include "stdio.h"

// Board
#define BOARD_WIDTH  10
#define BOARD_HEIGHT 20
// UI Layout
#define PADDING_LEFT 70
#define PADDING_TOP 40

enum OverallGameState {
  GAME_PLAYING,
  GAME_PAUSED
};

enum Rotation {
  ROTATED_0 = 0,
  ROTATED_90 = 1,
  ROTATED_180 = 1,
  ROTATED_270 = 1
};

// TODO
typedef struct tetrimino {
  Color color;
  enum Rotation rotation;
  int structure[4][4];
} tetrimino;

typedef struct game_state {
  enum OverallGameState state;
  int board[BOARD_WIDTH][BOARD_HEIGHT];
} game_state;

void handle_input(game_state* gs) {
  if (IsKeyReleased(KEY_UP)) printf("Key up\n");
  if (IsKeyReleased(KEY_DOWN)) printf("Key down\n");
  if (IsKeyReleased(KEY_LEFT)) printf("Key left\n");
  if (IsKeyReleased(KEY_RIGHT)) printf("Key right\n");

  if (IsKeyReleased(KEY_SPACE)) {
    if (gs->state = GAME_PLAYING) {
      printf("Game paused\n");
      gs->state = GAME_PAUSED;
    }
    if (gs->state = GAME_PAUSED) {
      printf("Game playing\n");
      gs->state = GAME_PLAYING;
    }
  }
}

void init_game_state(game_state* gs) {
  printf("Initialise game state\n");
  gs->state = GAME_PAUSED;

  for (int x = 0; x < BOARD_WIDTH; x++) {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
      gs->board[x][y] = 0;
    }
  }

  // Test -> draw one "tetrimino"
  gs->board[4][BOARD_HEIGHT-1] = 1;
  gs->board[4][BOARD_HEIGHT-2] = 1;
  gs->board[5][BOARD_HEIGHT-1] = 1;
  gs->board[5][BOARD_HEIGHT-2] = 1;
}

static Color TET_TO_COLOR[3] = {
  (Color){ 0, 0, 0, 0 },
  (Color){ 0, 255, 255, 255 }, // Cyan
  (Color){ 0, 121, 241, 255 }  // Blue
};

void draw_board(game_state* gs) {
  for (int x = 0; x < BOARD_WIDTH; x++) {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
      if (gs->board[x][y] == 0) {
        // Draw empty square as outline
        DrawRectangleLines(0 + x * 25 + PADDING_LEFT, 0 + y * 25 + PADDING_TOP, 25, 25, LIGHTGRAY);
      } else {
        Color square_color = TET_TO_COLOR[gs->board[x][y]];
        // Draw filled square for frozen tetrimino
        DrawRectangle(0 + x * 25 + PADDING_LEFT, 0 + y * 25 + PADDING_TOP, 25, 25, square_color);
      }
    }
  }
}

// Every 'tick' we should move current floating block down one
void tick() {
  // if any part of floating block body + 1 in y direction is already occupied
  // -- then freeze this block

}

/* Spawn random tetrimino */
// void spawn_tetrimino() {
//   // for now just spawn the one type
//   tetrimino new_tet = {
//     .color = BLUE,
//     .rotation = 
//   }
// }

int main(void) {
  InitWindow(800, 600, "Tetris");

  game_state gs;
  init_game_state(&gs);

  while (!WindowShouldClose()) {
    handle_input(&gs);

    BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_board(&gs);

        DrawText("Tetris Time", 500, 200, 20, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}