

#include <iostream>

using namespace std;

unsigned nrBits(int);
unsigned isPrime(int);
int palindrom(unsigned int);
int invers(unsigned int);
int powerOf2(int, int*);
int progresie_aritmetica(int, int*);

int main()
{
	int n = 5;
	int v[5] = { 1,4,3,4,5 };
	cout<<powerOf2(n, v);
	return 0;

}

unsigned nrBits(int)
{
	_asm
	{
		MOV ebx, [ebp + 8]
		MOV EAX, 0
		start_while:
		CMP ebx, 0
			JE stop_while
			MOV ecx, ebx;
		AND ecx, 1
			CMP ecx, 0
			JE not_increment
			INC eax
			not_increment :
		SHR ebx, 1
			JMP start_while
			stop_while :
	}

}

unsigned isPrime(int)
{
	_asm
	{
		MOV ebx, [ebp + 8]
		CMP ebx, 2
		je prim
		jl not_prim

		MOV edx, 0
		MOV ecx, 2
		MOV eax, ebx
		DIV ecx
		MOV esi, eax

		for_start :
		cmp ecx, esi
			JG for_stop

			MOV edx, 0
			MOV eax, ebx
			DIV ecx
			CMP edx, 0
			JE not_prim

			INC ecx
			for_stop :

	prim:
		MOV eax, 1
			jmp endu
			not_prim :
		MOV eax, 0
			jmp endu

			endu :
	}
}
int palindrom(unsigned int)
{
	_asm
	{
		MOV ebx, [ebp + 8]
		MOV esi, ebx

		MOV ecx, 0
		MOV edi, 10

		while_start:
		cmp esi, 0
			je while_stop

			MOV edx, 0
			MOV eax, esi
			DIV edi
			MOV esi, eax

			MOV[ebp + 12 + ecx * 4], edx
			inc ecx

			jmp while_start
			while_stop :

		MOV eax, 0

			MOV esi, 0
			for_start :
			CMP esi, ecx
			JGE for_stop
			MUL edi
			ADD eax, [ebp + 12 + esi * 4]
			INC esi

			jmp for_start
			for_stop :



		CMP eax, ebx
			JNE not_pali


			is_pali :
		mov eax, 1
			jmp _end

			not_pali :
		mov eax, 0
			jmp _end
			_end :
	}
}
int invers(unsigned int)
{
	_asm
	{
		MOV ebx, [ebp + 8]
		MOV esi, ebx

		MOV ecx, 0
		MOV edi, 10

		while_start:
		cmp esi, 0
			je while_stop

			MOV edx, 0
			MOV eax, esi
			DIV edi
			MOV esi, eax

			MOV[ebp + 12 + ecx * 4], edx
			inc ecx

			jmp while_start
			while_stop :

		MOV eax, 0

			MOV esi, 0
			for_start :
			CMP esi, ecx
			JGE for_stop
			MUL edi
			ADD eax, [ebp + 12 + esi * 4]
			INC esi

			jmp for_start
			for_stop :


	}
}
int powerOf2(int, int*)
{
	_asm
	{
		MOV eax, 0
		MOV ebx, [ebp + 12]
		MOV ecx, [ebp + 8]

		for_start:
		cmp ecx, 0
			JLE for_stop
			MOV edi, [ebx + 4 * ecx - 4]
			MOV esi, edi
			DEC edi
			AND esi, edi
			CMP esi, 0
			JNE not_power_of_2

			power_of_2 :
		INC eax

			not_power_of_2 :

		DEC ecx
			jmp for_start
			for_stop :
	_end:
	}
}
int progresie_aritmetica(int, int*) {
	_asm {
		//Se da un vector prin intermediul a doi parametri: primul reprezinta numarul de elemente din vector iar al II-lea este pointer catre primul element din vector.
	   // Functia retuneaza 1 daca elementele vectorului formeaza o progresie aritmetica, 0 in caz contrar


		MOV ebx, [ebp + 12]
		MOV ecx, [ebp + 8]

		cmp ecx, 3
		JL not_progresie


		MOV edx, [ebx + 4]
		SUB edx, [ebx]




	for_start:
			CMP ecx, 1
				JL for_stop


				MOV edi, [ebx + 4 * ecx - 4]
				SUB edi, [ebx + 4 * ecx - 8]

				CMP edi, edx
				JNE not_progresie

				DEC ecx
				for_stop :

		progresie:
			MOV eax, 1
				JMP _end
				not_progresie :
			MOV eax, 0
				JMP _end
				_end :
	}
}

