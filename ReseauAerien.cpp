/**
 * \file ReseauAerien.cpp
 * \brief Implémentattion de la classe ReseauAerien.
 * \author Jean-Francois Lemieux
 * \version 0.1
 * \date 28 juin 2020
 *
 *  Travail pratique numéro 2
 *
 */

#include "ReseauAerien.h"
#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2
{

// Méthode fournie
/**
 * \fn void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
 * \param[in] le fichier contenant l'information sur le réseau
 */
    void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
    {
        if (!fichierEntree.is_open())
            throw std::logic_error("ReseauAerien::chargerReseau: Le fichier n'est pas ouvert !");

        std::string buff;
        getline(fichierEntree, nomReseau);
        nomReseau.erase(0, 15);

        int nbVilles;

        fichierEntree >> nbVilles;
        getline(fichierEntree, buff); //villes

        unReseau.resize(nbVilles);

        getline(fichierEntree, buff); //Liste des villes

        size_t i = 0;

        getline(fichierEntree, buff); //Premiere ville

        while(buff != "Liste des trajets:")
        {
            std::string ville = buff;

            unReseau.nommer(i, ville);

            getline(fichierEntree, buff);
            i++;
        }

        while(!fichierEntree.eof())
        {
            getline(fichierEntree, buff);
            std::string source = buff;

            getline(fichierEntree, buff);
            std::string destination = buff;

            getline(fichierEntree, buff);
            std::istringstream iss(buff);

            float duree;
            iss >> duree;

            float cout;
            iss >> cout;

            int ns;
            iss >> ns;

            unReseau.ajouterArc(unReseau.getNumeroSommet(source), unReseau.getNumeroSommet(destination), duree, cout, ns);
        }
    }

    /**
     * \brief Constructeur avec paramètres
     * @param nomReseau Le nom du réseau aérien
     * @param nbVilles Le nombre de villes qui constituent le réseau
     */
    ReseauAerien::ReseauAerien(std::string nomReseau, size_t nbVilles)
    : nomReseau(nomReseau), unReseau(Graphe(nbVilles))
    {}

    /**
     * \brief Destructeur de la classe
     */
    ReseauAerien::~ReseauAerien() {}

    /**
     * \brief Change la taille du réseau en utilisant un nombre de villes = nouvelleTaille
     * @param nouvelleTaille La nouvelle taille du réseau
     */
    void ReseauAerien::resize(size_t nouvelleTaille) {
        // Utilisation de la methode de Graphe pour modifier la taille.
        unReseau.resize(nouvelleTaille);
    }

    /**
     * \brief Retourne le plus court chemin selon l'algorithme de Dijkstra
     * @param origine La ville d'origine
     * @param destination La ville de destination
     * @param dureeCout Booléen indiquant s'il faut utiliser la durée du trajet (true) ou bien son cout (false)
     * @return Le plus court chemin de l'origine à la destination
     */
    Chemin ReseauAerien::rechercheCheminDijkstra(const std::string &origine, const std::string &destination,
                                                 bool dureeCout) const {
        // L'origine n'est pas valide
        for (int i = 0; i <= unReseau.getNombreSommets(); i++) {
            if (unReseau.getNomSommet(i) == origine) {
                break;
            }
            else if (i == unReseau.getNombreSommets()) {
                throw std::logic_error("La destination n'est pas valide.");
            }
        }

        // La destination n'est pas valide
        for (int i = 0; i <= unReseau.getNombreSommets(); i++) {
            if (unReseau.getNomSommet(i) == destination) {
                break;
            }
            else if (i == unReseau.getNombreSommets()) {
                throw std::logic_error("L'origine n'est pas valide.");
            }
        }

        // Vecteur avec tous les sommets T
        std::vector<std::string> T;
        for (int i = 0; i < unReseau.getNombreSommets(); i++) {
            T.push_back(unReseau.getNomSommet(i));
        }

        // Vecteur des sommets visités S
        std::vector<std::string> S;

        // Vecteur des poids Y
        std::vector<double> Y;
        for (int i = 0; i < unReseau.getNombreSommets(); i++) {
            Y.push_back(INT_MAX);
        }

        // Poids de la source mis à 0
        Y[unReseau.getNumeroSommet(origine)] = 0;

        // Vecteur des prédécesseurs (initialisés à NULL)
        std::vector<std::string> P;
        for (int i = 0; i < unReseau.getNombreSommets(); i++) {
            P.push_back("NULL");
        }

        // Définition du sommet courant
        size_t sommetCourant = unReseau.getNumeroSommet(origine);

        while (!T.empty()) {
            // Marquer le sommet courant comme visité
            T.erase(std::remove(T.begin(), T.end(), unReseau.getNomSommet(sommetCourant)), T.end());
            S.push_back(unReseau.getNomSommet(sommetCourant));

            // Trouver les sommets adjacents
            std::vector<size_t> sommetsAdj =
                    unReseau.listerSommetsAdjacents(sommetCourant);

            // Relachement et définition du prochain sommet à visiter
            double min = INT_MAX;
            size_t next;
            for (auto &adj : sommetsAdj) {
                double poidsCourant = Y[adj];
                double newPoids;
                Ponderations pond = unReseau.getPonderationsArc(sommetCourant, adj);

                // Poids en DURÉE
                if (dureeCout) {
                    newPoids = Y[sommetCourant] + pond.duree ;
                }
                // Poids en COUT
                else { newPoids = Y[sommetCourant] + pond.cout; }

                if (poidsCourant > newPoids) {
                    Y[adj] = newPoids;
                    P[adj] = unReseau.getNomSommet(sommetCourant);
                    if (Y[adj] < min) { next = adj; }
                }
            }

            // Prochain sommet
            if (std::find(T.begin(), T.end(), unReseau.getNomSommet(next)) == T.end()) {
                sommetCourant = unReseau.getNumeroSommet(T[0]);
            } else { sommetCourant = next; }

            // Destination franchie
            if (sommetCourant == unReseau.getNumeroSommet(destination)) {
                // Définition du Chemin
                Chemin reponse;

                // Poids total
                if (dureeCout) {
                    reponse.dureeTotale = Y[sommetCourant];
                } else { reponse.coutTotal = Y[sommetCourant]; }

                // Chemin
                size_t current = unReseau.getNumeroSommet(destination);
                while (current != unReseau.getNumeroSommet(origine)) {
                    reponse.listeVilles.insert(reponse.listeVilles.begin(), unReseau.getNomSommet(current));
                    // Pas de chemin
                    if (P[current] == "NULL") {
                        reponse.reussi = false;
                        return reponse;
                    }
                    current = unReseau.getNumeroSommet(P[current]);
                }
                reponse.listeVilles.insert(reponse.listeVilles.begin(), unReseau.getNomSommet(current));

                // Réussi
                reponse.reussi = true;

                return reponse;
            }

        } // fin de la boucle while

        // On a pas trouvé de chemin
        Chemin reponse;
        reponse.reussi = false;

        return reponse;

    }

    /**
     * \brief Retourne le plus court chemin selon l'algorithme Bellman-Ford
     * @param origine La ville d'origine
     * @param destination La ville de destination
     * @param dureeCoutNiveau 1 pour utiliser la durée, 2 pour utiliser le cout et 3 pour
     *        utiliser le niveau de sécurité comme pondération des Arcs.
     * @return Le plus court chemin de l'origine à la destination
     */
    Chemin ReseauAerien::rechercheCheminBellManFord(const std::string &origine, const std::string &destination,
                                                    int dureeCoutNiveau) const {
        // L'origine n'est pas valide
        for (int i = 0; i <= unReseau.getNombreSommets(); i++) {
            if (unReseau.getNomSommet(i) == origine) {
                break;
            }
            else if (i == unReseau.getNombreSommets()) {
                throw std::logic_error("La destination n'est pas valide.");
            }
        }

        // La destination n'est pas valide
        for (int i = 0; i <= unReseau.getNombreSommets(); i++) {
            if (unReseau.getNomSommet(i) == destination) {
                break;
            }
            else if (i == unReseau.getNombreSommets()) {
                throw std::logic_error("L'origine n'est pas valide.");
            }
        }

        // La variable dureeCoutNiveau est invalide
        if (dureeCoutNiveau < 1 || dureeCoutNiveau > 3) {
            throw std::logic_error("Le choix de pondération entré est invalide.");
        }

        // Vecteur avec tous les sommets T
        std::vector<std::string> T;
        for (int i = 0; i < unReseau.getNombreSommets(); i++) {
            T.push_back(unReseau.getNomSommet(i));
        }

        // Vecteur des poids Y
        std::vector<double> Y;
        for (int i = 0; i < unReseau.getNombreSommets(); i++) {
            Y.push_back(INT_MAX);
        }

        // Poids de la source mis à 0
        Y[unReseau.getNumeroSommet(origine)] = 0;

        // Vecteur des prédécesseurs (initialisés à NULL)
        std::vector<std::string> P;
        for (int i = 0; i < unReseau.getNombreSommets(); i++) {
            P.push_back("NULL");
        }

        // Algorithme de Bellman-Ford
        for (int i = 0; i < unReseau.getNombreSommets(); i++) {
            for (int j = 0; j < unReseau.getNombreSommets(); j++) {
                // Trouver les sommets adjacents
                std::vector<size_t> sommetsAdj =
                        unReseau.listerSommetsAdjacents(j);

                // Relachement
                for (auto &adj : sommetsAdj) {
                    double poidsCourant = Y[adj];
                    double newPoids;
                    Ponderations pond = unReseau.getPonderationsArc(j, adj);

                    // Poids en DURÉE
                    if (dureeCoutNiveau == 1) {
                        newPoids = Y[j] + pond.duree;
                    }
                    // Poids en COUT
                    else if (dureeCoutNiveau == 2) {
                        newPoids = Y[j] + pond.cout;
                    }
                    // Poids en niveau de sécurité
                    else { newPoids = Y[j] + pond.ns; }

                    if (poidsCourant > newPoids) {
                        Y[adj] = newPoids;
                        P[adj] = unReseau.getNomSommet(j);
                    }
                }
            }
        }
        // Vérification de la convergeance
        for (int i = 0; i < unReseau.getNombreSommets(); i++) {
            // Trouver les sommets adjacents
            std::vector<size_t> sommetsAdj =
                    unReseau.listerSommetsAdjacents(i);

            // Relachement
            for (auto &adj : sommetsAdj) {
                double poidsCourant = Y[adj];
                double newPoids;
                Ponderations pond = unReseau.getPonderationsArc(i, adj);

                // Poids en DURÉE
                if (dureeCoutNiveau == 1) {
                    newPoids = Y[i] + pond.duree;
                }
                // Poids en COUT
                else if (dureeCoutNiveau == 2) {
                    newPoids = Y[i] + pond.cout;
                }
                // Poids en niveau de sécurité
                else { newPoids = Y[i] + pond.ns; }

                // Présence d'un circuit négatif
                if (poidsCourant > newPoids) {
                    Chemin reponse;
                    reponse.reussi = false;
                    return reponse;
                }
            }
        }
        // Définition du Chemin
        Chemin reponse;

        // Poids total
        if (dureeCoutNiveau == 1) {
            reponse.dureeTotale = Y[unReseau.getNumeroSommet(destination)];
        }
        else if (dureeCoutNiveau == 2){
            reponse.coutTotal = Y[unReseau.getNumeroSommet(destination)];
        }
        else { reponse.nsTotal = Y[unReseau.getNumeroSommet(destination)]; }

        // Chemin
        size_t current = unReseau.getNumeroSommet(destination);
        while (current != unReseau.getNumeroSommet(origine)) {
            reponse.listeVilles.insert(reponse.listeVilles.begin(), unReseau.getNomSommet(current));
            // Pas de chemin
            if (P[current] == "NULL") {
                reponse.reussi = false;
                return reponse;
            }
            current = unReseau.getNumeroSommet(P[current]);
        }
        reponse.listeVilles.insert(reponse.listeVilles.begin(), unReseau.getNomSommet(current));

        // Réussi
        reponse.reussi = true;

        return reponse;


    } // fin de la methode Bellman-Ford



    //À compléter par l'implémentation des autres méthodes demandées

}//Fin du namespace
