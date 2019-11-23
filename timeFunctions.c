#include <stddef.h>
#include <sys/time.h>

long currentMillis(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec + currentTime.tv_usec;
}