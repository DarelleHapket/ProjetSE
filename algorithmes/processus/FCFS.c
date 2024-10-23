#include <stdio.h>

struct FCFS {
    int id;
    int temp_arriver;
    int temp_execution;
};

// Fonction pour calculer les temps moyens de séjour et d'attente
void TempMoyen(struct FCFS proc[], int n) {
    int temp_attente[n], temp_sejour[n];
    int completion_time[n];
    
    /* En déclarant int completion_time[n];, on crée un tableau capable de stocker les temps 
       de fin pour n processus. */ 
       
    // Calcul des temps de fin pour chaque processus
    completion_time[0] = proc[0].temp_arriver + proc[0].temp_execution; // temps de fin du premier processus

    for (int i = 1; i < n; i++) {//i=0 car on considere que le premier processus est deja traiter

   /*Vérifier si le temps d'arrivée du processus actuel (proc[i].temp_arriver) est supérieur au 
   temps de fin du processus précédent (completion_time[i - 1]).Si c'est le cas, cela signifie que le
    processus doit attendre jusqu'à son propre temps d'arrivée. 
    On calcule alors son temps de fin comme la somme de son temps d'arrivée et de son temps d'exécution
    et else Si le processus arrive pendant ou après l'exécution du processus précédent, 
    on calcule son temps de fin en ajoutant son temps d'exécution au temps de fin du processus précédent..*/


        if (proc[i].temp_arriver > completion_time[i - 1]) {
            completion_time[i] = proc[i].temp_arriver + proc[i].temp_execution;
        } else {
            completion_time[i] = completion_time[i - 1] + proc[i].temp_execution; // Pour le processus suivant
        }
    }

    // Calcul du temps de séjour et du temps d'attente
    for (int i = 0; i < n; i++) {
        temp_sejour[i] = completion_time[i] - proc[i].temp_arriver; // Temps de séjour = Temps de fin - Temps d'arrivée
        temp_attente[i] = temp_sejour[i] - proc[i].temp_execution; // Temps d'attente = Temps de séjour - Temps d'exécution
    }

    // Affichage des détails des processus et de leurs temps
    printf("ID\tTemps_arriver\tTemps_execution\tTemps_attente\tTemps_sejour\tTemps_fin\n");
    for (int i = 0; i < n; i++) {
         printf("%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\t\t\t\t" "%d\n", 
      
               proc[i].id,
               proc[i].temp_arriver,
               proc[i].temp_execution, 
               temp_attente[i],
               temp_sejour[i],
               completion_time[i]);
    }

    // Calcul et affichage des temps moyens d'attente et de séjour
    float temp_attente_moyen = 0, temp_de_sejour_moyen = 0;
    for (int i = 0; i < n; i++) {
        temp_attente_moyen += temp_attente[i]; // Somme des temps d'attente
        temp_de_sejour_moyen += temp_sejour[i]; // Somme des temps de séjour
    }
    printf("\nTemps d'attente moyen: %.2f\n", temp_attente_moyen / n); // Affichage du temps d'attente moyen
    printf("Temps de séjour moyen: %.2f\n", temp_de_sejour_moyen / n); // Affichage du temps de séjour moyen
}

// Fonction principale
int main() {
    // Définir les processus avec leur ID, temps d'arrivée et temps d'exécution
    struct FCFS proc[] = { {1, 0, 4}, {2, 1, 3}, {3, 2, 5}, {4, 3, 2} };
    int n = sizeof(proc) / sizeof(proc[0]); // Calculer le nombre de processus
    /* sizeof(proc) :  donne la taille totale en octets du tableau proc. sizeof(proc[0]) : 
       donne la taille en octets d'un seul élément du tableau. En divisant la taille totale du tableau 
       par la taille d'un élément, on obtient le nombre d'éléments dans le tableau. */
    
    // Appeler la fonction pour calculer les temps moyens
    TempMoyen(proc, n);
    return 0;
}












    
