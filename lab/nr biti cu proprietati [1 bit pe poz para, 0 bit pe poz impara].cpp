/*Functia bits:
Parametrul t reprezintă adresa de început a unui tablou de numere întregi fără semn,
iar nr reprezintă numărul elementelor din tablou. Funcţia returnează numărul total de
biţi din elementele tabloului t care satisfac una din următoarele proprietăţi:
- fie au valoarea 1 şi se află pe o poziţie pară în numărul de care aparţin -
fie au valoarea 0 şi se află pe o poziţie impară în numărul de care aparţin Tipul unsigned int are 32 biţi.
În cadrul său, poziţiile pare sunt cele care corespund puterilor 0, 2, ..., 30 în scrierea poziţională,
iar poziţiile impare corespund puterilor 1, 3, ..., 31. */


#include <cstdio>
unsigned int bits(unsigned int*, int) {

	_asm {
		mov eax, [ebp + 8]
		mov ebx, [ebp + 12] //numarul de elemente

		mov esi, 0 //contor indici vector
		mov ecx, 0  //contor biti



	_buclaMare:
		cmp esi, ebx
			jae _finito		//if esi<ebx, contorul < nr de elemente


			mov edx, 1 //0000...0001, 1 pe pozitie para

			_if1PePozitiePara:

				test [eax + esi * 4], edx //testez masca: 1 pe pozitie para
					jz _continuare1
					inc ecx

				_continuare1:
				shl edx, 2
				jz _afaraif1Par //s-a produs depasire, adica am terminat de scanat/shiftat

				jmp _if1PePozitiePara

			_afaraif1Par:

			mov edx, 2 //000...0010, 0 pe pozitie para

			_if0PePozitieImpara:

				test [eax + esi * 4], edx
					jnz _continuare2
					inc ecx

				_continuare2:
				shl edx, 2
				jz _afaraif0Impar

				jmp _if0PePozitieImpara

			_afaraif0Impar:

		inc esi

		jmp _buclaMare


			_finito:
		mov eax, ecx

	}
}

int main() {
	unsigned int v[2] = { 25, 13};//
	printf("%d", bits(v, 2)); // se va afisa valoarea 34 pe ecran
}

