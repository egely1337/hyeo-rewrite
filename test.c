#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PLAYER_JUMP 0b00000001
#define PLAYER_DIE 	0b00000010
#define PLAYER_KILL 0b00000100


// AND & = ikiside 1 ise, sonuç 1'dir
// OR | = ikisinden biri 1 ise, sonuç 1'dir
// XOR ^ = iki bitten biri farklıysa, sonuç 1'dir
// Invert ~


// 0b10000000
// 0b00000001
// 0b10000000

int _PlayerStatus = 0;

char* ithex(int a) {
    char* ascii_numbers = (char*)"0123456789ABCDEF";
    char* res;
    int i = 0;
    uint8_t nibble;

    do {
        nibble = (uint8_t)a & 0x0F;
        nibble = ascii_numbers[nibble];
        res[i] = nibble;
        a >>= 4;
        i++;
    } while(a > 0);

    res[i] = '\0';
    return res;
}

// i = 14; // Bit pattern 00001110
// j = i >> 1; // here we have the bit pattern shifted by 1 thus we get 00000111 = 7 which is 14/2

int main(int argc, char** argv) {
	printf("%s\n", ithex(0xDEADBEEF));
}