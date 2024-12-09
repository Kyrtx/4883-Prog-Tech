#include <locale.h>
#include <ncurses.h>
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

class Player {
    string name;
    int score;

public:
    Player(string n) : name(n), score(0) {}
    void addScore(int s) { score += s; }
    int getScore() const { return score; }
    string getName() const { return name; }
};

class Grid {
    int values[3][3]; // 3x3 grid
    int base_y, base_x;
    WINDOW *win;

public:
    Grid(int y, int x) : base_y(y), base_x(x) {
        for (auto &row : values)
            fill(row, row + 3, 0); // Initialize with 0
        win = newwin(7, 13, y, x); // 7 rows x 13 columns for grid
        refreshGrid();
    }

    void refreshGrid() {
        wclear(win);
        box(win, 0, 0); // Draw border
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int y = i * 2 + 1, x = j * 4 + 2; // Calculate cell center
                if (values[i][j] > 0)
                    mvwprintw(win, y, x, "%d", values[i][j]); // Display values
            }
        }
        wrefresh(win);
    }

    bool addValue(int col, int value) {
        for (int row = 2; row >= 0; --row) {
            if (values[row][col] == 0) {
                values[row][col] = value;
                refreshGrid();
                return true;
            }
        }
        return false; // Column full
    }

    int calculateColumnScore(int col) const {
        int product = 1, count = 0;
        for (int row = 0; row < 3; ++row) {
            if (values[row][col] > 0) {
                product *= values[row][col];
                count++;
            }
        }
        return count > 0 ? product : 0;
    }

    int calculateScore() const {
        int total = 0;
        for (int col = 0; col < 3; ++col)
            total += calculateColumnScore(col);
        return total;
    }

    bool isFull() const {
        for (int col = 0; col < 3; ++col)
            for (int row = 0; row < 3; ++row)
                if (values[row][col] == 0)
                    return false;
        return true;
    }
};

class Game {
    Player player1, player2;
    Grid grid1, grid2;
    int turn;
    bool running;

public:
    Game() : player1("Player 1"), player2("Player 2"), grid1(2, 5), grid2(2, 30), turn(0), running(true) {}

    void play() {
        while (running) {
            render();
            handleInput();
            checkGameOver();
        }
        endGame();
    }

    void render() {
        clear();
        mvprintw(0, 5, "%s's Turn", turn % 2 == 0 ? player1.getName().c_str() : player2.getName().c_str());
        mvprintw(1, 5, "Press 'r' to roll the dice. Press 'q' to quit.");
        mvprintw(12, 5, "Player 1 Score: %d", grid1.calculateScore());
        mvprintw(13, 5, "Player 2 Score: %d", grid2.calculateScore());
        grid1.refreshGrid();
        grid2.refreshGrid();
        refresh();
    }

    void handleInput() {
        char ch = getch();
        if (ch == 'q') {
            running = false;
            return;
        }
        if (ch == 'r') {
            int dice = rollDice();
            Player &currentPlayer = turn % 2 == 0 ? player1 : player2;
            Grid &currentGrid = turn % 2 == 0 ? grid1 : grid2;

            mvprintw(15, 5, "You rolled: %d", dice);
            refresh();

            int col;
            while (true) {
                mvprintw(16, 5, "Choose a column (0-2): ");
                refresh();
                col = getch() - '0';
                if (col >= 0 && col < 3 && currentGrid.addValue(col, dice))
                    break;
                mvprintw(17, 5, "Invalid column. Try again.");
                refresh();
            }
            turn++;
        }
    }

    int rollDice() {
        return rand() % 6 + 1; // Roll a dice (1-6)
    }

    void checkGameOver() {
        if (grid1.isFull() && grid2.isFull())
            running = false;
    }

    void endGame() {
        int score1 = grid1.calculateScore();
        int score2 = grid2.calculateScore();
        clear();
        mvprintw(5, 10, "Game Over!");
        mvprintw(6, 10, "Player 1 Score: %d", score1);
        mvprintw(7, 10, "Player 2 Score: %d", score2);
        if (score1 > score2)
            mvprintw(8, 10, "Player 1 Wins!");
        else if (score2 > score1)
            mvprintw(8, 10, "Player 2 Wins!");
        else
            mvprintw(8, 10, "It's a Draw!");
        refresh();
        getch();
    }
};

int main() {
    srand(time(0));
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    Game game;
    game.play();

    endwin();
    return 0;
}
