#include <stdio.h>

// Structure pour représenter un processus
struct Processuss {
    int id;              // ID du processus
    int temp_execution;  // Temps d'exécution
    int temp_arriver;    // Temps d'arrivée
};

// Fonction pour calculer et afficher les temps d'attente et de séjour
void findAverageTime(struct Processuss proc[], int n) {
    int temp_attente[n], temp_sejour[n], temp_fin[n];
    int total_temp_attente = 0, total_temp_sejour = 0;

    // Trier les processus par temps d'arrivée, et par temps d'exécution si les temps d'arrivée sont les mêmes
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].temp_arriver > proc[j].temp_arriver ||
                (proc[i].temp_arriver == proc[j].temp_arriver && proc[i].temp_execution > proc[j].temp_execution)) {
                struct Processuss temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    int compte = 0, current_time = 0; // Compteur de processus terminés, temps actuel dans le système

    // Tant que tous les processus ne sont pas terminés
    while (compte < n) {
        int idx = -1; // Variable pour stocker l'indice du processus à exécuter
        for (int i = 0; i < n; i++) {
            if (proc[i].temp_arriver <= current_time && (idx == -1 || proc[i].temp_execution < proc[idx].temp_execution) && temp_attente[i] == 0) {
                idx = i; // Mettre à jour l'indice si un processus plus court est trouvé
            }
        }

        if (idx == -1) { // Si aucun processus n'est disponible pour l'exécution
            current_time++; // Incrémenter le temps actuel
            continue;
        }

        temp_attente[idx] = current_time - proc[idx].temp_arriver; // Calculer le temps d'attente
        current_time += proc[idx].temp_execution; // Mettre à jour le temps actuel
        temp_fin[idx] = current_time; // Enregistrer le temps de fin
        temp_sejour[idx] = temp_attente[idx] + proc[idx].temp_execution; // Calculer le temps de séjour
        compte++; // Incrémenter le compteur de processus terminés
    }

    // Afficher les résultats
    printf("Processus ID\tTemps d'exécution\tTemps d'arrivée\tTemps d'attente\tTemps de séjour\tTemps de fin\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t\t%d\t\t%d\t\t%d\t\t%d\n",
            proc[i].id, proc[i].temp_execution, proc[i].temp_arriver, temp_attente[i], temp_sejour[i], temp_fin[i]);
        total_temp_attente += temp_attente[i];
        total_temp_sejour += temp_sejour[i];
    }

    // Afficher les temps moyens d'attente et de séjour
    printf("\nTemps d'attente moyen: %.2f\n", (float)total_temp_attente / n);
    printf("Temps de séjour moyen: %.2f\n", (float)total_temp_sejour / n);
}

int main() {
    struct Processuss proc[] = { {1, 6, 2}, {2, 8, 0}, {3, 7, 1}, {4, 3, 3} };
    int n = sizeof(proc) / sizeof(proc[0]);

    findAverageTime(proc, n);
    return 0;
}

