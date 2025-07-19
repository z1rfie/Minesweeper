#pragma once
#define N 16
#define M 16

// поле
void init_user_field(int user_field[N][M], int game_field[N][M], int size);
void print_user_field(int user_field[N][M], int size);

// игровое поле
void init_game_field(int game_field[N][M], int size);
void print_game_field(int user_field[N][M], int game_field[N][M], int size);

// рандомно расставляем бомбы
int rand_generation(int first_number, int second_number);
int swap(int game_field[N][M], int size);

// высчитываем соседние с бомбой клетки
int calculate_neightbours_bombs(int game_field[N][M]);

// открытие ячеек
int opening_cell(int x, int y, int game_field[N][M], int user_field[N][M], int* open_cells);
int moving_field(int game_field[N][M], int user_field[N][M], int* y, int* x, int* open_cells, int* flag);

// начало игры
void start_game(int game_field[N][M], int user_field[N][M], int* y, int* x, int* flag);
