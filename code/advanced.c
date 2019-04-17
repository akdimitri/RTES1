#include <stdio.h>                /* printf() */
#include <sys/time.h>             /* gettimeofday() */
#include <unistd.h>               /* usleep() */
#include <stdlib.h>               /* atof(), malloc() */

int main(int argc, char const *argv[]) {
  /* Check of available inputs */
  if( argc != 3){
    printf("Error: Program's Execution need two(2) arguments\n");
    return 1;
  }

  /* Execution Time of the test to be performed
   * in Hours. Interval time between each sample in
   * seconds.
   */
  int i;
  double executionTime = atof(argv[1]);
  double intervalTime = atof(argv[2]);
  int iterations = (int)(executionTime*3600/intervalTime) + 1;
  struct timeval sample;
  long int *timeStamps = ( long int*)malloc( ((unsigned int) iterations)*sizeof( long int));
  unsigned int uIntervalTime = (unsigned int)(intervalTime*1000000);      //1 sec = 1000000 usecs
  int delay = 0;
  
  printf("Execution Time: %.2lf HOURS or %.2lf MINUTES\n", executionTime, executionTime*60);
  printf("Interval Time: %.2lf SECONDS\n", intervalTime);
  printf("Interval Time: %u MICRO SECONDS\n", uIntervalTime);


  printf("Time Sampling:... \n");
  /* 1st Time Stamp */
  gettimeofday(&sample, NULL);
  timeStamps[0] = sample.tv_sec * 1000000 + sample.tv_usec;
  usleep( uIntervalTime);
  
  /* 2nd to Nth Time Stamps */
  for( i = 1; i < (iterations - 1); i++){
    gettimeofday(&sample, NULL);
    timeStamps[i] = sample.tv_sec * 1000000 + sample.tv_usec;
    delay = timeStamps[i] - (i*uIntervalTime + timeStamps[0]);
    if(delay > uIntervalTime){
      printf("Negative Argument in USLEEP\n");
     return 3;
    }
    usleep( uIntervalTime - delay);    
  }

  /* Nth + 1 Time Stamp */
  gettimeofday(&sample, NULL);
  timeStamps[iterations - 1] = sample.tv_sec * 1000000 + sample.tv_usec;

  printf("Time Sampling: DONE\n");

  /* Write Results to a text file */
  FILE *fp = fopen("./WithTimestampsCheck/testResults.txt", "w");
  for( i = 0; i < iterations; i++){
    fprintf(fp, "%lu\n", timeStamps[i]);
  }
  fclose(fp);

  printf("Write Results to FILE: DONE\n");

  free(timeStamps);

  return 0;
}
