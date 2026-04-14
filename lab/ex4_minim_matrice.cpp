#include <iostream>

using namespace std;

//Sa se determine minimul elementelor unei matrice patratice.

int min(int** mat, int dimensiune)
{
	_asm
	{
		mov esi, [ebp + 8]                   //esi = [ebp + 8]; adresa vectorului de pointeri (adrese) catre linii
		mov ebx, [esi]                       //ebx = [esi] = adresa primei linii
		mov ebx, [ebx]                       //initializam minimul; ebx = [ebx] = valoarea primului element din matrice (mat[0][0])            
		mov ecx, 0                           //ecx = 0 - ecx e folosit ca si contor pentru linii

		_bucla_linii:
		cmp ecx, [ebp + 12]                  //compar contorul liniilor cu numarul de linii (si de coloane, pentru ca matricea este patratica)
		jge _final                           //daca ecx (contorul liniilor) >= numarul de linii, am terminat de parcurs matricea, sarim la final
		mov edi, 0                           //edi = 0; edi e folosit ca si contor pentru coloane; trebuie reinitializat cu 0 de fiecare daca cand se reia prima bucla
		_bucla_coloane :
		cmp edi, [ebp + 12]                  //comparam contorul pentru coloane cu numarul de coloane
		jge _reia_bucla_linii                //daca edi (contorul coloanelor) >= numarul de coloane, am terminat de parcurs o linie, reluam prima bucla
		mov eax, [esi + ecx * 4]             //eax = adresa liniei ecx
		mov eax, [eax + edi * 4]             //eax = elementul de pe linia ecx si coloana edi 
		cmp ebx, eax                         //comparam ebx (minimul curent) cu eax (valoarea curenta din matrice)
		jg _minim_nou                        //daca ebx > eax, sarim la _minim_nou
		inc edi                              //altfel, incrementam contorul pentru coloana
		jmp _bucla_coloane                   //reluam a doua bucla

		_minim_nou:
		inc edi                              //incrementam contorul pentru coloana
		mov ebx, eax                         //ebx = eax; actualizam minimul
		jmp _bucla_coloane                   //reluam a doua bucla

		_reia_bucla_linii :
		inc ecx                              //incrementam contorul pentru linie
		jmp _bucla_linii                     //reluam prima bucla

		_final :
		mov eax, ebx                         //mutam minimul in eax (returnam valoarea minimului)
	}
}


int main()
{
	int** mat;
	int i, j, k = 0, dimensiune = 3, minim;

	mat = new int* [dimensiune];

	for (i = 0; i < dimensiune; i++)
		mat[i] = new int[dimensiune];

	for (i = 0; i < dimensiune; i++)
		for (j = 0; j < dimensiune; j++)
			mat[i][j] = ++k;

	mat[1][1] = -2;

	minim = min(mat, dimensiune);

	printf("Minimul este: %d", minim);
	//Ar trebui sa afiseze "Minimul este -2"

	return 0;
}