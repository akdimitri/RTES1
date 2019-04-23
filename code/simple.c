#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  /* Check number of arguments */
  if(argc != 3){
    printf("ERROR: WRONG NUMBER OF INPUT ARGUMENTS\nEXITING...\n");
    return 1;
  }

  /* Variables declaration */
  unsigned int INTERVAL_USEC, EXECUTION_TIME;
  long unsigned int iterations, i;
  long long unsigned int *TIMESTAMPS;
  double INTERVAL;
  struct timeval SAMPLE;

  /* Initializations */
  iterations = ( long unsigned int)(atof( argv[1])*3600/atof( argv[2])) + 1;      // hours*3600/interval_in_seconds + 1
  INTERVAL = atof( argv[2]);    // interval time between 2 sleeps() in seconds
  INTERVAL_USEC = ( unsigned int)( INTERVAL*1000000);   // usec = sec*1000000
  TIMESTAMPS = ( long long unsigned int*)malloc( iterations*sizeof( long long unsigned int));

  /* Print execution information */
  printf("EXECUTION TIME: %.2lf HOURS or %ld SECS\n", atof( argv[1]), (long int)(3600*atof( argv[1])));
  printf("INTERVAL TIME: %.2lf SECS or %u USECS\n", INTERVAL, INTERVAL_USEC);
  printf("ITERATIONS: %lu\n", iterations);
  printf("ALLOCATION SIZE: %lu BYTES\n", iterations*sizeof( long long unsigned int));

  /* Time sampling */
  printf("TIME SAMPLING:...\n");
  /* 1st timestamp */
  gettimeofday( &SAMPLE, NULL);
  TIMESTAMPS[0] = (long long unsigned int)(SAMPLE.tv_sec*1000000 + SAMPLE.tv_usec);
  //printf("TIMESTAMP[0] = %Lu\n", TIMESTAMPS[0]);
  /* 2nd to Nth timestamp */
  for( i = 1; i < iterations; i++){
    usleep( INTERVAL_USEC);
    gettimeofday( &SAMPLE, NULL);
    TIMESTAMPS[i] = (long long unsigned int)(SAMPLE.tv_sec*1000000 + SAMPLE.tv_usec);
    //printf("TIMESTAMP[%lu] = %Lu\n", i, TIMESTAMPS[i]);
  }
  printf("TIME SAMPLING: DONE\n");

  /* Write results to file */
  FILE *fp;
  if(fp = fopen("simpleResults.txt", "w")){
    for( i = 0; i < iterations; i++){
      fprintf( fp, "%Lu\n", TIMESTAMPS[i]);
    }
    fclose(fp);
  }
  else{
    printf("ERROR: cannot open new file\nEXITING...\n");
    return 2;
  }
  printf("WRITING RESULTS TO FILE: DONE\n");

  /* Free allocated space */
  free(TIMESTAMPS);

  printf("EXECUTION: DONE\n");
  return 0;
}
