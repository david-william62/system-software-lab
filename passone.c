#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPCODE 10
#define MAX_OPERAND 20
#define MAX_LABEL 20
#define MAX_SYMBOL 200
#define MAX_LINE 200

int locctr = 0;
int start_addr = 0;
int s = -1, o = -1;

typedef struct {
  char opcode[MAX_OPCODE];
  char hex[10]
} Optab;

typedef struct {
  char label[MAX_LABEL];
  int address;
} Symtab;

Optab optab[MAX_OPCODE];
int optab_size = 0;

Symtab symtab[MAX_SYMBOL];
int symtab_size = 0;

void loadOptab(char *filename) {
  FILE *file = fopen(filename, "r");
  while (fscanf(file, "%s %s", optab[optab_size].opcode,
                optab[optab_size].hex) != EOF) {
    optab_size++;
    if (optab_size >= MAX_OPCODE) {
      printf("Optab size exceeded");
      break;
    }
  }
  fclose(file);
}

int search_symbol(char *label) {
  for (int i = 0; i < symtab_size; i++) {
    if (strcmp(symtab[i].label, label) == 0)
      return i;
    i++;
  }
}

void add_symbol(char *label, int address) {
  if (symcount < MAX_LABEL) {
    strcpy(symtab[symtab_size].label, label);
    symtab[symtab_size].address = address;
  }
}

void main() {
  FILE *input, *intermediate;
  char line[MAX_LINE];
  char label[MAX_LABEL], opcode[MAX_OPCODE], operand[MAX_OPERAND];
  int line_num = 0;

  input = fopen("input.asm", "r");
  if (input == NULL) {
    printf("Error opening input file. \n");
    return;
  }

  intermediate = fopen("intermediate.txt", "w");
  if (intermediate == NULL) {
    printf("Error creating intermediate file.\n");
    return;
  }
  loadOptab("optab.txt");
  fgets(line, MAX_LINE, input);
  sscanf(line, "%s %s %s", label, opcode, operand);

  if (strcmp(opcode, "START") == 0) {
    start_addr = (int)strtol(operand, NULL, 16);
    locctr = start_addr;
    fprintf(intermediate, "%04X\t%s", locctr, line);
    fgets(line, MAX_LINE, input);
  }

  while (!feof(input)) {
    label[0] = opcode[0] = operand[0] = '\0';
    sscanf(line, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "END") == 0) {
      fprintf(intermediate, "\t\t%s\n", line);
      break;
    }
    if (label[0] != '/0') {
      if (search_symbol(label) == -1)
        add_symbol(label, locctr);
      else {
        printf("Duplicate Symbol");
        return;
      }
    }

    fprintf(intermediate, "%04X\t%s", locctr, line);
  }
}
