#include "P4.h"


void P4::reset()
{
    for(size_t ligne = 0; ligne < HEIGHT; ++ligne)
    {
        for(size_t col = 0; col < WIDTH; ++col)
        {
            board[ligne][col] = EMPTY;
        }
     }
}


 P4::P4()
 {
     for(size_t ligne = 0; ligne < HEIGHT; ++ligne)
     {
         maxJetonPerColumn[ligne] = 0; 
        for(size_t col = 0; col < WIDTH; ++col)
        {
            board[ligne][col] = EMPTY;
        }
     }
 }
 
 
 void P4::playInColumn(size_t c, Player p)
 {
    if(board[HEIGHT-1][c] == EMPTY)
    {
        board[HEIGHT-1][c] = p;
        maxJetonPerColumn[c]++;
        maxJetonPerLines[HEIGHT - 1]++;
         // incrémente le nb de jetons dans cette colonne
    }
    else if(board[HEIGHT-2][c] == EMPTY) // un truc du genre
    {
       board[HEIGHT-2][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 2]++;
    }
    else if(board[HEIGHT-3][c] == EMPTY) // un truc du genre
    {
       board[HEIGHT-3][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 3]++;
    }
    else if(board[HEIGHT-4][c] == EMPTY) // un truc du genre
    {
       board[HEIGHT-4][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 4]++;
    }
    else if(board[HEIGHT-5][c] == EMPTY) // un truc du genre
    {
       board[HEIGHT-5][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 5]++;
    }
    else if(board[HEIGHT-6][c] == EMPTY) // un truc du genre
    {
       board[HEIGHT-6][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 6]++;
    }  
 }
 
std::string P4::getName() const
{
    return "Les Cuistos";
}

bool P4::isValidMove(size_t c) const
{
    return ((maxJetonPerColumn[c] < HEIGHT) && (c < WIDTH));
}

bool P4::isWinner(Player p) const
{
    for (size_t i = 0; i < WIDTH; ++i) 
    {
        
        if (maxJetonPerColumn[i] >= 4 && 
               (board[2][i] == p 
            &&  board[3][i] == p
            &&  board[4][i] == p
            &&  board[5][i] == p)  
            || (board[1][i] == p 
            &&  board[2][i] == p
            &&  board[3][i] == p
            &&  board[4][i] == p)
            || (board[0][i] == p 
            &&  board[1][i] == p
            &&  board[2][i] == p
            &&  board[3][i] == p)) // Check vertical
        {
            return true;
        }
        else if(maxJetonPerLines[i] >= 4 && i < WIDTH - 1 && 
                (board[i][0] == p
                && board[i][1] == p
                && board[i][2] == p
                && board[i][3] == p)||
                (board[i][1] == p
                && board[i][2] == p
                && board[i][3] == p
                && board[i][4] == p)||
                (board[i][2] == p
                && board[i][3] == p
                && board[i][4] == p
                && board[i][5] == p)||
                (board[i][3] == p
                && board[i][4] == p
                && board[i][5] == p
                && board[i][6] == p)) // Check horizontal
        {
            return true;
        } 
    }
    for(size_t i = 3; i < WIDTH; ++i) // Check diagonales ascendantes
    {
        for(size_t j = 0; j < HEIGHT - 3; ++j)
        {
            if(board[i][j] == p && board[i -1][j + 1] == p && board[i - 2][j + 2] == p && board[i - 3][j + 3] == p)
            {
                return true;
            }
        }
    }
    
    for(size_t i = 3; i < WIDTH; ++i) // Check diagonales descendantes
    {
        for(size_t j = WIDTH -1; j >= 3; --j)
        {
            if(board[i][j] == p && board[i - 1][j - 1] == p && board[i - 2][j - 2] == p && board[i - 3][j - 3] == p)
            {
                return true;
            }
        }
    }
    return false;
}



size_t P4::chooseNextMove(Player p, unsigned depth)
{
    return 1;
}



std::ostream& operator << ( std::ostream& os, const P4& p4)
{
    os << "\n+-+-+-+-+-+-+-+\n";
    for(size_t ligne = 0; ligne < HEIGHT; ++ligne)
    {
        os << "|";
        for(size_t col = 0; col < WIDTH; col++)
        {
            switch(p4.board[ligne][col])
            {
                case (int)X:
                    os << "X";
                    break;
                case (int)O: 
                    os << "O";
                    break;
                case (int)EMPTY:
                    os << " ";
                    break;
                default: os << "k";
            }
            os << "|";          
        }
        os << "\n+-+-+-+-+-+-+-+\n";
       
     }
     os << " 0 1 2 3 4 5 6\n";
    return os;
}
