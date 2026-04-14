#include <iostream>

void insert(int* arr, int siz, int max, int value) {
	//Funcţia inserează în tabloul array un element cu valoarea value, astfel încât elementele tabloului să rămână
	//ordonate crescător după inserare.

	//asumand ca tabloul este deja ordonat crescator, un while de la coada pana la valoarea mai mica decat cea de inserat will do
	//la o retrospectiva nu vad la ce e util max-ul
	_asm {
		mov eax, arr
		mov ebx, siz
		mov ecx, max
		mov edx, value

		_bucla :
			cmp ebx, 0
				je _insereaza

			cmp [eax + ebx * 4 - 4], edx //incep cu size in ebx, dar size este 1 mai mare decat indicii mei, deci scad 4
				jb _insereaza
				mov esi, [eax + ebx * 4 - 4]			//iau elementul curent 
				mov [eax + ebx * 4 ], esi			//il mut la dreapta
				dec ebx						//scad ebx, il folosesc totodata si drept contor
				jmp _bucla

			_insereaza :
				mov [eax + ebx * 4], edx		//mut valoarea pe pozitia indicata de ebx, dupa ce am mutat elementele mai mari decat el la dreapta
				jmp _afara

		_afara:
	}
}

int main() {

	int v[10] = { 15,29,57 }, i;
	insert(v, 3, 10, 40); // insereaza valoarea 40
	for (i = 0; i < 4; i++)
		std::cout << v[i] << ' '; // se va afisa "15 29 40 57" pe ecran
	return 0;
}

