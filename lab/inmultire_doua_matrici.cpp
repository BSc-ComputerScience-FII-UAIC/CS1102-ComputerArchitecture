#include <iostream>

using namespace std;

int main()
{
	unsigned numarLinii = 3, numarColoane = 3;
	int a[3][3] = {
		{2, 3, 4},
		{1, 3, 5},
		{9, 7, 1} };

	int b[3][3] = {
		{1, 4, 2},
		{2, 1, 6},
		{8, 5, 2} };
	int c[3][3];

	_asm
	{
		lea eax, a
		lea ebx, b
		lea edx, c
		mov edi, 0
		mov ecx, 0

		startfor1:
		cmp ecx, numarLinii
			jae endfor1

			push ecx
			mov ecx, 0
			startfor2 :
			cmp ecx, numarColoane
			jae endfor2

			mov edi, 0
			push ecx
			mov ecx, 0
			adunare:
		cmp ecx, numarLinii
			jae endadd

			push edx
			push eax
			mov eax, [eax]
			mul[ebx]
			add edi, eax
			pop eax
			pop edx
			inc ecx
			add eax, 4
			add ebx, 12
			jmp adunare

			endadd :
		sub eax, 12
			sub ebx, 36
			add ebx, 4
			mov[edx], edi
			add edx, 4
			pop ecx
			inc ecx
			jmp startfor2

			endfor2 :
		add eax, 12
			lea ebx, b
			pop ecx
			inc ecx
			jmp startfor1

			endfor1 :

	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << c[i][j] << " ";
		cout << endl;
	}
	int x;
	cin >> x;
}
