typedef struct 
{
    int id;
    int temp_arriver;
    int heure_debut;
    int temp_execution;
    int temp_sejour;
    int temp_attente;
    int temp_fin;
    int temp_restant;
} Round_Robin;

    // declarer une fonction pour entrer les details du processus qui prend en parametre un tableau de processus  et le nombre
    void entrer_detail_processus(Round_Robin processus[] ,int nombre_processus){
        for (int i = 0; i < nombre_processus ; i++)
        {
            processus[i].id = i+1; //incrementation des processus
             printf("\n entrer l'heure d'arriver et le temps d'execution du processus [%d]\n" , processus[i].id);
             printf("l'heure d'arriver est :\n");
             scanf("%d" , &processus[i].temp_arriver);
             printf("le temps d'excution est:\n");
             scanf("%d" ,&processus[i].temp_execution );
             processus[i].temp_restant = processus[i].temp_execution;// Initialise le temps restant au temps de d'execution initial.
             processus[i].heure_debut = -1;// initialise le temps de debut 
        }
    }
        //afficher les details du processus et calculer leurs temps
    void afficher_detail_processus(Round_Robin processus[] , int nombre_processus , int quantum){
             int somme = 0, compteur = 0, y = nombre_processus;
             int attente_totale = 0, sejour_total = 0;
             //Affiche l'en-tête du tableau.
             printf("\nProcessus id\tHeure d'arrivée\tTemps de burst\tTemps de fin\tTemps de séjour\tTemps d'attente\n");
          
           //La boucle peut donc être lue comme : "Pour i initialisé à 0, 
            //continuer tant que y est différent de 0,  sans modification automatique de i."

            for (int  i=0 ;  y != 0 ;) {
            if (processus[i].temp_restant <= quantum && processus[i].temp_restant > 0)
             {// Vérifie si le temps restant du processus est inférieur ou égal au quantum.
            if (processus[i].heure_debut == -1) {// Si le processus n'a pas encore commencé, initialise l'heure de début.
                processus[i].heure_debut = somme;
            }
            somme += processus[i].temp_restant;//Ajoute le temps restant à la somme totale.
            processus[i].temp_restant = 0;//Définit le temps restant à 0.
            compteur = 1;//Indique que le processus a été traité
           } else if (processus[i].temp_restant > 0) {//Si le temps restant est supérieur à 0, mais supérieur au quantum.
            if (processus[i].heure_debut == -1) {
                processus[i].heure_debut = somme;
            }
            processus[i].temp_restant -= quantum;//Réduit le temps restant par le quantum.
            somme += quantum;
           }
           if (processus[i].temp_restant == 0 && compteur == 1)
            {
              y--; // décrémenter le nombre de processus
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
                if (i == nombre_processus - 1) {//Si c'est le dernier processus, recommence au début.
                        i = 0;
                        //Si l'heure d'arrivée du prochain processus est inférieure ou égale à la somme totale.
                } else if (processus[i + 1].temp_arriver <= somme) {
                     i++;
                 }
                  else {
                     i = 0;//remet i a 0
                    }
                }
                // Afficher le diagramme de Gantt
                        /*printf("\nDiagramme de Gantt:\n|");
                        for (int i = 0; i < nombre_processus; i++) {
                            printf(" P%d |", processus[i].id);
                        }
                        printf("\n");
                        for (int i = 0; i < nombre_processus; i++) {
                            printf("%d\t", processus[i].heure_debut);
                        }
                        printf("%d\n", somme);
                        */
            }

                    void main() {
                        int nombre_processus, quantum;
                        Round_Robin processus[10];

                        printf("Nombre total de processus dans le système: ");
                        scanf("%d", &nombre_processus);

                        entrer_details_processus(processus, nombre_processus);

                        // Accepter le quantum de temps
                        printf("Entrez le quantum de temps pour le processus: ");
                        scanf("%d", &quantum);

                        afficher_details_processus(processus, nombre_processus, quantum);
                    }
                        
                            
   



