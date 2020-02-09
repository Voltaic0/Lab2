#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{
  buffer *Buffer;        // Used to access missile codes in shared memory page
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  //lock_t TheLock;
  char* phrase = "Hello World";
  char inserted[1];
  int i;

  if (argc != 4) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 
  
  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);
  //TheLock = dstrtol(argv[3], NULL, 10);
  
  // Map shared memory page into this process's memory space
  if ((Buffer = (buffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
  
  for(i = 0; i < 11; i++){
	  lock_acquire(Buffer->TheLock);
	  if(!((Buffer->head+1) % 10 == Buffer->tail)){
		  Buffer->chars[Buffer->head]= phrase[i];
		  inserted[0] = phrase[i];
		  Buffer->head = (++Buffer->head) % 10;
		  Printf("Producer "); Printf(argv[3]); Printf(" inserted: "); Printf(inserted); Printf("\n");
	  }
	  else{
		  i--;
	  }
	  
	  lock_release(Buffer->TheLock);
	  
  }
  
  
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}