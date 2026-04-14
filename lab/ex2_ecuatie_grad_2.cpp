#include <iostream>

using namespace std;

/*
	Se considera structura:

	struct Ecuatie
	{
		double rad1, rad2;
		float a, b, c;
	};

	ce reprezinta o ecuatie de gradul 2: ax^2 + bx + c = 0

	Sa se scrie in limbaj de asamblare o functie definita astfel

	void calculeazaRadacini(Ecuatie *ec);

	care va calcula radacinile ecuatiei si le va pune in rad1 si rad2.

	OBSERVATII:
	* se considera ca exemplele sunt date astfel incat delta > 0.
	* se pot defini variabilele float valoare4 = 4; si float valoare2 = 2; in cadrul functiei pentru calcule.
*/


struct Ecuatie
{
	double rad1, rad2;
	float a, b, c;
};

void calculeazaRadacini(Ecuatie* ec)
{
	float valoare4 = 4;
	float valoare2 = 2;

	_asm
	{
		mov esi, [ebp + 8]            //esi = adresa structurii

		fld dword ptr[esi + 20]      //st(0) = ec.b
		fmul st(0), st(0)             //st(0) = ec.b * ec.b

		fld valoare4                  //st(0) = 4 (st(1) devine vechiul st(0), adica ec.b * ec.b)
		fld dword ptr[esi + 16]      //st(0) = ec.a (st(1) = 4, st(2) = ec.b * ec.b)
		fld dword ptr[esi + 24]      //st(0) = ec.c (st(1) = ec.a, st(2) = 4, st(3) = ec.b * ec.b)
		fmulp st(1), st(0)            //st(0) = ec.a * ec.c (intai se calculeaza rezultatul, apoi st(0) este eliminat din stiva)
									  //la acest moment st(0) = ec.a * ec.c, st(1) = 4, st(2) = ec.b * ec.b
		fmulp st(1), st(0)           //st(0) = 4 * ec.a * ec.c
									//la acest moment st(1) = ec.b * ec.b
		fsubp st(1), st(0)            //st(0) = ec.b * ec.b - 4 * ec.a * ec.c = delta
		fsqrt                         //st(0) = sqrt(ec.b * ec.b - 4 * ec.a * ec.c) = sqrt(delta)

		fld dword ptr[esi + 20]      //st(0) = ec.b (st(1) = sqrt(delta))
		fchs                          //st(0) = -ec.b
		fadd st(0), st(1)             //st(0) = -ec.b + sqrt(delta)
		fld valoare2                  //st(0) = 2 (st(1) = -ec.b + sqrt(delta), st(2) = sqrt(delta))
		fld dword ptr[esi + 16]      //st(0) = ec.a (st(1) = 2, st(2) = -ec.b + sqrt(delta), st(3) = sqrt(delta))
		fmulp st(1), st(0)            //st(0) = 2 * ec.a (st(1) = -ec.b + sqrt(delta), st(2) = sqrt(delta))
		fdivp st(1), st(0)            //st(0) = (-ec.b + sqrt(delta)) / (2 * ec.a) (st(1) = sqrt(delta))

		fstp qword ptr[esi]          //ec.rad1 = st(0), st(0) devine sqrt(1) adica sqrt(0) = sqrt(delta)

		fld dword ptr[esi + 20]       //st(0) = ec.b (st(1) = sqrt(delta))
		fchs                          //st(0) = -ec.b
		fsub st(0), st(1)             //st(0) = -ec.b - sqrt(delta)
		fld valoare2                  //st(0) = 2 (st(1) = -ec.b - sqrt(delta), st(2) = sqrt(delta))
		fld dword ptr[esi + 16]       //st(0) = ec.a (st(1) = 2, st(2) = -ec.b - sqrt(delta), st(3) = sqrt(delta))
		fmulp st(1), st(0)            //st(0) = 2 * ec.a (st(1) = -ec.b - sqrt(delta), st(2) = sqrt(delta))
		fdivp st(1), st(0)            //st(0) = (-ec.b - sqrt(delta)) / (2 * ec.a) (st(1) = sqrt(delta))

		fstp qword ptr[esi + 8]      //ec.rad2 = st(0), st(0) devine sqrt(1) adica sqrt(0) = sqrt(delta)
	}
}


int main()
{
	Ecuatie ec;

	ec.a = 1;
	ec.b = 4;
	ec.c = 3;

	calculeazaRadacini(&ec);

	cout << ec.rad1 << " " << ec.rad2;

	return 0;
}