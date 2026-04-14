#include <cstdio>

//Sa se scrie codul in limbaj de asamblare care calculeaza maximul dintre doua numere intregi
//Pentru acest calcul va fi utlizata o functie; apelul acesteia, precum si returnarea rezultatului se va face in assembly

int maxim(int a, int b)
{
	_asm
	{
		mov eax, [ebp + 8]    //eax = a; la adresa ebp + 8 se afla valoarea primului parametru, o accesam cu [ebp + 8]
		mov ebx, [ebp + 12]   //ebx = b; la adresa ebp + 12 se afla valoarea celui de-al doilea parametru, o accesam cu [ebp + 12]

		cmp eax, ebx          //comparam eax cu ebx
		jge _sfarsit          //daca eax >= ebx, sari la _sfarsit (valoarea returnata trebuie pusa in eax, daca e deja in eax, nu mai facem nimic)

		mov eax, ebx          //altfel, eax = ebx (in eax se pune valoarea care trebuie returnata)

		_sfarsit :
	}
}


int main()
{
	int a, b, maxi;

	a = 10;
	b = -5;

	_asm
	{
		mov ebx, a      //ebx = a
		mov edx, b      //edx = b

		//PARAMETRII SE PUN PE STIVA IN ORDINE INVERSA

		push edx        //punem edx pe stiva (al doilea parametru al functiei)
		push ebx        //punem ebx pe stiva (primul parametru al functiei)

		call maxim      //apelam functia)

		add esp, 8      //curatam stiva; am pus edx si ebx pe stiva (8 octeti) deci adunam 8 la esp

		mov maxi, eax   //maxi = eax
	}

	printf("MAX(%d, %d) = %d", a, b, maxi);

	return 0;
}