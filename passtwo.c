#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_OPCODE 20
#define MAX_OBJODE 70

int start_addr = 0, program_length = 0;
char program_name[20] = "";

typedef struct {
  char label[20];
  int address;
} Symtab;

typedef struct {
  char opcode[10];
  char code[10];
} Optab;

typedef struct {
  int address;
  char label[20];
  char opcode[20];
  char operand[20];
} Infile;

Symtab symtab[100];
Optab optab[50];
Infile infile;

void main() {
  FILE *input, *intermediate, *symtabf, *optabf, *output;
  char line[MAX_LINE];
  char text_start_addr[20], first_exec_addr[20];

  input = fopen("input.asm", "r") intermediate = fopen("intermediate.txt", "r");
  symtabf = fopen("symtab.txt", "r");
  optabf = fopen("optab.txt", "r");
  output = fopen("output.txt", "w");

  fgets(line, MAX_LINE, input)
      sscanf(line, "%x %s %s %s", &infile.address, infile.label, infile.opcode,
             infile.operand);
  if (strcmp(infile.opcode, "START") == 0) {
    start_addr = strtol(infile.operand, NULL, 16);
    strcpy(infile.label, program_name);
    text_start_addr = start_addr;
    first_exec_addr = start_addr;
    fprint(output, "H^%s^%06X^", program_name, start_addr);

    fgets(line, MAX_LINE, intermediate);
  }

  while (!feof(*intermediate)) {
    sscanf(line, "%x %s %s %s", &infile.address, infile.label, infile.opcode,
           infile.operand);:
  }
}
