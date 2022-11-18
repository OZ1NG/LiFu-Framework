#include "pmanager.h"

// 자식 프로세스 pid 리스트. 맨 마지막 인덱스는 항상 0으로 고정 (무한 생성 방지)
pid_t pid_array[MAX_CHILD_PROCESS_COUNT];
uint32_t crash_count;

// 자식 프로세스 와처
// pid_array에서 종료된 자식 프로세스의 인덱스 번호를 리턴
unsigned int Pmanager::watch_child_process(int create_child_process_count){
    int i = 0;
    for(i = 0; i <= create_child_process_count; i++){
        pid_t end_pid = waitpid(pid_array[i], NULL, WNOHANG); 
        #ifdef DEBUG
        printf("i: %d, pid_array[i] : %d, end_pid : %d\n", i,pid_array[i], end_pid);
        #endif
        if(end_pid != 0){ // 해당 프로세스는 종료되었거나 없는 것. 실행중이면 0 리턴
            crash_count++;
            return i;
        }        
    }
    return i;
}

// init
Pmanager::Pmanager(void (*mutator_main)()){
    signal(SIGABRT, sigint_handler);
    this->idx_child_process = 0;
    this->c_process_count = 0;
    this->mutator_main = mutator_main;
}

extern void sigabrt_handler(int signum); // save.cpp에 구현

// 자식 프로세스 생성 및 실행기
void Pmanager::run(){
    Monitor monitor;
    while(1){
        monitor.update_moniter();
        idx_child_process = watch_child_process(c_process_count);
        if(idx_child_process >= MAX_CHILD_PROCESS_COUNT) // 인덱스 꽉참 
            continue;
        if(c_process_count < MAX_CHILD_PROCESS_COUNT-1)
            c_process_count++;
        // 자식 프로세스 생성
        pid_array[idx_child_process] = fork();
        if(pid_array[idx_child_process] == 0){ // 자식 프로세스
            signal(SIGABRT, sigabrt_handler); // 자식프로세스에 입력값 저장 모듈 등록
            // mutator main
            (*mutator_main)(); 
            break;
        }
    }
}

void sigint_handler(int signum){
    int status;
    for(int i = 0; i < MAX_CHILD_PROCESS_COUNT; i++){
        kill(pid_array[i], SIGKILL);
        waitpid(pid_array[i], &status, 0);
    }
    puts("[!] Fuzz Done! - Keyboard Interrupt");
    exit(0);
}