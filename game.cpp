#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    const int n = 20, m = 40;
    int score = 0;
    bool gameOver = false;

    srand(time(0));

    vector<pair<int, int>> snake = {{10, 5}, {10, 4}, {10, 3}};
    char direction = 'R';

    vector<vector<char>> grid(n, vector<char>(m, '.'));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
                grid[i][j] = '+';
        }
    }

    pair<int, int> food = {rand() % (n - 2) + 1, rand() % (m - 2) + 1};

    cout << "Welcome to Snake Game!" << endl;
    cout << "Press any key to start..." << endl;
    _getch();

    while (!gameOver) {
        system("cls");

        for (int i = 1; i < n - 1; i++) {
            for (int j = 1; j < m - 1; j++) {
                grid[i][j] = '.';
            }
        }

        grid[food.first][food.second] = '*';

        for (int i = snake.size() - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'q' || ch == 'Q') break;
            if ((int)ch == 72 && direction != 'D') direction = 'U';
            else if ((int)ch == 80 && direction != 'U') direction = 'D';
            else if ((int)ch == 75 && direction != 'R') direction = 'L';
            else if ((int)ch == 77 && direction != 'L') direction = 'R';
        }

        if (direction == 'U') snake[0].first--;
        else if (direction == 'D') snake[0].first++;
        else if (direction == 'L') snake[0].second--;
        else if (direction == 'R') snake[0].second++;

        int hx = snake[0].first;
        int hy = snake[0].second;

        if (hx == 0 || hx == n - 1 || hy == 0 || hy == m - 1) {
            gameOver = true;
            break;
        }

        for (int i = 1; i < snake.size(); i++) {
            if (snake[i].first == hx && snake[i].second == hy) {
                gameOver = true;
                break;
            }
        }

        if (hx == food.first && hy == food.second) {
            score += 10;
            snake.push_back(snake.back());
            while (true) {
                int fx = rand() % (n - 2) + 1;
                int fy = rand() % (m - 2) + 1;
                bool onSnake = false;

                for (auto &part : snake) {
                    if (part.first == fx && part.second == fy) {
                        onSnake = true;
                        break;
                    }
                }

                if (!onSnake) {
                    food = {fx, fy};
                    break;
                }
            }
        }

        for (auto &part : snake) {
            grid[part.first][part.second] = '#';
        }

        for (auto &row : grid) {
            for (char c : row) cout << c;
            cout << endl;
        }

        cout << "Score: " << score << endl;
        cout << "Press 'q' to quit" << endl;

        Sleep(100);
    }

    cout << "\nGame Over!" << endl;
    cout << "Your final score: " << score << endl;
    return 0;
}
