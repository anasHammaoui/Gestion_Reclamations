// ************************************************Projet Sas: Gestion des reclamations*******************************************
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define MAX_CHAR 30
// structure qui co ntient les utilisateurs
struct utilisateurs {
    char identifiant[MAX_CHAR];
    char motPass[MAX_CHAR];
    char role[MAX_CHAR];
    char nom[MAX_CHAR];
}utilisateursList[100];

// structure qui contient les reclamations
struct reclamations {
    int id; //id generer aleratoirement
    char motif[MAX_CHAR];
    char description[300];
    char categorie[MAX_CHAR];
    char status[MAX_CHAR]; 
    char date[MAX_CHAR]; //la date d'ajout pour afficher a admins/agents
    time_t dateI;//la date d'ajout en seconde
    char dateRech[MAX_CHAR]; //la date en forme de string en forme de mm/dd/yy-hh:mm::ss
    int estTraiter; //la rec traiter sera prend la valeur 1
    time_t dateTraiter; //la date qui la reclamation a traiter
    time_t tempsTraitement; // combien de temps pour la reclamation a ete traiter
    int client; // index de l'utilisateur qui ajouter la reclamation
    char priorite[MAX_CHAR]; //la prioriter form de string
    int prioriteInt; //niveau de pririter en int "heute= 3, moyenne = 2, basse = 1"
    char noteInterne[100];
} reclamationList[100];

// ****************************************************Gerer les reclamations****************************************

// compteur qui a combien des reclamation exists
int countReclamations = 0;
// compteur des reclamations resouler
int countResolue = 0;
// var pour connaître le client qui ajout la reclamation / utilisateur qui sign in
int indexUtilisateur;
// intializer time de commencer le program pour afficher le rapport quotidien
time_t commenceJournee;
// ++++++++++++++++++++++++Ajouter /  Afficher Reclamations++++++++++++++++++
// fonction qui ajout les reclamations
void ajoutReclamation() {
    srand(time(NULL));
    // generer des id aleatoir
    reclamationList[countReclamations].id = (rand() % 90000)+ 10000;
    // entrer la motif
    printf("1.1 Entrer le motif de reclamation(exemples: produit defectueux, service client, facturation)\n");
    printf("==>");
    fgets(reclamationList[countReclamations].motif,MAX_CHAR,stdin);
    reclamationList[countReclamations].motif[strcspn(reclamationList[countReclamations].motif,"\n")] = '\0';
    // entrer la description de reclamtion  
    printf("1.2 Entrer une description detaillee du probleme rencontre.\n");
    printf("==>");
    fgets(reclamationList[countReclamations].description,300,stdin);
    reclamationList[countReclamations].description[strcspn(reclamationList[countReclamations].description,"\n")] = '\0';
    // entrer la categorie de reclamation  
    printf("1.3 Entrer la categorie de reclamation(produit, service, facturation) .\n");
    printf("==>");
    fgets(reclamationList[countReclamations].categorie,MAX_CHAR,stdin);
    reclamationList[countReclamations].categorie[strcspn(reclamationList[countReclamations].categorie,"\n")] = '\0';
    // status de reclamation en cours par defaut
    strcpy(reclamationList[countReclamations].status,"en cours");
    // date de reclamation prendra automatiqument
    //stocker la date en secondes pour utiliser en modifier pour client
    reclamationList[countReclamations].dateI = time(NULL); 
    // utiliser la date en seconde dans un variable pour utiliser de afficher comme un string
   time_t dateToPrint = reclamationList[countReclamations].dateI; 
   strcpy(reclamationList[countReclamations].date,ctime(&dateToPrint));
   reclamationList[countReclamations].date[strcspn(reclamationList[countReclamations].date,"\n")]='\0';
   
   //utiliser dateToPrint pour ajouter la date sous form de mm/dd/yy-hh:mm:ss en struct pour rechercher en date
   strftime(reclamationList[countReclamations].dateRech,MAX_CHAR,"%x-%X",localtime(&dateToPrint));
   
   //traitement par default est non traiter
   reclamationList[countReclamations].estTraiter =0;
   // ajouter l'index de client qui ajout la reclamation
   reclamationList[countReclamations].client = indexUtilisateur;
       //afficher a le client id de la reclamation pour modifier ou supprimer.
    printf("+++Reclamation Id %d a ete cree avec success+++\n", reclamationList[countReclamations].id);
    countReclamations++;

}
// fonction de afficher par prioriter
void afficherParPrioriter(){
	for (int i =0; i < countReclamations; i++){
		for (int j = i+1; j< countReclamations;j++){
			if (reclamationList[i].prioriteInt < reclamationList[j].prioriteInt){
			struct reclamations temp = reclamationList[i] ;
				reclamationList[i] = reclamationList[j];
				reclamationList[j]= temp;
				}
			}
		}
	}
