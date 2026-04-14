#include <iostream>

struct Tree {
	int value;
	Tree* left, * right;
};

int find(int v, Tree* root){

	_asm {
		mov ecx, [ebp + 8]	//v
		mov ebx, [ebp + 12]	//root
		
		cmp eax, 1
			je _afara		//as fi putut folosi stiva, dar pot compara si, daca am gasit, pot iesi din viitoarele recursii
			mov eax, 0		//insa n-am avut cum s-o initializez din primul call

		cmp [ebx], ecx
			je _gasit

			cmp [ebx+4], NULL
				je _nuMergPeStanga
				push [ebx+4]
				push ecx
				call find
				add esp, 8

				cmp eax, 1
				je _afara

				_nuMergPeStanga:

			cmp [ebx + 8], NULL
				je _nuMergPeDreapta
				push [ebx+8]
				push ecx
				call find
				add esp, 8

				cmp eax, 1
				je _afara

				_nuMergPeDreapta:

			cmp eax, 1
				je _afara
				mov eax, 0

			jmp _afara

		_gasit:
		mov eax, 1
		
		_afara:
		
	}
}

int main(){

	Tree* r;
	r = new Tree;
	r->value = 7;
	r->left = new Tree;
	r->left->value = 4;
	r->left->left = new Tree;
	r->left->left->value = 3;
	r->left->left->left = r->left->left->right = NULL;
	r->left->right = NULL;
	r->right = new Tree;
	r->right->value = 2;
	r->right->left = r->right->right = NULL;
	std::cout<< "De gasit 5: " << find(5, r);
	std::cout << std::endl;
	std::cout << "De gasit 3: " << find(3, r);
	return 0;
}