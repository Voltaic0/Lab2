#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{
  buffer *Buffer;        // Used to access missile codes in shared memory page
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  char taken;
  int i;
  lock_t TheLock;
  
  if (argc != 3) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);
  TheLock = dstrtol(argv[3], NULL, 10);

  // Map shared memory page into this process's memory space
  if ((Buffer = (buffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }

  
  for (i = 0; i < 11; i++){
	  lock_acquire(TheLock);
	  if(!(Buffer->head == Buffer->tail)){
		  taken = Buffer->chars[Buffer->tail];
		  Buffer->tail = (++Buffer->tail) % 10;
		  Printf("Consumer "); Printf(argv[2]); Printf(" removed: "); Printf(taken); Printf("\n");
	  }
	  else{
		  i--;
	  }
	  
	  
	  
	  lock_release(TheLock);
	  
  }
  
  
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}