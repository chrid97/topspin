#include "raylib.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define PLAYER_SPEED 300.0f
#define VIRTUAL_WIDTH 800
#define VIRTUAL_HEIGHT 450

typedef enum { SERVING, BALL_IN_PLAY } PlayerState;

typedef struct {
  Vector2 position;
  Vector2 velocity;
  int height;
  int width;
  float radius;
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

  Entity ball = {.radius = 6};
  PlayerState player_state = SERVING;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    // Screen scaling
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    float delta = GetFrameTime();
    float scale_x = (float)screen_width / VIRTUAL_WIDTH;
    float scale_y = (float)screen_height / VIRTUAL_HEIGHT;
    float scale = (scale_x < scale_y) ? scale_x : scale_y;

    // --------------- //
    // ---- Input ---- //
    // --------------- //
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
    if (IsKeyDown(KEY_SPACE)) {
      if (SERVING) {
        player_state = BALL_IN_PLAY;
        ball.velocity.x;
        // ball.velocity.x = -player.position;
        // if im in the bottom left i should serve to the top right and vice
        // versa
        // it should depend on my x axis
      }
    }

    // if (!ball_in_play && IsKeyDown(KEY_SPACE)) {
    //   ball =
    //       (Entity){.position = {.x = player.position.x, .y =
    //       player.position.y},
    //                .height = 6,
    //                .width = 6};
    //   ball_in_play = true;
    // }

    // ---------------- //
    // ---- Update ---- //
    // ---------------- //

    // Normalize diagonal player movement
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

    if (player_state == SERVING) {
      ball.position.x = player.position.x;
      ball.position.y = player.position.y;
    }

    // if (ball_in_play) {
    //   ball.position.x += ball.velocity.x * dt;
    //   ball.position.y += ball.velocity.y * dt;
    //   Rectangle playerRect = {player.position.x, player.position.y,
    //                           player.width, player.height};
    //   if (CheckCollisionCircleRec(ball.position, ball.height, playerRect)) {
    //     float closest_x_position =
    //         fmaxf(player.position.x,
    //               fminf(ball.position.x, player.position.x + player.width));
    //     float closest_y_position =
    //         fmaxf(player.position.y,
    //               (fmin(ball.position.y, player.position.y +
    //               player.height)));
    //
    //     Vector2 normal = {0, -1};
    //     float dx = ball.position.x - closest_x_position;
    //     float dy = ball.position.y - closest_y_position;
    //     float distance = sqrtf(dx * dx + dy * dy);
    //     if (distance != 0) {
    //       normal.x = dx / distance;
    //       normal.y = dy / distance;
    //
    //       // Push ball out
    //       float overlap = ball.height - distance;
    //       ball.position.x += normal.x * overlap;
    //       ball.position.y += normal.y * overlap;
    //     }
    //   }
    //
    //   if (ball.position.x - ball.height < 0 ||
    //       ball.position.x + ball.height > VIRTUAL_WIDTH) {
    //     ball.velocity.x *= -1;
    //   }
    //   if (ball.position.y - ball.height < 0 ||
    //       ball.position.y + ball.height > VIRTUAL_HEIGHT) {
    //     ball.velocity.y *= -1;
    //   }
    // }

    // ---------------- //
    // ----- Draw ----- //
    // ---------------- //
    BeginDrawing();
    ClearBackground(BLACK);

    DrawRectangle(player.position.x * scale, player.position.y * scale,
                  player.width * scale, player.height * scale, BLUE);

    DrawCircle(ball.position.x * scale, ball.position.y * scale,
               ball.radius * scale, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
