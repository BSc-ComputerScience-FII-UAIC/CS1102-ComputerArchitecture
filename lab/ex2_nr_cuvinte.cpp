#include <cstdio>

/*
Sa se scrie in limbaj de asamblare o functie definita astfel:
int countCuvinte(char *sir);

Parametrul sir este un pointer catre un sir de caractere terminat prin '\0', care contine doar litere si spatii,
iar intre doua cuvinte consecutive exista exact un spatiu.

Functia va returna numarul de cuvinte din sirul de caractere indicat prin parametrul sir.

Exemplu:
	- apelul countCuvinte("Ana are pere") va returna 3
	- apelul countCuvinte(" Ana mai are si mere") va returna 5
*/

/*
	Strategia de rezolvare utilizata este urmatoarea:
		- se parcurge vectorul incepand cu a doua pozitie
		- daca elementul curent este o litera si elementul precedent este un spatiu, incrementam numarul de cuvinte
	Se poate observa ca daca sirul nostru incepe cu un cuvant iar programul nostru are n cuvinte, din metoda
	descrisa de mai sus va rezulta ca avem n-1 cuvinte. Pentru a corecta acest lucru, in program se verifica daca
	sirul incepe cu un caracter. In acest caz, se incrementeaza numarul de cuvinte.
*/


int countCuvinte(char* sir)
{
	_asm
	{
		mov esi, [ebp + 8]        //esi = [ebp + 8]; in esi se va afla adresa primului element din sirul de caractere
		mov ebx, 0                //ebx = 0; in ebx se va retine numarul de cuvinte

		//verificam primul caracter

		mov al, [esi]             //al = [esi]; al = primul caracter din sir
		cmp al, '\0'              //comparam al cu '\0' pentru a vedea daca am terminat cu parcurgerea sirului; echivalent cu cmp byte ptr [esi], '\0'
		je _sfarsit               //daca al == '\0', am parcurs sirul, se face salt la eticheta _sfarsit
		cmp al, ' '               //comparam al cu ' ' (spatiu); echivalent cu cmp byte ptr [esi], ' '
		je _pregatire_bucla       //daca al == ' ', sirul nu incepe cu un cuvant, sarim la _pregatire_bucla
		inc ebx                   //al este un caracter, sirul incepe cu un cuvant, incrementam numarul de cuvinte (retinut in ebx)

		_pregatire_bucla :
		mov ecx, 1                //ecx = 1; initializam contorul, pornim de la a doua pozitie din sir

			_bucla :
			mov al, [esi + ecx]       //al = [esi + ecx], punem in al caracterul curent;
			cmp al, '\0'              //comparam al cu '\0' pentru a vedea daca am terminat parcurgerea; echivalent cu cmp byte ptr [esi + ecx], '\0'
			je _sfarsit               //daca al == '\0', am terminat parcurgerea, se sare la _sfarsit

			//in continuare verificam conditia sir[i] == caracter si sir[i - 1] == ' '

			cmp al, ' '               //comparam al (caracterul curent cu ' ')
			je _reia_bucla            //daca al == ' ', se sare la _reia_bucla, se incrementeaza contorul se reia bucla
			push ecx                  //al != ' ', retinem temporar valoarea lui ecx pe stiva
			dec ecx                   //decrementam contorul (echivalent cu a calcula i - 1)
			mov al, [esi + ecx]       //al = [esi + ecx]; al = caracterul precedent (echivalent cu al = sir[i - 1]
			pop ecx                   //restabilim valoarea lui ecx; (se poate observa ca puteam face dec ecx si dupa inc ecx pentru functionalitatea pe care o doream, am ales sa utilizez stiva pentru a da un exemplu)
			cmp al, ' '               //compar al (caracterul precedent) cu ' '
			jne _reia_bucla           //daca al (caracterul precedent) != ' ', sari la _reia_bucla
			inc ebx                   //altfel, este indeplinita conditia sir[i] == caracter si sir[i - i] == ' ', incrementez numarul de cuvinte

			_reia_bucla :
		inc ecx                   //ecx = ecx + 1; incrementez contorul
			jmp _bucla                //reiau bucla

			_sfarsit :
		mov eax, ebx              //returnarea valorii se face punand-o in registrul eax
	}
}


int main()
{
	char test1[] = "Ana are pere";
	char test2[] = " Ana mai are si mere";

	printf("Sirul '%s' are %d cuvinte\n", test1, countCuvinte(test1));
	printf("Sirul '%s' are %d cuvinte", test2, countCuvinte(test2));

	return 0;
}