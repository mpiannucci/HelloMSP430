/**
 * timer.h
 *
 * Interface for the timers on the msp430.
 *
 * @author Matthew Iannucci, 2015
 */
#ifndef TIMER_H
#define TIMER_H

/**
 * Timer Mode abstraction types
 * Up: Count up to CCR0 capture register
 * UP_CONTINUOUS: Count up continuously
 * UP_DOWN: Count up to CCR0, then back to 0
 */
typedef enum {
    UP,
    UP_CONTINUOUS,
    UP_DOWN
} Timer_Mode;

/**
 * Initialize Timer A
 */
void timer_a_init(void);

/**
 * Set the isr function pointer for CCR0 interrupts
 *
 * @param[in] isr_ptr Function pointer to call on interrupt
 */
void timer_a_set_isr(void (*isr_ptr)(void));

/**
 * Set the threhold for the counter to count to
 * This sets the value of the CCR0 capture register
 *
 * @param count The count in micro seconds
 */
void timer_a_set_count(int count);

/**
 * Start the timer with the given mode
 *
 * @param mode The mode for the timer to function
 */
void timer_a_start(Timer_Mode mode);

/**
 * Stop the timer where it is
 */
void timer_a_stop(void);

/**
 * Reset the timer to 0
 */
void timer_a_reset(void);

/**
 * Enable or disable timer interrupts
 *
 * @param enable 1 for enabled, 0 for disabled
 */
void timer_a_enable_isr(int enable);

/**
 * Get the count from the timer register
 *
 * @return  The count from the timer
 */
unsigned char timer_a_count(void);

#endif // TIMER_H