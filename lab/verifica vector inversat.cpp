#include <cstdio>

//functia returneaza 1 daca vector1 are elementele in ordine inversa fata de vector2

int Reverse(int* vector1, int* vector2, int count) {
	_asm {
		mov ebx, vector1
		mov ecx, vector2
		mov edx, count

		mov esi, 0
		_buclaUrcaInStiva:
			cmp esi, edx
				jge _nemaElemente		//esi<edx
				push [ebx+esi*4]
				inc esi
				jmp _buclaUrcaInStiva

			_nemaElemente:				//daca ajung aici, au fost urcate toate elementele din vector1

		mov eax, 1

		mov esi, 0
		_buclaVerifica:
			cmp esi, edx
				jge _finito
				pop edi
				cmp edi, [ecx+esi*4]
					jne _nuEReverse
					jmp _incesi
					
				_nuEReverse :
				mov eax, 0

				_incesi:
				inc esi

			jmp _buclaVerifica

		_finito :
	}
}

int main() {
	int v1[] = { 1,2,3,4,5 };
	int v2[] = { 5,4,3,2,1 };
	printf("%d", Reverse(v1,v2,5));		//se va afisa 1 pe ecran
}