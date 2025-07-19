#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h> 

#define N 16
#define M 16
#define SIZE 16
#define BOMB -1
#define FLAG 30  

#include "sapper.h"

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    int game_field[N][M];
    int user_field[N][M];

    init_user_field(user_field, game_field, SIZE);
    init_game_field(game_field, SIZE);

    int y = 0, x = 0;
    int flag = 0;

    start_game(game_field, user_field, &y, &x, &flag);

    return 0;
}
