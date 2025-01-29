#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake_utils.h"
#include "state.h"

/* Helper function definitions */
static char get_board_at(game_state_t *state, int x, int y);
static void set_board_at(game_state_t *state, int x, int y, char ch);
static bool is_tail(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static int incr_x(char c);
static int incr_y(char c);
static void find_head(game_state_t *state, int snum);
static char next_square(game_state_t *state, int snum);
static void update_tail(game_state_t *state, int snum);
static void update_head(game_state_t *state, int snum);

/* Helper function to get a character from the board (already implemented for you). */
static char get_board_at(game_state_t *state, int x, int y)
{
  return state->board[y][x];
}

/* Helper function to set a character on the board (already implemented for you). */
static void set_board_at(game_state_t *state, int x, int y, char ch)
{
  state->board[y][x] = ch;
}

/* Task 1 */
game_state_t *create_default_state()
{
  game_state_t *state = malloc(sizeof(game_state_t));
  if (state == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  state->x_size = 14;
  state->y_size = 10;
  state->board = malloc(sizeof(char *) * state->y_size);
  if (state->board == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  for (int i = 0; i < state->y_size; i++)
  {
    state->board[i] = malloc(sizeof(char) * state->x_size);
    if (state->board[i] == NULL)
    {
      fprintf(stderr, "Out of memory.\n");
      exit(1);
    }
  }
  for (int i = 0; i < state->y_size; i++)
  {
    for (int j = 0; j < state->x_size; j++)
    {
      state->board[i][j] = ' ';
    }
  }
  set_board_at(state, 9, 2, '*');
  set_board_at(state, 4, 4, 'd');
  set_board_at(state, 5, 4, '>');
  for (int i = 0; i < state->y_size; i++)
  {
    if (i == 0 || i == state->y_size - 1)
    {
      for (int j = 0; j < state->x_size; j++)
      {
        set_board_at(state, j, i, '#');
      }
    }
    else
    {
      set_board_at(state, 0, i, '#');
      set_board_at(state, state->x_size - 1, i, '#');
    }
  }
  state->num_snakes = 1;
  state->snakes = malloc(sizeof(snake_t) * state->num_snakes);
  if (state->snakes == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  state->snakes[0].tail_x = 4;
  state->snakes[0].tail_y = 4;
  state->snakes[0].head_x = 5;
  state->snakes[0].head_y = 4;
  state->snakes[0].live = true;
  return state;
}

/* Task 2 */
void free_state(game_state_t *state)
{
  // TODO: Implement this function.
  free(state->snakes);
  for (int i = 0; i < state->y_size; i++)
  {
    free(state->board[i]);
  }
  free(state->board);
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp)
{
  // TODO: Implement this function.
  for (int i = 0; i < state->y_size; i++)
  {
    for (int j = 0; j < state->x_size; j++)
    {
      fprintf(fp, "%c", state->board[i][j]);
    }
    fprintf(fp, "\n");
  }
  return;
}

/* Saves the current state into filename (already implemented for you). */
void save_board(game_state_t *state, char *filename)
{
  FILE *f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */
static bool is_tail(char c)
{
  // TODO: Implement this function.
  if (c != 'w' && c != 'a' && c != 's' && c != 'd')
  {
    return false;
  }
  return true;
}

static bool is_snake(char c)
{
  // TODO: Implement this function.
  if (c != '^' && c != '<' && c != 'v' && c != '>' &&
      c != 'w' && c != 'a' && c != 's' && c != 'd')
  {
    return false;
  }
  return true;
}

static char body_to_tail(char c)
{
  // TODO: Implement this function.
  switch (c)
  {
  case '^':
    return 'w';
  case '<':
    return 'a';
  case 'v':
    return 's';
  case '>':
    return 'd';
  default:
    return '?';
  }
}

static int incr_x(char c)
{
  // TODO: Implement this function.
  if (c == '>' || c == 'd')
  {
    return 1;
  }
  if (c == '<' || c == 'a')
  {
    return -1;
  }
  return 0;
}

static int incr_y(char c)
{
  // TODO: Implement this function.
  if (c == 'v' || c == 's')
  {
    return 1;
  }
  if (c == '^' || c == 'w')
  {
    return -1;
  }
  return 0;
}

/* Task 4.2 */
static char next_square(game_state_t *state, int snum)
{
  // TODO: Implement this function.
  char **board = state->board;
  int head_x = state->snakes[snum].head_x;
  int head_y = state->snakes[snum].head_y;
  char direction = board[head_y][head_x];
  int new_head_x = head_x + incr_x(direction);
  int new_head_y = head_y + incr_y(direction);
  return board[new_head_y][new_head_x];
}

/* Task 4.3 */
static void update_head(game_state_t *state, int snum)
{
  // TODO: Implement this function.
  char **board = state->board;
  int head_x = state->snakes[snum].head_x;
  int head_y = state->snakes[snum].head_y;
  char direction = board[head_y][head_x];
  int new_head_x = head_x + incr_x(direction);
  int new_head_y = head_y + incr_y(direction);
  board[new_head_y][new_head_x] = board[head_y][head_x];
  state->snakes[snum].head_x = new_head_x;
  state->snakes[snum].head_y = new_head_y;
  return;
}

/* Task 4.4 */
static void update_tail(game_state_t *state, int snum)
{
  // TODO: Implement this function.
  char **board = state->board;
  int tail_x = state->snakes[snum].tail_x;
  int tail_y = state->snakes[snum].tail_y;
  char direction = board[tail_y][tail_x];
  int new_tail_x = tail_x + incr_x(direction);
  int new_tail_y = tail_y + incr_y(direction);
  board[tail_y][tail_x] = ' ';
  board[new_tail_y][new_tail_x] = body_to_tail(board[new_tail_y][new_tail_x]);
  state->snakes[snum].tail_x = new_tail_x;
  state->snakes[snum].tail_y = new_tail_y;
  return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state))
{
  // TODO: Implement this function.
  for (int i = 0; i < state->num_snakes; i++)
  {
    if (state->snakes[i].live)
    {
      char next = next_square(state, i);
      if (next == ' ')
      {
        update_head(state, i);
        update_tail(state, i);
      }
      else if (next == '*')
      {
        add_food(state);
        update_head(state, i);
      }
      else if (is_snake(next) || next == '#')
      {
        state->snakes[i].live = false;
        state->board[state->snakes[i].head_y][state->snakes[i].head_x] = 'x';
      }
      for (int j = 0; j < state->num_snakes; j++)
      {
        if (j == i)
        {
          continue;
        }
        if (state->snakes[j].head_x == state->snakes[i].head_x &&
            state->snakes[j].head_y == state->snakes[i].head_y)
        {
          state->snakes[j].live = false;
        }
      }
    }
  }
  return;
}

/* Task 5 */
game_state_t *load_board(char *filename)
{
  // TODO: Implement this function.
  game_state_t *state = malloc(sizeof(game_state_t));
  if (state == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  FILE *f = fopen(filename, "r");
  if (f == NULL)
  {
    fprintf(stderr, "File not found.\n");
    exit(1);
  }
  char c;
  int y_size = 0;
  int x_size = 0;
  // 计算行数和列数
  while ((c = fgetc(f)) != '\n')
  {
    x_size++;
  }
  y_size++; // 加上第一行
  while ((c = fgetc(f)) != EOF)
  {
    if (c == '\n')
    {
      y_size++;
    }
  }
  state->x_size = x_size;
  state->y_size = y_size;
  // 动态分配内存
  state->board = malloc(y_size * sizeof(char *));
  if (state->board == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  for (int i = 0; i < y_size; i++)
  {
    state->board[i] = malloc(x_size * sizeof(char));
    if (state->board[i] == NULL)
    {
      fprintf(stderr, "Out of memory.\n");
      exit(1);
    }
  }
  // 重新读取文件并填充board
  rewind(f);
  for (int i = 0; i < y_size; i++)
  {
    for (int j = 0; j < x_size; j++)
    {
      c = fgetc(f);
      if (c == '\n')
      {
        c = fgetc(f);
      }
      if (c != EOF)
      {
        state->board[i][j] = c;
      }
    }
  }
  fclose(f);
  return state;
}

/* Task 6.1 */
static void find_head(game_state_t *state, int snum)
{
  // TODO: Implement this function.
  int num = 0;
  char **board = state->board;
  for (int i = 0; i < state->y_size; i++)
  {
    for (int j = 0; j < state->x_size; j++)
    {
      if (board[i][j] == 'w' || board[i][j] == 'a' ||
          board[i][j] == 's' || board[i][j] == 'd')
      {
        num++;
        if (num == snum + 1)
        {
          state->snakes[snum].tail_x = j;
          state->snakes[snum].tail_y = i;
          while (1)
          {
            int new_j = j + incr_x(board[i][j]);
            int new_i = i + incr_y(board[i][j]);
            if (!is_snake(board[new_i][new_j]))
            {
              state->snakes[snum].head_x = j;
              state->snakes[snum].head_y = i;
              return;
            }
            i = new_i;
            j = new_j;
          }
        }
      }
    }
  }
  return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state)
{
  // TODO: Implement this function.
  state->snakes = 0;
  for (int i = 0; i < state->y_size; i++)
  {
    for (int j = 0; j < state->x_size; j++)
    {
      if (state->board[i][j] == 'w' || state->board[i][j] == 'a' ||
          state->board[i][j] == 's' || state->board[i][j] == 'd')
      {

        state->num_snakes++;
      }
    }
  }
  state->snakes = malloc(state->num_snakes * sizeof(snake_t));
  if (state->snakes == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  for (int i = 0; i < state->num_snakes; i++)
  {
    find_head(state, i);
    state->snakes[i].live = true;
  }
  return state;
}
