#include <iostream>

using namespace std;

//Sa se determine suma elementelor unei matrice PATRATICE.

int suma(int v[][3], int dimensiune)
{
	_asm
	{
		mov ebx, 0     //ebx = 0 - in acest registru va fi retinuta suma
		mov esi, v     //esi - adresa
		mov ecx, 0     //ecx = 0 - va fi utilizat ca si counter pentru linii

		_bucla_linii:
		mov edi, 0              //edi = 0 - va fi utilizat ca si contor pentru coloane (trebuie initializat cu 0 de fiecare data cand se reia prima bucla)
		cmp ecx, [ebp + 12]     //comparam contorul pentru linii cu dimensiunea vectorului; [ebp + 12] este numarul de linii (si de coloane pentru ca matricea este patratica)
		jge _final              //daca ecx (contorul liniilor) >= [ebp + 12] (numarul de linii ale matricei), am parcurs matricea, sari la final

		_bucla_coloane :
		cmp edi, [ebp + 12]			//compara edi (contorul coloanelor) cu [ebp + 12] (numarul de coloane al matricei)
		jge _reia_bucla_linii		//daca edi (contorul coloanelor) >= [ebp + 12] (numarul de coloane), am parcurs linia, reiau prima bucla
		mov eax, ecx				//eax = ecx; eax = indexul liniei
		mul[ebp + 12]				//eax = ecx * [ebp + 12]; eax = indexul liniei * numarul de coloane
		add eax, edi				//eax = ecx * [ebp + 12] + edi; eax = indexul liniei * numarul de coloane + indexul coloanei
		add ebx, [esi + eax * 4]    //adunam elementul curent al matricei la suma; [esi + eax * 4] = elementul de pe linia ecx si coloana edi din matrice
		inc edi                     //incrementam indexul coloanei
		jmp _bucla_coloane          //reluam a doua bucla

		_reia_bucla_linii :
		inc ecx                     //incrementam indexul liniei 
		jmp _bucla_linii            //reluam prima bucla

		_final :
		mov eax, ebx                //eax = ebx = suma elementelor (returnarea unei valori se face punand-o in eax)
	}
}


int main()
{
	int v[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
	int suma_elemente;

	suma_elemente = suma(v, 3);
	printf("Suma elementelor din matrice este %d", suma_elemente);
	//Ar trebui sa afiseze "Suma elementelor din matrice este 9"

	return 0;
}