// fonction qui afficher les reclamation pour les agents et l'administrateur;
void afficherReclamations() {
    // donne la prioriter a les reclamation
    for (int i = 0; i < countReclamations; i++) {
         //ajouter la system de priorite
    if (strstr(reclamationList[i].description, "urgent") != NULL || strstr(reclamationList[i].description, "instant") != NULL|| strstr(reclamationList[i].description,"crise") != NULL) {
    strcpy(	reclamationList[i].priorite,"haute");
    reclamationList[i].prioriteInt = 3;
    	} else if (strstr(reclamationList[i].description, "important") != NULL || strstr(reclamationList[i].description, "principal") != NULL|| strstr(reclamationList[i].description, "prioritaire") != NULL) {
    		 strcpy(	reclamationList[i].priorite,"moyenne");
  		  reclamationList[i].prioriteInt = 2;
    		} else if (strstr(reclamationList[i].description, "optionnel") != NULL || strstr(reclamationList[i].description, "facultatif") != NULL|| strstr(reclamationList[i].description, "secondaire") != NULL) {
    		 strcpy(	reclamationList[i].priorite,"basse");
    		  reclamationList[i].prioriteInt = 1;
    		}
    }
   //afficher les reclamation ordonnee par priorite
    afficherParPrioriter();
   if (countReclamations > 0) {
     for (int i = 0; i < countReclamations; i++) {
        printf("******************Reclamation %d****************\n",i+1);
        printf("+++Id de reclamation: %d\n",reclamationList[i].id);
        printf("+++Client: %s\n",utilisateursList[reclamationList[i].client].nom);
        printf("+++Motif de reclamation: %s\n",reclamationList[i].motif);
        printf("+++Description de reclamation: %s\n",reclamationList[i].description);
        printf("+++Categorie de reclamation: %s\n",reclamationList[i].categorie);
        printf("+++priorite de reclamation: %s\n",reclamationList[i].priorite);
        printf("+++status de reclamation: %s\n",reclamationList[i].status);
        if ( strcmp(reclamationList[i].noteInterne,"")!= 0) {
        printf("+++Notes interne: %s\n",reclamationList[i].noteInterne);
        }
        printf("+++Date de reclamation: %s\n",reclamationList[i].date);
        if(reclamationList[i].estTraiter == 0){
        	printf("+++Traiter ou Non: Non traiter\n");
        	} else {
        		printf("+++Traiter ou Non: traiter avec success\n");
        		}
    }
   } else {
    printf("+++Il y'a aucune reclamation\n");
   }
}
// +++++++++++++++++++++++++Modifier/supprimer/traiter un reclamation++++++++++++++++++

// Fonction de modifier les reclamation pour les agents/ administrateurs
void modifierRec(int id){
    int estModifier = 0; // variable pour verifier si la modification est terminee
    // modifier la reclamation en utilisent l'identifiant
    for(int i = 0; i < countReclamations;i++) {
        if (id == reclamationList[i].id) {
            // entrer la motif
            printf("1.Entrer le motif de reclamation(exemples: produit defectueux, service client, facturation)\n");
            printf("==>");
            fgets(reclamationList[i].motif,MAX_CHAR,stdin);
            reclamationList[i].motif[strcspn(reclamationList[i].motif,"\n")] = '\0';
            // entrer la description de reclamtion  
            printf("2.Entrer une description detaillee du probleme rencontre.\n");
            printf("==>");
            fgets(reclamationList[i].description,300,stdin);
            reclamationList[i].description[strcspn(reclamationList[i].description,"\n")] = '\0';
            // entrer la categorie de reclamation  
            printf("3.Entrer la categorie de reclamation (exemples: produit, service, facturation).\n");
            printf("==>");
            fgets(reclamationList[i].categorie,MAX_CHAR,stdin);
            reclamationList[i].categorie[strcspn(reclamationList[i].categorie,"\n")] = '\0';
            estModifier = 1;
        }
    }
    // print success si la modification est terminer/ non si il n'est pas terminer
    if (estModifier == 1) {
        printf("+++++++La modification est terminer avec success+++++\n");
    } else{
        printf("-------La modification est echoue-----\n");
    }
}
// Fonction de supprimer la reclamation pour les agent et admins
void supprimerRec(int id) {
    int estSupprimer = 0;
    int indexRec;
    // boucle pour trouver l'index de reclamation
    for (int i =0; i < countReclamations; i++) {
        if (id == reclamationList[i].id) {
            indexRec = i;
            estSupprimer = 1;
        }
    }
    // boucle pour supprimer la reclamation
    for (int i = indexRec; i < countReclamations;i++) {
        reclamationList[i] = reclamationList[i+1];
        estSupprimer = 1;
    }
   if (estSupprimer == 1) {
        printf("+++++++La reclamation a ete supprimer avec success+++++\n");
        countReclamations--;
    } else{
        printf("-------La supprission est echoue-----\n");
    }
 
}
// Fonction de modifier les reclamation pour les clients
void modifierRecClient(int id){
  	int estModifier = 0; // variable pour verifier si la modification est terminee
    for (int i =0; i < countReclamations; i++){
    	if (reclamationList[i].id == id){
    		 if (reclamationList[i].client == indexUtilisateur) {
    		 	 time_t dateModif = time(NULL);
    		int nvMoinsP = difftime(dateModif,reclamationList[i].dateI);
    		if (nvMoinsP <  24*3600){
    // modifier la reclamation en utilisent l'identifiant
            // entrer la motif
            printf("1.Entrer le motif de reclamation(exemples: produit defectueux, service client, facturation)\n");
            printf("==>");
            fgets(reclamationList[i].motif,MAX_CHAR,stdin);
            reclamationList[i].motif[strcspn(reclamationList[i].motif,"\n")] = '\0';
            // entrer la description de reclamtion  
            printf("2.Entrer une description detaillee du probleme rencontre.\n");
            printf("==>");
            fgets(reclamationList[i].description,300,stdin);
            reclamationList[i].description[strcspn(reclamationList[i].description,"\n")] = '\0';
            // entrer la categorie de reclamation  
            printf("3.Entrer la categorie de reclamation .\n");
            printf("==>");
            fgets(reclamationList[i].categorie,MAX_CHAR,stdin);
            reclamationList[i].categorie[strcspn(reclamationList[i].categorie,"\n")] = '\0';
            estModifier = 1;
    			}
    		 	}
    		}
    	}
    // print success si la modification est terminer/ non si il n'est pas terminer
    if (estModifier == 1) {
        printf("+++++++La modification est terminer avec success+++++\n");
    } else{
        printf("-------La modification est echoue-----\n");
    }
}

