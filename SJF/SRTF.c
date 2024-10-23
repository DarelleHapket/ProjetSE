#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct SRTF {
    int ID;                // Identifiant du processus
    int temp_debut;       // Temps de début
    int temp_execution;   // Temps d'exécution
};

// Fonction pour calculer les temps moyens d'attente et de séjour
void TempsMoyenTotal(struct SRTF proc[], int n) {
    int temp_attente[n], temp_sejour[n], temp_fin[n]; // Tableaux pour stocker les temps d'attente, de séjour et de fin
    int remaining_temp[n]; // Temps d'exécution restant pour chaque processus

    // Initialiser les temps
    for (int i = 0; i < n; i++) {
        remaining_temp[i] = proc[i].temp_execution;
        temp_attente[i] = 0;
        temp_sejour[i] = 0;
        temp_fin[i] = 0; // Initialiser le temps de fin
    }

    int compte = 0, current_time = 0; // Compteur de processus terminés et temps actuel

    // Continue jusqu'à ce que tous les processus soient terminés
    while (compte < n) {
        int idx = -1;
        int min_remaining_temp = INT_MAX; // Temps d'exécution restant minimum
        //INT_MAX est une constante définie dans la bibliothèque limits.h. 
        /*Elle représente la valeur maximale qu'un type int peut avoir sur la plateforme donnée./*/

        // Trouver le processus avec le temps d'exécution restant le plus court qui est prêt à s'exécuter
        for (int i = 0; i < n; i++) {
            if (proc[i].temp_debut <= current_time && remaining_temp[i] > 0 && remaining_temp[i] < min_remaining_temp) {
                min_remaining_temp = remaining_temp[i];
                idx = i; // Index du processus choisi
            }
        }

        if (idx != -1) {
            remaining_temp[idx]--; // Exécuter le processus choisi
            current_time++; // Incrémenter le temps actuel

            // Si le processus est terminé
            if (remaining_temp[idx] == 0) {
                temp_fin[idx] = current_time; // Enregistrer le temps de fin
                temp_sejour[idx] = current_time - proc[idx].temp_debut; // Calculer le temps de séjour
                temp_attente[idx] = temp_sejour[idx] - proc[idx].temp_execution; // Calculer le temps d'attente
                compte++; // Incrémenter le compteur de processus terminés
            }
        } else {
            current_time++; // Si aucun processus n'est prêt, incrémenter le temps actuel
        }
    }

    // Afficher les résultats
    printf("Processus ID\tTemps_debut\t Temp_execution\t Temp_attente\tTemp_sejour\tTemp_fin\n");
    for (int i = 0; i < n; i++) {
        //printf("\t%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\n", 
          printf("\t%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\n", 
               proc[i].ID, 
               proc[i].temp_debut, 
               proc[i].temp_execution,
               temp_attente[i], 
               temp_sejour[i], 
               temp_fin[i]); // Afficher le temps de fin du processus
    }

    // Afficher les temps moyens d'attente et de séjour
    float moyenne_attente = 0, moyenne_sejour = 0;
    for (int i = 0; i < n; i++) {
        moyenne_attente += temp_attente[i];
        moyenne_sejour += temp_sejour[i];
    }
    printf("\nTemps d'attente moyen: %.2f\n", moyenne_attente / n);
    printf("Temps de séjour moyen: %.2f\n", moyenne_sejour / n);
}

// Fonction principale
int main() {
    // Définir les processus avec leurs ID, temps de début et temps d'exécution
    struct SRTF proc[] = { {1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5} };
    int n = sizeof(proc) / sizeof(proc[0]); // Nombre de processus

    // Appeler la fonction pour calculer les temps moyens
    TempsMoyenTotal(proc, n);
    return 0;
}
