#include "monitor.h"

struct timeval start_time_val;

Monitor::Monitor(){
    gettimeofday(&start_time_val, NULL); // set start time
    printf("\e[1;1H\e[2J"); // cls

}

void Monitor::move_cur(int x, int y){
    printf("\033[%dd\033[%dG", y, x);
}

// 실행 시간
// 크래시 개수
// 테스트 케이스 개수
// 실행중인 자식 프로세스의 pid
void Monitor::update_moniter(){
    move_cur(0,0);
    printf("+------------- [Fuzzing] -------------+\n");
    printf("+-------------------------------------+\n");
    cout << "  Run Time : " << getruntime() << endl;

    printf("  Crash Count : %d\n", crash_count);
    printf("  Child Process List : \n");
    for(int i = 0; i < MAX_CHILD_PROCESS_COUNT; i++){
        printf("    - %d\n", pid_array[i]);
    }
    printf("+-------------------------------------+\n");
}

// 퍼징 시작 후 실행 시간 리턴
string Monitor::getruntime(){
    struct timeval val;
    struct tm *ptm;
 
    gettimeofday(&val, NULL);
    const time_t run_time = val.tv_sec - start_time_val.tv_sec;
    ptm = localtime(&run_time);
 
    // format : MM.DD-hh:mm:ss.uuuuuu
    string result = to_string(ptm->tm_mon + 1) + "." + 
                 to_string(ptm->tm_mday) + "-" + 
                 to_string(ptm->tm_hour) + ":" + 
                 to_string(ptm->tm_min) + ":" + 
                 to_string(ptm->tm_sec) + "." +
                 to_string(val.tv_usec);
    return result;
}