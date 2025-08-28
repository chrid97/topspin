#include "raylib.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define PLAYER_SPEED 300.0f
#define VIRTUAL_WIDTH 800
#define VIRTUAL_HEIGHT 450

typedef struct {
  Vector2 position;
  Vector2 velocity;
  int height;
  int width;
} Entity;

void test(char *text) {
  DrawText(text, GetScreenWidth() / 2, GetScreenHeight() / 2, 100, RED);
}

int main(void) {
  InitWindow(800, 450, "Topspin");
  SetTargetFPS(60);
  Entity player = {
      .position = {.x = GetScreenWidth() / 2.0f,
                   .y = GetScreenHeight() - (GetScreenHeight() / 4.0f)},
      .height = 32,
      .width = 32};

  Entity ball = {0};
  bool ball_in_play = false;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    // Screen scaling
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    float delta = GetFrameTime();
    float scale_x = (float)screen_width / VIRTUAL_WIDTH;
    float scale_y = (float)screen_height / VIRTUAL_HEIGHT;
    float scale = (scale_x < scale_y) ? scale_x : scale_y;

    // --- Input --- //

    if (IsKeyDown(KEY_R)) {
      ball =
          (Entity){.position = {.x = player.position.x, .y = player.position.y},
                   // .velocity = {.x = 250, .y = 250},
                   .velocity = {.x = 0, .y = 0},
                   .height = 6,
                   .width = 6};
    }

    Vector2 input = {0, 0};
    if (IsKeyDown(KEY_W)) {
      input.y -= 1;
    }
    if (IsKeyDown(KEY_S)) {
      input.y += 1;
    }
    if (IsKeyDown(KEY_A)) {
      input.x -= 1;
    }
    if (IsKeyDown(KEY_D)) {
      input.x += 1;
    }

    if (!ball_in_play && IsKeyDown(KEY_SPACE)) {
      ball =
          (Entity){.position = {.x = player.position.x, .y = player.position.y},
                   .velocity = {.x = 250, .y = 250},
                   .height = 6,
                   .width = 6};
      ball_in_play = true;
    }

    if (IsKeyDown(KEY_SPACE)) {
    }

    // --- Update --- //

    // Normalize diagonal movement
    if (input.x != 0 || input.y != 0) {
      float len = sqrt(input.x * input.x + input.y * input.y);
      input.x /= len;
      input.y /= len;
    }
    player.position.x += input.x * PLAYER_SPEED * dt;
    player.position.y += input.y * PLAYER_SPEED * dt;

    // --- Check Player Collison w/ Walls --- //
    if (player.position.x > VIRTUAL_WIDTH - player.width) {
      player.position.x = VIRTUAL_WIDTH - player.width;
    }
    if (player.position.x < 0) {
      player.position.x = 0;
    }
    if (player.position.y > VIRTUAL_HEIGHT - player.height) {
      player.position.y = VIRTUAL_HEIGHT - player.height;
    }
    if (player.position.y < 0) {
      player.position.y = 0;
    }

    if (ball_in_play) {
      Rectangle playerRect = {player.position.x, player.position.y,
                              player.width, player.height};
      if (CheckCollisionCircleRec(ball.position, ball.height, playerRect)) {
        test("IM INISDE");

        ball.velocity.y *= -1;
        // Reverse ball Y velocity to simulate hit
        // ball.velocity.y *= -1;
        // float hitOffset =
        //     (ball.position.x - (player.position.x + player.width / 2.0f)) /
        //     (player.width / 2.0f);

        // Bounce ball upward
        // ball.velocity.y = -ball.velocity.y;

        // Add some horizontal angle based on hit offset
        // ball.velocity.x = hitOffset * ball.velocity.x * 0.7f;

        // Optional: add horizontal velocity based on player input
        // ball.velocity.x += input.x * 2; // tweak for feel
      }
      // ball.position.y -= ball.velocity.y * dt;
      // ball.position.x -= ball.velocity.x * dt;

      ball.position.y -= ball.velocity.y * dt;
      if (ball.position.y < 0) {
        ball.velocity.y = -ball.velocity.y;
      }

      if (ball.position.y > VIRTUAL_HEIGHT - ball.height) {
        ball.velocity.y = -ball.velocity.y;
      }
    }

    // --- Draw --- //
    BeginDrawing();
    ClearBackground(BLACK);

    DrawRectangle(player.position.x * scale, player.position.y * scale,
                  player.width * scale, player.height * scale, BLUE);

    DrawCircle(ball.position.x * scale, ball.position.y * scale,
               ball.width * scale, WHITE);

    // DrawRectangle(0, (screen_height / 2.0f) * scale, screen_width * scale,
    //               5 * scale, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
