#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <stdbool.h>

/**
 * @brief return true if the number is a valid number (1-10, 25, 50, 75 or 100)
 * 
 * @param n 
 * @return true 
 * @return false 
 */
bool isValidNumber(int n);

/**
 * @brief return true if the target is a valid number (100-999)
 * 
 * @param target 
 * @return true 
 * @return false 
 */
bool isValidTarget(int target);

/**
 * @brief given 2 strictly positive integers, returns the list of possible
 * results for each allowed operation (+, -, *, /). Eachs result must stay in
 * the range [1, 999]. Otherwise, it is set to -1.
 *
 * @param a
 * @param b
 * @param pcStrings the list of operations in string format (e.g. ["1 + 2 = 3",
 * "1 * 2 = 2", ...])
 * @return int*
 */
int *operations(int a, int b, char ***pcStrings);

/**
 * @brief given a list of integers nums, 2 indices i and j and an integer n,
 * returns a new list where the element at index i has been replaced with n and
 * the element at index j has been removed.
 *
 * @param nums
 * @param numsSize
 * @param i
 * @param j
 * @param n
 * @param returnSize
 * @return int*
 */
int *insertPair(int *nums, int numsSize, int i, int j, int n, int *returnSize);

/**
 * @brief  Given an array of integers nums and an integer target, return true if
 * it is possible to obtain target using the values in nums and the operations
 * (+, -, *, /) in any order.
 *
 * @param nums an array of strictly positive integers in the range [1, 999]
 * @param numsSize
 * @param solutions the list of operations to obtain target in string format
 * @param solutionsSize the number of elements in solutions
 * @param target
 * @return true
 * @return false
 */
bool hasSolutions(int *nums, int numsSize, char ***solutions,
                  int *solutionsSize, int target);

#endif