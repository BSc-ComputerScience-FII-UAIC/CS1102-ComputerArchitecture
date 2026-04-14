#include <cstdio>

int CountDiv(int* vect, int count, int divizor) {
	_asm {
		
		mov ebx, vect
		mov ecx, count
		mov esi, divizor
		mov edi, 0		//contor indici vector

		push 0		//am urcat valoarea initiala a numarului de elemente divizibile

		_bucla:
			cmp edi, ecx	
				jae _afara	
				mov edx, 0
				mov eax, [ebx + edi * 4]
				idiv esi
				cmp edx, 0		//nu am rest
					jne _salt
					pop eax		//am ramas fara registri, oricum eax e rescris, so why not? iau de pe stiva si pun in eax
					inc eax		//am gasit un element divizibil, incrementez
					push eax		//si urc la loc pe stiva
				_salt:
			inc edi
			jmp _bucla

		_afara:
		pop eax
	}
}

int main() {
	int v[] = { 15,6,100,3,25,18,19 };
	printf("%d", CountDiv(v, 7, 5));
}

