#include <cstdio>

/*
Sa se scrie in limbaj de asamblare o functie definita astfel:
void removePalindrom(unsigned int *arr, unsigned int &arrSize);

Functia primeste ca parametri un vector de numere naturale, precum si numarul de elemente al acestuia (prin referinta).
Functia va elimina numerele palindrom din vector (bineinteles, va trebui scazut si numarul de elemente).

!!!ATENTIE: numarul de elemente al vectorului este dat prin referinta, deci nu vom primi ca parametru numarul efectiv
de elemente, ci adresa la care se afla aceasta valoare.

!!!Exemplu de accesare / modificare a valorii arrSize (programul vostru poate sa difere):
_asm
{
	mov eax, [ebp + 12] //eax va avea locatia de memorie la care se afla numarul de elemente din vector
	mov ebx, [eax] //ebx are numarul de elemente din vector
	mov [eax], 5   //modificam arrSize si ii dam valoarea 5
}

Un numar este palindrom daca este identic atunci cand este citit de la dreapta la stanga si respectiv de la stanga la
dreapta (Ex.: 1221, 1111, 0, 12321, 123321)

Pentru a verifica daca un numar este palindrom se poate utiliza o functie auxiliara
int estePalindrom(unsigned int numar);

Exemplu:
	- daca vectorul este [1221, 2453, 1, 567765], dupa apelul functiei removePalindrom, vectorul va fi [2453]
	- daca vectorul este [4837, 382, 878, 987, 11], dupa apelul functiei removePalindrom, vectorul va fi [4837, 382, 987]

RECOMANDARE: rezolvati intai problema de verificare a palindromului si apoi cea de eliminare din vector.

*/
int estePalindrom(unsigned int numar) {

	unsigned int rezultat;

	/*	unsigned int aux;
	unsigned int suma;
	int aux=numar;
	int suma
	while(aux){
	suma=suma*10+aux%10;
	aux=aux/10;
	}
	if(suma==numar) return 1;
	else return 0;

	*/

	_asm {
		
		mov ecx, numar			// aux=numar
		mov eax, 0				// initializez eax=suma=0
		mov edx, 0
		mov ebx, 10				// ebx=10, il voi pastra pe tot parcursul programului
		
		bucla_while:
			cmp ecx, 0				// if eax(aux)==0
				je afara_bucla_while

				mul ebx					// eax=eax*abx
				push eax					// salvez eax (eax*10) in stiva
				mov eax, ecx				// eax=ecx (aux)
				mov edx, 0
				div ebx					// eax%ebx, ebx inca e 10;
				pop eax					//n-am nevoie de cat, ci de rest, pot inlocui eax
				add eax, edx				// suma= eax=eax+edx
				push eax					//urc iar in stiva
				mov eax, ecx				//ecx=eax
				mov edx,0
				div ebx					// ebx inca e 10, eax/10, adica aux/10
				mov ecx, eax				//ecx=eax
				pop eax					// exista alt registru liber ca sa mut eax si sa nu-l mai urc pe stiva si eu nu-l vad?

				jmp bucla_while			//ecx este aux, este impartit la 10, pot continua; suma=eax a revenit de pe stiva

		afara_bucla_while:

		cmp eax, numar			// if eax==numar
			jne nu_e_palindrom		
			
			mov rezultat, 1			// rezltat=1
			
			jmp afara_palindrom
		
		nu_e_palindrom:
			mov rezultat, 0			//rezultat=0
			
		
		afara_palindrom:
			mov eax, rezultat
	}
	//return rezultat;
}

void removePalindrom(unsigned int arr[], unsigned int& arrSize) {
	/*
	for(int i = 0; i<arrSize;i++)
		if(estePalindrom(arr[i])){
			arrSize--;
			for(int j=i; j<arrSize; j++)
				arr[j]=arr[j+1];
		}
		
		*/
	_asm{
	
		mov eax, [ebp+8]       //incarca adresa primului element din vector in eax
		mov edi, [ebp+12]   //ebx = arrSize, de ce expres ebp+12?!
		mov ebx, [edi]

		mov ecx, 0         //initializam un contor pentru a traversa vectorul

		_bucla_for1:
			cmp ecx, ebx          //i<arrsize
				jae _vectorul_e_parcurs
				push eax					//urc vectorul pe stiva
				push ebx
				push ecx
				
				mov edx, [eax+ecx*4] 
				push edx
				call estePalindrom
				mov edx, eax					// nu mai am nevoie de edx, il pot retine rezultatul functiei Palindrom
				add esp, 4
				
				pop ecx
				pop ebx
				pop eax					//imi iau vectorul inapoi

				cmp edx, 1
					jne nu_e_palindrom
					dec ebx				///ebx--, arrSize--
					mov [edi], ebx
					push ecx				//patrez contorul i

					bucla_fordoi:
						cmp ecx, ebx		// pastrez j-ul, ca j=i
							jae _afara_bucla_for2			//if ecx < ebx; j<arrSize

							mov edx, [eax + ecx*4+4]
							mov [eax+ecx*4], edx			//arr[j]=arr[j+1]
							inc ecx						//j++
							
							jmp bucla_fordoi
							
							_afara_bucla_for2:
					pop ecx				//imi iau inapoi ecx-ul, adica i
					dec ecx				// problema era aici, eu mutam cu o pozitie inapoi elementele de pe pozitia ecx, dar nu verificam daca pe pozitia ecx s-a pus iarasi un numar palindrom
					nu_e_palindrom:
				inc ecx				//i++ | aici, si treceam pe pozitia urmatoare fara sa verific daca pe pozitia actuala s-a pus iarasi un nr palindrom
				jmp _bucla_for1

		_vectorul_e_parcurs:
		
	}
}

int main()
{
	unsigned int testArr1[] = { 1221, 2453, 1, 567765 }, testArrSize1 = 4;
	unsigned int testArr2[] = { 4837, 382, 878, 987, 11 }, testArrSize2 = 5;
	unsigned int i;

	/*
		dupa apelul functiei, ar trebui sa se afiseze la consola
		Primul vector: 2345
		Al doilea vector: 4837 382 987
	*/

	
	removePalindrom(testArr1, testArrSize1);
	removePalindrom(testArr2, testArrSize2);

	printf("Primul vector: ");
	for (i = 0; i < testArrSize1; i++)
		printf("%d ", testArr1[i]);
	
	printf("\n");

	printf("Al doilea vector: ");
	for (i = 0; i < testArrSize2; i++)
		printf("%d ", testArr2[i]);
	

	/*

	//printf("%d", estePalindrom(123321));
	unsigned int rez;
	_asm {
		mov eax, 1221
		push eax
		call estePalindrom
		mov rez, eax
		add esp, 4
		//mov rez, ecx
	}
	printf("%d", rez);
	*/
	return 0;
}