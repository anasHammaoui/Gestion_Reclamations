// ************************************************Projet Sas: Gestion des reclamations*******************************************
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#define MAX_CHAR 30

// ****************************************************Gerer les reclamations****************************************
// structure qui contient les reclamations
struct reclamations {
    int id;
    char motif[MAX_CHAR];
    char description[300];
    char categorie[MAX_CHAR];
    char status[MAX_CHAR];
    char date[MAX_CHAR];
} reclamationList[100];
// compteur qui a combien des reclamation exists
int countReclamations = 0;

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
    printf("1.3 Entrer la categorie de reclamation .\n");
    printf("==>");
    fgets(reclamationList[countReclamations].categorie,MAX_CHAR,stdin);
    reclamationList[countReclamations].categorie[strcspn(reclamationList[countReclamations].categorie,"\n")] = '\0';
    // status de reclamation en cours par defaut
    strcpy(reclamationList[countReclamations].status,"en cours");
    // date de reclamation prendra automatiquement
    time_t autodate;
    autodate = time(NULL);
    strcpy(reclamationList[countReclamations].date,ctime(&autodate));
    countReclamations++;
}
// fonction qui afficher les reclamation pour les agents et l'administrateur;
void afficherReclamations() {
   if (countReclamations > 0) {
     for (int i = 0; i < countReclamations; i++) {
        printf("******************Reclamation %d****************\n",i+1);
        printf("+++Id de reclamation: %d\n",reclamationList[i].id);
        printf("+++Motif de reclamation: %s\n",reclamationList[i].motif);
        printf("+++Description de reclamation: %s\n",reclamationList[i].description);
        printf("+++Categorie de reclamation: %s\n",reclamationList[i].categorie);
        printf("+++status de reclamation: %s\n",reclamationList[i].status);
        printf("+++Date de reclamation: %s\n",reclamationList[i].date);
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
            printf("3.Entrer la categorie de reclamation .\n");
            printf("==>");
            fgets(reclamationList[i].categorie,MAX_CHAR,stdin);
            reclamationList[i].categorie[strcspn(reclamationList[i].categorie,"\n")] = '\0';
            // entrer le status
              printf("4.Entrer le status de reclamation (en cours, resolue, ou fermee).\n");
            printf("==>");
            fgets(reclamationList[i].status,MAX_CHAR,stdin);
            reclamationList[i].status[strcspn(reclamationList[i].status,"\n")] = '\0';
        }
    }
    // print success si la modification est terminer/ non si il n'est pas terminer
    if (estModifier == 1) {
        printf("+++++++La modification est traiter avec success+++++\n");
    } else{
        printf("-------La modification est echoue-----\n");
    }
}
// Fonction de supprimer la reclamation
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
        reclamationList[i].id = reclamationList[i+1].id;
        strcpy(reclamationList[i].motif,reclamationList[i+1].motif);
        strcpy(reclamationList[i].description,reclamationList[i+1].description);
        strcpy(reclamationList[i].categorie,reclamationList[i+1].categorie);
        strcpy(reclamationList[i].status,reclamationList[i+1].status);
        strcpy(reclamationList[i].date,reclamationList[i+1].date);
        estSupprimer = 1;
    }
    if (estSupprimer ==1) {
        printf("----La reclamation a ete supprimer avec succes---\n");
    }
    countReclamations--; //deincrementer les reclamations
}

// traiter une reclamation pour les agents et admins
void traiterRec(int id){
    int estTraiter = 0; // variable pour verifier si la reclamation est traitee
    // boucle pour traiter la reclamation
    for(int i = 0; i < countReclamations;i++) {
        if (id == reclamationList[i].id) {
            //Entrer la nouvelle status apres traitement reclamation
             printf("1.Entrer la nouvelle status (en cours, resolue, ou fermee).\n");
            printf("==>");
            fgets(reclamationList[i].status,MAX_CHAR,stdin);
            reclamationList[i].status[strcspn(reclamationList[i].status,"\n")] = '\0';
        }
    }
    // print success si le traitement est terminer/ non si il n'est pas terminer
    if (estTraiter == 1) {
        printf("+++++++L'operation est traiter avec success+++++\n");
    } else{
        printf("-------Le traitement est echoue-----\n");
    }
}

