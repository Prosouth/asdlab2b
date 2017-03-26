#include "P4.h"


void P4::reset()
{
    for(size_t i = 0; i < WIDTH; ++i)
    {
        for(size_t j = 0; j < HEIGHT; ++j)
        {
            board[i][j] = EMPTY;
        }
     }
}


 P4::P4()
 {
     for(size_t i = 0; i < WIDTH; ++i)
     {
         maxJetonPerColumn[i] = 0; 
        for(size_t j = 0; j < HEIGHT; ++j)
        {
            board[i][j] = EMPTY;
        }
     }
 }
 
 
 void P4::playInColumn(size_t c, Player p)
 {
     for(size_t i = 0; i < HEIGHT; ++i)
     {
         if(board[c][i] == EMPTY)
         {
             board[c][i] = p;
             maxJetonPerColumn[c]++; // incrémente le nb de jetons dans cette colonne
         }
         break;
     }
 }
 
std::string P4::getName() const
{
    return "Les Cuistos";
}

bool P4::isValidMove(size_t c) const
{
    return (board[c][HEIGHT - 1] == EMPTY && (c < WIDTH));
}

bool P4::isWinner(Player p) const
{
    for (size_t i = 0; i < WIDTH; ++i) 
    {
        if (maxJetonPerColumn[i] >= 4
            && board[i][maxJetonPerColumn[i] - 1] == p
            && board[i][maxJetonPerColumn[i] - 2] == p
            && board[i][maxJetonPerColumn[i] - 3] == p) 
        {
            return true;
        }


        for (int dy = -1; dy <= 1; dy++) { // Iterate on horizontal (dy = 0) or two diagonal directions (dy = -1 or dy = 1).
            int nb = 0; // counter of the number of stones of current player surronding the played stone in tested direction.
            for (int dx = -1; dx <= 1; dx += 2) // count continuous stones of current player on the left, then right of the played column.
                for (int x = i + dx, y = maxJetonPerColumn[i] + dx * dy; x >= 0 && 
                     x < WIDTH && y >= 0 && y < HEIGHT && board[x][y] == p; nb++) 
                {
                    x += dx;
                    y += dx*dy;
                }
            if (nb >= 4) return true; // there is an aligment if at least 3 other stones of the current user 
            // are surronding the played stone in the tested direction.
        }
    }
    return false;
}



size_t P4::chooseNextMove(Player p, unsigned depth)
{
    return 1;
}



void P4::test()
{
   
}



std::ostream& operator << ( std::ostream& os, const P4& p4)
{
    os << "\n+-+-+-+-+-+-+-\n+";
    for(size_t i = 0; i < WIDTH; ++i)
     {
        os << "|";
        for(size_t j = 0; j < HEIGHT; ++j)
        {
            switch(p4.board[i][j])
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
            }
            os << "|";          
        }
        os << "\n+-+-+-+-+-+-+-\n+";
     }
    return os;
}
