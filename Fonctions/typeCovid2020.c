/* Code par TekneX */
/* https://github.com/Teknexx */

#include <stdlib.h>
#include <stdio.h>

typedef struct citoyen {
	char nom [40];
	char prenom [40];
	struct citoyen * pnext;
	struct citoyen * pprevious;
} Tcitoyen;

typedef struct participant {
	int date;
	Tcitoyen * ppersonne;
	struct participant * psuivant;
} Tparticipant;

typedef struct lieu {
	char nomLieu [40];
	Tparticipant * pliste;
	struct lieu * pavant;
	struct lieu * pprecedent;
} Tlieu;
