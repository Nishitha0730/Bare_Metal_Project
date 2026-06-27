#include <stdint.h>
#include <stdio.h>

uint8_t x = 'a';

int main(void){
    x = x & 0xF0;
    printf("value is : %d", x);
    return 0;
}