// Fonction de modifier les reclamation pour les clients
void supprimerRecClient(int id){
  	int estSupprimer = 0; // variable pour verifier si supprimer
  	int indexSupp; //index de rec que nous supprimer'
    for (int i =0; i < countReclamations; i++){
    	if (reclamationList[i].id == id){
    		  if (reclamationList[i].client == indexUtilisateur) {
                time_t dateModif = time(NULL);
    		int nvMoinsP = difftime(dateModif,reclamationList[i].dateI);
    		if (nvMoinsP <  24*3600){
			indexSupp = i;
            estSupprimer = 1;
    			}
              }
    		}
    	}
    // print success si la supprission est terminer/ non si il n'est pas terminer
    if (estSupprimer == 1) {
        // boucle pour supprimer la reclamation
    for (int i = indexSupp; i < countReclamations;i++) {
        reclamationList[i] = reclamationList[i+1];
        estSupprimer = 1;
    }
        printf("+++++++La reclamation a ete supprimer avec success+++++\n");
        countReclamations--;
    } else{
        printf("-------La supprission est echoue-----\n");
    }
}
// traiter une reclamation pour les agents et admins
void traiterRec(int id){
    int estTraiter = 0 ; // variable pour verifier si la reclamation est traitee
    // boucle pour traiter la reclamation
    for(int i = 0; i < countReclamations;i++) {
        if (id == reclamationList[i].id) {
            //Entrer la nouvelle status apres traitement reclamation
             printf("1.Entrer la nouvelle status (en cours, resolue, ou fermee).\n");
            printf("==>");
            fgets(reclamationList[i].status,MAX_CHAR,stdin);
            reclamationList[i].status[strcspn(reclamationList[i].status,"\n")] = '\0';
            //Ajouter des notes interne
             printf("2.Entrer des notes internes si vous pouvez.\n");
            printf("==>");
            fgets(reclamationList[i].noteInterne,MAX_CHAR,stdin);
            reclamationList[i].noteInterne[strcspn(reclamationList[i].noteInterne,"\n")] = '\0';
            estTraiter = 1;
            reclamationList[i].estTraiter = estTraiter;
            reclamationList[i].dateTraiter = time(NULL); //date de traitement
            // calclutler combien de temps et prend pour traiter
             reclamationList[i].tempsTraitement = difftime(reclamationList[i].dateTraiter,reclamationList[i].dateI);
            // counter les reclamation resolue
            if (strcmp(reclamationList[i].status,"resolue") == 0) {
                countResolue++;
            }
        }
    }
    // print success si le traitement est terminer/ non si il n'est pas terminer
    if (estTraiter == 1) {
        printf("+++++++L'operation est traiter avec success+++++\n");
    } else{
        printf("-------Le traitement est echoue-----\n");
    }
}
//Rechercher reclamation pour les agent/admins
void rechercher(){
	int menuChoix;
	do{
		int estTrouver = 0;
		printf("1.Rechercher par identifiant.\n");
		printf("2.Rechercher par le nom de client.\n");
		printf("3.Rechercher par date de soumission.\n");
		printf("4.Rechercher par status(en cours, resolu, fermee).\n");
		printf("5.Rechercher par categorie.\n");
		printf("6.Menu principal.\n");
		scanf("%d",&menuChoix);
		getchar();
		if (menuChoix == 1){ // rechercher par id
			int id;
			printf("1.Entrer l'identifiant.\n");
			scanf("%d",&id);
			getchar();
			for (int i = 0; i < countReclamations;i++){
				if(id == reclamationList[i].id){
					   printf("******************Reclamation %d****************\n",i+1);
        printf("+++Le nom de client: %s\n",utilisateursList[reclamationList[i].client].nom);
        printf("+++Id de reclamation: %d\n",reclamationList[i].id);
        printf("+++Motif de reclamation: %s\n",reclamationList[i].motif);
        printf("+++Description de reclamation: %s\n",reclamationList[i].description);
        printf("+++Categorie de reclamation: %s\n",reclamationList[i].categorie);
        printf("+++status de reclamation: %s\n",reclamationList[i].status);
        printf("+++Date de reclamation: %s\n",reclamationList[i].date);
        if(reclamationList[i].estTraiter == 0){
        	printf("+++Traiter ou Non: Non traiter\n");
        	} else {
        		printf("+++Traiter ou Non: traiter avec success\n");
        		}
        		estTrouver = 1;
					}
				}
					if (estTrouver != 1){
						printf("+++ce reclamation n'existe pas+++\n");
					}
			} else if (menuChoix == 2){ // rechercher par nom de client
			char nom[MAX_CHAR];
			printf("1.Entrer le nom de client.\n");
			fgets(nom,MAX_CHAR,stdin);
			nom[strcspn(nom,"\n")] = '\0';
			for (int i = 0; i < countReclamations;i++){
		if(strcmp(utilisateursList[reclamationList[i].client].nom,nom) == 0 ){
					   printf("******************Reclamation %d****************\n",i+1);
		 printf("+++Le nom de client: %s\n",utilisateursList[reclamationList[i].client].nom);
        printf("+++Id de reclamation: %d\n",reclamationList[i].id);
        printf("+++Motif de reclamation: %s\n",reclamationList[i].motif);
        printf("+++Description de reclamation: %s\n",reclamationList[i].description);
        printf("+++Categorie de reclamation: %s\n",reclamationList[i].categorie);
        printf("+++status de reclamation: %s\n",reclamationList[i].status);
        printf("+++Date de reclamation: %s\n",reclamationList[i].date);
        if(reclamationList[i].estTraiter == 0){
        	printf("+++Traiter ou Non: Non traiter\n");
        	} else {
        		printf("+++Traiter ou Non: traiter avec success\n");
        		}
        		estTrouver = 1;
					}
				}
				if (estTrouver != 1){
						printf("+++ce reclamation n'existe pas+++\n");
					}
			} else if (menuChoix == 3){
				char date[MAX_CHAR];
			printf("1.Entrer la date sous forme de mm/dd/yy-hh:mm:ss.\n");
			scanf("%s",&date);
			getchar();
			for (int i = 0; i <countReclamations;i++){
		if(strcmp(reclamationList[i].dateRech,date) == 0)	{
					   printf("******************Reclamation %d****************\n",i+1);
		 printf("+++Le nom de client: %s\n",utilisateursList[reclamationList[i].client].nom);
        printf("+++Id de reclamation: %d\n",reclamationList[i].id);
        printf("+++Motif de reclamation: %s\n",reclamationList[i].motif);
        printf("+++Description de reclamation: %s\n",reclamationList[i].description);
        printf("+++Categorie de reclamation: %s\n",reclamationList[i].categorie);
        printf("+++status de reclamation: %s\n",reclamationList[i].status);
        printf("+++Date de reclamation: %s\n",reclamationList[i].date);
        if(reclamationList[i].estTraiter == 0){
        	printf("+++Traiter ou Non: Non traiter\n");
        	} else {
        		printf("+++Traiter ou Non: traiter avec success\n");
        		}
        		estTrouver = 1;
					}
				}
				if (estTrouver != 1){
						printf("+++ce reclamation n'existe pas+++\n");
					}
				} else if (menuChoix == 4) {
					char status[MAX_CHAR];
					printf("1.Entrer le status(en cours, resolue, fermee).\n");
					fgets(status,MAX_CHAR,stdin);
					status[strcspn(status,"\n")] ='\0';
					for (int i =0; i < countReclamations;i++){
						if(strcmp(reclamationList[i].status,status) == 0){
							 printf("******************Reclamation %d****************\n",i+1);
		 printf("+++Le nom de client: %s\n",utilisateursList[reclamationList[i].client].nom);
        printf("+++Id de reclamation: %d\n",reclamationList[i].id);
        printf("+++Motif de reclamation: %s\n",reclamationList[i].motif);
        printf("+++Description de reclamation: %s\n",reclamationList[i].description);
        printf("+++Categorie de reclamation: %s\n",reclamationList[i].categorie);
        printf("+++status de reclamation: %s\n",reclamationList[i].status);
        printf("+++Date de reclamation: %s\n",reclamationList[i].date);
        if(reclamationList[i].estTraiter == 0){
        	printf("+++Traiter ou Non: Non traiter\n");
        	} else {
        		printf("+++Traiter ou Non: traiter avec success\n");
        		}
        		estTrouver = 1;
					}
				}
				if (estTrouver != 1){
						printf("+++ce reclamation n'existe pas+++\n");
						}
					}else if (menuChoix == 5) {
					char categorie[MAX_CHAR];
					printf("1.Entrer la categorie pour rechercher(produit, service, facturation).\n");
					fgets(categorie,MAX_CHAR,stdin);
					categorie[strcspn(categorie,"\n")] ='\0';
					for (int i =0; i < countReclamations;i++){
						if(strcmp(reclamationList[i].categorie,categorie) == 0){
							 printf("******************Reclamation %d****************\n",i+1);
		 printf("+++Le nom de client: %s\n",utilisateursList[reclamationList[i].client].nom);
        printf("+++Id de reclamation: %d\n",reclamationList[i].id);
        printf("+++Motif de reclamation: %s\n",reclamationList[i].motif);
        printf("+++Description de reclamation: %s\n",reclamationList[i].description);
        printf("+++Categorie de reclamation: %s\n",reclamationList[i].categorie);
        printf("+++status de reclamation: %s\n",reclamationList[i].status);
        printf("+++Date de reclamation: %s\n",reclamationList[i].date);
        if(reclamationList[i].estTraiter == 0){
        	printf("+++Traiter ou Non: Non traiter\n");
        	} else {
        		printf("+++Traiter ou Non: traiter avec success\n");
        		}
        		estTrouver = 1;
					}
				}
				if (estTrouver != 1){
						printf("+++ce reclamation n'existe pas+++\n");
						}
					}	
		} while (menuChoix != 6);
	} 
