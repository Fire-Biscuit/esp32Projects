/*!
 * @file    utilities.c
 * 
 * @brief   This file defines the implementation of general functions for the
 *          project.
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
#include "utilities.h"


/// @brief Return the current time in microseconds
uint64_t get_current_time(void) {

  struct timespec time;

  /* Obtain the time */
  clock_gettime(CLOCK_MONOTONIC, &time);

  /* Convert it in microseconds */
  return (uint64_t)((time.tv_sec * USEC_PER_SEC) + (time.tv_nsec / USEC_PER_NSEC));

}


/// @brief Prints the help message
void usage(FILE *fp, char **argv) {

  fprintf(fp,
    "Usage: %s [options]\n\n"
    "Version 1.0\n"
    "Options:\n"
    "-h | --help          Print this message\n"
    "\n"
    "Example usage: ./main -h \n"
    "Prints the help message.\n\n",
    argv[0]);

}

