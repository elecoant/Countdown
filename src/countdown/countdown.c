#include "countdown.h"
#include <stdio.h>
#include <stdlib.h>

// number of possible operations (a + b, a - b, b - a, a * b, a / b, b / a)
const int OPERATIONS_SIZE = 6;

// Given an array of size 6, there are at most 15 possible subsequent operations
// between 2 numbers
const int OPERATION_STR_MAX_SIZE = 15;

bool isValidNumber(int n) {
  return (n >= 1 && n <= 10) || n == 25 || n == 50 || n == 75 || n == 100;
}

bool isValidTarget(int target) { return target > 99 && target < 1000; }

int *operations(int a, int b, char ***pcStrings) {
  int *res = (int *)malloc(OPERATIONS_SIZE * sizeof(int));

  res[0] = a + b < 1000 ? a + b : -1;
  res[1] = a - b > 0 ? a - b : -1;
  res[2] = b - a > 0 ? b - a : -1;
  res[3] = a * b < 1000 ? a * b : -1;
  res[4] = a % b == 0 ? a / b : -1;
  res[5] = b % a == 0 ? b / a : -1;

  *pcStrings = (char **)malloc(OPERATIONS_SIZE * sizeof(char *));

  // Longest possible string is "xxx + yyy = zzz" -> 15 + 1 (\0) = 16
  const int MAX_STRING_SIZE = 16;

  for (int i = 0; i < OPERATIONS_SIZE; i++) {
    (*pcStrings)[i] = (char *)malloc(MAX_STRING_SIZE * sizeof(char));
  }

  snprintf((*pcStrings)[0], MAX_STRING_SIZE, "%d + %d = %d", a, b, res[0]);
  snprintf((*pcStrings)[1], MAX_STRING_SIZE, "%d - %d = %d", a, b, res[1]);
  snprintf((*pcStrings)[2], MAX_STRING_SIZE, "%d - %d = %d", b, a, res[2]);
  snprintf((*pcStrings)[3], MAX_STRING_SIZE, "%d * %d = %d", a, b, res[3]);
  snprintf((*pcStrings)[4], MAX_STRING_SIZE, "%d / %d = %d", a, b, res[4]);
  snprintf((*pcStrings)[5], MAX_STRING_SIZE, "%d / %d = %d", b, a, res[5]);

  return res;
}

int *insertPair(int *nums, int numsSize, int i, int j, int n, int *returnSize) {
  *returnSize = numsSize - 1;
  int *res = (int *)malloc(*returnSize * sizeof(int));
  int k = 0, l = 0;
  while (k < numsSize) {
    if (k != j) {
      res[l++] = nums[k];
    }
    k++;
  }
  res[i] = n;

  return res;
}

bool hasSolutions(int *nums, int numsSize, char ***solution, int *solutionSize,
                  int target) {
  // Base case
  if (numsSize < 2) {
    return false;
  }

  int *pCombinations;
  char **pcStrings;
  int *nextNums;
  int nextNumsSize;
  bool res = false;

  int i = 0, j, k, solutionStringIndex = -1;
  while (!res && i < numsSize - 1) {
    j = i + 1;
    while (!res && j < numsSize) {
      // Get all possible operations' results for nums[i] and nums[j]
      pCombinations = operations(nums[i], nums[j], &pcStrings);
      k = 0;
      // Loop over all possible operations
      while (k < OPERATIONS_SIZE) {
        // Check if the operation results is equal to target
        if (pCombinations[k] == target) {
          res = true;
          // Initialize the solution strings array
          *solutionSize = 0;
          *solution = (char **)malloc(OPERATION_STR_MAX_SIZE * sizeof(char *));
          (*solution)[(*solutionSize)++] = pcStrings[k];
          solutionStringIndex = k;
        } else if (!res && pCombinations[k] > 0) {
          // If the operation result is not equal to target and it is a valid
          // result, Insert the last operation result in the nextNums array and
          // recurse
          nextNums =
              insertPair(nums, numsSize, i, j, pCombinations[k], &nextNumsSize);
          res |= hasSolutions(nextNums, nextNumsSize, solution, solutionSize,
                              target);
          free(nextNums);

          // If a solution has been found, add the last operation to the
          // solution strings array
          if (res) {
            (*solution)[(*solutionSize)++] = pcStrings[k];
            solutionStringIndex = k;
          }
        }

        // Free the current operation string if it is not part of the solution
        if (k != solutionStringIndex) {
          free(pcStrings[k]);
        }

        k++;
      }
      free(pcStrings);
      free(pCombinations);
      j++;
    }
    i++;
  }

  return res;
}