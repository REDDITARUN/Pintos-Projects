#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/thread.h"

/*This is a basic test to check functionality of thread_set_priority for a single thread. Operating Systems PA0*/

static thread_func change_prio;

void 
pa0( void ){
	
	ASSERT(!thread_mlfqs);
	msg("Test 0 beginning");
	thread_create("test_thread", PRI_MAX, change_prio, NULL);
	thread_yield();
	msg("Test 0 Finished");
}

/* Function Pointer given to thread_create() in order to run properly */
static void 
change_prio( void *aux UNUSED ){
	int i;
	msg("Test thread priority is %d", thread_current()->priority);
	for(i = 0 ; i < 5; ++i){
		struct thread *t = thread_current();
		thread_set_priority( (t->priority)-1 );
		msg("Test thread priority is %d", thread_current()->priority);
	}
}
