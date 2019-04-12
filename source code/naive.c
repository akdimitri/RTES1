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
  double executionTime = atof(argv[1]);
  double intervalTime = atof(argv[2]);

  /* Loop Iterations */
  int iterations = (int) (executionTime*3600/intervalTime);
  printf("Execution Time: %lf secs\nInterval Time: %lf secs\nLoop Iterations: %d\n", executionTime*3600, intervalTime, iterations);

  /* timeStamps table */
  long double *timeStamps = ( long double*)malloc( iterations*sizeof( long double));

  /* Variables to hold timestamps */
  struct timeval start, end, startProgram, endProgram;

  /* Interval time in micro seconds */
  int uIntervalTime = (int)(intervalTime*1000000);      //1 sec = 1000000 usecs
  int i;

  printf("Interval time in microsecs: %d\n", uIntervalTime);
  gettimeofday(&startProgram, NULL);
  for( i = 1; i <= iterations; i++){
    gettimeofday(&start, NULL);
    //printf("i: %d   ",i );
    usleep( uIntervalTime);
    gettimeofday(&end, NULL);
    timeStamps[i-1] = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
    //printf("%Lf \n", timeStamps[i-1]);
  }
  gettimeofday(&endProgram, NULL);


  /* Write Results to a text file */
  FILE *fp;

  fp = fopen("./testResults", "w");
  for( i = 0; i < iterations; i++){
    fprintf(fp, "%Lf\n", timeStamps[i]);
  }

  long double time = (endProgram.tv_sec * 1000000 + endProgram.tv_usec) - (startProgram.tv_sec * 1000000 + startProgram.tv_usec);
  printf("Program's Execution Time: %Lf secs\n", time/1000000 );
  free(timeStamps);

  return 0;
}
