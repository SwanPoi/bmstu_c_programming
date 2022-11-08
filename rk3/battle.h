#ifndef __BATTLE_H

#define __BATTLE_H

int is_killed(int **matrix, int rows, int columns, int x, int y);
int is_clean(int **matrix, int rows, int columns);
void get_coordinates(int *row, int *column);
void battle(int **matrix, int rows, int columns);

#endif // __BATTLE_H
