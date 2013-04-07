To work well with makefile I change all file with ".c" to ".cc"
Due to the difference between g++ and gcc.

OS_project1
===========
1.MyCopy_core.c directly copy the file.
  MyCopy.c copy the file and calculate the execution time.

2.ForkCopy_core.c copy the file in a child process.
  ForkCopy.c copy the file and calculate the execution time.

3.PipeCopy_core.c copy the file during a pipe which gives communication between parent and child process.
  PipeCopy.c copy the file and calculate the execution time.

4.MyShell.c execute the command without arguments.

5.MoreShell.c execute the command with arguments.

6.DupShell.c execute the command with "|".

7.Mss_core.c mergesort the data in only one thread.
  MergesortSingle.c sort the data and calculate the execution time.

8.Msm_core.c mergesort the data in many threads 
  MergesortMulti.c sort the data and calculate the execution time.

9.BurgerBuddies.c imitate the relationship between cooks,      cashiers and customers to avoid contradicion and starvaiotn.

10.produceData.c procduce the data for mergesort.