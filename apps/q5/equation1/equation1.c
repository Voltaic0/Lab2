#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"


void main (int argc, char *argv[])
{      // Used to access missile codes in shared memory page
        // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  sem_t s_water_signal;
  sem_t s_hydro_signal;
  sem_t s_oxy_signal;
  int injections;
  int i;
  //lock_t TheLock;
  
  if (argc != 6) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  s_procs_completed = dstrtol(argv[1], NULL, 10);
  injections = dstrtol(argv[2], NULL, 10);
  s_water_signal = dstrtol(argv[3], NULL, 10);
  s_hydro_signal = dstrtol(argv[4], NULL, 10);
  s_oxy_signal = dstrtol(argv[5], NULL, 10);
  

  
  for (i = 0; i < injections; i++){
	  sem_wait(s_water_signal);
	  sem_wait(s_water_signal);
	  Printf("2 H2O -> 2 H2 + O2 reacted, PID: %d\n", getpid());
	  sem_signal(s_hydro_signal);
	  sem_signal(s_hydro_signal);
	  sem_signal(s_oxy_signal);
	  
	  
  }
  
  
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}