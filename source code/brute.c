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
  struct timeval start, end;

  /* Interval time in micro seconds */
  unsigned long int uIntervalTime = (unsigned long int)(intervalTime*1000000);      //1 sec = 1000000 usecs
  int i;

  //printf("Interval time in microsecs: %ld\n", uIntervalTime);
  unsigned long int delay = 0;
  gettimeofday(&start, NULL);
  timeStamps[0] = (start.tv_sec * 1000000 + start.tv_usec);
  for( i = 1; i < iterations; i++){

    //printf("i: %d   ",i );
    usleep( uIntervalTime - delay);
    gettimeofday(&end, NULL);
    timeStamps[i] = (end.tv_sec * 1000000 + end.tv_usec) ;
    delay = timeStamps[i] - timeStamps[i-1] + uIntervalTime;
    //printf("%Lf \n", timeStamps[i-1]);
  }


  /* Write Results to a text file */
  FILE *fp;

  fp = fopen("./testResultsBrute", "w");
  for( i = 0; i < iterations; i++){
    fprintf(fp, "%Lf\n", timeStamps[i]);
  }

  long double time = timeStamps[iterations-1] - timeStamps[0];
  printf("Program's Execution Time: %Lf secs\n", time/1000000 );
  free(timeStamps);

  return 0;
}
