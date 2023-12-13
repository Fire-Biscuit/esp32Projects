/*!
 * @file    periodic_tasks.c
 * 
 * @brief   This file defines the implementation for the proper use of periodic
 *          tasks.
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
#include "periodic_tasks.h"


/// @brief  Add time in nanoseconds
static inline void timespec_add_ns(struct timespec *initial_time, uint64_t addition) {

  /* Add the corresponding time */
  initial_time->tv_nsec += addition;

  /* Convert the resulting nanoseconds into seconds */
  while (initial_time->tv_nsec >= NSEC_PER_SEC) {

    /* Decrement the nanoseconds (-1e9) */
    initial_time->tv_nsec -= NSEC_PER_SEC;

    /* Increment the seconds */
    initial_time->tv_sec++;

  }

}



/// @brief  Sleep until the next periodic activation
void wait_next_periodic_activation(struct periodic_task *task) {

  /* Sleep for an absolute time */
  clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &task->elapsed_time, NULL);

  /* Calculate the time for the next periodic activation */
  timespec_add_ns(&task->elapsed_time, task->period);

}



/// @brief  Set a periodic timer
struct periodic_task *start_periodic_timer(uint64_t initial_offset, uint64_t task_period) {

  struct periodic_task *task;

  /* Allocates the memory for the periodic task */
  task = malloc(sizeof(struct periodic_task));

  /* Check if the memory was properly allocated */
  if (task == NULL) {
    return NULL;
  }

  /* Obtain the current time */
  clock_gettime(CLOCK_MONOTONIC, &task->elapsed_time);

  /* Add the initial offset to the task */
  timespec_add_ns(&task->elapsed_time, initial_offset);

  /* Set the task period */
  task->period = task_period;

  return task;

}

