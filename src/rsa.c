#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct Pubkey {
    unsigned int n, e;
};
struct Privkey {
    unsigned int n, d;
};

unsigned int const P = 59, Q = 101, K = 2;

size_t bufferlen(unsigned int *const str) {
    size_t i = 0;
    while (str[i++] != -1)
        ;
    return i - 1;
}

// Converting char array into unsigned int array to prevent integer-overflow
void convert(char *const str, unsigned int *const buffer) {
    size_t i;
    for (i = 0; i < strlen(str); i++) {
        buffer[i] = (unsigned int)str[i];
    }
    buffer[i] = -1; // null-terminator
}

// Print unsigned int buffer
void printBuffer(unsigned int *const str) {
    for (size_t i = 0; i < bufferlen(str); ++i) {
        printf("%u ", str[i]);
    }
}

// using RSA-encryption algorithm
void encrypt(unsigned int *const str, struct Pubkey pubkey) {
    for (size_t i = 0; i < bufferlen(str); ++i) {
        str[i] = fastpowmod(str[i], pubkey.e, pubkey.n);
    }
}

// using RSA-decryption algorithm
void decrypt(unsigned int *const str, struct Privkey privkey) {
    for (size_t i = 0; i < bufferlen(str); ++i) {
        str[i] = fastpowmod(str[i], privkey.d, privkey.n);
    }
}

int receive_input()
{

    // Calculate Pub, Priv

    unsigned int n = P * Q;
    unsigned int phi = (P - 1) * (Q - 1);
    unsigned int e = 2;
    while (e < phi && gcd(++e, phi) != 1)
        ;

    unsigned int d = (1 + (K * phi)) / e;

    unsigned int command_flag;
    printf("RSA Calculator\n---Properties\nP=%u\nQ=%u\nK=%u\n---Commands(-1 "
           "exit)\n0.Encrypt Message\n1.Decrypt Message\n:",
           P, Q, K);
    scanf("%d", &command_flag);

    char rawstr[1000];
    unsigned int message[1000];
    if (command_flag == 0) {
        printf("Encrpyt Message: ");
        scanf("%1000s", rawstr);
        convert(rawstr, message);
        encrypt(message, (struct Pubkey){n, e});
        printBuffer(message);
        printf("\n");
    } else if (command_flag == 1) {
        printf("Decrypt Message: ");
        size_t l = 0;

        char c;
        unsigned int num = 0;
        getchar(); // trash
        while ((c = getchar()) != '\n') {
            if (isdigit(c)) {
                num = (num * 10) + (c - '0');
            } else if (c == ' ') {
                message[l++] = num;
                num = 0;
            }
        }
        message[l++] = num;
        message[l] = -1;
        decrypt(message, (struct Privkey){n, d});
        for (size_t i = 0; i < l; i++) {
            printf("%c", message[i]);
        }
        printf("\n");
    }

    return command_flag;
}

int main()
{
    while (receive_input() >= 0)
        ;
    return 0;
}