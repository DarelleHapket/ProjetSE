
//structure de donnes pour representer le processus et un tableau pour stocker plusieur processus
#include <stdio.h>

#define MAX_PROCESSUS 100

typedef struct {
    int id_processus;      // Identifiant du processus
    int temps_arrivee;     // Temps d'arrivée
    int temps_execution;    // Temps d'exécution
    int temps_attente;      // Temps d'attente
    int temps_fin;          // Temps de fin
} Processus;


//tableau pour stocker plusieurs processus
Processus processus[MAX_PROCESSUS];
int nombre_processus = 0; // Nombre de processus ajoutés

