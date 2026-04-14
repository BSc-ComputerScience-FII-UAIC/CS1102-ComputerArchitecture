#include <cstdio>

/*
Sa se scrie in limbaj de asamblare o functie definita astfel:
void removePalindrom(unsigned int *arr, unsigned int &arrSize);

Functia primeste ca parametri un vector de numere naturale, precum si numarul de elemente al acestuia (prin referinta).
Functia va elimina numerele palindrom din vector (bineinteles, va trebui scazut si numarul de elemente).

!!!ATENTIE: numarul de elemente al vectorului este dat prin referinta, deci nu vom primi ca parametru numarul efectiv
de elemente, ci adresa la care se afla aceasta valoare.

!!!Exemplu de accesare / modificare a valorii arrSize (programul vostru poate sa difere):
_asm
{
	mov eax, [ebp + 12] //eax va avea locatia de memorie la care se afla numarul de elemente din vector
	mov ebx, [eax] //ebx are numarul de elemente din vector
	mov [eax], 5   //modificam arrSize si ii dam valoarea 5
}

Un numar este palindrom daca este identic atunci cand este citit de la dreapta la stanga si respectiv de la stanga la
dreapta (Ex.: 1221, 1111, 0, 12321, 123321)

Pentru a verifica daca un numar este palindrom se poate utiliza o functie auxiliara
int estePalindrom(unsigned int numar);

Exemplu:
	- daca vectorul este [1221, 2453, 1, 567765], dupa apelul functiei removePalindrom, vectorul va fi [2453]
	- daca vectorul este [4837, 382, 878, 987, 11], dupa apelul functiei removePalindrom, vectorul va fi [4837, 382, 987]

RECOMANDARE: rezolvati intai problema de verificare a palindromului si apoi cea de eliminare din vector.

*/




int main()
{
	unsigned int testArr1[] = { 1221, 2453, 1, 567765 }, testArrSize1 = 4;
	unsigned int testArr2[] = { 4837, 382, 878, 987, 11 }, testArrSize2 = 5;
	unsigned int i;

	/*
		dupa apelul functiei, ar trebui sa se afiseze la consola
		Primul vector: 2345
		Al doilea vector: 4837 382 987
	*/

	removePalindrom(testArr1, testArrSize1);
	removePalindrom(testArr2, testArrSize2);

	printf("Primul vector: ");
	for (i = 0; i < testArrSize1; i++)
	{
		printf("%d ", testArr1[i]);
	}
	printf("\n");

	printf("Al doilea vector: ");
	for (i = 0; i < testArrSize2; i++)
	{
		printf("%d ", testArr2[i]);
	}

	return 0;
}