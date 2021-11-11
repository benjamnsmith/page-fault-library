// Source: https://stackoverflow.com/questions/23302763/measure-page-faults-from-a-c-program


#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct perf_event_attr attrs;

int record_fd;

int page_faults;

int begin_recording(){
    if(ioctl(record_fd, PERF_EVENT_IOC_RESET, 0) != 0){
        return -1;
    }
    if(ioctl(record_fd, PERF_EVENT_IOC_ENABLE, 0) != 0){
        return -1;
    }

    return 0;
}

int stop_recording(){
    if(ioctl(record_fd, PERF_EVENT_IOC_DISABLE, 0) != 0){
        return -1;
    }
    if(read(record_fd, &page_faults, sizeof(page_faults)) != 0){
        return -1;
    }
    return page_faults;
}

int init(){
    memset(&attrs, 0, sizeof(attrs));
    attrs.size = sizeof(attrs);
    attrs.type = PERF_TYPE_SOFTWARE;
    attrs.config = PERF_COUNT_SW_PAGE_FAULTS;
    attrs.disabled = 1; 
    attrs.exclude_kernel = 1;
    record_fd = perf_event_open(&attrs, 0, CPU, -1, 0);
    if(record_fd < 0){
        perror("Couldn't open log file");
        return -1;
    }
    return 0;
}

int main(int argc, char** argv){

  int x[64][64];

  int i, j = 0;

  init();

  begin_recording();

  for(i = 0; i < 64; i++){
    for(j = 0; j < 64; j++){
      x[i][j] = 0;
    }
  }

  int pf = stop_recording();

  printf("Page-faults: %d\n", pf);

  return 0;
}
