#include <cstdio>

//Functia returneaza numarul de perechi din sirul s formate din 2 caractere consecutive in care primul este o
//vocala si al doilea este o consoana.

char GetMaxConsecutiveChar(char* s) {
	_asm {
		mov eax, '\0'
		mov ebx, s
		mov esi, 0		//contor indice vector
		mov edx, 1		//contor nr maxim	- initiat cu 1 ca incep pe pe pozitia 1 [vectorul incepand de pe 0]

		mov cl, [ebx]		//in cl pun primul caracter
		
		mov al, [ebx]		//in eax, mai bine spus al pasterez caracterul care se repeta de cel mai multe ori in linie

		mov edi, 0		//contor local
		_bucla:
			
			mov ch, [ebx+esi]		//in ch pun al doilea caracter
			
			cmp ch, '\0'			//verific daca n-am ajuns la final
				je _afara
				cmp cl, ch		//verific daca am caractere consecutive
					jne _sirRupt
					inc edi
					jmp _nuAmRescriere
												
				_sirRupt:
					cmp edi, edx
						jl _resetContorLocal
						mov al, cl
						mov edx, edi
					
				_resetContorLocal:
					mov edi, 1

				_nuAmRescriere:
					inc esi
					mov cl, ch

			jmp _bucla

		_afara:
	}
}

int main() {
	char s[] = { "aa22aahhkkxxxwwii9\0" };
	printf("%c", GetMaxConsecutiveChar(s));		//se va afisa x
}