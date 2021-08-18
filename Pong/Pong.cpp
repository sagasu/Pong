// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <conio.h>

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
        return stream;
    }
};

class Paddle {
private:
    int x, y;
    int originalX, originalY;
public:
    Paddle() {
        x = y = 0;
    }
    Paddle(int posX, int posY) : Paddle() {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    inline void Reset() {
        x = originalX;
        y = originalY;
    }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }

    friend ostream& operator<<(ostream& stream, Paddle paddle) {
        stream << "Paddle [" << paddle.x << "," << paddle.y << "]" << endl;
        return stream;
    }
};

class Game {
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    Ball* ball;
    Paddle* player1;
    Paddle* player2;
public:
    Game(int w, int h) {
        srand(time(NULL));
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new Ball(w / 2, h / 2);
        player1 = new Paddle(1, h/2 - 3);
        player2 = new Paddle(w-2, h/2 - 3);
    }
    ~Game() {
        delete ball, player1, player2;
    }
    void ScoreUp(Paddle* player) {
        if (player == player1) score1++;
        if (player == player2) score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    void Draw() {
        system("cls");
        for (int i = 0; i < i < width + 2; i++)
            cout << "#";
        
        for (int i = 0; i < i < width + 2; i++)
            cout << "#";


    }
};

int main()
{
    Game g(40, 20);
    g.Draw();

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
