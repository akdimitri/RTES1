#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {

  if( argc != 3){
    printf("Error: Wrong number of arguments\n");
    return 1;
  }

  /* Initializations */
  int i;
  const double executionTime = atof( argv[1]);                       //execution time in hours
  const double intervalTime = atof( argv[2]);                        //interval time between timestamps in seconds
  const double iterations = 3600*executionTime/intervalTime;         //no. samples
  struct timeval sample, start, end;
  long int *timestamps = ( long int*)malloc( (( long unsigned int) iterations)*sizeof(long int));

  printf("Execution Time: %.2lf hours = %.2lf mins = %lf secs\nInterval Time: %.2lf secs\nIterations: %ld\n", executionTime, executionTime*60, executionTime*3600, intervalTime, (long unsigned int)iterations);

  /* Time Sampling */
  const unsigned int intervalTime_usec = (unsigned int)(intervalTime*1000000); printf("Interval Time: %d usecs\n", intervalTime_usec);
  gettimeofday( &start, NULL);
  for( i = 0; i < iterations; i++){
    usleep( intervalTime_usec);
    if(gettimeofday( &sample, NULL) == 0){
      timestamps[i] = sample.tv_sec*1000000 + sample.tv_usec;
      printf("%ld\n", timestamps[i]);
    }
    else{
      fprintf(stderr, "Error: gettimeofday() error\n");
    }
  }
  gettimeofday( &end, NULL);
  printf("Time sampling: Completed  ---- %lf secs\n", (double)((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec*1000000 + start.tv_usec))/1000000);

  /* Write timestamps to File */
  gettimeofday( &start, NULL);
  FILE *fp;
  fp = fopen("./timestampsResults.txt", "w");
  if (fp == NULL) {
    fprintf(stderr, "Error: Cannot open file\n");
    return 2;
  }
  for( i = 0; i < iterations; i++){
    fprintf(fp, "%ld"\r\n"", timestamps[i]);
  }
  fclose(fp);
  gettimeofday( &end, NULL);
  printf("Copying Results: Completed  ---- %lf secs\n", (double)((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec*1000000 + start.tv_usec))/1000000);
  free(timestamps);
  return 0;
}
