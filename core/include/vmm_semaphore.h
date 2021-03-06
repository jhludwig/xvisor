/**
 * Copyright (c) 2012 Anup Patel.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * @file vmm_semaphore.h
 * @author Anup Patel (anup@brainfault.org)
 * @brief Header file of sempahore locks for Orphan VCPU (or Thread).
 */

#ifndef __VMM_SEMAPHORE_H__
#define __VMM_SEMAPHORE_H__

#include <vmm_types.h>
#include <vmm_waitqueue.h>

/** Semaphore lock structure */
struct vmm_semaphore {
	u32 limit;
	u32 value;
	struct vmm_waitqueue wq;
};

/** Initialize semaphore lock */
#define INIT_SEMAPHORE(sem, value)	do { \
					(sem)->limit = (value); \
					(sem)->value = (value); \
					INIT_WAITQUEUE(&(sem)->wq, (sem)); \
					} while (0);

#define __SEMAPHORE_INITIALIZER(sem, val) \
		{ \
			.limit = (val), \
			.value = (val), \
			.wq = __WAITQUEUE_INITIALIZER((sem).wq, &(sem)), \
		}

#define DEFINE_SEMAPHORE(sem, value) \
	struct vmm_semaphore sem = __SEMAPHORE_INITIALIZER(sem)

/** Check if semaphore is available */
bool vmm_semaphore_avail(struct vmm_semaphore *sem);

/** Get maximum value (or limit) of semaphore */
u32 vmm_semaphore_limit(struct vmm_semaphore *sem);

/** Release (or increment) semaphore */
int vmm_semaphore_up(struct vmm_semaphore *sem);

/** Acquire (or decrement) semaphore */
int vmm_semaphore_down(struct vmm_semaphore *sem);

/** Acquire (or decrement) semaphore with timeout */
int vmm_semaphore_down_timeout(struct vmm_semaphore *sem, u64 *timeout);

#endif /* __VMM_SEMAPHORE_H__ */
