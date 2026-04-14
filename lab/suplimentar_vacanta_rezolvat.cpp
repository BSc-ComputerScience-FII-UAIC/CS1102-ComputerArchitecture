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

/*
	Observatii REZOLVARE:

	Pentru rezolvarea problemei s-a utilizat o functie auxiliara de verificare daca un numar este palindrom care
	construieste intr-un registru numarul oglindit si il compara cu cel original; daca sunt egale, numarul este
	palindrom, altfel nu este.

*/


int estePalindrom(unsigned int numar)
{
	_asm
	{
		mov ebx, [ebp + 8]             //ebx = numar
		mov esi, 10                    //esi = 10; vom avea nevoie ca sa facem inmultiri / impartiri la 10
		mov ecx, 0                     //ecx = 0

		_bucla_construire_palindrom:
		cmp ebx, 0                     //compara ebx cu 0
			je _compara_numere             //daca ebx == 0, am terminat de construit oglinditul numarului, sar la comparatie
			mov eax, ebx                   //eax = ebx
			mov edx, 0                     //edx = 0; ne pregatim de o impartire
			div esi                        //eax = eax / esi; edx = eax % esi; altfel spus, eax = eax fara ultima cifra, edx = ultima cifra a lui eax
			mov ebx, eax                   //ebx = eax
			mov edi, edx                   //edi = edx (ultima cifra)
			mov eax, ecx                   //eax = ecx (oglinditul pe care il construim)
			mul esi                        //eax = ecx * 10
			add eax, edi                   //eax = ecx * 10 + ultima_cifra
			mov ecx, eax                   //ecx = eax
			jmp _bucla_construire_palindrom    //reiau bucla de construire

			_compara_numere :
		mov ebx, [ebp + 8]     //ebx = numar
			cmp ecx, ebx           //comparam numarul oglindit cu cel original
			je _este_palindrom     //daca sunt egale, inseamna ca este palndrom, returnam 1
			mov eax, 0             //altfel eax = 0 (adica se returneaza 0)
			jmp _sfarsit           //sari la sfarsit

			_este_palindrom :
		mov eax, 1             //numarul este palindrom, eax = 1 (se returneaza 1)

			_sfarsit :
	}
}


void removePalindrom(unsigned int* arr, unsigned int& arrSize)
{
	_asm
	{
		mov esi, [ebp + 8]                  //esi = adresa vectorului
		mov ebx, [ebp + 12]                 //ebx = adresa la care se afla numarul de elemente
		mov ebx, [ebx]                      //ebx = numarul de elemente
		mov ecx, 0                          //ecx = 0 - il vom utiliza ca si index pentru accesarea elementelor din vector

		_bucla_parcurgere:
		cmp ecx, ebx                        //comparam indexul elementului cu numarul de elemente din fector
			jae _sfarsit                        //daca ecx (index) >= ebx (dimensiune vector), am terminat de parcurs, sarim la final
			mov eax, [esi + ecx * 4]            //eax = elementul curent din vector (arr[ecx])
			push ebx                            //salvam ebx pe stiva; nu e garantat ca va avea aceeasi valoare dupa apelul functiei
			push ecx                            //salvam ecx pe stiva; nu e garantat ca va avea aceeasi valoare dupa apelul functiei
			push esi                            //salvam esi pe stiva; nu e garantat ca va avea aceeasi valoare dupa apelul functiei
			push eax                            //punem eax (arr[i]) pe stiva (parametrul functiei)
			call estePalindrom                  //apelam functia
			add esp, 4                          //eliberam stiva
			pop esi                             //restauram esi
			pop ecx                             //restauram ecx
			pop ebx                             //restauram ebx
			cmp eax, 1                          //comparam eax (rezultatul returnat de functie) cu 1
			je _pregatire_stergere_element      //daca eax == 1, numarul este palindrom, sarim la instructiunile de eliminare din vector
			inc ecx                             //altfel, incrementam contorul (pentru a accesa urmatorul element)
			jmp _bucla_parcurgere               //sari la bucla de parcurgere a elementelor din vector

			_pregatire_stergere_element :
		mov edx, ecx                        //edx = ecx = indexul elementului care trebuie eliminat
			mov edi, ebx                        //edi = ebx = numarul de elemente din vector
			dec edi                             //edi = ebx - 1 (arrSize - 1; pana acolo parcurgem cand vrem sa eliminam cu metoda prezentata)
			_bucla_stergere :
		cmp edx, edi                        //comparam edx (indexul curent) cu edi (arrSize - 1)
			je _terminare_stergere              //daca sunt egale, sar la _terminare_stergere, am eliminat elementul
			inc edx                             //edx = edx + 1   
			mov eax, [esi + edx * 4]            //eax = arr[edx + 1]
			dec edx                             //edx = edx - 1
			mov[esi + edx * 4], eax            //arr[edx] = eax = arr[edx + 1]
			inc edx                             //edx = edx + 1
			jmp _bucla_stergere                 //reia bucla de stergere

			_terminare_stergere :
		dec ebx                             //ebx = ebx - 1; s-a eliminat un element din vector, deci dimensiunea lui scade
											//(in acest caz nu mai incrementam contorul ecx pentru ca, in urma stergerii unui element, indexul ecx se va afla un nou element care trebuie verificat si il vom sari daca incrementam ecx
			jmp _bucla_parcurgere               //sari la bucla de parcurgere a elementelor 

			_sfarsit :
		mov eax, [ebp + 12]                 //eax = adresa numarului de elemente ale vectorului
			mov[eax], ebx                      //actualizam numarul de elemente ale vectorului
	}
}


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