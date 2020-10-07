/**
 * \file Graphe.h
 * \brief Gestion d'un graphe.
 * \author IFT-2008
 * \version 0.1
 * \date juin 2020
 *
 *  Travail pratique numéro 2
 *
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
//Vous pouvez ajouter d'autres librairies de la STL

#ifndef _GRAPHE__H
#define _GRAPHE__H

namespace TP2
{

/**
 * \struct Ponderations
 * \brief Une struture utilisée pour stocker les pondérations utilisées sur les arcs
 */
struct Ponderations
{
	float duree;		// La durée du vol en heures (ex. 0.8 heures entre Québec et Montréal)
	float cout;			// Le cout du trajet en dollars (ex. 220.46 $ pour un vol entre Québec et Montréal)
	int ns;				// Un niveau de sécurité représentant un indice qui peut être négatif

	Ponderations(float d, float c, int n) : duree(d), cout(c), ns(n) {}
};


/**
 * \class Graphe
 * \brief Classe représentant un graphe
 */
class Graphe
{
public:

	// Constructeur
	Graphe(size_t nbSommets = 10);

	// Destructeur
	~Graphe();

	// Change la taille du graphe en utilisant un nombre de sommet = nouvelleTaille
	// Vous pouvez supposer que cette méthode va être appliquée uniquement sur un graphe vide.
	void resize(size_t nouvelleTaille);

	// Donne un nom à un sommet en utlisant son numéro (indice dans le vector).
	// Exception logic_error si sommet supérieur à nbSommets
	void nommer(size_t sommet, const std::string& nom);

	// Ajoute un arc au graphe
	// Exception logic_error si source ou destination supérieur à nbSommets
	// Exception logic_error si l'arc existe déjà dans le graphe
	void ajouterArc(size_t source, size_t destination, float duree, float cout, int ns);

	// Supprime un arc du graphe
	// Exception logic_error si source ou destination supérieur à nbSommets
	// Exception logic_error si l'arc n'existe pas dans le graphe
	void enleverArc(size_t source, size_t destination);

	// Vérifie si un arc existe
	// Exception logic_error si source ou destination supérieur à nbSommets
	bool arcExiste(size_t source, size_t destination) const;

	// Retourne la liste de successeurs d'un sommmet
	// Exception logic_error si sommet supérieur à nbSommets
	std::vector<size_t> listerSommetsAdjacents(size_t sommet) const;

	// Retourne le nom d'un sommet
	// Exception logic_error si sommet supérieur à nbSommets
	std::string getNomSommet(size_t sommet) const;

	// Retourne le numéro d'un sommet
	// Exception logic_error si nom n'existe pas dans le graphe
	size_t getNumeroSommet(const std::string& nom) const;

	// Retourne le nombre de sommet du graphe
	int getNombreSommets() const;

	// Retourne le nombre des arcs du graphe
	int getNombreArcs() const;

	// Retourne les pondérations se trouvant dans un arc (source -> destination)
	// Exception logic_error si source ou destination supérieur à nbSommets
	Ponderations getPonderationsArc(size_t source, size_t destination) const;

	//Surcharge de l'opérateur de sortie.
	//Ne touchez pas à cette fonction !
	friend std::ostream& operator<<(std::ostream& out, const Graphe& g)
	{
		out << "Le graphe contient " << g.nbSommets << " sommet(s) et "
			<< g.nbArcs << " arc(s)" << std::endl << std::endl;
		for (size_t i = 0; i < g.nbSommets; ++i)
		{
			out << "Sommet: " << g.sommets[i] << std::endl << "Voisin(s): ";

			if (g.listesAdj[i].size() == 0)
				out << "Rien";
			else
			{
				for (auto it = g.listesAdj[i].begin(); it != g.listesAdj[i].end(); ++it)
					if (it == --g.listesAdj[i].end())
						out << g.sommets[it->destination];
					else
						out << g.sommets[it->destination] << ", ";
			}
			out << std::endl;
		}
		return out;
	}

	//Vous pouvez ajoutez d'autres méthodes publiques si vous sentez leur nécessité

private:

	std::vector<std::string> sommets; /*!< Le vecteur des sommets */

	struct Arc
	{
		size_t destination;
		Ponderations poids;	// Les pondérations utilisées pour un trajet entre deux villes

		Arc(size_t dest, Ponderations p) : destination(dest), poids(p) {}
	};

	std::vector<std::list<Arc> > listesAdj; /*!< les listes d'adjacence */

	size_t nbSommets;					// Le nombre de sommets dans le graphe
	size_t nbArcs;						// Le nombre des arcs dans le graphe

	//Vous pouvez ajoutez des méthodes privées si vous sentez leur nécessité

};

}//Fin du namespace

#endif
