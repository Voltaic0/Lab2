#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"
//#include "stdio.h"

#include "spawn.h"

void main (int argc, char *argv[])
{
  int numprocs = 5;               // Used to store number of processes to create
  sem_t s_procs_completed;        // Semaphore used to wait until all spawned processes have completed
  sem_t s_water_made;
  sem_t s_suloxy_made;
  sem_t s_hydro_made;
  sem_t s_oxy_made;
  sem_t s_sultwo_made; 
  
  char s_procs_completed_str[10]; // Used as command-line argument to pass page_mapped handle to new processes
  char s_water_str[10];
  char s_suloxy_str[10];
  char s_hydro_str[10];
  char s_oxy_str[10];
  char s_sultwo_str[10];
  char first_eq[10];
  char second_eq[10];
  char third_eq[10];
  
  int water = 0;
  int sul_oxy = 0;
  
  int first_equation = 0;
  int second_equation = 0;
  int third_equation = 0;
  

  if (argc != 3) {
    Printf("Usage: "); Printf(argv[0]); Printf(" <number of processes to create>\n");
    Exit();
  }

  // Convert string from ascii command line argument to integer number
  water = dstrtol(argv[1], NULL, 10); // the "10" means base 10
  sul_oxy = dstrtol(argv[2], NULL, 10);
  Printf("Creating %d H2Os and %d SO4s.\n", water, sul_oxy);
  
  first_equation = water /2;
  second_equation = sul_oxy;
  
  if((water / 2) * 2 >= sul_oxy){
	  third_equation = sul_oxy;
  }else{
	  third_equation = (water /2) * 2;
  }
  //Printf("%d, %d, %d \n", first_equation, second_equation, third_equation);
  

  // Create semaphore to not exit this process until all other processes 
  // have signalled that they are complete.  To do this, we will initialize
  // the semaphore to (-1) * (number of signals), where "number of signals"
  // should be equal to the number of processes we're spawning - 1.  Once 
  // each of the processes has signaled, the semaphore should be back to
  // zero and the final sem_wait below will return.
  if ((s_procs_completed = sem_create(-(numprocs-1))) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }
  //Create H2O Semaphore
  if ((s_water_made = sem_create(0)) == SYNC_FAIL) {
      Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
      Exit();
    }
  //Create SO4 Semaphore
    if ((s_suloxy_made = sem_create((0))) == SYNC_FAIL) {
        Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
        Exit();
      }
   //Create H2 Semaphore
     if ((s_hydro_made = sem_create((0))) == SYNC_FAIL) {
         Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
         Exit();
      }
  //Create O2 Semaphore
	  if ((s_oxy_made = sem_create((0))) == SYNC_FAIL) {
		  Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
		  Exit();
	   }
  //Create SO2 Semaphore
	  if ((s_sultwo_made = sem_create((0))) == SYNC_FAIL) {
		  Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
		  Exit();
	   }	  
	  
  // Setup the command-line arguments for the new process.  We're going to
  // pass the handles to the shared memory page and the semaphore as strings
  // on the command line, so we must first convert them from ints to strings.
  ditoa(s_procs_completed, s_procs_completed_str);
  ditoa(s_water_made, s_water_str);
  ditoa(s_suloxy_made, s_suloxy_str);
  ditoa(s_hydro_made, s_hydro_str);
  ditoa(s_oxy_made, s_oxy_str);
  ditoa(s_sultwo_made, s_sultwo_str);
  ditoa(first_equation, first_eq);
  ditoa(second_equation, second_eq);
  ditoa(third_equation, third_eq);
  

  // Now we can create the processes.  Note that you MUST end your call to
  // process_create with a NULL argument so that the operating system
  // knows how many arguments you are sending.
  //ADDING
  //l = lock_create();

  
  process_create(FILENAME_TO_RUN, s_procs_completed_str, argv[1], s_water_str, NULL); // pro
  process_create(FILENAME_TO_RUNTOO, s_procs_completed_str, argv[2], s_suloxy_str, NULL);
  process_create(FILENAME_TO_RUNTHREE, s_procs_completed_str, first_eq, s_water_str, s_hydro_str, s_oxy_str, NULL);
  process_create(FILENAME_TO_RUNFOUR, s_procs_completed_str, second_eq, s_suloxy_str, s_sultwo_str, s_oxy_str, NULL);
  process_create(FILENAME_TO_RUNFIVE, s_procs_completed_str, third_eq, s_sultwo_str, s_hydro_str, s_oxy_str, NULL); 
  
  
  
  // And finally, wait until all spawned processes have finished.
  if (sem_wait(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
    Exit();
  }
  Printf("%d H2O's left. %d H2's left over. %d O2's left over. %d SO2's leftover.", 
  		  (water%2), ((water/2)*2-third_equation), (water/2)+sul_oxy-third_equation, sul_oxy - third_equation);
  Printf("%d \nH2SO4's created. \n", third_equation);
  Printf("All other processes completed, exiting main process.\n");
}
