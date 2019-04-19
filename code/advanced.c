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
  int i, iterations, uIntervalTime, delay;
  double executionTime, intervalTime;
  long long int *timeStamps = ( long long int*)malloc( ((unsigned int) iterations)*sizeof( long long int));
  struct timeval sample;

  executionTime = atof(argv[1]);
  intervalTime = atof(argv[2]);
  iterations = (int)(executionTime*3600/intervalTime) + 1;
  uIntervalTime = (int)(intervalTime*1000000);      //1 sec = 1000000 usecs

  printf("Execution Time: %.2lf HOURS or %.2lf MINUTES\n", executionTime, executionTime*60);
  printf("Interval Time: %.2lf SECONDS\n", intervalTime);
  printf("Interval Time: %d MICRO SECONDS\n", uIntervalTime);
  printf("Iterations: %d\n", iterations);

  printf("Time Sampling:... \n");

  /* 1st Time Stamp */
  gettimeofday(&sample, NULL);
  timeStamps[0] = (sample.tv_sec * 1000000) + sample.tv_usec;
  usleep( (unsigned int)uIntervalTime);

  /* 2nd to Nth Time Stamps */
  for( i = 1; i <= (iterations - 2); i++){
    gettimeofday(&sample, NULL);
    timeStamps[i] = (sample.tv_sec * 1000000) + sample.tv_usec;
    delay = (int)(timeStamps[i] - (i*uIntervalTime + timeStamps[0]));
    printf("TIMESATMP: %Ld usecs \t DELAY = %d\n", timeStamps[i], delay);
    //if(delay < uIntervalTime)
    usleep( (unsigned int)(uIntervalTime - delay));
  }

  /* Nth + 1 Time Stamp */
  gettimeofday(&sample, NULL);
  timeStamps[iterations - 1] = sample.tv_sec * 1000000 + sample.tv_usec;

  printf("Time Sampling: DONE\n");

  /* Write Results to a text file */
  FILE *fp;
  fp =  fopen("./testResults.txt", "w");
  for( i = 0; i < iterations; i++){
    fprintf(fp, "%Ld\n", timeStamps[i]);
  }
  fclose(fp);

  printf("Write Results to FILE: DONE\n");

  free(timeStamps);

  return 0;
}
