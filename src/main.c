#include "countdown/countdown.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMS_SIZE 6
#define BUFFER_SIZE 1024

/**
 * @brief read n positive numbers from a string (ignoring all non-digit
 * characters)
 *
 * @param s
 * @param n
 * @return int*
 */
int *readNumbers(char *s, int n) {
  int *res = (int *)malloc(n * sizeof(int));

  int size = 0;

  while (*s && size < n) {
    while (*s && !isdigit(*s)) {
      s++;
    }

    if (!*s) {
      break;
    }

    while (*s && isdigit(*s)) {
      if (res[size] < 1000) {
        res[size] = res[size] * 10 + (*s - '0');
      }

      s++;
    }

    size++;
  }

  if (size < n) {
    fprintf(stderr, "Expected %d numbers but got %d\n", n, size);
    free(res);
    res = NULL;
  }

  return res;
}

int main(int argc, char *argv[]) {

  printf("   ____                  _      _                     \n");
  printf("  / ___|___  _   _ _ __ | |_ __| | _____      ___ __  \n");
  printf(" | |   / _ \\| | | | '_ \\| __/ _` |/ _ \\ \\ /\\ / / '_ \\ \n");
  printf(" | |__| (_) | |_| | | | | || (_| | (_) \\ V  V /| | | |\n");
  printf("  \\____\\___/ \\__,_|_| |_|\\__\\__,_|\\___/ \\_/\\_/ |_| |_| "
         "v1.0\n\n");

  char inputBuffer[BUFFER_SIZE];

  printf("Enter 6 space separated numbers (1-10, 25, 50, 75 or 100): ");

  if (!fgets(inputBuffer, BUFFER_SIZE, stdin)) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }

  int *nums = readNumbers(inputBuffer, NUMS_SIZE);

  if (!nums) {
    return 1;
  }

  for (int i = 0; i < NUMS_SIZE; i++) {
    if (!isValidNumber(nums[i])) {
      fprintf(stderr, "Invalid number: %d\n", nums[i]);
      return 1;
    }
  }

  printf("Enter target number (100-999): ");

  if (!fgets(inputBuffer, BUFFER_SIZE, stdin)) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }

  int *targets = readNumbers(inputBuffer, 1);

  if (!isValidTarget(targets[0])) {
    fprintf(stderr, "Invalid target: %d\n", targets[0]);
    return 1;
  }

  char **solution;
  int solutionSize;

  if (hasSolutions(nums, NUMS_SIZE, &solution, &solutionSize, targets[0])) {
    printf("\nSolution:\n");
    for (int i = solutionSize - 1; i >= 0; i--) {
      printf("%s\n", solution[i]);
      free(solution[i]);
    }
    free(solution);
  } else {
    printf("No solution found\n");
  }

  free(nums);
  free(targets);

  return 0;
}