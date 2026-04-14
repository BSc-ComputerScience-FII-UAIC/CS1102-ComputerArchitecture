#include <cstdio>
#include <math.h> 

int radical(int n) {
	return sqrt(n); // trebuie inclus 
}

struct complex {
	int re, im;
};

int modul(complex* c1, complex* c2) { //Funcţia  returnează  modulul  produsului  numerelor  complexe  ale  căror  adrese  sunt  indicate  de  parametrii c1şi c2.
	//deci (x+yi)(z+ti)=xz+xti+yzi-yt, numarul complex obtinut e (xz-yt) +i(xt+yz), modulul numarului astuia
	//modulul unui nr complex e sqrt(x^2+y^2)
	int rezultat;
	_asm {
		mov ebx, [ebp + 8]	//ebx tine c1
		mov ecx, [ebp + 12]	//ecx tine c2


		mov eax, [ecx]
		mov edx, 0
		imul [ebx]			//x*z
		mov esi, eax			//esi tine x*z

		mov eax, [ebx+4]
		imul [ecx+4]

		sub esi, eax			//esi tine xz-yt
		mov eax, esi
		imul eax			// (xz-yt)^2
		mov esi, eax			//esi = (xz - yt) ^ 2

		mov eax, [ebx]		//x*t
		imul [ecx+4]
		mov edi, eax

		mov eax, [ecx]		//y*z
		imul [ebx+4]

		add edi, eax
		mov eax, edi
		imul eax	
		mov edi, eax		//edi=(xt+yz)^2

		mov edx, esi
		add edx, edi

		push edx
		call radical
		add esp,4

		mov rezultat, eax
	} 
	return rezultat;
}

int main() {
	complex* c1 = new complex{0,1};
	complex* c2 = new complex{1,3};
	
	printf("%d", modul(c1, c2));
}