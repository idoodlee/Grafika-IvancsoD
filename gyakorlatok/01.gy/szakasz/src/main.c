#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>

typedef struct Color {
  char r, g, b;
} Color;

typedef struct Line {
  int x0, y0;
  int x1, y1;
  Color color;
} Line;

const int MAX_LINE_COUNT = 1000;

void clear(SDL_Renderer *renderer, const Color* color) {
  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
}

void draw_line(SDL_Renderer *renderer, const Line *line, const Color *color) {
  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, line->x0, line->y0, line->x1, line->y1);
}

/**
 * SDL2 example
 */
int main(int argc, char* argv[])
{
  int error_code;
  SDL_Window *window;
  bool need_run;
  SDL_Event event;
  SDL_Renderer *renderer;
  int i;

  Line lines[MAX_LINE_COUNT];
  int line_count = 0;

  error_code = SDL_Init(SDL_INIT_EVERYTHING);
  if (error_code != 0) {
    printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    return error_code;
  }

  window = SDL_CreateWindow(
    "Hello SDL!",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 600, 0);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  int mouseX, mouseY;
  bool new_line_created = false;

  Color background_color = { 0, 0, 0 };

  clear(renderer, &background_color);
  SDL_RenderPresent(renderer);

  need_run = true;
  while (need_run) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
        case SDL_SCANCODE_Q:
        need_run = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&mouseX, &mouseY);
        printf("(%d,%d)\n", mouseX, mouseY);
        if (line_count < MAX_LINE_COUNT && !new_line_created) {
          Line new_line = { mouseX, mouseY, mouseX, mouseY };
          lines[line_count++] = new_line;
          new_line_created = true;
        }
        break;
      case SDL_MOUSEMOTION:
        SDL_GetMouseState(&mouseX, &mouseY);
        if (new_line_created) {
          lines[line_count - 1].x1 = mouseX;
          lines[line_count - 1].y1 = mouseY;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        new_line_created = false;
        break;
      case SDL_QUIT:
        need_run = false;
        break;
      }

      clear(renderer, &background_color);

      for (int i = 0; i < line_count; i++)
      {
        Color color = { 255, 255, 255 };
        draw_line(renderer, &lines[i], &color);
      }

      SDL_RenderPresent(renderer);
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
