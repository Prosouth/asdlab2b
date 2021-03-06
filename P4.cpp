#include "P4.h"
#include <limits>

using namespace std;

int random(int min, int max) //range : [min, max[
{
   static bool first = true;
   if ( first ) 
   {  
      srand(time(NULL)); 
      first = false;
   }
   return min + rand() % (max - min);
}


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
        maxJetonPerColumn[c]++; //incrémente le nombre de jetons présent dans la colonne c
        maxJetonPerLines[HEIGHT - 1]++; //incrément le nombre de jetons dans la ligne correspondante
        nbMove++;               //incrémente le compteur de coups joués
    }
    else if(board[HEIGHT-2][c] == EMPTY) 
    {
       board[HEIGHT-2][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 2]++;
       nbMove++;
    }
    else if(board[HEIGHT-3][c] == EMPTY) 
    {
       board[HEIGHT-3][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 3]++;
       nbMove++;
    }
    else if(board[HEIGHT-4][c] == EMPTY) 
    {
       board[HEIGHT-4][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 4]++;
       nbMove++;
    }
    else if(board[HEIGHT-5][c] == EMPTY) 
    {
       board[HEIGHT-5][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 5]++;
       nbMove++;
    }
    else if(board[HEIGHT-6][c] == EMPTY) 
    {
       board[HEIGHT-6][c] = p;
       maxJetonPerColumn[c]++;
       maxJetonPerLines[HEIGHT - 6]++;
       nbMove++;
    }  
 }
 
void P4::unPlayInColumn(size_t lastLine, size_t lastColumn)
{    
    board[lastLine][lastColumn] = EMPTY; //on met EMPTY dans la dernière position
    maxJetonPerColumn[lastColumn]--; //on décrémente le nombre de jetons dans la colonne
    maxJetonPerLines[lastLine]--;   //on décrémente le nombre de jetons dans la ligne
    nbMove--;
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
        
        if (((maxJetonPerColumn[i] >= 4) && 
            ((board[2][i] == p))
        &&  ((board[3][i] == p))
        &&  ((board[4][i] == p))
        &&  ((board[5][i] == p)))
        || (((board[1][i] == p))
        &&  ((board[2][i] == p))
        &&  ((board[3][i] == p))
        &&  ((board[4][i] == p)))
        || (((board[0][i] == p))
        &&  ((board[1][i] == p))
        &&  ((board[2][i] == p))
        &&  ((board[3][i] == p)))) // Check vertical
        {
            return true;
        }
        else if(((maxJetonPerLines[i] >= 4) && (i < WIDTH - 1) 
        &&  ((board[i][0] == p))
        &&  ((board[i][1] == p))
        &&  ((board[i][2] == p))
        &&  ((board[i][3] == p)))
        || (((board[i][1] == p))
        &&  ((board[i][2] == p))
        &&  ((board[i][3] == p))
        &&  ((board[i][4] == p)))
        || (((board[i][2] == p))
        &&  ((board[i][3] == p))
        &&  ((board[i][4] == p))
        &&  ((board[i][5] == p)))
        || (((board[i][3] == p))
        &&  ((board[i][4] == p))
        &&  ((board[i][5] == p))
        &&  ((board[i][6] == p)))) // Check horizontal
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
        for(size_t j = WIDTH - 1; j >= 3; --j)
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
    static bool firstStone = true;
    size_t bestMove = 0;
    
    //on initialise le score à "moins l'infini"
    int bestScore = -(WIDTH * HEIGHT);

    //si il s'agit du premier coup joué alors on doit jouer au milieu
    if (firstStone) 
    {
        firstStone = false;
        return WIDTH / 2;
    }
  
    
    //on appelle la fonction heuristique pour déterminer la meilleure case à jouer
    size_t nextMove = heuristique(p); 
    
    for(size_t i = 0 ; i < WIDTH ; i++)
    {
        //on regarde la colonne suivante en faisant attention de ne pas dépasser WIDTH
        nextMove = (nextMove + i)%WIDTH;

        if (isValidMove(nextMove)) 
        {
            int score = calculeScore(nextMove, p, depth, ALPHA, BETA);
            
            if(score > bestScore)
            {
                    bestScore = score;
                    bestMove = nextMove;
            }
        }
    }   
    return bestMove;
}
   
    
int P4::calculeScore(size_t col, const Player& p, unsigned depth, int alpha, int beta) 
{
    //le score de la case à retourner
    int scorePlayer;

    //on applique le mouvement donnée en paramètre
    playInColumn(col, p);
    
    //si le mouvement joué gagnant alors on renvoie le score max
    if(isWinner(p))
    {
        unPlayInColumn(HEIGHT - maxJetonPerColumn[col], col);
        return WIDTH*HEIGHT;
    }
    //le cas de l'égalité -> on renvoie un score de 0
    if (nbMove == WIDTH * HEIGHT) {
        scorePlayer = 0;
    }
    //on atteint la profondeur limite
    else if(depth == 0)
    {
        unPlayInColumn(HEIGHT - maxJetonPerColumn[col], col);
        return heuristique(p);
    }
    //sinon, on doit calculer le score du prochain coup
    else
    {
        int bestScore = -WIDTH*HEIGHT;
         //choix d'une colonne aléatoire pour faire calculer le score et entrer dans la récursion
        size_t nextMove = random(0,WIDTH) % WIDTH;

        for(size_t i = 0 ; i < WIDTH ; i++)
        {
            //on regarde la colonne suivante en faisant attention de ne pas dépasser WIDTH
            nextMove = (nextMove + i)%WIDTH;

            if (isValidMove(nextMove)) 
            {
                int score = calculeScore(nextMove, (Player)((int)p*-1), depth-1, alpha, beta);
                
                if(score > bestScore)
                {
                    bestScore = score;
                } 
                if (ELAGAGE_ALPHA_BETA) 
                {
                    if(score > alpha)
                    {
                        alpha = score;
                    } 
                    //sort de la boucle for
                    if (alpha >= beta) 
                    {
                        break;
                    }
                }
            }
        }
        scorePlayer = -bestScore;    
    }
    //on efface le coup joué
    unPlayInColumn(HEIGHT - maxJetonPerColumn[col], col);

    return scorePlayer;
}


int P4::heuristique(const Player& p) 
{
    //on remplit la colonne du milieu tant que l'adevrsaire joue au centre
    if(nbMove <= 5 && board[HEIGHT - nbMove][3] != EMPTY)
    {
        return 3;
    }
    
    //on regarde si 3 jetons d'affilés sont alignés et si on peut gagner au prochain coup
    for(size_t i = 0; i < WIDTH; i++)
    {
        if(isValidMove(i))
        {
            playInColumn(i,p);
            if(isWinner(p))
            {
                unPlayInColumn(HEIGHT - maxJetonPerColumn[i], i);
                return 2 *(int)i;
            }
            unPlayInColumn(HEIGHT - maxJetonPerColumn[i], i);
        }
    }
    
    //on joue sur le coup gagnant de l'adversaire
    for(size_t i = 0; i < WIDTH; i++)
    {
        if(isValidMove(i))
        {
            playInColumn(i,(Player((int)p*-1)));
            if(isWinner((Player((int)p*-1))))
            {
                unPlayInColumn(HEIGHT - maxJetonPerColumn[i], i);
                return (int)i;
            }
            unPlayInColumn(HEIGHT - maxJetonPerColumn[i], i);
        }
    } 
    //sinon on joue aléatoirement
    int colonneAleatoire = random(0,WIDTH);
    
    return colonneAleatoire;
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