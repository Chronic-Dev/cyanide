/*
 *
 *  greenpois0n - payload/include/lock.h
 *  (c) 2010 Chronic-Dev Team
 *
 */

#ifndef LOCK_H
#define LOCK_H

void enter_critical_section();
void exit_critical_section();

void enable_irq();
void disable_irq();

#endif /* LOCK_H */

