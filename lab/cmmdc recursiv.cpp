#include <cstdio>

unsigned int cmmdc(unsigned int a, unsigned int b) { //a, b
	//unsigned int rezultat; 
	_asm {
		mov ebx, a //a
		mov ecx, b //b

		cmp ecx, 0
		jne _afaraif
		// mov rezultat, ebx
		mov eax, ebx		//mut in eax ca se pastreaza in stiva, din fericire

		jmp _afara

		_afaraif :
		mov edx, 0
			mov eax, ebx
			div ecx

			push edx
			push ecx
			call cmmdc
			add esp, 8

			//mov rezultat, eax //recursivitatea e prea ciudata

		_afara:
	}
	//return rezultat; 	//se poate folosi atat return cat si simpla mutare a valorii in eax, ca eax se pastreaza intre frameurile stackului
}

int main() {
	unsigned int a = 125, b = 25;
	printf("%d", cmmdc(a, b));
}
