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

	FILE * p_subor = fopen("predaj.txt", "r"); //otovrí subor
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

void o() {
	FILE * p_subor = fopen("predaj.txt", "r"); //otvorí subor
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
		if (((pocr % 5) == 0)&&(pocr!=0)) {  //zisti èi zamestanec pracuje dlhsie ako rok
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

void n(char ***pole, int *pocz) {
	FILE * p_subor = fopen("predaj.txt", "r");
	if (p_subor == NULL) return NULL;
	char r[50];
	int i = 0,x = 1, y = 0,a = 0;
	(*pocz) = 0;

	while ((fgets(r, sizeof(r), p_subor))) {
		i++;
		if ((i % 5) == 0) {
			(*pocz)++;
		}
	}
	(*pole) = (char*)malloc((*pocz) * sizeof(char)); //alokujem pole pre spz
	for (a; a <= (*pocz); a++) {
		((*pole))[a] = (char*)malloc(7 * sizeof(char));
	}
	rewind(p_subor); //zresetuje súbor
	while ((fgets(r, sizeof(r), p_subor))) {
		if (x == 6) {
			x = 0;
		}
		if (r[0] == EOF) break;
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
void s(char ***pole,int pocz) {
	int b = 0;
	for (b; b < pocz; b++) {
		printf("%c%c %c%c%c %c%c\n", (*pole)[b][0], (*pole)[b][1], (*pole)[b][2], (*pole)[b][3], (*pole)[b][4], (*pole)[b][5], (*pole)[b][6]);
	}

}
void p(char ***pole,int pocz) {
	int b = 0;
	for (b ; b < pocz; b++) {
		if((*pole)[b][0] == (*pole)[b][6] && (*pole)[b][1] == (*pole)[b][5] && (*pole)[b][2] == (*pole)[b][4])
			printf("%c%c\n", (*pole)[b][0], (*pole)[b][1]);

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
		case 'v': {   // vypiše zoznam všetkých predajcov
			v();
			pomocv++;
			break;
		}
		case 'o': {  //vypíše meno,priezvisko,spz a odmenu pre zamestnanca
			if (pomocv == 1) {
				o();
				break;
			}
			else
				break;


		}
		case'n':    { // vytvorí pole z SPZ
			if (pomocv == 1) {
				n(&pole, &pocz);
				pomocpole++;
				break;
			}
			else
				break;
		}
		case's': {   // vypiše SPZ s medzerami
			if (pomocpole == 1) {
				s(&pole, pocz);
				break;
			}
			else
				printf("Pole nie je vytvorene\n");
			break;

		}
		case'p': {     // vypíše SPZ,ktoré sú polyndromické
			if (pomocpole == 1) {
				p(&pole, pocz);
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
