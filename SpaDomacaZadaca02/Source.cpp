#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;

const int CELL_SIZE = 10;
const int ROWS = 60;
const int COLS = 80;
const int WINDOW_WIDTH = COLS * CELL_SIZE;
const int WINDOW_HEIGHT = ROWS * CELL_SIZE;
const int FPS = 60;

int getNeighborCount(bool grid[ROWS][COLS], int row, int col)
{
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = row + i;
            int c = col + j;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS && !(i == 0 && j == 0)) {
                count += grid[r][c];
            }
        }
    }
    return count;
}

void update(bool grid[ROWS][COLS])
{
    bool new_grid[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int count = getNeighborCount(grid, i, j);
            if (grid[i][j] && (count < 2 || count > 3)) {
                new_grid[i][j] = false;
            }
            else if (!grid[i][j] && count == 3) {
                new_grid[i][j] = true;
            }
            else {
                new_grid[i][j] = grid[i][j];
            }
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}

void render(sf::RenderWindow& window, bool grid[ROWS][COLS])
{
    window.clear(sf::Color::Black);
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cell.setFillColor(sf::Color::Magenta);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j]) {
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                window.draw(cell);
            }
        }
    }
    window.display();
}


void initialize(bool grid[ROWS][COLS])
{
    srand(time(nullptr));
   
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}


int main()
{
    bool grid[ROWS][COLS];
    initialize(grid);


	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game of life");
	window.setFramerateLimit(FPS);
    sf::Clock clock;

	while (window.isOpen())
	{
        sf::Time elapsed = clock.restart();
        double dt = elapsed.asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

        update(grid);

        render(window, grid);

        sf::sleep(sf::seconds(1.0 / FPS - dt));

	}

	return 0;
}