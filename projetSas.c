// Projet Sas: Gestion des reclamations
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define MAX_CHAR 30
// structure qui contient les utilisateurs
struct utilisateurs {
    char identifiant[MAX_CHAR];
    char motPass[MAX_CHAR];
    char role[MAX_CHAR];
    char nomComplet[MAX_CHAR];
}utilisateursList[100];
// initialiser un variable pour counter les utilisateurs
int countUtilisateurs = 0;
//incrementer en les fausse essay de sign in
int countSiFausse = 0; 
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
    // ajouter le premiere utilisateur comme un administrateur
    if (countUtilisateurs == 0) {
        strcpy(utilisateursList[countUtilisateurs].role,"administrateur");
    } else {  // ajouter les autres utilisateur comme des clients
        strcpy(utilisateursList[countUtilisateurs].role,"client");
    }
    // entree le mot de pass
    printf("1.3 Entrer le mot de pass:\n");
    printf("====>");
    // utiliser mot pass temp pour verifier si est valid ou non
    fgets(tempPass,MAX_CHAR,stdin);
    tempPass[strcspn(tempPass,"\n")] = '\0';
    if (validePass(tempPass) == 1) {
       strcpy(utilisateursList[countUtilisateurs].motPass,tempPass);
       countUtilisateurs++;
       system("@cls||clear"); //vider le console
       printf("+++votre compte a ete cree avec succes++++\n");
    } else {
        printf("Entrer un mot pass valid (plus 8 caractere avec des lettres majusculles et miniscule et des chiffres et des lettres special et ne repete pas le nom utilisateur!!)\n");
        signUp();
    }
}
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
// fonction pour afficher le menu par rapport de de role qui est connecter
int menu(int roleNum) {
    int menuChoix;
    if (roleNum == 1) {
        do {
            // Afficher la menu d'adminstrateur
            printf("*****Menu d'administrateur******\n");
            printf("1.Gerer les reclamations.\n");
            printf("2.Gerer les utilisateurs.\n");
            printf("3.generer les statistique.\n");
            printf("4.Attribuer les roles.\n");
            printf("5.Retour au menu principal.\n");
            printf("==> ");
            scanf("%d",&menuChoix);
            getchar();
        } while (menuChoix != 5);
    } else if (roleNum == 3) {
         do
         {
            // Afficher la menu d'adminstrateur
            printf("*****Menu de client******\n");
            printf("1.Soummetre un reclamation.\n");
            printf("2.Modifier un reclamation.\n");
            printf("3.Supprimer un reclamation.\n");
            printf("4.Retour au menu principal.\n");
            printf("==> ");
            scanf("%d",&menuChoix);
            getchar();
         } while (menuChoix != 4);
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
        Sleep(30000);
         }
        //  demander a l'utilisateur de saisir son infos un autre fois
        signIn();
    }
}
int main() {
    int choixMenuPrincipal;
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