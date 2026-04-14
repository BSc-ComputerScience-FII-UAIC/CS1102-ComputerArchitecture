#include <cstdio>

//Functia returneaza numarul de perechi din sirul s formate din 2 caractere consecutive in care primul este o
//vocala si al doilea este o consoana.

int GetNrVocaleConsoane(char* s) {
	_asm {
		mov ebx, s
		mov eax, 0		//contor perechi
		mov ecx, 0		//contor

		_bucla:
			mov dl, [ebx+ecx]
			cmp dl, '\0'
				je _finito

					cmp dl, 'a'
						jne	_urmVocala1
						jmp	_controlConsoana
				
				_urmVocala1:	
					cmp dl, 'A'				//in cazul in care propozita incepe cu litera mare
						jne	_urmVocala2
						jmp	_controlConsoana

				_urmVocala2 :
					cmp dl, 'e'
						jne	_urmVocala3
						jmp	_controlConsoana

				_urmVocala3 :
					cmp dl, 'E'
						jne	_urmVocala4
						jmp	_controlConsoana

				_urmVocala4 :
					cmp dl, 'i'
						jne	_urmVocala5
						jmp	_controlConsoana

				_urmVocala5 :
					cmp dl, 'I'
						jne	_urmVocala6
						jmp	_controlConsoana

				_urmVocala6 :
					cmp dl, 'o'
						jne	_urmVocala7
						jmp	_controlConsoana

				_urmVocala7 :
					cmp dl, 'O'
						jne	_urmVocala8
						jmp	_controlConsoana

				_urmVocala8 :
					cmp dl, 'u'
						jne	_urmVocala9
						jmp	_controlConsoana

				_urmVocala9 :
					cmp dl, 'U'
						jne	_nuEVocala
						jmp	_controlConsoana



				_controlConsoana:
					mov dh, [ebx + ecx + 1]

					cmp dh, 'a'
						je _eVocala 

					cmp dh, 'e'
						je _eVocala

					cmp dh, 'i'
						je _eVocala

					cmp dh, 'o'
						je _eVocala

					cmp dh, 'u'
						je _eVocala

					cmp dh, ' '
						je _eVocala

					cmp dh, '\0'
						je _eVocala

					// si orice alte caractere; exista totusi posibilitatea unei alte bucle cu un vector declarat local si sa trec prin el, dar am atins deja POC-ul

					inc eax
					inc ecx		//de ce sa nu incrementez de 2 ori? stiind ca pe pozitia 2 din pereche am un caracter care nu e vocala 
								//[tinand cont ca se va numara si pentru alte caractere], trec peste pereche

				_eVocala:
				_nuEVocala:
					inc ecx

				jmp _bucla

		_finito:

	}
}

int main() {
	char s[] = { "Azi am examen la arhitectura\0" };
	printf("%d", GetNrVocaleConsoane(s));		//se va afisa 9
}