// **************************************************Gerer les utilisateurs**************************************************

// structure qui co ntient les utilisateurs
struct utilisateurs {
    char identifiant[MAX_CHAR];
    char motPass[MAX_CHAR];
    char role[MAX_CHAR];
    char nomComplet[MAX_CHAR];
}utilisateursList[100];
// initialiser un variable pour counter les utilisateurs
int countUtilisateurs = 1; // nous commencons avec 1 car nous avon un administrateur par default

//incrementer en les fausse essay de sign in
int countSiFausse = 0; 

// -----------------------------------------------Partie Sign Up/ validation motpass-----------------------------

// fonction de validation de motPass
int validePass(char motPass[]) {
    // verifier si les quatre type de caracteres est exist
    int siMaj = 0, siMin = 0, siChiff = 0, siSpec = 0, nomEti = 1;

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

    // verifier si le mot de pass == le nom utilisateur
    if (strcmp(motPass,utilisateursList[countUtilisateurs].identifiant) == 0) {
        nomEti = 0;
    }

     // la somme des quatre somme de caracteres
    int verifierPass = siMaj + siMin+ siChiff +siSpec+ nomEti;
    if (strlen(motPass) >= 8 && verifierPass == 5) {
        return 1;
    } else {
        return 0;
    }
}

// Sign up fonction pour inscription
void signUp(){
    char tempPass[30];
     // ajouter les autres utilisateur comme des clients
        // entree de l'identifiant
    printf("1.1 Entrer un identifiants:\n");
    printf("====>");
    fgets(utilisateursList[countUtilisateurs].identifiant,MAX_CHAR,stdin);
    // supprimer la routeur a la ligne de la chaine de caractere
    utilisateursList[countUtilisateurs].identifiant[strcspn(utilisateursList[countUtilisateurs].identifiant,"\n")] = '\0';

    // entree le nom complet
    printf("1.2 Entrer votre nom complet:\n");
    printf("====>");
    fgets(utilisateursList[countUtilisateurs].nomComplet,MAX_CHAR,stdin);
    // supprimer la routeur a la ligne de la chaine de caractere
    utilisateursList[countUtilisateurs].nomComplet[strcspn(utilisateursList[countUtilisateurs].nomComplet,"\n")] = '\0';
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
        printf("Entrer un mot pass valid (plus 8 caractere avec des lettres majusculles et miniscule et des chiffres et des lettres special et ne repete pas le nom utilisateur!!)\n");
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
    printf("5.2 Entrer la nouvelle role qui'il sera prend: ");
    fgets(nvRole,MAX_CHAR,stdin);
    nvRole[strcspn(nvRole,"\n")] = '\0';
    // variable qui verifier si cette utilisateur est change ou non
    int estChange = 0;
    // boucle pour rechercher is utilisateur est exist si oui il change sa role
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
        printf("--Nom complet: %s--\n",utilisateursList[i].nomComplet);
        printf("--Identifiant: %s--\n",utilisateursList[i].identifiant);
        printf("--Role: %s--\n",utilisateursList[i].role);
        printf("--Mot pass: %s--\n",utilisateursList[i].motPass);
    }
}
// fonction pour afficher le menu par rapport de de role qui est connecter
int menu(int roleNum) {
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
            printf("6.Retour au menu principal.\n");
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
            }           
        } while (menuChoix != 6);
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
            }     
       } while (menuChoix != 5);
    } else if (roleNum == 3) {
         do
         {
            // Afficher la menu de client
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
            }
         } while (menuChoix != 3);
    }
}

// Sign in fonction pour connecter a l'application
void signIn(){
    char identifiant[MAX_CHAR], motPass[MAX_CHAR];
    int indexUtilisateur;
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
            indexUtilisateur = i;
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
    int choixMenuPrincipal;
    // ajouter le premiere utilisateur comme un administrateur par default
        strcpy(utilisateursList[0].identifiant,"admin2024");
        strcpy(utilisateursList[0].role,"administrateur");
        strcpy(utilisateursList[0].nomComplet,"admin projet");
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