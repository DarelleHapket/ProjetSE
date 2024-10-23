#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int temp_arriver;
    int heure_debut;
    int temp_execution;
    int temp_sejour;
    int temp_attente;
    int temp_fin;
    int temp_restant;
} Round_Robin;

// Fonction pour entrer les détails des processus
void entrer_detail_processus(Round_Robin *processus, int nombre_processus) {
    for (int i = 0; i < nombre_processus; i++) {
        processus[i].id = i + 1; // Incrémente l'identifiant du processus
        printf("\nEntrer l'heure d'arrivée et le temps d'exécution du processus [%d]:\n", processus[i].id);

        // Validation de l'entrée pour l'heure d'arrivée
        printf("L'heure d'arrivée : ");
        while (scanf("%d", &processus[i].temp_arriver) != 1 || processus[i].temp_arriver < 0) {
            printf("Entrée invalide. Veuillez entrer un entier non négatif pour l'heure d'arrivée : ");
            while(getchar() != '\n'); // Efface l'entrée invalide
        }

        // Validation de l'entrée pour le temps d'exécution
        printf("Le temps d'exécution : ");
        while (scanf("%d", &processus[i].temp_execution) != 1 || processus[i].temp_execution <= 0) {
            printf("Entrée invalide. Veuillez entrer un entier positif pour le temps d'exécution : ");
            while(getchar() != '\n'); // Efface l'entrée invalide
        }

        processus[i].temp_restant = processus[i].temp_execution; // Initialise le temps restant
        processus[i].heure_debut = -1; // Initialise le temps de début
    }
}

// Fonction pour afficher les détails des processus et calculer leurs temps
void afficher_detail_processus(Round_Robin *processus, int nombre_processus, int quantum) {
    int somme = 0, compteur = 0, y = nombre_processus;
    int attente_totale = 0, sejour_total = 0;

    // Affiche l'en-tête du tableau
    printf("\nProcessus id\tHeure d'arrivée\tTemps d'exécution\tTemps de fin\tTemps de séjour\tTemps d'attente\n");

    // Stockage des heures de début et des IDs pour le diagramme de Gantt
    int gantt_times[10] = {0};
    int gantt_process[10] = {0};
    int gantt_index = 0;

    for (int i = 0; y != 0;) {
        if (processus[i].temp_restant <= quantum && processus[i].temp_restant > 0) {
            if (processus[i].heure_debut == -1) {
                processus[i].heure_debut = somme;
            }
            somme += processus[i].temp_restant;
            processus[i].temp_restant = 0;
            gantt_times[gantt_index] = somme;
            gantt_process[gantt_index++] = processus[i].id;
            compteur = 1;
        } else if (processus[i].temp_restant > 0) {
            if (processus[i].heure_debut == -1) {
                processus[i].heure_debut = somme;
            }
            processus[i].temp_restant -= quantum;
            somme += quantum;
            gantt_times[gantt_index] = somme;
            gantt_process[gantt_index++] = processus[i].id;
        }

        if (processus[i].temp_restant == 0 && compteur == 1) {
            y--;
            processus[i].temp_fin = somme;
            processus[i].temp_sejour = processus[i].temp_fin - processus[i].temp_arriver;
            processus[i].temp_attente = processus[i].temp_sejour - processus[i].temp_execution;

            printf("Processus id[%d]\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                   processus[i].id, processus[i].temp_arriver, processus[i].temp_execution,
                   processus[i].temp_fin, processus[i].temp_sejour, processus[i].temp_attente);
            attente_totale += processus[i].temp_attente;
            sejour_total += processus[i].temp_sejour;
            compteur = 0;
        }

        // Gestion du passage d'un processus à l'autre
        if (i == nombre_processus - 1) {
            i = 0;
        } else if (processus[i + 1].temp_arriver <= somme) {
            i++;
        } else {
            i = 0;
        }
    }

    // Affichage du diagramme de Gantt
    printf("\nDiagramme de Gantt:\n|");
    for (int i = 0; i < gantt_index; i++) {
        printf(" P%d |", gantt_process[i]);
    }
    printf("\n");
    for (int i = 0; i < gantt_index; i++) {
        printf("%d\t", gantt_times[i]);
    }
    printf("%d\n", somme);
}

// Fonction principale
int main() {
    int nombre_processus, quantum;

    // Demande le nombre total de processus
    printf("Nombre total de processus dans le système : ");
    scanf("%d", &nombre_processus);

    // Validation du nombre de processus
    if (nombre_processus <= 0) {
        printf("Erreur : Veuillez entrer un nombre valide de processus (> 0).\n");
        return 1;
    }

    // Allocation dynamique de mémoire pour les processus
    Round_Robin *processus = malloc(nombre_processus * sizeof(Round_Robin));
    if (processus == NULL) {
        printf("Erreur : Échec de l'allocation de mémoire.\n");
        return 1;
    }

    // Appel de la fonction pour entrer les détails des processus
    entrer_detail_processus(processus, nombre_processus);

    // Acceptation du quantum de temps
    printf("Entrez le quantum de temps pour le processus : ");
    while (scanf("%d", &quantum) != 1 || quantum <= 0) {
        printf("Entrée invalide. Veuillez entrer un entier positif pour le quantum de temps : ");
        while(getchar() != '\n'); // Efface l'entrée invalide
    }

    // Ici, vous pouvez appeler la fonction pour afficher les détails et gérer le traitement (non inclus dans cet extrait)
    afficher_detail_processus(processus, nombre_processus, quantum);
    // Libération de la mémoire allouée dynamiquement
    free(processus);
    return 0;
}
