/*!
 * @file    periodic_tasks.h
 * 
 * @brief   This file defines the header for the proper use of periodic tasks.
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
#ifndef PERIODIC_TASK
#define PERIODIC_TASK


#include "utilities.h"


/* Structure to represent the periodic task */
struct periodic_task {

  struct timespec elapsed_time;     // Structure for the timer specification.
  uint64_t period;                  // Task period.

};



/// @brief Set a periodic timer.
///
/// This function defines an initializes a periodic task.
///
/// @param i_o:  is the initial offset of the task.
/// @param t_p:  is the period of the task.
///
/// @return a pointer to the periodic task.
struct periodic_task *start_periodic_timer(uint64_t i_o, uint64_t t_p);



/// @brief Sleep until the next activation.
///
/// This function make the program sleep until the next periodic activation.
///
/// @param t:  is the periodic task to be activated.
void wait_next_periodic_activation(struct periodic_task *t);


#endif	/* PERIODIC_TASK */
