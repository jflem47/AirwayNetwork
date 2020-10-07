/**
* \file Graphe.cpp
* \brief Implémentation d'un graphe orienté.
* \author Jean-Francois Lemieux
* \version 0.1
* \date 28 juin 2020
*
*  Travail pratique numéro 2
*
*/

#include "Graphe.h"
#include <algorithm>

//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2 {

    /**
     * \brief Constructeur
     */
    Graphe::Graphe(size_t nbSommets) : nbSommets(nbSommets), nbArcs(0) {
        sommets.resize(nbSommets, "");
        listesAdj.resize(nbSommets, std::list<Arc>());
    }

    /**
     * \brief Destructeur
     */
    Graphe::~Graphe() {}

    /**
     * \brief Change la taille du graphe en utilisant un nombre de sommet = nouvelleTaille
     * @param nouvelleTaille La nouvelle taille
     */
    void Graphe::resize(size_t nouvelleTaille) {
            nbSommets = nouvelleTaille; // Nouvelle définition de la taille
            sommets.resize(nbSommets);
            listesAdj.resize(nbSommets, std::list<Arc>());
    }

    /**
     * \brief Donne un nom à un sommet en utlisant son numéro (indice dans le vector).
     * @param sommet Un sommet
     * @param nom Le nom du sommet
     */
    void Graphe::nommer(size_t sommet, const std::string &nom) {
        // Vérification de la validité de l'indice en entrée
        if (sommet >= nbSommets) { throw std::logic_error("L'indice du sommet est invalide."); }
        else {
            sommets[sommet] = nom; // Assignation de la valeur "nom" au sommet donné.
        }
    }

    /**
     * \brief Ajoute un arc au graphe
     * @param source Le sommet source
     * @param destination Le sommet de destination
     * @param duree La durée du trajet
     * @param cout Le cout du trajet
     * @param ns Le niveau de sécurité du trajet
     */
    void Graphe::ajouterArc(size_t source, size_t destination, float duree, float cout, int ns) {
        // Vérification de la validité des sommets donnés en entrée.
        if (source >= nbSommets || destination >= nbSommets) {
            throw std::logic_error("La source ou la destination entrée est invalide.");
        }
        // Vérification de la présence de l'arc dans le Graph.
        else if (arcExiste(source, destination)) {
            throw std::logic_error("L'arc existe déjà dans le Graph.");
        }
        // Ajout de l'arc dans le Graph.
        else {
            Ponderations pond(duree, cout, ns);
            listesAdj[source].push_back(Arc(destination, pond));
            nbArcs++;
        }
    }

    /**
     * \brief Supprime un arc du graphe
     * @param source
     * @param destination
     */
    void Graphe::enleverArc(size_t source, size_t destination) {
        // Vérification de la validité des sommets donnés en entrée.
        if (source >= nbSommets || destination >= nbSommets) {
            throw std::logic_error("La source ou la destination entrée est invalide.");
        }
        // Vérification de la présence de l'arc dans le Graph.
        else if (!arcExiste(source, destination)) {
            throw std::logic_error("L'arc n'existe pas dans le Graph.");
        }
        // Retrait de l'arc
        else {
            auto it = listesAdj[source].begin();
            for (auto &arc : listesAdj[source]) {
                size_t A = destination;
                size_t B = arc.destination;
                if (A == B) {
                    listesAdj[source].erase(it);
                    nbArcs--;
                }
                else { it++; }
            }
        }
    }

    /**
     * \brief Vérifie si un arc existe
     * @param source
     * @param destination
     * @return Un booléen qui indique true si l'arc existe dans le Graph ou false s'il n'existe pas.
     */
    bool Graphe::arcExiste(size_t source, size_t destination) const {
        // Boucle dans le graph afin de vérifier la présence de l'arc
        for (auto &arc : listesAdj[source]) {
            if (arc.destination == destination) {
                // Arc présent
                return true;
            }
        }
        // L'arc n'a pas été trouvé dans le Graph
        return false;
    }

    /**
     * \brief Retourne la liste de successeurs d'un sommmet
     * @param sommet Le sommet dont on veut les successeurs
     * @return Un vecteur contenant les sommets successeurs
     */
    std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const {
        // Création du vecteur accumulateur de sommets
        std::vector<size_t> sommetsAdj;
        for (auto &arc : listesAdj[sommet]) {
            // Ajout des sommets adjacents dans le vecteur
            sommetsAdj.push_back(arc.destination);
        }
        // Retour du vecteur accumulateur
        return sommetsAdj;
    }

    /**
     * \brief Retourne le nom d'un sommet
     * @param sommet Le sommet dont on veut le nom
     * @return Le nom du sommet
     */
    std::string Graphe::getNomSommet(size_t sommet) const {
        if (sommet >= nbSommets) { throw std::logic_error("Le sommet entré n'est pas valide."); }
        return sommets[sommet];
    }

    /**
     * \brief Retourne le numéro d'un sommet
     * @param nom Le nom du sommet
     * @return Le numéro du sommet
     */
    size_t Graphe::getNumeroSommet(const std::string &nom) const {
        // Variable de type size_t initialisée
        size_t res;
        for (int i = 0; i < sommets.size(); i++) {
            // Sommet trouvé
            if (sommets[i] == nom) {
                // Assignation de la valeur à la variable
                res = i;
                // Retour de la valeur
                return res;
            }
            else { continue; }
        }
        // Sommet non trouvé
        throw std::logic_error("Le sommet n'est pas présent dans le graph.");

    }

    /**
     * \brief Retourne le nombre de sommet du graphe
     * @return Le nombre de sommets du Graph
     */
    int Graphe::getNombreSommets() const {
        return nbSommets;
    }

    /**
     * \brief Retourne le nombre des arcs du graphe
     * @return Le nombre d'arcs du Graph
     */
    int Graphe::getNombreArcs() const {
        return nbArcs;
    }

    /**
     * \brief Retourne les pondérations se trouvant dans un arc (source -> destination)
     * @param source Le sommet source
     * @param destination Le sommet de destination
     * @return La pondération de l'arc
     */
    Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const {
        // Vérification de la validité des sommets donnés en entrée.
        if (source >= nbSommets || destination >= nbSommets) {
            throw std::logic_error("La source ou la destination entrée est invalide.");
        }
        // Trouver l'arc
        for (auto &arc : listesAdj[source]) {
            if (arc.destination == destination) {
                // Retourner sa pondération
                return arc.poids;
            }
        }
    }

}//Fin du namespace
