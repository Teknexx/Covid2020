/* Florian TURMEL octobre/novembre/decembre 2020*/
/*Menu en couleurs, fonctions et main*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "Fonctions/typeCovid2020.c"

#define LARGEUR_CONS 120
#define HAUTEUR_CONS 30

void gotoligcol( int lig, int col ){
    COORD mycoord;

    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void centre(char * string){ //centrer un chaine de caractère au milieu de la console (modifier LARGEURF_CONS si la console est plus petite
    int i = 0;
    printf("\n");
    while (i< (LARGEUR_CONS - strlen(string)) / 2){
        printf(" ");
        i++;
    }
    printf("%s",string);
}

void bas_droite(char * string){ //mettre un élément dans le coin a droite
    int i = 0;
    gotoligcol(HAUTEUR_CONS-2,(LARGEUR_CONS - strlen(string)-3));
    printf("%s",string);
}

int afficheMenu(HANDLE hConsole){
    system("cls");
    SetConsoleTextAttribute(hConsole, 16*3+4);
    gotoligcol(1,(LARGEUR_CONS/2-15));printf("*-------------------------------*");
    gotoligcol(2,(LARGEUR_CONS/2-15));printf("|         MENU COVID 19         |");
    gotoligcol(3,(LARGEUR_CONS/2-15));printf("*-------------------------------*");
    SetConsoleTextAttribute(hConsole, 16*0+15);
    gotoligcol(10,9);printf("1 - Afficher la liste des citoyens");
    gotoligcol(11,9);printf("2 - Afficher la liste des lieux de fetes");
    gotoligcol(12,9);printf("3 - Ajouter un citoyen");
    gotoligcol(13,9);printf("4 - Ajouter un lieu de fetes");
    gotoligcol(14,9);printf("5 - Remplir les participants a une fete");
    gotoligcol(15,9);printf("6 - Afficher tous ceux qui ont rencontre un citoyen");
    gotoligcol(16,9);printf("7 - Enregistrer un fichier situation");
    gotoligcol(17,9);printf("8 - Ouvrir un ficher situation");
    gotoligcol(18,9);printf("9 - Supprimer tous les evenements anterieurs a une date");
    gotoligcol(19,9);printf("+ - Afficher la liste des evenements");
    gotoligcol(20,9);printf("0 - Quit");
    bas_droite("*utilisez le pave numerique");
    gotoligcol(25,3);
    return 0;
}

void affiche(HANDLE hConsole,int fond, int couleur){
    int i;
    i=16*fond+couleur;
    SetConsoleTextAttribute(hConsole, i);
}

void Appui(){ //renvoie la touche appuye ou un combo de deux touches pour les fleches directionnelles
    int c = getch();
    printf("%d",c);
    int c2 = getch();
    printf("%d",c2);
}

void WaitPress(){ //attends la pression de enter ou esc
    int c;
    while ((c != 13) && (c != 27)){c=getch();}
}

void AfficherCitoyens(Tcitoyen * pcitoyens, Tcitoyen * pdebutcitoyens){
    system("cls");
    centre("Affichage de la liste des citoyens : \n\n\n\n");
    pcitoyens = pdebutcitoyens->pnext;

	while(pcitoyens->pnext != NULL ){
        printf(" - %s %s\n",pcitoyens->nom,pcitoyens->prenom);
		pcitoyens = pcitoyens->pnext;
	}
	bas_droite("Press Enter");
}

void AfficherLieux(Tlieu * plieux, Tlieu * pdebutlieux){
	system("cls");
    centre("Affichage de la liste des lieux : \n\n\n\n");
    plieux = pdebutlieux->pavant;
	while(plieux->pavant != NULL ){
        printf(" - %s\n",plieux->nomLieu);
		plieux = plieux->pavant;
	}
	bas_droite("Press Enter");
}

void AfficherEvenements (Tlieu * plieux, Tlieu * pdebutlieux){
    system("cls");
    centre("Affichage des evenements\n\n\n");
	plieux = pdebutlieux->pavant;
    while(plieux->pavant != NULL ){
        printf("A %s :\n",plieux->nomLieu);
        if(plieux->pliste != NULL){
            Tparticipant * pdeplacement = plieux->pliste;
            printf(" Le %d :\n",pdeplacement->date);
            int date = pdeplacement->date;
            printf("  - %s %s\n",pdeplacement->ppersonne->nom, pdeplacement->ppersonne->prenom);
            while(pdeplacement->psuivant != NULL){
                pdeplacement = pdeplacement->psuivant;
                if (date != pdeplacement->date)printf(" Le %d :\n",pdeplacement->date);
                printf("  - %s %s\n",pdeplacement->ppersonne->nom, pdeplacement->ppersonne->prenom);
            }
        }
        printf("\n\n");
		plieux = plieux->pavant;
	}
}

void AjoutCitoyen(Tcitoyen * pcitoyens, Tcitoyen * pdebutcitoyens){
    system("cls");
    centre("Ajout d'un citoyen");
    pcitoyens = pdebutcitoyens;

    while( pcitoyens->pnext->pnext != NULL){
        pcitoyens = pcitoyens->pnext;
    }

    pcitoyens->pnext->pprevious = (Tcitoyen *)malloc(sizeof(Tcitoyen));
    pcitoyens->pnext->pprevious->pnext = pcitoyens->pnext;
    pcitoyens->pnext->pprevious->pprevious = pcitoyens;
    pcitoyens->pnext = pcitoyens->pnext->pprevious;

    pcitoyens = pcitoyens->pnext;

    gotoligcol(10,10);printf("Nom : ");
    scanf("%s",pcitoyens->nom);
    gotoligcol(12,10);printf("Prenom : ");
    scanf("%s",pcitoyens->prenom);
}

void AjoutLieu(Tlieu * plieux, Tlieu * pdebutlieux){
    system("cls");
    centre("Ajout d'un citoyen");

    plieux = pdebutlieux;
    while( plieux->pavant->pavant != NULL){
        plieux = plieux->pavant;
    }
    plieux->pavant->pprecedent = (Tlieu *)malloc(sizeof(Tlieu));
    plieux->pavant->pprecedent->pavant = plieux->pavant;
    plieux->pavant->pprecedent->pprecedent = plieux;
    plieux->pavant = plieux->pavant->pprecedent;

    plieux = plieux->pavant;
    plieux->pliste = NULL;

   gotoligcol(11,10); printf("Lieu : ");
    scanf("%s",plieux->nomLieu);
}

void RemplirParticipants(Tparticipant * pparticipants, Tparticipant * pdebutparticipants, Tlieu * plieux, Tlieu * pdebutlieux, Tcitoyen * pcitoyens, Tcitoyen * pdebutcitoyens){
    system("cls");
    pparticipants = pdebutparticipants;
	pparticipants->psuivant =(Tparticipant *)malloc(sizeof(Tparticipant));
	pparticipants = pparticipants->psuivant;
	pdebutparticipants->psuivant = NULL;

	centre("Ajout d'un participant");
	int jour, mois, annee;
    gotoligcol(5,4);printf("Date de la fete : ");
    gotoligcol(5,26);printf("Jour :  ");scanf("%d",&jour);
    gotoligcol(6,26);printf("Mois :  ");scanf("%d",&mois);
    gotoligcol(7,26);printf("Annee :    (2 chiffres)");gotoligcol(7,34);scanf("%d",&annee);

    pparticipants->date = jour*10000 + mois*100 + annee;
    printf("%d",pparticipants->date);

    //choix du lieu
    gotoligcol(10,20);printf("Choix du lieu :");
    gotoligcol(13,3);printf("*------------------------------------------------------*");
    gotoligcol(14,3);printf("|                                                      |");
    gotoligcol(15,3);printf("|                                                      |");
    gotoligcol(16,3);printf("|                                                      |");
    gotoligcol(17,3);printf("|                                                      |");
    gotoligcol(18,3);printf("|                                                      |");
    gotoligcol(19,3);printf("*------------------------------------------------------*");
    gotoligcol(16,10);printf("->");

    int taille = 0;
    plieux = pdebutlieux -> pavant;
    while(plieux->pavant != NULL){plieux = plieux->pavant;taille++;}
    taille = taille-1;
    plieux = pdebutlieux -> pavant;
    int charac = ' ', charac2 = ' ';
    int position = 0;

    //menu deroulant
    gotoligcol(15,13);printf("                   ");
    gotoligcol(16,13);printf("%s                   ",plieux->nomLieu);
    gotoligcol(17,13);printf("%s                   ",plieux->pavant->nomLieu);
    gotoligcol(0,0);
    while( charac != 13){
        charac = getch();
        if(charac == 224){
            charac2 = getch();
            if(charac2==72){
                if(position == 0){
                    gotoligcol(15,13);printf("                   ");
                }
                else if(position == 1){
                    plieux = plieux->pprecedent;
                    gotoligcol(15,13);printf("                   ");
                    position--;
                }
                else{
                    plieux = plieux->pprecedent;
                    gotoligcol(15,13);printf("%s                   ",plieux->pprecedent->nomLieu);
                    position--;
                }
                gotoligcol(16,13);printf("%s                   ",plieux->nomLieu);
                gotoligcol(17,13);printf("%s                   ",plieux->pavant->nomLieu);
            }
            if(charac2==80){
                if(position == taille){
                    gotoligcol(17,13);printf("                   ");
                }
                else if(position == taille-1){
                    plieux = plieux->pavant;
                    gotoligcol(17,13);printf("                   ");
                    position++;
                }
                else{
                    plieux = plieux->pavant;
                    gotoligcol(17,13);printf("%s                   ",plieux->pavant->nomLieu);
                    position++;
                }
                gotoligcol(15,13);printf("%s                   ",plieux->pprecedent->nomLieu);
                gotoligcol(16,13);printf("%s                   ",plieux->nomLieu);
            }
        }
        gotoligcol(0,0);
    }
    if(plieux->pliste == NULL){plieux->pliste = pparticipants;}
    else{
        Tparticipant * pdeplacement = plieux->pliste;
        while(pdeplacement->psuivant != NULL){pdeplacement = pdeplacement->psuivant;}
        pdeplacement->psuivant = pparticipants;

    }
    pparticipants->psuivant = NULL;


    //choix du citoyen
    gotoligcol(10,80);printf("Choix du citoyen :");
    gotoligcol(13,63);printf("*------------------------------------------------------*");
    gotoligcol(14,63);printf("|                                                      |");
    gotoligcol(15,63);printf("|                                                      |");
    gotoligcol(16,63);printf("|                                                      |");
    gotoligcol(17,63);printf("|                                                      |");
    gotoligcol(18,63);printf("|                                                      |");
    gotoligcol(19,63);printf("*------------------------------------------------------*");
    gotoligcol(16,70);printf("->");

    taille = 0;
    pcitoyens = pdebutcitoyens -> pnext;
    while(pcitoyens->pnext != NULL){pcitoyens = pcitoyens->pnext;taille++;}
    taille = taille-1;
    pcitoyens = pdebutcitoyens -> pnext;

    charac = ' ', charac2 = ' ';
    position = 0;
    gotoligcol(15,74);printf("                      ");
    gotoligcol(16,74);printf("%s %s                      ",pcitoyens->nom,pcitoyens->prenom);
    gotoligcol(17,74);printf("%s %s                      ",pcitoyens->pnext->nom,pcitoyens->pnext->prenom);
    gotoligcol(0,0);

    while( charac != 13){
        charac = getch();
        if(charac == 224){
            charac2 = getch();
            if(charac2==72){
                if(position == 0){
                    gotoligcol(15,74);printf("                      ");
                }
                else if(position == 1){
                    pcitoyens = pcitoyens->pprevious;
                    gotoligcol(15,74);printf("                      ");
                    position--;
                }
                else{
                    pcitoyens = pcitoyens->pprevious;
                    gotoligcol(15,74);printf("%s %s                      ",pcitoyens->pprevious->nom,pcitoyens->pprevious->prenom);
                    position--;
                }
                gotoligcol(16,74);printf("%s %s                      ",pcitoyens->nom,pcitoyens->prenom);
                gotoligcol(17,74);printf("%s %s                      ",pcitoyens->pnext->nom,pcitoyens->pnext->prenom);
            }
            if(charac2==80){
                if(position == taille){
                    gotoligcol(17,74);printf("                      ");
                }
                else if(position == taille-1){
                    pcitoyens = pcitoyens->pnext;
                    gotoligcol(17,74);printf("                      ");
                    position++;
                }
                else{
                    pcitoyens = pcitoyens->pnext;
                    gotoligcol(17,74);printf("%s %s                      ",pcitoyens->pnext->nom,pcitoyens->pnext->prenom);
                    position++;
                }
                gotoligcol(15,74);printf("%s %s                      ",pcitoyens->pprevious->nom,pcitoyens->pprevious->prenom);
                gotoligcol(16,74);printf("%s %s                      ",pcitoyens->nom,pcitoyens->prenom);
            }
        }
        gotoligcol(0,0);
    }
    pcitoyens = pdebutcitoyens;
    int i = 0;
    while(i <= position) {pcitoyens = pcitoyens->pnext;i++;}
    pparticipants->ppersonne = pcitoyens;
    pparticipants->psuivant = NULL;

}

void Rencontre(Tlieu * plieux, Tlieu * pdebutlieux, Tcitoyen * pcitoyens, Tcitoyen * pdebutcitoyens){
    system("cls");
    centre("Liste des gens ayant rencontre une personne");

    //menu choix citoyen
    gotoligcol(10,50);printf("Citoyen :");
    gotoligcol(13,20);printf("*-------------------------------------------------------------------*");
    gotoligcol(14,20);printf("|                                                                   |");
    gotoligcol(15,20);printf("|                                                                   |");
    gotoligcol(16,20);printf("|                                                                   |");
    gotoligcol(17,20);printf("|                                                                   |");
    gotoligcol(18,20);printf("|                                                                   |");
    gotoligcol(19,20);printf("*-------------------------------------------------------------------*");
    gotoligcol(16,44);printf("->");


    int charac = ' ', charac2 = ' ';
    int position = 0;
    int taille = 0;
    pcitoyens = pdebutcitoyens -> pnext;
    while(pcitoyens->pnext != NULL){pcitoyens = pcitoyens->pnext;taille++;}
    taille = taille-1;
    pcitoyens = pdebutcitoyens -> pnext;
    gotoligcol(15,47);printf("                      ");
    gotoligcol(16,47);printf("%s %s                      ",pcitoyens->nom,pcitoyens->prenom);
    gotoligcol(17,47);printf("%s %s                      ",pcitoyens->pnext->nom,pcitoyens->pnext->prenom);
    gotoligcol(0,0);
    while( charac != 13){ //menu déroulant
        charac = getch();
        if(charac == 224){
            charac2 = getch();
            if(charac2==72){
                if(position == 0){
                    gotoligcol(15,47);printf("                      ");
                }
                else if(position == 1){
                    pcitoyens = pcitoyens->pprevious;
                    gotoligcol(15,47);printf("                      ");
                    position--;
                }
                else{
                    pcitoyens = pcitoyens->pprevious;
                    gotoligcol(15,47);printf("%s %s                      ",pcitoyens->pprevious->nom,pcitoyens->pprevious->prenom);
                    position--;
                }
                gotoligcol(16,47);printf("%s %s                      ",pcitoyens->nom,pcitoyens->prenom);
                gotoligcol(17,47);printf("%s %s                      ",pcitoyens->pnext->nom,pcitoyens->pnext->prenom);
            }
            if(charac2==80){
                if(position == taille){
                    gotoligcol(17,47);printf("                      ");
                }
                else if(position == taille-1){
                    pcitoyens = pcitoyens->pnext;
                    gotoligcol(17,47);printf("                      ");
                    position++;
                }
                else{
                    pcitoyens = pcitoyens->pnext;
                    gotoligcol(17,47);printf("%s %s                      ",pcitoyens->pnext->nom,pcitoyens->pnext->prenom);
                    position++;
                }
                gotoligcol(15,47);printf("%s %s                      ",pcitoyens->pprevious->nom,pcitoyens->pprevious->prenom);
                gotoligcol(16,47);printf("%s %s                      ",pcitoyens->nom,pcitoyens->prenom);
            }
        }
        gotoligcol(0,0);
    }

    char nomchoisi[40], prenomchoisi[40];
    strcpy(nomchoisi,pcitoyens->nom);
    strcpy(prenomchoisi,pcitoyens->prenom);

    system("cls");
    centre("Liste des gens ayant rencontre une personne");
    gotoligcol(5,7);printf("Citoyen : %s %s",nomchoisi, prenomchoisi);
    gotoligcol(7,0);

    plieux = pdebutlieux->pavant;
    while(plieux->pavant != NULL ){

        if(plieux->pliste != NULL){
            Tparticipant * pdeplacement = plieux->pliste;

            if(strcmp(nomchoisi, pdeplacement->ppersonne->nom)  == 0 && strcmp(prenomchoisi, pdeplacement->ppersonne->prenom)  == 0 ){
                int datechoisi = pdeplacement->date;
                Tparticipant * paffichage = plieux->pliste;
                printf("Au lieu %s le %d :\n\n",plieux->nomLieu,datechoisi);

                if((strcmp(nomchoisi, paffichage->ppersonne->nom)  != 0 || strcmp(prenomchoisi, paffichage->ppersonne->prenom)  != 0 )&& datechoisi == paffichage->date)
                printf("- %s %s\n",paffichage->ppersonne->nom, paffichage->ppersonne->prenom);
                while(paffichage->psuivant != NULL){
                    paffichage = paffichage->psuivant;
                    if((strcmp(nomchoisi, paffichage->ppersonne->nom)  != 0 || strcmp(prenomchoisi, paffichage->ppersonne->prenom)  != 0 )&& datechoisi == paffichage->date)
                    printf("- %s %s\n",paffichage->ppersonne->nom, paffichage->ppersonne->prenom);

                }
                printf("\n");
            }
            while(pdeplacement->psuivant != NULL){
                pdeplacement = pdeplacement->psuivant;
                if(strcmp(nomchoisi, pdeplacement->ppersonne->nom)  == 0 && strcmp(prenomchoisi, pdeplacement->ppersonne->prenom)  == 0 ){
                    int datechoisi = pdeplacement->date;
                    Tparticipant * paffichage = plieux->pliste;
                    printf("Au lieu %s le %d :\n\n",plieux->nomLieu,datechoisi);

                    if((strcmp(nomchoisi, paffichage->ppersonne->nom)  != 0 || strcmp(prenomchoisi, paffichage->ppersonne->prenom)  != 0 )&& datechoisi == paffichage->date)
                    printf("- %s %s\n",paffichage->ppersonne->nom, paffichage->ppersonne->prenom);
                    while(paffichage->psuivant != NULL){
                        paffichage = paffichage->psuivant;
                        if((strcmp(nomchoisi, paffichage->ppersonne->nom)  != 0 || strcmp(prenomchoisi, paffichage->ppersonne->prenom)  != 0 )&& datechoisi == paffichage->date)
                        printf("- %s %s\n",paffichage->ppersonne->nom, paffichage->ppersonne->prenom);

                    }
                    printf("\n");
                }
            }
        }
		plieux = plieux->pavant;
	}
    for(int i=0;i < (LARGEUR_CONS - 14); i++){printf(" ");};printf("Press Enter");
	gotoligcol(0,0);
    WaitPress();

}

void EnregistreSituation(Tlieu * plieux, Tlieu * pdebutlieux, Tcitoyen * pcitoyens, Tcitoyen * pdebutcitoyens){
    system("cls");
    centre("Enregistrement des fichiers Situations\n\n\n");

    //affichage contenu du dossier
    char profil[40];
    WIN32_FIND_DATA File;
    HANDLE hSearch;
    hSearch = FindFirstFile("Fichiers_Situations/*.*", &File);
    if (hSearch != INVALID_HANDLE_VALUE){
        printf("                               Liste des profils :\n\n                                       *--------------\n");
        FindNextFile(hSearch, &File);
        while (FindNextFile(hSearch, &File)){
            printf("                                       |  - %s\n", File.cFileName);
        }
        printf("                                       *--------------\n\n");
        FindClose(hSearch);
    }

    printf("   Choix du profil : \n     ");
    scanf("%s",&profil);

    system("cls");
    centre("Enregistrement des fichiers Situations");
    gotoligcol(8,39); printf("*-----------------------------*----------*");
    gotoligcol(9,39); printf("|                             |          |");
    gotoligcol(10,39);printf("|    Fichier Citoyens :       |   CREE   |");
    gotoligcol(11,39);printf("|                             |          |");
    gotoligcol(12,39);printf("*-----------------------------+----------*");
    gotoligcol(13,39);printf("|                             |          |");
    gotoligcol(14,39);printf("|    Fichier Lieux :          |   CREE   |");
    gotoligcol(15,39);printf("|                             |          |");
    gotoligcol(16,39);printf("*-----------------------------+----------*");
    gotoligcol(17,39);printf("|                             |          |");
    gotoligcol(18,39);printf("|    Fichier Participants :   |   CREE   |");
    gotoligcol(19,39);printf("|                             |          |");
    gotoligcol(20,39);printf("*-----------------------------*----------*");


    //concatenation pour suppression
    char suppr[100]= "rd /q /s \"Fichiers_Situations/";char ajout[100]= "md \"Fichiers_Situations/";
    strcat(suppr,profil);strcat(suppr,"\"");
    strcat(ajout,profil);strcat(ajout,"\"");

    //suppression et creation du dossier qui va recevoir les fichiers
    gotoligcol(HAUTEUR_CONS-2,0);
    system(suppr);
    system(ajout);//NB : uniquement possible sur Windows

    //concatenation pour trouver le path
    char pathcitoyen[100]="Fichiers_Situations/", pathlieu[100]="Fichiers_Situations/", pathparticipants[100]="Fichiers_Situations/";
    strcat(pathcitoyen,profil);strcat(pathcitoyen,"/Citoyens.dat");
    strcat(pathlieu,profil);strcat(pathlieu,"/Lieux.dat");
    strcat(pathparticipants,profil);strcat(pathparticipants,"/Participants.dat");

    //fichier situation Citoyens
    FILE * fCitoyens = fopen(pathcitoyen,"wt");
    pcitoyens = pdebutcitoyens->pnext;

	while(pcitoyens->pnext != NULL ){
        fprintf(fCitoyens,"%s", pcitoyens->nom);
        fprintf(fCitoyens,"\n");
        fprintf(fCitoyens, "%s", pcitoyens->prenom);
        fprintf(fCitoyens,"\n");
		pcitoyens = pcitoyens->pnext;
	}
	fprintf(fCitoyens,"$");
    fclose(fCitoyens);

    //fichier situation Lieux
    FILE * fLieux = fopen(pathlieu,"wt");
    plieux = pdebutlieux->pavant;
	while(plieux->pavant != NULL ){
        fprintf(fLieux,"%s", plieux->nomLieu);
        fprintf(fLieux,"\n");
		plieux = plieux->pavant;
	}
	fprintf(fCitoyens,"$");
    fclose(fLieux);


    //fichier situation Participants
    FILE * fParticipants = fopen(pathparticipants,"wt");

    plieux = pdebutlieux->pavant;
    while(plieux->pavant != NULL ){

        if(plieux->pliste != NULL){
            Tparticipant * pdeplacement = plieux->pliste;
            fprintf(fParticipants,"%d\n",pdeplacement->date);
            fprintf(fParticipants,"%s\n",pdeplacement->ppersonne->nom);
            fprintf(fParticipants,"%s\n",pdeplacement->ppersonne->prenom);
            while(pdeplacement->psuivant != NULL){
                pdeplacement = pdeplacement->psuivant;
                fprintf(fParticipants,"%d\n",pdeplacement->date);
                fprintf(fParticipants,"%s\n",pdeplacement->ppersonne->nom);
                fprintf(fParticipants,"%s\n",pdeplacement->ppersonne->prenom);
            }
        }
        fprintf(fParticipants,"£\n");
		plieux = plieux->pavant;
	}
	fprintf(fParticipants,"$");
	fclose(fParticipants);

    bas_droite("Press Enter");
}

void OuvrirSituation(Tparticipant * pparticipants, Tparticipant * pdebutparticipants, Tlieu * plieux, Tlieu * pdebutlieux, Tlieu * pfinlieux, Tcitoyen * pcitoyens, Tcitoyen * pdebutcitoyens, Tcitoyen * pfincitoyens){
    system("cls");
    centre("Ouverture des fichiers Participants\n\n\n\n");

    //affichage contenu du dossier
    char profil[40];
    WIN32_FIND_DATA File;
    HANDLE hSearch;
    hSearch = FindFirstFile("Fichiers_Situations/*.*", &File);
    if (hSearch != INVALID_HANDLE_VALUE){
        printf("                               Liste des profils :\n\n                                       *--------------\n");
        FindNextFile(hSearch, &File);
        while (FindNextFile(hSearch, &File)){
            printf("                                       |  - %s\n", File.cFileName);
        }
        printf("                                       *--------------\n\n");
        FindClose(hSearch);
    }

    printf("   Choix du profil : \n     ");
    scanf("%s",&profil);

    system("cls");
    centre("Ouverture des fichiers Participants");
    gotoligcol(8,39); printf("*-----------------------------*----------*");
    gotoligcol(9,39); printf("|                             |          |");
    gotoligcol(10,39);printf("|    Fichier Citoyens :       |          |");
    gotoligcol(11,39);printf("|                             |          |");
    gotoligcol(12,39);printf("*-----------------------------+----------*");
    gotoligcol(13,39);printf("|                             |          |");
    gotoligcol(14,39);printf("|    Fichier Lieux :          |          |");
    gotoligcol(15,39);printf("|                             |          |");
    gotoligcol(16,39);printf("*-----------------------------+----------*");
    gotoligcol(17,39);printf("|                             |          |");
    gotoligcol(18,39);printf("|    Fichier Participants :   |          |");
    gotoligcol(19,39);printf("|                             |          |");
    gotoligcol(20,39);printf("*-----------------------------*----------*");

    gotoligcol(25,1);printf("OK  : Fichier ouvert avec succes");
    gotoligcol(26,1);printf("ABS : Fichier absent");
    gotoligcol(27,1);printf("ERR : Erreur due a l'absence du fichier Citoyens ou/et Lieux");

    //concatenations pour creer le chemin en fonction de ce que l'utilisateur a entre
    char pathcitoyen[100]="Fichiers_Situations/", pathlieu[100]="Fichiers_Situations/", pathparticipants[100]="Fichiers_Situations/";
    strcat(pathcitoyen,profil);strcat(pathcitoyen,"/Citoyens.dat");
    strcat(pathlieu,profil);strcat(pathlieu,"/Lieux.dat");
    strcat(pathparticipants,profil);strcat(pathparticipants,"/Participants.dat");


    //fichier situation Citoyens
    FILE * fCitoyens = fopen(pathcitoyen,"r");
    if (fCitoyens == NULL){gotoligcol(10,74);printf("ABS");}
    else {
        //remise a zero de la liste citoyens
        pdebutcitoyens->pprevious = NULL;
        pfincitoyens->pnext = NULL;
        pdebutcitoyens->pnext = pfincitoyens;
        pfincitoyens->pprevious = pdebutcitoyens;

        char string [40];
        fscanf(fCitoyens, "%s",string);
        while(string[0] != '$'){
            //insertion d'un maillon
            pcitoyens = pdebutcitoyens;
            while( pcitoyens->pnext->pnext != NULL) pcitoyens = pcitoyens->pnext;
            pcitoyens->pnext->pprevious = (Tcitoyen *)malloc(sizeof(Tcitoyen));
            pcitoyens->pnext->pprevious->pnext = pcitoyens->pnext;
            pcitoyens->pnext->pprevious->pprevious = pcitoyens;
            pcitoyens->pnext = pcitoyens->pnext->pprevious;
            pcitoyens = pcitoyens->pnext;

            strcpy(pcitoyens->nom,string);
            fscanf(fCitoyens, "%s",string);
            strcpy(pcitoyens->prenom,string);
            fscanf(fCitoyens, "%s",string);
        }
        fclose(fCitoyens);
        gotoligcol(10,74);printf("OK");
    }

    //fichier situation Lieux
    FILE * fLieux = fopen(pathlieu,"r");
    if (fLieux == NULL){gotoligcol(14,74);printf("ABS");}
    else {
        //remise a zero de la liste lieux
        pdebutlieux->pprecedent = NULL;
        pfinlieux->pavant = NULL;
        pdebutlieux->pavant = pfinlieux;
        pfinlieux->pprecedent = pdebutlieux;

        char string [40];
        fscanf(fLieux, "%s",string);
        while(string[0] != '$'){
            //insertion d'un maillon
            plieux = pdebutlieux;
            while( plieux->pavant->pavant != NULL) plieux = plieux->pavant;
            plieux->pavant->pprecedent = (Tlieu *)malloc(sizeof(Tlieu));
            plieux->pavant->pprecedent->pavant = plieux->pavant;
            plieux->pavant->pprecedent->pprecedent = plieux;
            plieux->pavant = plieux->pavant->pprecedent;
            plieux = plieux->pavant;
            plieux->pliste = NULL;

            strcpy(plieux->nomLieu,string);
            fscanf(fLieux, "%s",string);
        }
        fclose(fLieux);
        gotoligcol(14,74);printf("OK");
    }

    //fichier situation Participants
    FILE * fParticipants = fopen(pathparticipants,"r");
    if (fParticipants == NULL){gotoligcol(18,74);printf("ABS");}
    else if (fCitoyens == NULL || fLieux == NULL){gotoligcol(18,74);printf("ERR");fclose(fParticipants);}
    else {
        char string [40];
        fscanf(fParticipants, "%s",string);
        plieux = pdebutlieux->pavant;
        while(string[0] != '$'){
            while(string[0] != '£'){
                //creation du maillon participants et suppression des liens avec pdebutparticipants
                pparticipants = pdebutparticipants;
                pparticipants->psuivant =(Tparticipant *)malloc(sizeof(Tparticipant));
                pparticipants = pparticipants->psuivant;
                pdebutparticipants->psuivant = NULL;

                if(plieux->pliste == NULL){plieux->pliste = pparticipants;}
                else{
                    Tparticipant * pdeplacement = plieux->pliste;
                    while(pdeplacement->psuivant != NULL){pdeplacement = pdeplacement->psuivant;}
                    pdeplacement->psuivant = pparticipants;
                }
                pparticipants->psuivant = NULL;

                pparticipants->date = atoi(string); //atoi servant a tranformer un char en int
                char nomsitu[40];
                char prenomsitu[40];
                fscanf(fLieux, "%s",nomsitu);
                fscanf(fLieux, "%s",prenomsitu);

                pcitoyens=pdebutcitoyens->pnext;
                while(strcmp(nomsitu, pcitoyens->nom)  != 0 || strcmp(prenomsitu, pcitoyens->prenom)  != 0) pcitoyens = pcitoyens->pnext;

                pparticipants->ppersonne = pcitoyens;
                pparticipants->psuivant = NULL;
                fscanf(fParticipants, "%s",string);
            }
            plieux = plieux->pavant;
            fscanf(fParticipants, "%s",string);

        }
        fclose(fParticipants);
        gotoligcol(18,74);printf("OK");
    }
    bas_droite("Press Enter");
}

void SupprimerApresDate(Tlieu * plieux, Tlieu * pdebutlieux){
    system("cls");
    centre("Suppression des evenements");

    int joursaisi, moissaisi, anneesaisi, jourmaillon, moismaillon, anneemaillon, date;
    gotoligcol(7,2);printf("Choix de la date a partir de laquelle supprimer : ");
    gotoligcol(8,5);printf("Jour :  ");scanf("%d",&joursaisi);
    gotoligcol(9,5);printf("Mois :  ");scanf("%d",&moissaisi);
    gotoligcol(10,5);printf("Annee : ");scanf("%d",&anneesaisi);

    void SupprMaillon(Tparticipant * pdeplacement, Tlieu * plieux){
        pdeplacement = plieux->pliste;
        if(pdeplacement->date == date && pdeplacement->psuivant == NULL)plieux->pliste = NULL;
        else if(pdeplacement->date == date)plieux->pliste = pdeplacement->psuivant;
        else{
            while(pdeplacement->psuivant->date != date)pdeplacement=pdeplacement->psuivant;
            pdeplacement->psuivant = pdeplacement->psuivant->psuivant;
        }
    }

    plieux = pdebutlieux->pavant;
    while(plieux->pavant != NULL ){
        if(plieux->pliste != NULL){
            Tparticipant * pdeplacement = plieux->pliste;
            while(pdeplacement->psuivant != NULL){

                date = pdeplacement->date;
                jourmaillon = date/10000;
                moismaillon = (date/100)%100;
                anneemaillon = date%100;
                if(anneemaillon < anneesaisi){
                    SupprMaillon(pdeplacement, plieux);
                }else if(anneemaillon == anneesaisi){
                    if(moismaillon < moissaisi){
                        SupprMaillon(pdeplacement, plieux);
                    }else if(moismaillon == moissaisi){
                        if(jourmaillon < joursaisi){
                            SupprMaillon(pdeplacement, plieux);
                        }
                    }
                }
                pdeplacement = pdeplacement->psuivant;
            }

            date = pdeplacement->date;
            jourmaillon = date/10000;
            moismaillon = (date/100)%100;
            anneemaillon = date%100;
            if(anneemaillon < anneesaisi){
                SupprMaillon(pdeplacement, plieux);
            }else if(anneemaillon == anneesaisi){
                if(moismaillon < moissaisi){
                    SupprMaillon(pdeplacement, plieux);
                }else if(moismaillon == moissaisi){
                    if(jourmaillon < joursaisi){
                        SupprMaillon(pdeplacement, plieux);
                    }
                }
            }
        }
		plieux = plieux->pavant;
	}
    printf("Tous les evenements anterieurs au %d/%d/%d ont ete supprimes", joursaisi, moissaisi, anneesaisi);
    bas_droite("Press Enter");
}

int main(void){
    char c = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //init de la liste des citoyens
    Tcitoyen * pcitoyens;
	Tcitoyen * pdebutcitoyens;
	Tcitoyen * pfincitoyens;
	pdebutcitoyens =(Tcitoyen *)malloc(sizeof(Tcitoyen));
	pfincitoyens =(Tcitoyen *)malloc(sizeof(Tcitoyen));
	pdebutcitoyens->pprevious = NULL;
	pfincitoyens->pnext = NULL;
	pdebutcitoyens->pnext = pfincitoyens;
	pfincitoyens->pprevious = pdebutcitoyens;

    //init de la liste des lieuxchar * string
    Tlieu * plieux;
	Tlieu * pdebutlieux;
	Tlieu * pfinlieux;
	pdebutlieux=(Tlieu *)malloc(sizeof(Tlieu));
	pfinlieux=(Tlieu *)malloc(sizeof(Tlieu));
	pdebutlieux->pprecedent = NULL;
	pfinlieux->pavant = NULL;
	pdebutlieux->pavant = pfinlieux;
	pfinlieux->pprecedent = pdebutlieux;
	pdebutlieux->pliste = NULL;
	pfinlieux->pliste = NULL;

    //init de la liste des particpipants
    Tparticipant * pparticipants;
	Tparticipant * pdebutparticipants;
	pdebutparticipants =(Tparticipant *)malloc(sizeof(Tparticipant));
	pdebutparticipants->psuivant = NULL;


    while(c != 27 && c != 133){
        afficheMenu(hConsole);
        c = getch();
        //if (c == 112){Appui(); WaitPress();} //aff getch avec la lettre p

        if(c ==49) { //1
            AfficherCitoyens(pcitoyens, pdebutcitoyens);
            WaitPress();
        }
        if(c ==50) { //2
            AfficherLieux(plieux, pdebutlieux);
            WaitPress();
        }
        if(c ==51) { //3
            AjoutCitoyen(pcitoyens, pdebutcitoyens);
        }
        if(c ==52) { //4
            AjoutLieu( plieux, pdebutlieux);
        }
        if(c ==53) { //5
            RemplirParticipants(pparticipants, pdebutparticipants, plieux, pdebutlieux, pcitoyens, pdebutcitoyens);
        }
        if(c ==54) { //6
            Rencontre(plieux, pdebutlieux, pcitoyens, pdebutcitoyens);
        }
        if(c ==55) { //7
            EnregistreSituation(plieux, pdebutlieux, pcitoyens, pdebutcitoyens);
            WaitPress();
        }
        if(c ==56) { //8
            OuvrirSituation(pparticipants, pdebutparticipants, plieux, pdebutlieux, pfinlieux, pcitoyens, pdebutcitoyens, pfincitoyens);
            WaitPress();
        }
        if(c ==57) { //9
            SupprimerApresDate(plieux, pdebutlieux);
            WaitPress();
        }
        if(c ==43) { //+
            AfficherEvenements(plieux, pdebutlieux);
            WaitPress();
        }
        if(c ==48) { //0
            break;
        }
    }
    return 0;
}
