/**
 * \file Principal.cpp
 * \brief Fichier pour les différents tests
 * \author IFT-2018
 * \version 0.1
 * \date juin 2020
 *
 */

#include <iostream>
#include <fstream>
#include <ctime>

#include "ReseauAerien.h"

using namespace std;
using namespace TP2;

int main()
{

	int nb = 1;						//Choix de l'utilisateur dans le menu initialisé à 1.
	string villeDepart;				//Chaîne de caractères représentant la ville de départ.
	string villeDestination;		//Chaîne de caractères représentant la ville de d'arrivée.
	ReseauAerien reseau("");		//Le reseau utilisé pour les tests.
	ifstream EntreeFichier;			//Flux d'entrée
	ofstream SortieFichier;			//Flux d'entrée
	clock_t startTime, endTime;  	//Pour mesurer l'efficacité des algorithmes


	cout << "Bienvenue dans votre reseau aerien !" << endl;
	//Affichage du menu
	cout << "------------------ Menu --------------------------------" << endl;
	cout << "1 - Charger le reseau a partir d'un fichier texte." << endl;
	cout << "2 - Trouver le plus court chemin avec Dijkstra." << endl;
	cout << "3 - Trouver le plus court chemin avec Bellman-Ford." << endl;
	cout << "4 - Mesurer le temps d'exécution de Dijkstra." << endl;
	cout << "5 - Mesurer le temps d'exécution de Bellman-Ford." << endl;
	cout << "0 - Quitter." << endl;
	cout << "--------------------------------------------------------" << endl;

	while (nb != 0)
	{

		do
		{
			cout << endl;
			cout << "Entrer s.v.p. votre choix (0 a 5):? ";
			cin >> nb;
			if(nb <0 || nb>5)
				cout << "***Option invalide!***\n";
		}while(nb <0 || nb>5);

		try
		{
			switch (nb)
			{
				case 1: //Charger le réseau à partir d'un fichier texte.
				{
					EntreeFichier.open("ReseauAerien.txt", ios::in);
					if(EntreeFichier.is_open())
					{
						reseau.chargerReseau(EntreeFichier);
					}
					EntreeFichier.close();
					cout << "Le reseau a ete charge !" << endl;
					cout << "Affichage du reseau: " << endl << reseau;
					break;
				}
				case 2: //Trouver le plus court chemin avec Dijkstra.
				{
					cout << "Recherche du plus court chemin avec Dijkstra." << endl;
					cout << "Entrez la ville de depart:? ";
					cin >> villeDepart;
					cout << "Entrez la ville de destination:? ";
					cin >> villeDestination;
					Chemin ch1_dijkstra = reseau.rechercheCheminDijkstra(villeDepart, villeDestination, true);
					Chemin ch2_dijkstra = reseau.rechercheCheminDijkstra(villeDepart, villeDestination, false);
					if(ch1_dijkstra.reussi)
					{
						cout << "Liste des villes du plus court chemin en utilisant la duree du vol: ";
						for (auto itr = ch1_dijkstra.listeVilles.begin(); itr != ch1_dijkstra.listeVilles.end(); ++itr)
							if (itr == --ch1_dijkstra.listeVilles.end())
								cout << *itr;
							else
								cout << *itr << ", ";
						cout << endl << "Duree totale du plus court chemin: " << ch1_dijkstra.dureeTotale << endl;
					}
					else
						cout << "Pas de chemin trouve !" << endl;
					if(ch2_dijkstra.reussi)
					{
						cout << "Liste des villes du plus court chemin en utilisant le cout du vol: ";
						for (auto itr = ch2_dijkstra.listeVilles.begin(); itr != ch2_dijkstra.listeVilles.end(); ++itr)
							if (itr == --ch2_dijkstra.listeVilles.end())
								cout << *itr;
							else
								cout << *itr << ", ";
						cout << endl << "Cout total du plus court chemin: " << ch2_dijkstra.coutTotal << endl;
					}
					else
						cout << "Pas de chemin trouve !" << endl;
					break;
				}
				case 3: //Trouver le plus court chemin avec Bellman-Ford.
				{
					cout << "Recherche du plus court chemin avec Bellman-Ford." << endl;
					cout << "Entrez la ville de depart:? ";
					cin >> villeDepart;
					cout << "Entrez la ville de destination:? ";
					cin >> villeDestination;
					Chemin ch1_BellmanFord = reseau.rechercheCheminBellManFord(villeDepart, villeDestination, 1);
					Chemin ch2_BellmanFord = reseau.rechercheCheminBellManFord(villeDepart, villeDestination, 2);
					Chemin ch3_BellmanFord = reseau.rechercheCheminBellManFord(villeDepart, villeDestination, 3);
					if(ch1_BellmanFord.reussi)
					{
						cout << "Liste des villes du plus court chemin en utilisant la duree du vol: ";
						for (auto itr = ch1_BellmanFord.listeVilles.begin(); itr != ch1_BellmanFord.listeVilles.end(); ++itr)
							if (itr == --ch1_BellmanFord.listeVilles.end())
								cout << *itr;
							else
								cout << *itr << ", ";
						cout << endl << "Duree totale du plus court chemin: " << ch1_BellmanFord.dureeTotale << endl;
					}
					else
						cout << "Pas de chemin trouve !" << endl;
					if(ch2_BellmanFord.reussi)
					{
						cout << "Liste des villes du plus court chemin en utilisant le cout du vol: ";
						for (auto itr = ch2_BellmanFord.listeVilles.begin(); itr != ch2_BellmanFord.listeVilles.end(); ++itr)
							if (itr == --ch2_BellmanFord.listeVilles.end())
								cout << *itr;
							else
								cout << *itr << ", ";
						cout << endl << "Cout total du plus court chemin: " << ch2_BellmanFord.coutTotal << endl;
					}
					else
						cout << "Pas de chemin trouve !" << endl;
					if(ch3_BellmanFord.reussi)
					{
						cout << "Liste des villes du plus court chemin en utilisant niveau de securite: ";
						for (auto itr = ch3_BellmanFord.listeVilles.begin(); itr != ch3_BellmanFord.listeVilles.end(); ++itr)
							if (itr == --ch3_BellmanFord.listeVilles.end())
								cout << *itr;
							else
								cout << *itr << ", ";
						cout << endl << "Niveau de securite total du plus court chemin: " << ch3_BellmanFord.nsTotal << endl;
					}
					else
						cout << "Pas de chemin trouve !" << endl;
					break;
				}
				case 4: //Mesurer le temps d'exécution de Dijkstra.
				{
					cout << "Mesurer le temps d'execution de Dijkstra." << endl;
					startTime = clock();
					for(int i=0; i<100; i++)
						Chemin bench_qt_dikstra = reseau.rechercheCheminDijkstra("Quebec", "Tokyo", true);
					endTime = clock();
					cout << "Temps d'execution: " << endTime - startTime << " microsecondes" << endl;
					break;
				}
				case 5: //Mesurer le temps d'exécution de Bellman-Ford.
				{
					cout << "Mesurer le temps d'execution de Bellman-Ford." << endl;
					startTime = clock();
					for(int i=0; i<100; i++)
						Chemin bench_qt_bellmanford = reseau.rechercheCheminBellManFord("Quebec", "Tokyo", 1);
					endTime = clock();
					cout << "Temps d'execution: " << endTime - startTime << " microsecondes" << endl;
					break;
				}
			}
		}
		catch(exception & e)
		{
			std::cerr << "ERREUR: " << e.what() << std::endl;
		}
	}

	cout << "***Merci et au revoir !***" << endl;
	return 0;
}
