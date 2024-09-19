// Projet Sas: Gestion des reclamations
#include <stdio.h>
#include <string.h>
#define MAX_CHAR 30
// structure qui contient les utilisateurs
struct utilisateurs {
    char identifiant[MAX_CHAR];
    char motPass[MAX_CHAR];
    char role[MAX_CHAR];
}utilisateursList[100];
// initialiser un variable pour counter les utilisateurs
int countUtilisateurs = 0;
// fonction de validation de motPass
int validePass(char motPass[]) {
    // verifier si les quatre type de caracteres est exist
    int siMaj = 0, siMin = 0, siChiff = 0, siSpec = 0;
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
     // la somme des quatre somme de caracteres
    int verifierPass = siMaj + siMin+ siChiff +siSpec;
    if (strlen(motPass) >= 8 && verifierPass == 4) {
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
    // entree le mot de pass
    printf("1.2 Entrer le mot de pass:\n");
    printf("====>");
    // utiliser mot pass temp pour verifier si est valid ou non
    fgets(tempPass,MAX_CHAR,stdin);
    tempPass[strcspn(tempPass,"\n")] = '\0';
    if (validePass(tempPass) == 1) {
       strcpy(utilisateursList[countUtilisateurs].motPass,tempPass);
       countUtilisateurs++;
       printf("+++votre compte a ete cree avec succes++++\n");
    } else {
        printf("Entrer un mot pass valid (plus 8 caractere avec des lettres majusculles et miniscule et des chiffres et des lettres special!!)\n");
        signUp();
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
        } 
    }
    // sign in si les infos sont correct, et repeter si il sont fausse
    if (vrai == 1) {
        printf("+++Vous avez sign in avec succes+++\n");
    } else {
        printf("+++veuillez verifier votre information+++\n");
        signIn();
    }
}
int main() {
    int choixMenuPrincipal, choixMenuSecond;
    do {
        // Afficher la menu principal
        printf("****************MENU***************\n");
        printf("1.Gestion des utilisatuers.\n");
        printf("2.Gerer les roles des utilisateurs.\n");
        printf("3.Gestion des reclamations.\n");
        printf("4.Quitter.\n");
        printf("==> ");
        scanf("%d",&choixMenuPrincipal);
        getchar(); // utiliser pour fixer la problem d'eviter le le scan suivant
        printf("****************FIN***************\n");
        switch (choixMenuPrincipal) {
            case 1:
            // menu de gestion des utilisateurs
            printf("*****Gestion des utilisateurs******\n");
            printf("1.Sign up.\n");
            printf("2.Sign in.\n");
            printf("3.Retour au menu principal.\n");
            printf("==> ");
            scanf("%d",&choixMenuSecond);
            getchar();
            if (choixMenuSecond == 1) {
                signUp();
            } else if (choixMenuSecond == 2) {
                signIn();
            }
        }
    } while (choixMenuPrincipal != 4);
}