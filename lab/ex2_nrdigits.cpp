#include <cstdio>

//Sa se scrie codul in limbaj de asamblare care calculeaza cate cifre are un numar natural > 0
//Pentru acest calcul va fi utlizata o functie; apelul acesteia, precum si returnarea rezultatului se va face in assembly

/*
	Rezolvarea utilizeaza urmatoarea metoda:

	nrCifre = 0

	while (numar != 0)
	{
		numar = numar / 10;
		nrCifre++;
	}
*/


int nrDigits(unsigned int a)
{
	_asm
	{
		mov eax, [ebp + 8]  //eax = a; a este primul parametru, valoare acestuia se afla la adresa ebp + 8; cu [ebp + 8] accesam aceasta valoare
		mov esi, 0          //esi = 0; aici vom pastra numarul de cifre

		_bucla:
		cmp eax, 0          //comparam ebx cu 0
			je _sfarsit         //daca ebx == 0, sari la _sfarsit
			mov ebx, 10         //ebx = 10
			mov edx, 0          //edx = 0 (necesar pentru operatia de impartire)
			div ebx             //eax = eax / 10; edx = eax % 10;
			inc esi             //esi = esi + 1; crestem numarul de cifre
			jmp _bucla          //reia bucla

			_sfarsit :
		mov eax, esi        //eax = esi; returnam rezultatul punandu-l in registrul eax
	}
}

int main()
{
	unsigned int numar;
	int nrCifre;

	numar = 1234;        //pentru a testa alte numere, se poate modifica valoarea; pentru 1234 ar trebui sa returneze 4 cifre

	_asm
	{
		mov edx, numar        //edx = numar

		push edx              //punem edx pe stiva; pregatim apelul de functie
		call nrDigits         //apelam functia
		add esp, 4            //curatam stiva

		mov nrCifre, eax      //nrCifre = eax; dupa executia functiei, rezultatul se va afla in eax
	}

	printf("Numarul %d are %d cifre", numar, nrCifre);

	return 0;
}

//cum se face in pur assembly