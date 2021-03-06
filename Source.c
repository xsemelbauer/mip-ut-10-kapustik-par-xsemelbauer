#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	char Meno_Priezvisko;
	char SPZ;
	char Typ_Auta;
	int Cena;
	int Datum;
	struct zaznam *dalsi;
}zaznam;

int pocet_zaznamov() {
	int x = 0;
	char pom;
	FILE *p_subor = fopen("predaj.txt", "r");
	if (p_subor == NULL) {
		printf("Zaznami neboli nacitane\n");
		return;
	}
	while ((pom = getc(p_subor)) != EOF) {
		if (pom == '$') {
			x++;
		}
	}
	rewind(p_subor);
	fclose(p_subor);
	return x;
}

double vyp_odmeny(double cena, int typa) {  //vypocita odmenu z ceny

	double odmena;
	if (typa == 0) {
		odmena = (0.022 * cena);
	}
	else {
	    odmena = (0.015 * cena);
	}
	return odmena;
}

void vypis_zaznamov()() {

    int i;

	FILE * p_subor = fopen("predaj.txt", "r"); //otovr� subor
	if (p_subor == NULL) return NULL;

(*akt) = (*zac);

	for (i = 0; i < x; i++)
	{
		printf("Meno Priezvisko: %s\n", (*akt)->Meno_Priezvisko);
		printf("SPZ: %s\n", (*akt)->SPZ);
		printf("Typ auta: %s\n", (*akt)->Typ_Auta);
		printf("Cena: %d\n", (*akt)->Cena);
		printf("Datum: %d\n", (*akt)->Datum);

		if (i < x - 1)
			(*akt) = (*akt)->dalsi
	}
	printf("\n"); //koniec riadku po ukonceni vypis
	fclose(p_subor);
}

void odmeny_zamestnanci()() {
	FILE * p_subor = fopen("predaj.txt", "r"); //otvor� subor
	if (p_subor == NULL) return NULL;

	char ch, p[9], r[50], meno[30], spz[10];
	int pocr = 1, y, datum, typa;
	double cena, odmena;
	printf("Zadajte datum: ");
	scanf("%d", &datum);
	printf("______________________________\n"); //koniec riadku

	while ((fgets(r, sizeof(r), p_subor))) {  //zisti pocet riadkov v subore
		switch (pocr) {
			case 1: {
				strcpy(meno, r);
				break; }
			case 2: {
				strcpy(spz, r);
				break; }
			case 3: {
				typa = atoi(r);
				break;
			}
			case 4:{
				cena = atof(r);
				odmena = vyp_odmeny(cena,typa);
				break;
			}

		}
		if (pocr == 6) pocr = 0;
		if (((pocr % 5) == 0)&&(pocr!=0)) {  //zisti �i zamestanec pracuje dlhsie ako rok
			y = atoi(r);            //prekonvertuje string na int
			if ((datum - y) >= 10000)
			{
				printf("Meno: %sSPZ: %sOdmena: %2.2lf\n\n", meno, spz, odmena);


			}

		}
		++pocr;
	}
	fclose(p_subor);
}

void vytvori_pole_spz(char ***pole, int *pocet_zaznamov) {
	FILE * p_subor = fopen("predaj.txt", "r");
	if (p_subor == NULL) return NULL;
	char riadok[50];
	int i = 0,x = 1, y = 0,a = 0;
	(*pocet_zaznamov) = 0;

	while ((fgets(r, sizeof(riadok), p_subor))) {
		i++;
		if ((i % 5) == 0) {
			(*poc_zaznamov)++;
		}
	}
	(*pole) = (char*)malloc((*pocet_zaznamov) * sizeof(char)); //alokujem pole pre spz
	for (a; a <= (*pocet_zaznamov); a++) {
		((*pole))[a] = (char*)malloc(7 * sizeof(char));
	}
	rewind(p_subor); //zresetuje s�bor
	while ((fgets(riadok, sizeof(riadok), p_subor))) {
		if (x == 6) {
			x = 0;
		}
		if (riadok[0] == EOF) break;
		switch (x) {
		case 2:
			strcpy((*pole)[y], r);
			y++;
			break;
		}
		++x;
	}

	fclose(p_subor);

}
void vypis_z_pola(char ***pole,int pocz) {
	int znak;
	for (znak =0; znak < pocet_zaznamov; znak++) {
		printf("%c%c %c%c%c %c%c\n", (*pole)[znak][0], (*pole)[znak][1], (*pole)[znak][2], (*pole)[znak][3], (*pole)[znak][4], (*pole)[znak][5], (*pole)[znak][6]);
	}

}
void vypis_palindrom(char ***pole,int pocz) {
	int znak;
	for (znak ; znak < pocet_zaznamov; znak++) {
		if((*pole)[znak][0] == (*pole)[znak][6] && (*pole)[znak][1] == (*pole)[znak][5] && (*pole)[znak][2] == (*pole)[znak][4])
			printf("%c%c\n", (*pole)[znak][0], (*pole)[znak][1]);

	}
}



int main()
{
    zaznam *zac,*akt;
	char f, **pole;      /*f = funkcia*/
	int pocz,pomocv = 0,pomocpole = 0,x;

    x = pocet_zaznamov();

	while (1) {
		f = getchar();
		switch (f) {

		case 'k': { return 0;  //skonci program
			break;
		}
		case 'v': {   // vypi�e zoznam v�etk�ch predajcov
			vypis_zaznamov();
			pomocv++;
			break;
		}
		case 'o': {  //vyp�e meno,priezvisko,spz a odmenu pre zamestnanca
			if (pomocv == 1) {
				odmeny_zamestnanci();
				break;
			}
			else
				break;


		}
		case'n':    { // vytvor� pole z SPZ
			if (pomocv == 1) {
				vytvori_pole_spz(&pole, &pocet_zaznamov);
				pomocpole++;
				break;
			}
			else
				break;
		}
		case's': {   // vypi�e SPZ s medzerami
			if (pomocpole == 1) {
				vypis_z_pola(&pole, pocet_zaznamov);
				break;
			}
			else
				printf("Pole nie je vytvorene\n");
			break;

		}
		case'p': {     // vyp�e SPZ,ktor� s� polyndromick�
			if (pomocpole == 1) {
				vypis_palindrom(&pole, pocet_zaznamov);
				break;
			}
			else
				printf("Pole nie je vytvorene\n");
			break;
		 }
	  }

   }
	return 0;

}
