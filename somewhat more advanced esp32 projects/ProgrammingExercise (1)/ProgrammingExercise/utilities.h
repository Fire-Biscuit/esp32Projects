/*!
 * @file    utilities.h
 * 
 * @brief   This file defines the header of general functions for the project.
 * 
 * @author  Bernardo Villalba Frías  <b.r.villalba.frias@hva.nl>
 * 
 * @version 1.0
 * 
 * @date    26 September 2022
 * 
 * This program is a free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */
#ifndef UTILITIES
#define UTILITIES


/* Included libraries */
#include <time.h>        // time(), clock_gettime()
#include <stdio.h>       // printf()
#include <stdint.h>      // uint64_t
#include <stdlib.h>      // srand(), rand(), malloc(), free()
#include <signal.h>      // signal()


/* Conversion to seconds */
#define USEC_PER_NSEC     1000ULL
#define USEC_PER_SEC      1000000ULL
#define NSEC_PER_SEC      1000000000ULL


/* Enumeration to represent the possible status of the missile */
typedef enum MISSILE_STATUS {
  UNDETECTABLE,
  DETECTED,
  INTERCEPTABLE,
  INTERCEPTED,
  NOT_INTERCEPTED
} MISSILE_STATUS_T;


/// @brief Return the current time in microseconds.
///
/// This function returns the current time of the system with a microsecond
/// precision.
///
/// @return the current time.
uint64_t get_current_time(void);


/// @brief Prints the usage/help message.
///
/// This function prints out the help message of the application including
/// some details about how to properly launch the program and what arguments
/// can receive.
///
/// @param fp:       is the desired text stream to be used (stdout or stderr).
/// @param argv:     is the list of arguments.
void usage(FILE *fp, char **argv);


#endif	/* UTILITIES */
