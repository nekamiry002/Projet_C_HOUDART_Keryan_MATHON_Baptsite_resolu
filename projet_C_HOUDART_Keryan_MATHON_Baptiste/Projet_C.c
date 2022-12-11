#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2000

int main(void) {
	char non[]="O";
	char reponse[MAX_LEN]="O";

    FILE * fichier = NULL;
    fichier = fopen("Gestionnaire.csv", "a");
    fclose(fichier);

	while(strcmp(reponse, non) == 0) {
		printf("---------------------------------------------\n"
			"BIENVENUE DANS MON GESTIONNAIRE DES NOTES\n"
			"---------------------------------------------\n"
			"1-Enregistrer un contact\n"
			"2-Afficher la liste des enregistrements\n"
			"3-Rechercher un contact ou des contacts\n"
			"4-Supprimer un contact\n"
            "---------------------------------------------");

		int userChoice = 0;
		printf("\nVeuillez choisir une option: ");
		fflush(stdout);
		scanf("%d", &userChoice);

		switch(userChoice){
			case 1: //Entre le nom et le numéro de téléphone du contact
                char nom[MAX_LEN];
				char numero[MAX_LEN];
				fichier = fopen("Gestionnaire.csv", "a");
				if (fichier != NULL){
					printf("Veuillez entrez le nom du contact: ");

					//nom avec espace
					while ((getchar()) != '\n');
                    fflush(stdout);
                    if (fgets(nom, sizeof(nom), stdin) == NULL) {
                        printf("Erreur");
                    }
                    else {
                        nom[strcspn(nom, "\n")] = '\0';
                    }
                    fseek(fichier, 0, SEEK_END);
					fprintf(fichier, "%s ; ", nom);


					printf("Veuillez entrez le numéro du contact: ");
					fflush(stdout);
					scanf("%s", numero);
                    fseek(fichier, 0, SEEK_END);
					fprintf(fichier, " %s \n", numero);

                    printf("Votre enregistrement à été bien pris en compte\n");

					fclose(fichier);
				} else{
					printf("Impossible d'ouvrir le fichier Gestionnaire.csv\n");
				}
				break;

			case 2: //affiche tous les contacts
				int caractereActuel = 0, compteurCaractere = 0;
				fichier = fopen("Gestionnaire.csv", "r");
				if(fichier != NULL){
					printf("\n-------------------------------------------------------------------------\n");
					printf("Nom                           |   Numéro de téléphone          \n");
					printf("-------------------------------------------------------------------------\n");
					do{
						caractereActuel = fgetc(fichier); //lit le caractere
						if (caractereActuel == ';'){
							for(int i = 0; i < 30-compteurCaractere; i++){
								printf(" ");
							}
							printf("|");
						} else if(caractereActuel == '\n'){
							compteurCaractere = -1;
							printf("\n");
						} else {
							printf("%c", caractereActuel);
						}
						compteurCaractere++;
					} while(caractereActuel != EOF);
					fclose(fichier);
				}
				break;

			case 3: //affiche le contact et le numéro que l'utilisateur demande si il y est
				caractereActuel = 0;
				compteurCaractere = 0;
				int test = 1, testMenu = 1;
				char recherche[MAX_LEN];
				char numeroRecherche[MAX_LEN];
				printf("Veuillez entrez le nom du contact: ");

				//nom avec espace
				while ((getchar()) != '\n');
				fflush(stdout);
				if (fgets(recherche, sizeof(recherche), stdin) == NULL) {
						printf("Erreur de lecture");
				}
				else {
					recherche[strcspn(recherche, "\n")] = '\0';
				}

				fichier = fopen("Gestionnaire.csv", "r");
				if (fichier != NULL){
                    int premLettre = 1;
					do{
						caractereActuel = fgetc(fichier);
						if (caractereActuel==recherche[compteurCaractere]){
							compteurCaractere++;
						}else if(caractereActuel == '\n'){
                            premLettre = 1;
                        }
						else if (recherche[compteurCaractere]=='\0' && premLettre == 1){
							if(testMenu){
								printf("\n-------------------------------------------------------------------------\n");
								printf("Nom                            |   Numéro de téléphone          \n");
								printf("-------------------------------------------------------------------------\n");
								testMenu = 0;
							}
							printf(recherche);
							printf("%c", caractereActuel);
							do{
                                caractereActuel = fgetc(fichier);
								if (caractereActuel == ';'){
									printf(" ");
								} else{
									printf("%c", caractereActuel);
								}
                                compteurCaractere++;
                            }while(caractereActuel != ';');
							for(int i = 0; i < 30-compteurCaractere; i++){
								printf(" ");
							}
							printf("|");
							compteurCaractere=0;
							fgets(numeroRecherche, MAX_LEN,fichier);
							printf(numeroRecherche);
							test = 0;
						}
						else{
							compteurCaractere=0;
                            premLettre = 0;
						}

					}while(caractereActuel != EOF);
					if (test){
						printf("Aucune entrée ne correspond à votre saisie\n");
					}
				}
				fclose(fichier);
				break;
			case 4:
				FILE *nouveauFichier;
                nouveauFichier = fopen("UpdateGestionnaire.csv", "w");

                if (fichier == NULL){
                    printf("Erreur de lecture dans Gestionnaire.csv");
                } else if(nouveauFichier == NULL){
                    printf("Erreur de lecture dans UpdateGestionnaire.csv");
                } else{

                    caractereActuel = 0;
                    compteurCaractere = 0;
                    int test = 1, testMenu = 1;
                    char recherche[MAX_LEN];
                    char numeroRecherche[MAX_LEN];
                    printf("Veuillez entrez le nom du contact que vous désirez supprimer: ");

                    //nom avec espace
                    while ((getchar()) != '\n');
                    fflush(stdout);
                    if (fgets(recherche, sizeof(recherche), stdin) == NULL) {
                            printf("Erreur de lecture");
                    }
                    else {
                        recherche[strcspn(recherche, "\n")] = '\0';
                    }

                    fichier = fopen("Gestionnaire.csv", "r");
                    if (fichier != NULL){
                        int premLettre = 1;
                        do{
                            caractereActuel = fgetc(fichier);
                            if (caractereActuel==recherche[compteurCaractere]){
                                compteurCaractere++;
                            }else if(caractereActuel == '\n'){
                                premLettre = 1;
                            }
                            else if (recherche[compteurCaractere]=='\0' && fgetc(fichier)==';' && premLettre == 1){
                                if(testMenu){
                                    printf("\n-------------------------------------------------------------------------\n");
                                    printf("Nom                            |   Numéro de téléphone          \n");
                                    printf("-------------------------------------------------------------------------\n");
                                    testMenu = 0;
                                }
                                printf(recherche);
                                printf("%c", caractereActuel);
                                for(int i = 0; i < 30-compteurCaractere; i++){
                                    printf(" ");
                                }
                                printf("|");
                                compteurCaractere=0;
                                fgets(numeroRecherche, MAX_LEN,fichier);
                                printf(numeroRecherche);
                                test = 0;

                                char DeleteUser;
                                printf("Voulez-vous supprimer cette entrée (O ou N): ");
                                fflush(stdout);
                                scanf("%c", &DeleteUser);

                                if (DeleteUser == 'O' || DeleteUser == 'o'){

                                    fseek(fichier, 0, SEEK_SET);
                                    char ligne[MAX_LEN];
                                    while(fgets(ligne, strlen(recherche)+1, fichier) != NULL){
                                        if (strcmp(ligne, recherche) != 0 ){
                                            fprintf(nouveauFichier, "%s", ligne);
                                            fprintf(nouveauFichier, "%s", fgets(ligne, MAX_LEN, fichier));
                                        } else {
                                            fgets(ligne, MAX_LEN, fichier);
                                        }

									}

									fclose(nouveauFichier);
									fclose(fichier);


									fichier = fopen("Gestionnaire.csv", "w");
									nouveauFichier = fopen("UpdateGestionnaire.csv", "r");

									while(fgets(ligne, MAX_LEN, nouveauFichier) != NULL){
										fputs(ligne, fichier);
									}
									fclose(fichier);
									fclose(nouveauFichier);


                                }
                            }
                            else{
                                compteurCaractere=0;
                                premLettre = 0;
                            }


                        }while(caractereActuel != EOF);
                        if (test){
                            printf("Aucune entrée ne correspond à votre saisie\n");
                        }
                    }

                }
                fclose(fichier);
                fclose(nouveauFichier);
				break;

			default:
				printf("Action invalide, veuillez choisir un nombre entre 1 et 4 (compris)\n");
				break;
		}
		printf("\nVoulez vous continuer (O ou N):");
		fflush(stdout);
		scanf("%s", reponse);
	}
	return 0;
}
