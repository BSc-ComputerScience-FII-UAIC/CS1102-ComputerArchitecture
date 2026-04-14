#include <iostream>

using namespace std;

/*
	Sa se scrie in limbaj de asamblare o functie definita astfel:

	bool VerificaLinii(double **matrice, unsigned int nr_linii, unsigned int nr_coloane);

	unde matrice este un pointer catre o matrice.
	Functia returneaza 1 daca liniile matricei sunt ordonate crescator si 0 daca nu sunt.
*/


bool VerificaLinii(double** matrice, unsigned int nr_linii, unsigned int nr_coloane)
{
	_asm
	{
		mov esi, [ebp + 8]             //esi = adresa matricei
		mov ebx, 0                     //ebx = 0 - contor pentru linii

		_bucla_linii:
		cmp ebx, [ebp + 12]            //comparam ebx (contorul pentru linii) cu nr_linii
			je _am_parcurs_matricea        //daca ebx == nr_linii, inseamna ca am parcurs matricea, sari la _am_parcurs_matricea
			mov ecx, 0                     //ecx = 0 - contor pentru coloane

			mov edi, [esi + ebx * 4]       //edi = adresa liniei ebx
			fld qword ptr[edi + ecx * 8]  //ecx va fi mereu 0 aici, deci st(0) = matrice[ebx][0] (in stiva FPU punem primul element de pe linia ebx) 
			inc ecx                        //ecx++

			_bucla_coloane :
		cmp ecx, [ebp + 16]            //comparam ecx (contorul pentru coloane) cu nr_coloane
			je _reia_bucla_linii           //daca ecx == nr_coloane, sari la _reia_bucla_linii (am terminat de parcurs linia)

			//strategia de verificare este urmatoarea:
			//pentru a nu umple stiva FPU, vom pune mereu primul element de pe lista in stiva (in st(0))
			//apoi, in bucla, vom pune pe rand urmatorul element de pe linie, vom interschimba st(0) cu st(1) si vom face
			//o comparatie care scoate varful stivei

			//cu alte cuvinte, la o iteratie vom avea in st(0) matrice[i][j] si vom pune in stiva matrice[i][j + 1]
			//dupa punerea in stiva, in st(0) vom avea matrice[i][j + 1], iar in st(1) vom avea matrice[i][j]
			//facem o interschimbare intre st(0) si st(1) astfel incat st(0) va fi matrice[i][j], iar st(1) va fi matrice[i][j + 1]
			//pentru comparatie vom folosi o instructiune care scoate varful stivei, astfel incat dupa comparatie in st(0) vom avea matrice[i][j + 1]
			//punem elementul urmator si reluam operatiile de mai sus

			fld qword ptr[edi + ecx * 8]   //st(0) = matrice[ebx][ecx] (punem elementul in varfu stivei FPU)
			fxch st(1)                     //schimbam st(0) cu st(1)
			fcomip st(0), st(1)            //comparam st(0) cu st(1) (matrice[i][j] cu matrice[i][j + 1])
			ja _nu_respecta_regula         //daca st(0) > st(1), sari la _nu_respecta_regula
			inc ecx                        //ecx++
			jmp _bucla_coloane             //reia bucla pentru parcurgerea liniei

			_reia_bucla_linii :
		inc ebx                        //ebx++
			jmp _bucla_linii               //reia bucla de parcurgere a liniilor

			_am_parcurs_matricea :       //daca am parcurs matricea inseamna ca nu am gasit niciun caz care incalca regula
		mov al, 1                    //al = 1 (vom returna 1)
			jmp _final                   //sari la _final

			_nu_respecta_regula :
		mov al, 0                    //al = 0 (returnam 0)

			_final :
	}
}


int main()
{
	unsigned int nr_linii = 3;
	unsigned int nr_coloane = 4;
	bool rezultat;

	double** matrice = new double* [3];

	for (unsigned int i = 0; i < nr_linii; ++i)
	{
		matrice[i] = new double[nr_coloane];

		for (unsigned int j = 0; j < nr_coloane; ++j)
		{
			matrice[i][j] = j;
		}
	}

	_asm
	{
		mov eax, matrice
		mov ebx, nr_linii
		mov ecx, nr_coloane
		push ecx
		push ebx
		push eax
		call VerificaLinii
		add esp, 12
		mov rezultat, al
	}

	if (rezultat)
	{
		cout << "Matricea respecta conditia!";
	}
	else
	{
		cout << "Matricea NU respecta conditia!";
	}

	return 0;
}