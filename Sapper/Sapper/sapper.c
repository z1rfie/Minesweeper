#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h> 
#include "sapper.h"

#define N 16
#define M 16
#define SIZE 16
#define BOMB -1
#define EMPTY ' '     
#define FLAG 30 

#define COLOR_RESET "\033[0m"
#define COLOR_BLUE "\033[34m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_PINK "\033[35m"
#define COLOR_CYAN "\033[36m"


// поле игрока
void init_user_field(int user_field[N][M], int game_field[N][M], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            user_field[i][j] = EMPTY;
        }
    }
}

void print_user_field(int user_field[N][M], int size) {
    for (int i = 0; i < N; i++) {
        printf("----");
    }
    printf("-\n");
    for (int i = 0; i < size; i++) {
        printf("| ");
        for (int j = 0; j < size; j++) {
            if (user_field[i][j] == EMPTY) {
                printf("  | ");
            }
            else if (user_field[i][j] == BOMB) {
                printf("* | "); 
            }
            else if (user_field[i][j] == 9) {
                printf("^ | ");
            }
            else if (user_field[i][j] == FLAG) {
                printf("F | ");
            }
            else {
                switch (user_field[i][j]) {
                case 1:
                    printf(COLOR_CYAN "%d" COLOR_RESET " | ", user_field[i][j]);
                    break;
                case 2:
                    printf(COLOR_GREEN "%d" COLOR_RESET " | ", user_field[i][j]);
                    break;
                case 3:
                    printf(COLOR_RED "%d" COLOR_RESET " | ", user_field[i][j]);
                    break;
                case 4:
                    printf(COLOR_BLUE "%d" COLOR_RESET " | ", user_field[i][j]);
                    break;
                case 5:
                    printf(COLOR_PINK "%d" COLOR_RESET " | ", user_field[i][j]);
                    break;
                default:
                    printf("%d | ", user_field[i][j]);
                    break;
                }
            }
        }
        printf("\n");
        for (int j = 0; j < M; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

// игровое поле
void init_game_field(int game_field[N][M], int size) {
    int bomb_placed = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bomb_placed += 1;
            if (bomb_placed <= 40) {
                game_field[i][j] = -1;
            }
        }
    }
    swap(game_field, SIZE);
    calculate_neightbours_bombs(game_field);
}

void print_game_field(int user_field[N][M], int game_field[N][M], int size) {
    for (int i = 0; i < N; i++) {
        printf("----");
    }
    printf("-\n");
    for (int i = 0; i < size; i++) {
        printf("| ");
        for (int j = 0; j < size; j++) {
            printf("%d  |", user_field[i][j]);
        }
        printf("\n");
        for (int j = 0; j < M; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

// рандомно расставляем бомбы
int rand_generation(int min, int max) {
    return min + rand() % (max - min + 1);
}

int swap(int game_field[N][M], int size) {
    int rand_i, rand_j;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            rand_i = rand_generation(0, size - 1);
            rand_j = rand_generation(0, size - 1);

            int tmp = game_field[i][j];
            game_field[i][j] = game_field[rand_i][rand_j];
            game_field[rand_i][rand_j] = tmp;
        }
    }
    return 1;
}

// высчитываем соседние с бомбой клетки
int calculate_neightbours_bombs(int game_field[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int bombs_count = 0;

            if (game_field[i][j] == BOMB) {
                continue;
            }
            if (i > 0 && game_field[i - 1][j] == BOMB) bombs_count++; // Вверх
            if (i > 0 && j < M - 1 && game_field[i - 1][j + 1] == BOMB) bombs_count++; // Вверх и вправо
            if (j < M - 1 && game_field[i][j + 1] == BOMB) bombs_count++; // Вправо
            if (i < N - 1 && j < M - 1 && game_field[i + 1][j + 1] == BOMB) bombs_count++; // Вниз и вправо
            if (i < N - 1 && game_field[i + 1][j] == BOMB) bombs_count++; // Вниз
            if (i < N - 1 && j > 0 && game_field[i + 1][j - 1] == BOMB) bombs_count++; // Вниз и влево
            if (j > 0 && game_field[i][j - 1] == BOMB) bombs_count++; // Влево
            if (i > 0 && j > 0 && game_field[i - 1][j - 1] == BOMB) bombs_count++; // Вверх и влево

            game_field[i][j] = bombs_count;
        }
    }
    return 1;
}


// открытие ячейки
int opening_cell(int x, int y, int game_field[N][M], int user_field[N][M], int* open_cells) {
    if (user_field[y][x] == ' ') {
        if (game_field[y][x] == BOMB) {
            system("cls");
            printf("Вы проиграли! \n"); 
            return 1;
        }  
        if (game_field[y][x] == 0) {
            user_field[y][x] = game_field[y][x];   
            if (x - 1 >= 0 && y - 1 >= 0 && (user_field[y - 1][x - 1] == ' ' || user_field[y - 1][x - 1] == 30)) {
                opening_cell(x - 1, y - 1, game_field, user_field, open_cells);
            }   
            if (x - 1 >= 0 && (user_field[y][x - 1] == ' ' || user_field[y][x - 1] == 30)) {
                opening_cell(x - 1, y, game_field, user_field, open_cells);
            }
            if (x - 1 >= 0 && y + 1 < SIZE && (user_field[y + 1][x - 1] == ' ' || user_field[y + 1][x - 1] == 30)) {
                opening_cell(x - 1, y + 1, game_field, user_field, open_cells);
            }
            if (y + 1 < SIZE && (user_field[y + 1][x] == ' ' || user_field[y + 1][x] == 30)) {    
                opening_cell(x, y + 1, game_field, user_field, open_cells);
            }
            if (x + 1 < SIZE && y + 1 < SIZE && (user_field[y + 1][x + 1] == ' ' || user_field[y + 1][x + 1] == 30)) {    
                opening_cell(x + 1, y + 1, game_field, user_field, open_cells);
            }
            if (x + 1 < SIZE && (user_field[y][x + 1] == ' ' || user_field[y][x + 1] == 30)) {    
                opening_cell(x + 1, y, game_field, user_field, open_cells);
            }
            if (x + 1 < SIZE && y - 1 >= 0 && (user_field[y - 1][x + 1] == ' ' || user_field[y - 1][x + 1] == 30)) {    
                opening_cell(x + 1, y - 1, game_field, user_field, open_cells);
            }
            if (y - 1 >= 0 && (user_field[y - 1][x] == ' ' || user_field[y - 1][x] == 30)) {  
                opening_cell(x, y - 1, game_field, user_field, open_cells);
            }
        }
        else {   
            user_field[y][x] = game_field[y][x];
        }
        (*open_cells) += 1;
    }
    return 0;
}

// процесс игры на клавишах
int moving_field(int game_field[N][M], int user_field[N][M], int* y, int* x, int* open_cells, int* flag) {
    char key = 2;
    *y = 0;
    *x = 0;
    while (key != '\r') {
        int tmp = user_field[*y][*x];
        user_field[*y][*x] = 9;
        print_user_field(user_field, SIZE);
        printf("Нажмите <ESC> для выхода\n");
        printf("Нажмите <w, a, s, d> для перемещения\n");
        printf("Нажмите <ENTER> чтобы открыть ячейку\n");\
        printf("Нажмите <F> для установки флага\n");
        printf("\n");
        printf("Количество ваших флажков: %d \n", *flag);
        user_field[*y][*x] = tmp;
        key = _getch();
        system("cls");
        switch (key) {
        case 27: // ESC для выхода
            return 0;
        case 'w':
            if (*y > 0) (*y)--;
            break;
        case 's':
            if (*y < N - 1) (*y)++;
            break;
        case 'a':
            if (*x > 0) (*x)--;
            break;
        case 'd':
            if (*x < M - 1) (*x)++;
            break;
        case 'f': 
            if (user_field[*y][*x] == EMPTY) {
                user_field[*y][*x] = FLAG; 
                (*flag)++;
            }
            else if (user_field[*y][*x] == FLAG) {
                user_field[*y][*x] = EMPTY; 
                (*flag)--;
            }
            break;
        }
    }
    return key;
}

int check_flags(int game_field[N][M], int user_field[N][M]) {
    int correct_flags = 0;
    int total_flags = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (user_field[i][j] == FLAG) {
                total_flags++;
                if (game_field[i][j] == BOMB) {
                    correct_flags++;
                }
            }
        }
    }
    return correct_flags == total_flags;
}


void start_game(int game_field[N][M], int user_field[N][M], int* y, int* x, int* flag) {
    system("cls");
    int open_cells = 0;

    while (1) {
        char key = moving_field(game_field, user_field, &y, &x, &open_cells, flag);
        if (key == 0) {
            printf("Вы вышли из игры.\n");
            return; // Выход из функции
        }
        if (key == '\r') {
            opening_cell(x, y, game_field, user_field, &open_cells);
            if (opening_cell(x, y, game_field, user_field, &open_cells)) {
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        if (game_field[i][j] == BOMB) {
                            user_field[i][j] = -1;
                        }
                    }
                }
                print_user_field(user_field, SIZE);
                break;
            }
        }
        //print_user_field(user_field, SIZE);
        if (open_cells >= (N * M - 40)) {
            if (check_flags(game_field, user_field)) {
                print_user_field(user_field, SIZE);
                printf("Вы выиграли! \n");
                return;
            }
            else {
                print_user_field(user_field, SIZE);
                printf("Вы проиграли, у вас неправильные флаги!\n");
                return;
            }
        }
    }
}