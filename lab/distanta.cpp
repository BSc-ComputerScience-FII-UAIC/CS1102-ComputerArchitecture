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
		mov esi, [ebp + 8]          //esi = adresa primei structuri
		mov edi, [ebp + 12]         //edi = adresa celei de-a doua structuri
		mov ebx, [ebp + 16]         //ebx = adresa variabilei distanta

		fld dword ptr[edi]                   //st(0) = [edi] = p2->x
		fsub dword ptr[esi]                  //st(0) = st(0) - [esi] = st(0) - p1->x = p2->x - p1->x
		fmul st(0), st(0)                     //st(0) = st(0) * st(0) = (p2->x - p1->x)^2
		fld dword ptr[edi + 4]               //st(0) = [edi + 4] = p2->y  (vechiul st(0) devine st(1) adica acum st(1) = (p2->x - p1->x)^2 )
		fsub dword ptr[esi + 4]              //st(0) = st(0) - [esi + 4] = st(0) - p1->y = p2->y - p1->y
		fmul st(0), st(0)                     //st(0) = st(0) * st(0) = (p2->y - p1->y)^2
		fadd st(0), st(1)                     //st(0) = st(0) + st(1) = (p2->y - p1->y)^2 + (p2->x - p1->x)^2
		fsqrt                                 //st(0) = sqrt(st(0)) = sqrt((p2->y - p1->y)^2 + (p2->x - p1->x)^2)
		fst dword ptr[ebx]                   //[ebx] = st(0), adica distanta = st(0) = sqrt((p2->y - p1->y)^2 + (p2->x - p1->x)^2)
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


	_asm
	{
		lea esi, p1
		lea edi, p2
		lea ebx, distanta
		push ebx
		push edi
		push esi
		call Distanta
		add esp, 12
	}

	cout << distanta;

	return 0;
}