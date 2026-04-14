#include <cstdio>

//Sa se scrie codul in limbaj de asamblare care dubleaza valoarea numerelor pare dintr-un vector
//Pentru acest calcul va fi utlizata o functie; apelul acesteia, precum si returnarea rezultatului se va face in assembly

void changeValue(int* arr, unsigned int arrSize)
{
	_asm
	{
		mov esi, [ebp + 8]    //esi = [ebp + 8] = adresa primului element din vector
		mov ebx, [ebp + 12]   //ebx = [ebp + 12] = arrSize (numarul de elemente din vector)

		mov ecx, 0            //initializam un contor pentru a traversa vectorul

		_bucla:
		cmp ecx, ebx          //compar ecx (contorul) cu ebx (limita / dimensiunea vectorului)
			jae _am_parcurs_vectorul  //daca ecx >= ebx, iesi din bucla de parcurgere
			mov eax, [esi + ecx * 4]  //eax = [esi + ecx * 4] = arr[ecx], luam elementul de la pozitia contorului
			mov edx, 0                //edx = 0; pregatim edx pentru o impartire
			mov edi, 2                //edi = 2
			div edi                   //eax = eax / edi; edx = eax % edi
			cmp edx, 0                //compar edx cu 0
			jne _creste_contor        //daca edx != 0, numarul NU este par, trebuie doar sa incrementez ecx si sa reiau bucla; sar la _creste_contor
			mov eax, [esi + ecx * 4]  //eax = [esi + ecx * 4] = arr[ecx]
			mov edi, 2                //edi = 2
			mul edi                   //eax = eax * edi = eax * 2
			mov[esi + ecx * 4], eax  //[esi + ecx * 4] = eax = [esi + ecx * 4] * 2  (echivalent cu arr[i] = arr[i] * 2)
			inc ecx                   //ecx = ecx + 1; incrementam contorul
			jmp _bucla                //se reia bucla

			_creste_contor :
		inc ecx                   //creste contor
			jmp _bucla                //reia bucla

			_am_parcurs_vectorul :
	}
}


int main()
{
	int arr[] = { 1, 2, 4, 7, 7, 16 };
	unsigned int arrSize = 6;

	_asm
	{
		lea eax, arr       //incarca adresa primului element din vector in eax
		mov ebx, arrSize   //ebx = arrSize

		push ebx           //pune ebx (arrSize - al doilea parametru) pe stiva
		push eax           //pune eax (*arr - primul parametru) pe stiva
		call changeValue   //apeleaza functia
		add esp, 8         //elibereaza stiva (am pus pe stiva 8 octeti, adunam 8 la esp)
	}

	printf("Noul vector este: ");
	for (unsigned int i = 0; i < arrSize; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}