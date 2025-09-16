#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPCODE 100
#define MAX_OPERAND 20
#define MAX_LABEL 20
#define MAX_SYMBOL 200
#define MAX_LINE 200

int locctr = 0;
int start_addr = 0;

typedef struct {
  char opcode[MAX_OPCODE];
  char hex[10];
} Optab;

typedef struct {
  char label[MAX_LABEL];
  int address;
} Symtab;

Optab optab[MAX_OPCODE];
int optab_size = 0;

Symtab symtab[MAX_SYMBOL];
int symtab_size = 0;

void loadOptab(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Error opening optab file: %s\n", filename);
    exit(1);
  }
  while (fscanf(file, "%s %s", optab[optab_size].opcode,
                optab[optab_size].hex) != EOF) {
    optab_size++;
  }
  fclose(file);
}

int search_symbol(char *label) {
  for (int i = 0; i < symtab_size; i++) {
    if (strcmp(symtab[i].label, label) == 0)
      return i;
  }
  return -1;
}

void add_symbol(char *label, int address) {
  if (symtab_size < MAX_SYMBOL) {
    strcpy(symtab[symtab_size].label, label);
    symtab[symtab_size].address = address;
    symtab_size++;
  }
}

int is_opcode(char *opcode) {
  for (int i = 0; i < optab_size; i++) {
    if (strcmp(optab[i].opcode, opcode) == 0)
      return 1;
  }
  return 0;
}

int main() {
  FILE *input, *intermediate;
  char line[MAX_LINE];
  char label[MAX_LABEL], opcode[MAX_OPCODE], operand[MAX_OPERAND];

  loadOptab("optab.txt");

  input = fopen("input.asm", "r");
  if (!input) {
    printf("Error opening input.asm\n");
    return 1;
  }

  intermediate = fopen("intermediate.txt", "w");
  if (!intermediate) {
    printf("Error creating intermediate.txt\n");
    return 1;
  }

  if (fgets(line, MAX_LINE, input) == NULL) {
    printf("Empty input file.\n");
    return 1;
  }

  sscanf(line, "%s %s %s", label, opcode, operand);

  if (strcmp(opcode, "START") == 0) {
    start_addr = (int)strtol(operand, NULL, 16);
    locctr = start_addr;
    fprintf(intermediate, "%04X\t%s", locctr, line);
    if (fgets(line, MAX_LINE, input) == NULL) {
      printf("No instructions after START.\n");
      return 1;
    }
  }

  while (!feof(input)) {
    label[0] = opcode[0] = operand[0] = '\0';

    // Use fgets and sscanf for flexible parsing
    if (line[0] == '*') {
      // Comment or blank label line
      sscanf(line, "%*s %s %s", opcode, operand);
      label[0] = '\0';
    } else {
      sscanf(line, "%s %s %s", label, opcode, operand);
      if (strcmp(label, "**") == 0 || label[0] == '*') {
        label[0] = '\0';
      }
    }

    if (strcmp(opcode, "END") == 0) {
      fprintf(intermediate, "\t\t%s\n", line);
      break;
    }

    // Handle label (if any)
    if (label[0] != '\0' && isalpha(label[0])) {
      if (search_symbol(label) == -1) {
        add_symbol(label, locctr);
      } else {
        printf("Duplicate symbol: %s\n", label);
        return 1;
      }
    }

    fprintf(intermediate, "%04X\t%s", locctr, line);

    // Update LOCCTR
    if (is_opcode(opcode)) {
      locctr += 3;
    } else if (strcmp(opcode, "WORD") == 0) {
      locctr += 3;
    } else if (strcmp(opcode, "RESW") == 0) {
      locctr += 3 * atoi(operand);
    } else if (strcmp(opcode, "RESB") == 0) {
      locctr += atoi(operand);
    } else if (strcmp(opcode, "BYTE") == 0) {
      if (operand[0] == 'C') {
        locctr += strlen(operand) - 3; // C'xxx'
      } else if (operand[0] == 'X') {
        locctr += (strlen(operand) - 3 + 1) / 2; // X'F1'
      }
    } else {
      printf("Warning: Unknown opcode/directive %s\n", opcode);
    }

    if (fgets(line, MAX_LINE, input) == NULL)
      break;
  }

  // Write SYMTAB
  FILE *symtab_file = fopen("symtab.txt", "w");
  if (!symtab_file) {
    printf("Error creating symtab.txt\n");
    return 1;
  }

  for (int i = 0; i < symtab_size; i++) {
    fprintf(symtab_file, "%s\t%04X\n", symtab[i].label, symtab[i].address);
  }

  fclose(symtab_file);
  fclose(input);
  fclose(intermediate);

  return 0;
}
