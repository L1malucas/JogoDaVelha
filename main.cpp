#include <iostream>
#include<algorithm>

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void ShowBoard(char board[][SIDE])
{
    std::cout << "\n\n";
    std::cout << "\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2];
    std::cout << "\t\t\t-------------\n";
    std::cout << "\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2];
    std::cout << "\t\t\t-------------\n";
    std::cout << "\t\t\t %c | %c | %c \n", board[2][0], board[2][1], board[2][2];
    return;
}

void ShowInstructions()
{
    std::cout << "\t\t\t Jogo da Velha \n\n";
    std::cout << "Escolha uma casa entre 1 e 9 \n\n";
    std::cout << "\t\t\t 1 | 2 | 3\n";
    std::cout << "\t\t\t-----------\n";
    std::cout << "\t\t\t 4 | 5 | 6\n\n";
    std::cout << "\t\t\t-----------\n";
    std::cout << "\t\t\t 7 | 8 | 9\n\n";
    std::cout << "-\t-\t-\t-\t-\t-\t-\t-\t-\n\n";
    return;
}

void Initialize(char board[][SIDE], int moves[])
{
    srand(time(NULL));
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = ' ';
    }

    for (int i = 0; i < SIDE * SIDE; i++)
        moves[i] = i;
    std::random_shuffle(moves, moves + SIDE * SIDE);
    return;
}

void DeclaraVencedor(int whoseturn)
{
    if (whoseturn == COMPUTER)
        std::cout << "Computador Venceu!\n";
    else
        std::cout << "Humano Venceu!\n";
    return;
}

bool LinhaCruzada(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != ' ')
            return (true);
    }
    return (false);
}

bool ColunaCruzada(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != ' ')
            return (true);
    }
    return (false);
}

bool DiagonalCruzada(char board[][SIDE])
{
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != ' ')
        return (true);
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != ' ')
        return (true);
    return (false);
}

bool GameOver(char board[][SIDE])
{
    return (LinhaCruzada(board) || ColunaCruzada(board) || DiagonalCruzada(board));
}

void Play(int whoseturn)
{
    char board[SIDE][SIDE];
    int moves[SIDE * SIDE];

    Initialize(board, moves);
    ShowInstructions();
    int moveIndex = 0, x, y;

    while (GameOver(board) == false && moveIndex != SIDE * SIDE)
    {
        if (whoseturn == COMPUTER)
        {
            x = moves[moveIndex] / SIDE;
            y = moves[moveIndex] % SIDE;
            board[x][y] = COMPUTERMOVE;
            std::cout<< "Computador colocou %c na casa %d\n",COMPUTERMOVE, moves[moveIndex]+1;
            ShowBoard(board);
            moveIndex++;
            whoseturn = HUMAN;
        }
        else if (whoseturn == HUMAN)
        {
            x = moves[moveIndex] / SIDE;
            y = moves[moveIndex] % SIDE;
            board[x][y] = HUMANMOVE;
            std::cout << " Humano colocou %c na casa %d\n", HUMANMOVE, moves[moveIndex]+1;
            ShowBoard(board);
            moveIndex++;
            whoseturn = COMPUTER;
        }
    }
    if (GameOver(board) == false && moveIndex == SIDE * SIDE)
        std::cout << "Empate!";
    else
    {
        if (whoseturn == COMPUTER)
            whoseturn = HUMAN;
        else if (whoseturn == HUMAN)
            whoseturn = COMPUTER;
        DeclaraVencedor(whoseturn);
    }
    return;
}

int main()
{
    Play(COMPUTER);
    return (0);
}