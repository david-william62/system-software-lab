#include <stdio.h>
#define R 10
#define C 10

typedef enum {
  true = 1,
  false = 0
} bool;

typedef struct {
  int avail[R];
  int max[R][C];
  int alloc[R][C];
  int need[R][C];
} Value;

int n, m;

Value getData() {
  Value v;
  int i, j;

  printf("\nEnter available resources:\n");
  for (i = 0; i < m; i++) {
    printf("avail[%d]: ", i);
    scanf("%d", &v.avail[i]);
  }

  printf("\nEnter Max need of Processes:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("max[%d][%d]: ", i, j);
      scanf("%d", &v.max[i][j]);
    }
  }

  printf("\nEnter Allocation of Processes:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("alloc[%d][%d]: ", i, j);
      scanf("%d", &v.alloc[i][j]);

      v.need[i][j] = v.max[i][j] - v.alloc[i][j];
    }
  }

  return v;
}

bool isDeadlocked(Value v) {
  int finish[R] = {0};
  int work[C];
  int i, j;

  for (j = 0; j < m; j++) {
    work[j] = v.avail[j];
  }

  bool changed = true;
  while (changed) {
    changed = false;
    for (i = 0; i < n; i++) {
      if (!finish[i]) {
        bool canRun = true;
        for (j = 0; j < m; j++) {
          if (v.need[i][j] > work[j]) {
            canRun = false;
            break;
          }
        }
        if (canRun) {
          for (j = 0; j < m; j++) {
            work[j] += v.alloc[i][j];
          }
          finish[i] = 1;
          changed = true;
        }
      }
    }
  }

  for (i = 0; i < n; i++) {
    if (!finish[i]) {
      return true;  // Deadlock detected
    }
  }
  return false;  // No deadlock, safe state
}

void main() {
  printf("Enter number of Processes: ");
  scanf("%d", &n);
  printf("Enter number of Resource Types: ");
  scanf("%d", &m);

  int avail[R], max[R][C], alloc[R][C], need[R][C];

  Value v = getData();

  for (int i = 0; i < n; i++) {
    avail[i] = v.avail[i];
    for (int j = 0; j < m; j++) {
      max[i][j] = v.max[i][j];
      alloc[i][j] = v.alloc[i][j];
      need[i][j] = v.need[i][j];
    }
  }

  if (isDeadlocked(v)) {
    printf("\nSystem is in DEADLOCKED state.\n");
  } else {
    printf("\nSystem is in SAFE state.\n");
  }
}


