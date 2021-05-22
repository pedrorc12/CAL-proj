#ifndef CAL_PROJECT_TESTS_H
#define CAL_PROJECT_TESTS_H

#include "../Graph.h"
#include "graphviewer.h"
#include "../Volunteer.h"
#include "../Donation.h"
#include "../DonationSolution.h"
#include "../Solver.h"

void test1();
void test2();
void test3();
void test4();

/*
 * Time complexity analysis increasing the number of volunteer at each iteration
 */
void test5();

/*
 * Time complexity analysis increasing the number of donations at each iteration
 */
void test6();

/*
 * Time complexity analysis increasing the number of volunteer and donation at each iteration
 * a combination of test 5 and 6
 */
void test7();

#endif //CAL_PROJECT_TESTS_H
