#include <windows.h>
#include <iostream>
#include <conio.h>

using namespace std;

#define WORLD_WIDTH 50
#define WORLD_HEIGHT 50

unsigned char worldOne[WORLD_HEIGHT * WORLD_WIDTH] = {};
unsigned char worldTwo[WORLD_HEIGHT * WORLD_WIDTH] = {};
unsigned char* visibleWorld = worldOne;
unsigned char* simWorld = worldTwo;
HANDLE handle = 0;

int GetIndex(int x, int y)
{
	x = (x + WORLD_WIDTH) % WORLD_WIDTH;
	y = (y + WORLD_HEIGHT) % WORLD_HEIGHT;
	return x + (y * WORLD_WIDTH);
}

bool Get(unsigned char* world, int x, int y)
{
	int index = GetIndex(x, y);
	return world[index] == 219;
}

void Set(unsigned char* world, int x, int y, bool alive)
{
	int index = GetIndex(x, y);

	if (alive)
	{
		world[index] = 219;
	}
	else
	{
		world[index] = ' ';
	}
}

void Init(unsigned char* world)
{
	for (int i = 0; i < WORLD_HEIGHT * WORLD_WIDTH; ++i)
	{
		world[i] = ' ';
	}

	// block
	Set(world, 1, 5, true);
	Set(world, 1, 6, true);
	Set(world, 2, 5, true);
	Set(world, 2, 6, true);

	Set(world, 35, 3, true);
	Set(world, 35, 4, true);
	Set(world, 36, 3, true);
	Set(world, 36, 4, true);

	// Glider Gun
	Set(world, 11, 5, true);
	Set(world, 11, 6, true);
	Set(world, 11, 7, true);

	Set(world, 12, 4, true);
	Set(world, 12, 8, true);

	Set(world, 13, 3, true);
	Set(world, 13, 9, true);

	Set(world, 14, 3, true);
	Set(world, 14, 9, true);

	Set(world, 15, 6, true);

	Set(world, 16, 4, true);
	Set(world, 16, 8, true);

	Set(world, 17, 5, true);
	Set(world, 17, 6, true);
	Set(world, 17, 7, true);

	Set(world, 18, 6, true);

	Set(world, 20, 3, true);
	Set(world, 20, 4, true);
	Set(world, 20, 5, true);

	Set(world, 21, 3, true);
	Set(world, 21, 4, true);
	Set(world, 21, 5, true);

	Set(world, 22, 2, true);
	Set(world, 22, 6, true);

	Set(world, 24, 1, true);
	Set(world, 24, 2, true);
	Set(world, 24, 6, true);
	Set(world, 24, 7, true);
}

void MoveCursor(int x, int y)
{
	COORD cursor_position;
	cursor_position.X = x;
	cursor_position.Y = y;
	SetConsoleCursorPosition(handle, cursor_position);
}

void printWorld()
{
	MoveCursor(0, 0);
	unsigned char* currentCell = visibleWorld;
	for (int y = 0; y < WORLD_HEIGHT; ++y)
	{
		for (int x = 0; x < WORLD_WIDTH; ++x)
		{
			cout << *currentCell;
			++currentCell;
		}

		cout << '\n';
	}
}

void Sim()
{
	for (int y = 0; y < WORLD_HEIGHT; ++y)
	{
		for (int x = 0; x < WORLD_WIDTH; ++x)
		{
			int liveNeighboors = 0;
			bool alive = Get(simWorld, x, y);

			for (int nx = x - 1; nx <= x + 1; ++nx)
			{
				for (int ny = y - 1; ny <= y + 1; ++ny)
				{
					if (!(x == nx && y == ny)
						&& Get(simWorld, nx, ny))
					{
						++liveNeighboors;
					}
				}
			}

			Set(visibleWorld, x, y, alive);

			if (alive)
			{
				if (liveNeighboors == 1 || liveNeighboors > 3)
				{
					Set(visibleWorld, x, y, false);
				}
			}
			else if (liveNeighboors == 3)
			{
				Set(visibleWorld, x, y, true);
			}
		}
	}

	unsigned char* swap = visibleWorld;
	visibleWorld = simWorld;
	simWorld = swap;
}

int main()
{
	const int APPSPEED = 30;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT screen_area = { 0, 0, WORLD_WIDTH , WORLD_HEIGHT };
	COORD new_size = { WORLD_WIDTH + 1, WORLD_HEIGHT + 1 };
	CONSOLE_CURSOR_INFO console_info;
	console_info.dwSize = 10;
	console_info.bVisible = false;

	//alters console window to fit perfectly
	//and hides the cursor
	SetConsoleCursorInfo(handle, &console_info);
	SetConsoleTitleA("Conway's Game of Life");
	SetConsoleWindowInfo(handle, true, &screen_area);
	SetConsoleScreenBufferSize(handle, new_size);

	Init(visibleWorld);
	Init(simWorld);

	bool isRunning = true;
	while (isRunning)
	{
		if (_kbhit())
		{
			char input = (char)_getch();
			if (input == 'q')
			{
				isRunning = false;
			}
		}

		Sim();
		printWorld();
		// Sleep(1000 / APPSPEED);
	}
}