#include <bits/stdc++.h>
#define MAX 4
using namespace std;

struct FISH {
  int y;
  int x;
  int dir;
  bool live;
};

int answer = 0;
int board[MAX][MAX];
FISH fishes[MAX * MAX + 1];

int dy[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dx[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

bool isvalid(int newy, int newx) {
  return 0 <= newy && newy < MAX && 0 <= newx && newx < MAX;
}

void swap_fish(int idx_a, int idx_b) {
  FISH temp = fishes[idx_a];
  fishes[idx_a].y = fishes[idx_b].y;
  fishes[idx_a].x = fishes[idx_b].x;
  fishes[idx_b].y = temp.y;
  fishes[idx_b].x = temp.x;
}

void move_fish() {
  for (int i = 1; i <= MAX * MAX; i++) {
    if (fishes[i].live == false) {
      continue;
    }

    int y = fishes[i].y;
    int x = fishes[i].x;
    int dir = fishes[i].dir;

    int newy = y + dy[dir];
    int newx = x + dx[dir];
    bool flag = false;
    if (isvalid(newy, newx)) {
      if (board[newy][newx] == 0) {
        flag = true;
        fishes[i].y = newy;
        fishes[i].x = newx;
        board[newy][newx] = i;
        board[y][x] = 0;
      } else if (board[newy][newx] != -1) {
        flag = true;
        swap_fish(i, board[newy][newx]);
        swap(board[y][x], board[newy][newx]);
      }
    }
    if (!flag) {
      int newdir = dir + 1;
      if (newdir == 9) {
        newdir = 1;
      }
      int newy = y + dy[newdir];
      int newx = x + dx[newdir];

      while (newdir != dir) {
        if (isvalid(newy, newx)) {
          if (board[newy][newx] == 0) {
            fishes[i].y = newy;
            fishes[i].x = newx;
            board[newy][newx] = i;
            board[y][x] = 0;
            fishes[i].dir = newdir;
            break;
          } else if (board[newy][newx] != -1) {
            swap_fish(i, board[newy][newx]);
            swap(board[y][x], board[newy][newx]);
            fishes[i].dir = newdir;
            break;
          }
        }
        newdir++;
        if (newdir == 9) {
          newdir = 1;
        }
        newy = y + dy[newdir];
        newx = x + dx[newdir];
      }
    }
  }
}

void make_state(int y, int x, int newy, int newx, int fish_num, bool flag) {
  if (flag) {
    board[y][x] = 0;
    board[newy][newx] = -1;
    fishes[fish_num].live = false;
  } else {
    board[y][x] = -1;
    board[newy][newx] = fish_num;
    fishes[fish_num].live = true;
  }
}

void dfs(int y, int x, int dir, int sum) {
  answer = max(answer, sum);

  int copied_board[MAX][MAX];
  FISH copied_fishes[MAX * MAX + 1];
  memcpy(copied_board, board, sizeof(board));
  memcpy(copied_fishes, fishes, sizeof(fishes));
  move_fish();

  for (int i = 1; i < MAX; i++) {
    int newy = y + dy[dir] * i;
    int newx = x + dx[dir] * i;
    if (isvalid(newy, newx)) {
      if (board[newy][newx] == 0) {
        continue;
      }

      int fish_num = board[newy][newx];
      int newdir = fishes[fish_num].dir;

      make_state(y, x, newy, newx, fish_num, true);
      dfs(newy, newx, newdir, sum + fish_num);
      make_state(y, x, newy, newx, fish_num, false);
    } else {
      break;
    }
  }
  memcpy(board, copied_board, sizeof(copied_board));
  memcpy(fishes, copied_fishes, sizeof(copied_fishes));
}

int main() {
  int a, b;
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      scanf("%d %d", &a, &b);
      board[i][j] = a;
      fishes[a] = {i, j, b, true};
    }
  }

  int fish_num = board[0][0];
  int dir = fishes[fish_num].dir;
  fishes[fish_num].live = false;
  board[0][0] = -1;
  dfs(0, 0, dir, fish_num);
  printf("%d\n", answer);
  return 0;
}