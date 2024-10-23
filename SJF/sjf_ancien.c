#include <stdio.h>
//structure pour représenter un processus avec 
  struct Processuss {
    int id;            // ID du processus
    int temp_execution;    // Temps d'exécution
    int temp_arriver;  // Temps d'arrivée
};


    /*Déclare une fonction qui prend un tableau de processus et leur nombre pour
     calculer et afficher les temps d'attente et de sejour et tableau pour stoker le temps d'attente ...*/
    void findAverageTime(struct Processuss proc[], int n) {

         int temp_attente[n], temp_sejour[n], temp_fin[n];
         int total_temp_attente = 0, total_temp_sejour = 0;

    // parcourir et tableau et trier les processus par temps d'arriver et par temps d'execution si leurs temps d'arriver sont egales

      for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].temp_arriver > proc[j].temp_arriver|| 
               (proc[i].temp_arriver == proc[j].temp_arriver && proc[i].temp_execution > proc[j].temp_execution)) {
                struct Processuss temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
        int compte= 0, current_time = 0;//Compte le nombre de processus terminés. et Suit le temps actuel du système.

            while (compte < n) {                      //continuer tant que les processus ne sont pas terminé
                int idx = -1;                                      //Variable pour stocker l'indice du processus à exécuter.
                for (int i = 0; i < n; i++) { //
                if (proc[i].temp_arriver <= current_time && (idx == -1 || proc[i].temp_execution < proc[idx].temp_execution) &&
                temp_attente [i] == 0) {     /*Parcourt tous les processus pour trouver celui avec le temps d'exécution 
                le plus court parmi ceux qui sont déjà arrivés (arrival_time <= current_time).*/
                idx = i;         //Met à jour l'indice du processus à exécuter si un processus plus court est trouvé.
                }
                    if (idx == -1) {       // Si aucun processus n'est disponible pour exécution, le temps actuel est incrémenté de 1.

                       current_time++;        //Passe à l'itération suivante de la boucle while.
                         continue;
                    }

                }

                        temp_attente [idx] = current_time - proc[idx].temp_arriver; //Calcule le temps d'attente pour le processus choisi.
                            current_time += proc[idx].temp_execution; //Incrémente le temps actuel de la durée d'exécution du processus.
                            temp_fin[idx] = current_time; //  Enregistre le temps de fin pour le processus.
                            //temp_attente=temp_sejour-temp_d'execution
                            temp_sejour[idx] = temp_attente[idx] + proc[idx].temp_execution; // Calcule le temps de sejour en ajoutant le temps d'attente et le temps d'exécution
                            compte++; // Incrémente le compteur de processus terminés.

                        /*printf : Affiche les en-têtes des colonnes pour les résultats.
                        Boucle for : Affiche les informations pour chaque processus, incluant son ID, temps d'exécution, temps d'arrivée,
                        temps d'attente, temps de retour et temps de fin. Accumulateurs : Ajoute les temps d'attente et de sejour à 
                        leurs totaux respectifs*/
                        printf("Processus ID\ttemp d'éxécution\ttemp d'arriver\ttemp d'attente\ttemp de sejour\ttemp de fin\n");
                            for (int i = 0; i < n; i++) {
                                 printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                                 proc[i].id, proc[i].temp_execution, proc[i].temp_arriver, temp_attente[i], temp_sejour[i], temp_fin[i]);
                                 total_temp_attente+= temp_attente[i];
                                 total_temp_sejour += temp_sejour[i];
                                }
                                //Affiche les temps moyens d'attente et de sejour en format décimal.
                                    printf("\nTemps d'attente moyen: %.2f\n", (float)total_temp_attente / n);
                                     printf("total temp de sejour: %.2f\n", (float)total_temp_sejour / n);
                                     
int main() {
    struct Processuss proc[] = { {1, 6, 2}, {2, 8, 0}, {3, 7, 1}, {4, 3, 3} };
    int n = sizeof(proc) / sizeof(proc[0]);

    findAverageTime(proc, n);
    return 0;
}

     }
            }