//****************************************************Statistiques et Rapports**********************************************
void StatsReports() {
    int menuChoix;
    do {
        printf("1.Afficher le nombre total de reclamations.\n");
        printf("2.Afficher le taux de resolution des reclamations\n");
        printf("3.Calculer le delai moyen de traitement des reclamations\n");
        printf("4.Rapport journalier\n");
        printf("5.Retour au menu principal.\n");
        printf("==>");
        scanf("%d",&menuChoix);
        getchar();
        if (menuChoix == 1) {
            printf("===>Il y'a %d reclamation en total<==\n",countReclamations); //total reclamations
        } else if (menuChoix == 2) {
            float tauxResolution = ((countResolue*1.0) / (countReclamations*1.0)) * 100;
            printf("===>Le taux de resolution des reclamations est %.2f%% <==\n",tauxResolution); //total reclamations resolue par rapport a total reclamations
        } else if (menuChoix == 3) {
            int tousDateTraitement = 0; //variable qui contient la somme de temps pour traiter tous les reclmations
            int reclamationsTraiter = 0; //les reclamation qui traiter
            // boucle pour calculer la somme
            for (int i = 0; i < countReclamations; i++) {
                if (reclamationList[i].estTraiter == 1) {
                    tousDateTraitement += reclamationList[i].tempsTraitement;
                    reclamationsTraiter++;
                }
            }
            // la moyenne de temps pour traiter un reclamation en secondes
            int moyenneTempsTraiter = (tousDateTraitement / reclamationsTraiter);
            // condition pour afficher le temps en fontion de minute et secondes
            int minutes, secondes;
            if (moyenneTempsTraiter >= 60) {
                minutes = moyenneTempsTraiter / 60;
                secondes = moyenneTempsTraiter%60;
                moyenneTempsTraiter /= 60;
            } else {
                secondes = moyenneTempsTraiter;
            }
            printf("===>La moyenne de traiter une reclamation est :%d minutes est %d secondes <==\n",minutes, secondes);
        } else if (menuChoix == 4) {
                time_t dateGenerer = time(NULL); //date d'essay pour generer le rapport
                int si24h  = difftime(dateGenerer,commenceJournee); //combien temps entre l debut de journee et la date de generation
                if (si24h > 24*3600) { 
                    FILE *stats = fopen("stats.txt","w");
                time_t dateStats = time(NULL);
            float tauxResolution = ((countResolue*1.0) / (countReclamations*1.0)) * 100; //multipler int * 1.0 pour changer int to float
               fprintf(stats,"******%s*******\n",ctime(&dateStats));
               fprintf(stats,"+++++Nous avons %d Reclamations en total++++\n",countReclamations);
               fprintf(stats,"===>Le taux de resolution des reclamations est %.2f%% <==\n",tauxResolution);
            fprintf(stats,"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            fclose(stats);
            printf("++++++Le rapport a ete generer avec success++++\n");
            commenceJournee = time(NULL); //commencer la journee avec la date de generation de rapport
                } else {
                    printf("++++++++Attender la journee pour terminer et essayer un autre fois+++++++\n");
                }
        }
    } while (menuChoix != 5);
}
// **************************************************Gerer les utilisateurs**************************************************
// initialiser un variable pour counter les utilisateurs
int countUtilisateurs = 1; // nous commencons avec 1 car nous avon un administrateur par default

//incrementer en les fausse essay de sign in
int countSiFausse = 0; 

// -----------------------------------------------Partie Sign Up/ validation motpass-----------------------------

// fonction de validation de motPass
int validePass(char motPass[]) {
    // verifier si les quatre type de caracteres est exist
    int siMaj = 0, siMin = 0, siChiff = 0, siSpec = 0, nomEti = 1, pasNom = 1;

    // boucle pour verifier les caracteres
    for (int i =0; i < strlen(motPass);i++) {
        if (motPass[i] >= 65 &&motPass[i] <= 90 ) {
          siMaj = 1;
        } else if (motPass[i] >= 97 && motPass[i] <= 122){
            siMin =1;
        } else if (motPass[i] >= 48 && motPass[i] <= 57) {
            siChiff = 1;
        } else if((motPass[i] >= 33 && motPass[i] <= 47) || (motPass[i] >= 58 &&motPass[i] <= 64) ||( motPass[i] >= 91 &&motPass[i] <= 96) || (motPass[i] >= 123 &&motPass[i] <= 126)) {
            siSpec = 1;
        }
    }
    // verifier si le mot pass contient le nom de utilisateurs
    if (strstr(motPass,utilisateursList[countUtilisateurs].nom) != NULL) { // fonciton qui verifier si string contient un substring
        pasNom = 0;
    }
    // verifier si le mot de pass == le nom utilisateur
    if (strcmp(motPass,utilisateursList[countUtilisateurs].identifiant) == 0) {
        nomEti = 0;
    }

     // la somme des 6 somme de caracteres
    int verifierPass = siMaj + siMin+ siChiff +siSpec+ nomEti+ pasNom;
    if (strlen(motPass) >= 8 && verifierPass == 6) {
        return 1;
    } else {
        return 0;
    }
}

// Sign up fonction pour inscription
void signUp(){
    char tempPass[MAX_CHAR], tempIdentif[MAX_CHAR];
        // entree de l'identifiant
    printf("1.1 Entrer un identifiants:\n");
    printf("====>");
    fgets(tempIdentif,MAX_CHAR,stdin);
    // supprimer la routeur a la ligne de la chaine de caractere
    tempIdentif[strcspn(tempIdentif,"\n")] = '\0'; 
    // verifier si l'identifiant est deja exister
    int estExist = 0;
    for (int i=0; i < countUtilisateurs; i++) {
        if (strcmp(utilisateursList[i].identifiant,tempIdentif) == 0) {
            estExist = 1;
        }
    }
    // la condition de verification
    if (estExist == 0) {
        strcpy(utilisateursList[countUtilisateurs].identifiant,tempIdentif);
    } else {
        printf("++++Ce identifient est deje exist , utiliser un autre identifiant+++\n");
        signUp(); //recaller la fonction de sign up
        return; // pour terminer la recursion
    }
    // entree le nom complet
    printf("1.2 Entrer votre nom:\n");
    printf("====>");
    fgets(utilisateursList[countUtilisateurs].nom,MAX_CHAR,stdin);
    // supprimer la routeur a la ligne de la chaine de caractere
    utilisateursList[countUtilisateurs].nom[strcspn(utilisateursList[countUtilisateurs].nom,"\n")] = '\0';
    strcpy(utilisateursList[countUtilisateurs].role,"client");

     // entree le mot de pass
    printf("1.3 Entrer le mot de pass:\n");
    printf("====>");

    // utiliser mot pass temp pour verifier si est valid ou non
    fgets(tempPass,MAX_CHAR,stdin);
    tempPass[strcspn(tempPass,"\n")] = '\0';
    if (validePass(tempPass) == 1) { //valider si le mot pass est valide
       strcpy(utilisateursList[countUtilisateurs].motPass,tempPass);
       countUtilisateurs++;
       system("@cls||clear"); //vider le console
       printf("+++votre compte a ete cree avec succes++++\n");
    } else {
        system("@cls||clear");
        printf("Entrer un mot pass valid (plus 8 caractere avec des lettres majusculles et miniscule et des chiffres et des lettres special et ne repete pas le nom utilisateur et ne contient pas votre nom!!)\n");
        signUp();
    }
   
}

// --------------------------------------verifier role/changerRole/Afficher utilisateur/Menu/sign in--------------------------

// fonction pour verifier quel est le role qui connecter
int verifierRole(int indexRole) {
    if (strcmp(utilisateursList[indexRole].role,"administrateur") == 0) {
        return 1;
    } else if (strcmp(utilisateursList[indexRole].role,"agent de reclamation") == 0) {
        return 2;
    } else if (strcmp(utilisateursList[indexRole].role,"client") == 0) {
        return 3;
    } else {
        return -1;
    }
}

// fonction pour changer les roles d'utilisateurs par admin
void changerRole() {
    // stocker les inputs d'admin
    char identif[MAX_CHAR], nvRole[MAX_CHAR];
    printf("5.1 Entrer l'identifiant que vous veuillez changer sa role: ");
    fgets(identif,MAX_CHAR,stdin);
    identif[strcspn(identif,"\n")] = '\0';
    printf("5.2 Entrer la nouvelle role qui'il sera prend(client, agent de reclamation, administrateur): ");
    fgets(nvRole,MAX_CHAR,stdin);
    nvRole[strcspn(nvRole,"\n")] = '\0';
    // variable qui verifier si cette utilisateur est change ou non
    int estChange = 0;
    // boucle pour rechercher si utilisateur est exist si oui il change sa role
    for (int i = 0; i < countUtilisateurs;i++) {
        if (strcmp(utilisateursList[i].identifiant,identif) == 0) {
            // donne ce identifiant le nouveau role
            strcpy(utilisateursList[i].role,nvRole);
            estChange = 1;
        }
    }
    // afficher a l'admin si le role est change ou non
    if (estChange == 1) {
        printf("++++++Le role est change avec success+++++\n");
    } else {
        printf("++++++ce identifiant n'existe pas+++++\n");
    }
}
// afficher les roles
void afficherUtilisateurs(){
    for(int i =0; i < countUtilisateurs; i++) {
        printf("********Utilisateur %d**********\n",i+1);
        printf("--Nom complet: %s--\n",utilisateursList[i].nom);
        printf("--Identifiant: %s--\n",utilisateursList[i].identifiant);
        printf("--Role: %s--\n",utilisateursList[i].role);
        printf("--Mot pass: %s--\n",utilisateursList[i].motPass);
    }
}
// fonction pour afficher le menu par rapport de de role qui est connecter
void menu(int roleNum) {
    int menuChoix,subMenuChoix;
    if (roleNum == 1) {
        do {// Afficher la menu d'adminstrateur
        int smRecId; //supprimer ou modifier un reclamation variable
        int idTraiter; //identifiant pour traiter
            printf("*****Menu d'administrateur******\n");
            printf("1.Afficher la liste des reclamations.\n");
            printf("2.Modifier ou supprimer une reclamation.\n");
            printf("3.Traiter une reclamation.\n");
            printf("4.Rechercher une reclamation.\n");
            printf("5.Gerer les utilisateurs.\n");
            printf("6.Statistiques et rapports.\n");
            printf("7.Retour au menu principal.\n");
            printf("==> ");
            scanf("%d",&menuChoix);
            getchar();
            switch (menuChoix){
                case 1:
                    system("@cls||clear");
                    afficherReclamations();
                break;
                case 2:
                    printf("1.Modifier un reclamation\n");
                    printf("2.Supprimer un reclamation\n");
                    scanf("%d",&subMenuChoix);
                    getchar();
                        if (subMenuChoix == 1) {
                            printf("1.Entrer l'identifiant que vous veuiller modifier: ");
                            scanf("%d",&smRecId);
                            getchar();
                            system("@cls||clear");
                            modifierRec(smRecId);
                        } else if (subMenuChoix ==2) {
                             printf("2.Entrer l'identifiant que vous veuiller supprimer: ");
                            scanf("%d",&smRecId);
                            getchar();
                            system("@cls||clear");
                            supprimerRec(smRecId);
                        };
                    break;
                    case 3:
                        printf("1.Entrer l'identifiant que vous veuiller traiter: ");
                        scanf("%d",&idTraiter);
                        getchar();
                        traiterRec(idTraiter);
                        break;
                        case 4:
                        rechercher();
                        break;
                case 5:
                    printf("1.Afficher les utilisateurs.\n");
                    printf("2.Changes le role d'un utilisateur.\n");
                    scanf("%d",&subMenuChoix);
                    getchar();
                    if (subMenuChoix == 1) {
                    system("@cls||clear");
                    afficherUtilisateurs();
                    } else if (subMenuChoix ==2) {
                    system("@cls||clear");
                    changerRole();
                    }
                break;
                case 6:
                system("@cls||clear");
                StatsReports();
                break;
                
            }           
        } while (menuChoix != 7);
    } else if (roleNum == 2) {
       do {// Afficher la menu d'agent de reclamation
        int smRecId; //supprimer ou modifier un reclamation variable
        int idTraiter; //identifiant pour traiter
            printf("*****Menu d'agent de reclamation******\n");
            printf("1.Afficher la liste des reclamations.\n");
            printf("2.Modifier ou supprimer une reclamation.\n");
            printf("3.Traiter une reclamation.\n");
            printf("4.Rechercher une reclamation.\n");
            printf("5.Retour au menu principal.\n");
            printf("==> ");
            scanf("%d",&menuChoix);
            getchar();
            switch (menuChoix){
                case 1:
                system("@cls||clear");
                afficherReclamations();
                break;
                case 2:
                    printf("1.Modifier un reclamation\n");
                    printf("2.Supprimer un reclamation\n");
                    scanf("%d",&subMenuChoix);
                    getchar();
                        if (subMenuChoix == 1) {
                            printf("1.Entrer l'identifiant que vous veuiller modifier: ");
                            scanf("%d",&smRecId);
                            getchar();
                            system("@cls||clear");
                            modifierRec(smRecId);
                        } else if (subMenuChoix ==2) {
                             printf("2.Entrer l'identifiant que vous veuiller supprimer: ");
                            scanf("%d",&smRecId);
                            getchar();
                            system("@cls||clear");
                            supprimerRec(smRecId);
                        };
                    break;
                    case 3:
                        printf("1.Entrer l'identifiant que vous veuiller traiter: ");
                        scanf("%d",&idTraiter);
                        getchar();
                        traiterRec(idTraiter);
                        break;
                    case 4:
                        system("@cls||clear");
                        rechercher();
                        break;
            }     
       } while (menuChoix != 5);
    } else if (roleNum == 3) {
         do
         {
            // Afficher la menu de client
             int smRecId; //supprimer ou modifier un reclamation variable
            printf("*****Menu de client******\n");
            printf("1.Ajouter une reclamation.\n");
            printf("2.Modifier ou supprimer une reclamation.\n");
            printf("3.Retour au menu principal.\n");
            printf("==> ");
            scanf("%d",&menuChoix);
            getchar();
             switch (menuChoix) {
                case 1:
                system("@cls||clear");
                ajoutReclamation();
                break;
                case 2:
                    printf("1.Modifier un reclamation\n");
                    printf("2.Supprimer un reclamation\n");
                    scanf("%d",&subMenuChoix);
                    getchar();
                        if (subMenuChoix == 1) {
                            printf("1.Entrer l'identifiant que vous veuiller modifier: ");
                            scanf("%d",&smRecId);
                            getchar();
                            system("@cls||clear");
                           modifierRecClient(smRecId);
                        } else if (subMenuChoix ==2) {
                             printf("2.Entrer l'identifiant que vous veuiller supprimer: ");
                            scanf("%d",&smRecId);
                            getchar();
                            system("@cls||clear");
                            supprimerRecClient(smRecId);
                        };
                    break;
            }
         } while (menuChoix != 3);
    } else if (roleNum == -1){
    	printf("--Ce role n'existe pas veuillez contacter l'administrateur pour resolver votre problem\n");
    	}
}
// Sign in fonction pour connecter a l'application
void signIn(){
    char identifiant[MAX_CHAR], motPass[MAX_CHAR];
     // entree de l'identifiant
    printf("2.1 Entrer votre identifiants:\n");
    printf("====>");
    fgets(identifiant,MAX_CHAR,stdin);
    identifiant[strcspn(identifiant,"\n")] = '\0';

     // entree le mot de pass
    printf("2.1 Entrer votre mot de pass:\n");
    printf("====>");
    fgets(motPass,MAX_CHAR,stdin);
    motPass[strcspn(motPass,"\n")] = '\0';

    // verifier si l'utilisateur est exist
    int vrai = 0;
    for (int i = 0; i < countUtilisateurs; i++) {
        if (strcmp(utilisateursList[i].identifiant, identifiant) == 0 && strcmp(utilisateursList[i].motPass, motPass) == 0) {
            vrai  =1;
            indexUtilisateur = i; //ajouter l'index de client qui est log in maintenant
        } 
    }

    // sign in si les infos sont correct, et repeter si il sont fausse
    if (vrai == 1) {
        system("@cls||clear");
        printf("+++Vous avez sign in avec succes+++\n");
        // afficher le menu par rapport a l'utilisateur qui est connnecter
        menu(verifierRole(indexUtilisateur));
        countSiFausse = 0;

    } else {
        system("@cls||clear");
        printf("+++veuillez verifier votre information+++\n");
        countSiFausse++;
        // verouiller l'input pour 30 second avant saisir un autre fois
         if (countSiFausse > 3) {
            printf("!!!!sytstem verouiller est activer attender 30 seconde est essaye un autre fois!!!\n");
        Sleep(30000);
        countSiFausse = 0;
         }
        //  demander a l'utilisateur de saisir son infos un autre fois
        signIn();
    }
}

int main() {
    commenceJournee = time(NULL);
    int choixMenuPrincipal;
    // ajouter le premiere utilisateur comme un administrateur par default
        strcpy(utilisateursList[0].identifiant,"admin123");
        strcpy(utilisateursList[0].role,"administrateur");
        strcpy(utilisateursList[0].nom,"owner");
        strcpy(utilisateursList[0].motPass,"Admin@2024");

    do {
         // Afficher la menu principal
            printf("*****Menu Principal******\n");
            printf("1.Sign up.\n");
            printf("2.Sign in.\n");
            printf("3.Quitter.\n");
            printf("==> ");
            scanf("%d",&choixMenuPrincipal);
            getchar();
            if (choixMenuPrincipal == 1) {
                system("@cls||clear");
                signUp();
            } else if (choixMenuPrincipal == 2) {
                system("@cls||clear");
                signIn();
            }
    } while (choixMenuPrincipal != 3);
}