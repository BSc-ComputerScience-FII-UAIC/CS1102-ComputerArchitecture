float harmean(int* x, int nr)
{
    _asm {
        mov edi, x
        mov ebx, nr
        mov ecx, 0
        fldz
    bucla:
        cmp ebx, ecx
        je exit_bucla
        fld1
        fild dword ptr [edi + ecx * 4]
        fdivp st(1), st
        faddp st(1), st
        inc ecx
        jmp bucla
    exit_bucla:
        fild nr
        fxch st(1)
        fdivp st(1), st
        fst [ebp - 4]
        mov eax, [ebp - 4]
    }
}

float patratica(int* a, int n) {
    _asm {
        fldz  // st(0) = 0
        mov ebx, [ebp+8]
        mov ecx, [ebp+12]
    while1:
        dec ecx
        cmp ecx, 0
        jl dupa_while

        fild [ebx + 4 * ecx]  // st(1) = st(0) st(0) = a[i]
        fmul st(0), st(0)
        faddp st(1), st(0)  // st(1) = st(1) + st(0),  st(0) = st(1)
        jmp while1

        fsqrt  // st(0) = sqrt(st(0))

    dupa_while:
        // st(0) = 1/st(0)
        fild [ebp+12] // st(1) = st(0),  st(0) = n
        fdiv st(1), st(0) // st(1) = st(1)/st(0)
        fxch st(1)
        fsqrt
    }
}