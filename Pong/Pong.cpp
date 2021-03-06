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
        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int ballx = ball->getX();
                int bally = ball->getY();

                int player1x = player1->getX();
                int player1y = player1->getY();

                int player2x = player2->getX();
                int player2y = player2->getY();

                if (j == 0) cout << "\xB2";
                if (ballx == j && bally == i) cout << "o";
                else if (player1x == j && player1y == i) cout << "\xDB";
                else if (player2x == j && player2y == i) cout << "\xDB";
                else if (player1x == j && player1y +1== i) cout << "\xDB";
                else if (player1x == j && player1y +2== i) cout << "\xDB";
                else if (player1x == j && player1y +3== i) cout << "\xDB";
                else if (player2x == j && player2y +1== i) cout << "\xDB";
                else if (player2x == j && player2y +2== i) cout << "\xDB";
                else if (player2x == j && player2y +3== i) cout << "\xDB";
                else cout << " ";

                if (j == width - 1) cout << "\xB2";
            }

            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;
        cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;

    }

    void Input() {
        ball->Move();

        int ballx = ball->getX();
        int bally = ball->getY();

        int player1x = player1->getX();
        int player1y = player1->getY();

        int player2x = player2->getX();
        int player2y = player2->getY();
        if (_kbhit()) {
            char current = _getch();
            if (current == up1)
                if (player1y > 0)
                    player1->moveUp();
            if (current == up1)
                if (player2y > 0)
                    player2->moveUp();
            if (current == down1)
                if (player1y +4 < height)
                    player1->moveDown();
            if (current == down1)
                if (player2y +4 < height)
                    player2->moveDown();

            if (ball->getDirection() == Stop)
                ball->RandomDirection();
            if (current == 'q')
                quit = true;


        }
       
    }
    void Colision() {
        int ballx = ball->getX();
        int bally = ball->getY();

        int player1x = player1->getX();
        int player1y = player1->getY();

        int player2x = player2->getX();
        int player2y = player2->getY();

        for (int i = 0; i < 4; i++) 
            if (ballx == player1x + 1)
                if (bally == player1y + i)
                    ball->ChangeDirection((Dir)((rand() % 3) + 4));
            
        for (int i = 0; i < 4; i++) 
            if (ballx == player2x -1 )
                if (bally == player2y + i)
                    ball->ChangeDirection((Dir)((rand() % 3) + 1));

        if (bally == height - 1)
            ball->ChangeDirection(ball->getDirection() == DownRight ? UpRight : UpLeft);
        
        if (bally == 0)
            ball->ChangeDirection(ball->getDirection() == UpRight? DownRight: DownLeft);

        if (ballx == width - 1)
            ScoreUp(player1);
        
        if (ballx == 0)
            ScoreUp(player2);
            
        
    }

    void Run() {
        while (!quit) {
            Draw();
            Input();
            Colision();
        }
    }
};

int main()
{
    Game g(40, 20);
    g.Run();

    std::cout << "Hello World!\n";
}