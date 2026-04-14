#include <iostream>

using namespace std;

/*
	Sa se scrie in limbaj de asamblare o functie definita astfel:

	void Distanta(Point *p1, Point *p2, float& distanta);

	unde p1 si p2 sunt pointeri catre doua variabile de tipul Point.
	Functia calculeaza distanta dintre cele doua puncte si o pune in variabila distanta.

	Precizari:

	*structura Point este declarata in felul urmator:

	struct Point
	{
		float x, y;
	}

	*calculul distantei se poate face cu formula sqrt((x2 - x1)^2 + (y2-y1)^2))
*/

struct Point
{
	float x, y;
};

void Distanta(Point* p1, Point* p2, float& distanta)
{
	_asm
	{
		mov eax, [ebp + 8]  //eax = p1 = adresa primei structuri
		mov ebx, [ebp + 12] //ebx = p2 = adresa celei de-a doua structuri

		fld dword ptr [eax]  //st(0) = [eax] = p1->x
		fld dword ptr [ebx]  //st(0) = [ebx] = p2->x  ; in urma operatiei st(1) va fi vechiul str(0), adica p1->x
		fsubp st(1), st(0)   //st(1) = st(1) - st(0) = p1->x - p2->x ; fsubp scoate valoarea din vf stivei, adica noul str(0) va fi st(1)
		
		fmul st(0), st(0)   //st(0) = st(0) * st(0) = (p1->x - p2->x)^2

		fld dword ptr [eax + 4]  //st(0) = [eax + 4] = p1->y
		fld dword ptr [ebx + 4]  //st(0) = [ebx + 4] = p2->y  ; in urma operatiei st(1) va fi vechiul str(0), adica p1->y
		fsubp st(1), st(0)   //st(1) = st(1) - st(0) = p1->y - p2->y ; fsubp scoate valoarea din vf stivei, adica noul str(0) va fi st(1)

		fmul st(0), st(0)   //st(0) = st(0) * st(0) = (p1->y - p2->y)^2

		faddp st(1), st(0)
		fsqrt   //in st(0) vom avea sqrt((x2 - x1)^2 + (y2-y1)^2))

		mov eax, [ebp + 16] //eax = adresa variabilei distanta
		fstp dword ptr [eax]  //la adresa lui distanta pun rezultatul
	}
}


int main()
{
	Point p1, p2;
	float distanta;

	p1.x = 5;
	p1.y = 6;
	p2.x = -7;
	p2.y = 11;

	//Distanta(&p1, &p2, distanta);

	_asm
	{
		lea eax, p1 //eax = adresa lui p1
		lea ebx, p2 //ebx = adresa lui p2
		lea ecx, distanta //ecx = adresa lui distanta

		push ecx
		push ebx
		push eax

		call Distanta

		add esp, 12
	}

	cout << distanta;

	return 0;
}