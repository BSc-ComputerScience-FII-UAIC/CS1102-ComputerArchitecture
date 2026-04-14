#include <iostream>

using namespace std;

/*
	Scrieti in limbaj de asamblare urmatoarea functie:

	void sumaMatrice(float** m1, float** m2, float* rezultat, unsigned int nrLinii, unsigned int nrColoane)
	{
		_asm
		{
			...
		}
	}

	Parametrii au urmatoarele semnificatii:
	m1 - adresa primei matrice (declarata dinamic)
	m2 - adresa celei de-a doua matrice (declarata dinamic)
	rezultat - adresa matricei rezultat (declarata dinamic)
	nrLinii - numarul de linii ale matricelor
	nrColoane - numarul de coloane ale matricelor


	Functia va calcula matricea rezultat dupa urmatoarea formula:
	daca linia este para, rezultat[i][j] = m1[i][j] + m2[i][j]
	daca linia este impara, rezultat[i][j] = m1[i][j] - m2[i][j]

	Observatie: liniile se indexeaza de la 0.

*/


void sumaMatrice(float** m1, float** m2, float** rezultat, unsigned int nrLinii, unsigned int nrColoane)
{
	_asm
	{
		mov ecx, 0 //contor pentru linii

		_bucla_linii:
		cmp ecx, [ebp + 20]      //comparam ecx (contor linii) cu nrLinii
			je _am_parcurs_matricea  //daca sunt egale, am terminat de parcurs matricele

			mov edx, 0               //contor pentru coloane
			_bucla_coloane :
			cmp edx, [ebp + 24]      //comparam edx (contor coloane) cu nrColoane
			je _reia_bucla_linii     //daca sunt egale, am terminat de parcurs matricele
			mov esi, [ebp + 8]       //esi = adresa matricei m1
			mov edi, [ebp + 12]      //edi = adresa matricei m2
			mov eax, [esi + ecx * 4] //eax = adresa primului element de pe linia ecx din matricea m1
			fld dword ptr[eax + edx * 4] //pun elementul de pe linia ecx si coloana edx din m1 m1[ecx][edx] in stiva FPU; st(0) = m1[ecx][edx]
			mov ebx, [edi + ecx * 4] //ebx = adresa primului element de pe linia ecx din matricea m2
			fld dword ptr[ebx + edx * 4] //pun elementul de pe linia ecx si coloana edx din m2 (m2[ecx][edx]) in stiva FPU; st(0) = m2[ecx][edx], iar st(1) = m1[ecx][edx]
			mov esi, ecx             //esi = ecx = indexul liniei
			and esi, 1               //esi = esi AND 1; facem AND intre esi si 1 (daca rezultatul este 0, inseamna ca esi are LSB = 0, adica e par; altfel e impar)
			cmp esi, 0               //comparam rezultatul cu 0
			je _linie_para           //daca rezultatul este 0, indexul liniei este par, sarim la _linie_para
			fsubp st(1), st(0)       //st(1) = st(1) - st(0) = m1[ecx][edx] - m2[ecx][edx] 
			//am folosit varianta operatiei care scoate si varful stivei, deci st(0) va deveni st(1), adica, in final, st(0) = m1[ecx][edx] - m2[ecx][edx]
			mov esi, [ebp + 16]      //esi = adresa matricei rezultat
			mov esi, [esi + ecx * 4] //esi = adresa primului element de pe linia ecx din matricea rezultat
			fstp dword ptr[esi + edx * 4] //rezultat[ecx][edx] = st(0) (st(0) va fi si eliminat din stiva pentru ca am folosit fstp)
			inc edx                        //incrementam counterul pentru coloane
			jmp _bucla_coloane             //sari la _bucla_coloane

			_linie_para :
		faddp st(1), st(0)       //st(1) = st(1) + st(0) = m1[ecx][edx] + m2[ecx][edx]
		//am folosit varianta operatiei care scoate si varful stivei, deci st(0) va deveni st(1), adica, in final, st(0) = m1[ecx][edx] + m2[ecx][edx]
			mov esi, [ebp + 16]      //esi = adresa matricei rezultat
			mov esi, [esi + ecx * 4] //esi = adresa primului element de pe linia ecx din matricea rezultat
			fstp dword ptr[esi + edx * 4] //rezultat[ecx][edx] = st(0) (st(0) va fi si eliminat din stiva pentru ca am folosit fstp)
			inc edx                  //incrementam counterul pentru coloane
			jmp _bucla_coloane       //sari la _bucla_coloane

			_reia_bucla_linii :
		inc ecx                  //incrementam counterul pentru linii
			jmp _bucla_linii         //sari la _bucla_linii

			_am_parcurs_matricea :
	}
}

int main()
{
	float** m1, ** m2, ** rezultat;
	unsigned int nrLinii = 3, nrColoane = 4;
	unsigned int i, j;

	m1 = new float* [nrLinii];
	m2 = new float* [nrLinii];
	rezultat = new float* [nrLinii];

	for (i = 0; i < nrLinii; ++i)
	{
		m1[i] = new float[nrColoane];
		m2[i] = new float[nrColoane];
		rezultat[i] = new float[nrColoane];
	}

	for (i = 0; i < nrLinii; ++i)
		for (j = 0; j < nrColoane; ++j)
		{
			m1[i][j] = 2.2;
			m2[i][j] = 5.5;
		}

	sumaMatrice(m1, m2, rezultat, nrLinii, nrColoane);

	for (i = 0; i < nrLinii; ++i)
	{
		for (j = 0; j < nrColoane; ++j)
		{
			cout << rezultat[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}