#include <stdio.h>

int main(unsigned n) {
        unsigned n = argc;
        unsigned a, b;
        printf("%d\n",n);

        // mov  edx, edi
        // shr  edx
        // or   edx, edi
        // mov  eax, edx
        a = b = (n >> 1) | n;

        // shr  eax, 2
        // or   eax, edx
        // mov  edx, eax
        b = a = (a >> 2) | b;

        // shr  edx, 4
        // or   edx, eax
        // mov  eax, edx
        a = b = (b >> 4) | a;

        // shr  eax, 8
        // or   eax, edx
        // mov  edx, eax
        b = a = (a >> 8) | b;

        // shr  edx, 16
        // or   edx, eax
        b = (b >> 16) | a;

        // imul eax, edx, 79355661 ; 0x4badf0d
        // shr  eax, 26
        a = (b * 0x4badf0d) >> 26;

        // mov  eax, DWORD PTR v[0+rax*4]
        // ret
        printf("%d\n",a);
}