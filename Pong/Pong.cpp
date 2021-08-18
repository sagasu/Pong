// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

enum Dir {Stop = 0, Left = 1, UpLeft = 2, DownLeft = 3, Right = 4, UpRight = 5, DownRight=6};

class Ball {
private:
    int x, y;
    int originalX, originalY;
    Dir direction;

public:
    Ball(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = Stop;
    }

    void Reset() {
        x = originalX;
        y = originalY;
        direction = Stop;
    }

    void ChangeDirection(Dir dir) {
        direction = dir;
    }

    void RandomDirection(){
        direction = (Dir)(rand() % 6 + 1);
    }

    void Move() {
        switch (direction) {
        case Stop:
            break;
        case Left:
            x--;
            break;
        case Right:
            x++;
            break;
        case UpLeft:
            x--;
            y--;
        case DownLeft:
            x--;
            y++;
            break;
        case UpRight:
            x++;
            y--;
            break;
        case DownRight:
            x++;
            y++;
            break;
        default:
            break;
        }
    }

    inline int getX() { return x; }
    inline int getY() { return y; }
    inline Dir getDirection() { return direction; }

    friend ostream& operator<<(ostream& stream, Ball ball) {
        stream << "Ball [" << ball.x << "," << ball.y << "][" << ball.direction << "]" << endl;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
