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
     for(size_t ligne = HEIGHT - 1; ligne >= 0; --ligne)
     {
         if(board[ligne][c] == EMPTY)
         {
             board[ligne][c] = p;
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



/*
 7 colonnes 6 lignes
 * on veut
 * 05|15|25|35|45|55|65    -> l0h5/l1h5/l2h5/l3h5/l4h5/l5h5/l6h5     j de 5(HEIGHT) à -> 0 
 * 04|14|24|34|44|54|64    -> l0h1/l1h4/l2h4/l3h4/l4h4/l5h4/l6h4     i de 0 à -> 6 (WIDTH)
 * 03 ......
 * 02                           .   .   .   .   ..  
 * 01                           .   .   .   ..  ..      ..  .       
 * 00|10|20|30|40|50|60       l0h0/l1h0/l2h0/l3h0/l4h0/l5h0/l6h0
 * 
 * Le putain de tableau sa mere la chienne il fait pas comme ça
 * il fait plutôt comme ça ce bâtard :
 * 
 * 00|01|02|03|04|05|
 * 10|11|12|13|14|15|
 * 20|21|22|23|24|25|
 * 30...
 * 40...
 * 50.....
 * 60|61|62|63|64|65|
 * donc c pour ça qu'on a une hauteur de 7 et une largeur de 6. -> FUCK.
 
 */

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
