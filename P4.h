#ifndef P4_h
#define P4_h
#include <limits>
#include "P4Interface.h"
#include <iostream>

class P4 : public P4Interface
{
    /**
     *  @brief Surcharge de << pour afficher la grille du jeu
     *
     *  @param std::ostream&     le flux utilise pour laffichage
     *  @param P4& un objet de votre classe P4
     *
     *  @return le flux original
    */
    friend std::ostream& operator << (std::ostream& os, const P4& p4);
    
private:
        
    size_t maxJetonPerColumn[WIDTH] = {0,0,0,0,0,0,0}; // utile pour tracker le nb de jeton par colonne
    size_t maxJetonPerLines[HEIGHT] = {0,0,0,0,0,0}; // de même pour les lignes
    Player board[HEIGHT][WIDTH];    //la grille de jeu
    int nbMove = 0;                 //le nombre de coups joués
    
    /**
     * 
     * @param p
     * @return un entier représentant la valeur de la case jou
     */
    int heuristique(const Player& p);
    
    
    /**
     * @brief permet de calculer le score d'une colonne
     * @param col, la colonne testée
     * @param p, le Player courant
     * @param depth, la profondeur de la recursion.
     * @return un entier représentant le score de la case courante obtenue avec la colonne passée en paramètre
     */
    int calculeScore(size_t col, const Player& p, unsigned depth);

    
public:

    // NE PAS MODIFIER L'INTERFACE PUBLIC.
    // IMPLEMENTER LES METHODES SEPAREMENT
    // DANS UN FICHIER .CPP

    /**
     *  @brief Constructeur par defaut
     */
    P4();
    
    /**
     *  @brief Remet à zèro les attributs pour jouer une nouvelle partie
     */
    void reset();
    
    /**
     *  @brief Le joueur p joue dans la colonne c.
     *
     *  @param c Le numero de colonne entre 0 et 6
     *  @param p Le joueur X ou O
     */
    void playInColumn(size_t c, Player p);
    
    void unPlayInColumn(size_t lastLine, size_t lastColumn);
   
    
    /**
     *  @brief Verifie si le joueur p gagne
     *
     *  @param p Le joueur X ou O
     *
     *  @return vrai si 4 a la suite pour p, faux sinon
     */
    bool isWinner(Player p) const;
        
    /**
     *  @brief Verifie si jouer dans la colonne c est valide
     *
     *  @param c Le numero de colonne entre 0 et 6
     *
     *  @return vrai si c est entre 0 et 6 et que la 
     *          colonne n'est pas pleine. Faux sinon
     */
    bool isValidMove(size_t c) const;
    
    /**
     *  @brief Choisit la prochain mouvement pour le joueur p
     *
     *  @param p     Le joueur X ou O
     *  @param depth La profondeur de recherche de l'algorithme minimax
     *
     *  @return retourne un numero de colonne entre 0 et 6
     *          sans modifier l'etat de la grille du jeu
     *          typiquement calcule avec une variante a 
     *          choix de l'algorithme minimax
     */
    size_t chooseNextMove(Player p, unsigned depth);

    /**
     *  @brief Renvoie le nom de votre classe pour le tournoi
     *
     *  @return Un nom qui sera typiquement tronque a l'affichage
     *          pour ne garder que les 4 premieres lettres
     */
    std::string getName() const;
    

    size_t nbMoves() const;
};


/**
	 * @brief Fonction recursive qui trouve la meilleure position a jouer dans la Grille de jeu et pour le Player p.
	 * Utilise l'elagage Alpha-Beta si le bool UTILISER_ELAGAGE_ALPHA_BETA est true.
	 *
	 * @param cln, la derniere colonne dans laquelle un jeton a ete joue.
	 * @param p, le Player pour qui on souhaite trouver la meilleure position a jouer.
	 * @param profondeur, la profondeur de la recursion.
	 * @param alpha minimum
	 * @param beta maximum
	 * @return une entier, le score qu'à obtenu la case testee.
	 */

#endif /* P4_h */
