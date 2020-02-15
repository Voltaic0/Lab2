#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"


void main (int argc, char *argv[])
{      // Used to access missile codes in shared memory page
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  sem_t s_water_signal;
  int injections;
  int i;
  //lock_t TheLock;
  
  if (argc != 4) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  s_procs_completed = dstrtol(argv[1], NULL, 10);
  injections = dstrtol(argv[2], NULL, 10);
  s_water_signal = dstrtol(argv[3], NULL, 10);
  

  
  for (i = 0; i < injections; i++){
	  Printf("H2O injected into Radeon atmosphere, PID: %d\n", getpid());
	  if(sem_signal(s_water_signal) != SYNC_SUCCESS) {
	      Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
	      Exit();
	    }
	  
  }
  
  
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}