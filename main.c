#include <raylib.h>
#include <ads7830.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define PLAYER_HOR_SPD 400.0f

typedef struct {
  Vector2 position;
  float velocity;
} Player;

void update_player(Player *player, float delta, ADC_device *adc) {
  if (ADC_read(adc, 1) > 134) {
    player->position.x += PLAYER_HOR_SPD * delta;
  }
  if (ADC_read(adc, 1) < 122) {
    player->position.x -= PLAYER_HOR_SPD * delta;
  }
  if (ADC_read(adc, 0) < 134) {
    player->position.y -= PLAYER_HOR_SPD * delta;
  }
  if (ADC_read(adc, 0) > 122) {
    player->position.y += PLAYER_HOR_SPD * delta;
  }

  if (IsKeyPressed(KEY_SPACE)) {
    DrawCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 5, GREEN);
  }
}

int main(void) {

  if (wiringPiSetup() == -1) {
      printf("Failed to initialize WiringPi\n");
      return 1;
  }

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Move the square game");
  Player player = {
      .position = {SCREEN_WIDTH/ 2, SCREEN_HEIGHT / 2},
      .velocity = 5.0f,
  };

  SetTargetFPS(60);

  ADC_device adc;
  if (ADC_init(&adc, 0x4b) < 0) {
    printf("ADC module failed to initialize.\n");
    return 1;
  };

  while (!WindowShouldClose()) {

    float deltaTime = GetFrameTime();

    update_player(&player, deltaTime, &adc);
    BeginDrawing();
    ClearBackground((Color){0, 0, 0, 255});
    Rectangle playerRect = {player.position.x - 20, player.position.y - 40,
                            40.0f, 40.0f};
    DrawRectangleRec(playerRect, RED);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
