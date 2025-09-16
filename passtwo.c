#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_OPCODE 20
#define MAX_OBJODE 70

typedef struct {
  char label[20];
  int address;
} Symtab;

typedef struct {
  char opcode[10];
  char code[10];
} Optab;

Symtab symtab[100];
Optab optab[50];

void main() {
  FILE *intermediate, *output;
  input = fopen("intermediate.txt", const char *)
}
