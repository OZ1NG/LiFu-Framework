#include "common.h"
#include "monitor.h"
#include <wait.h>

// 자식 프로세스 생성기 + 자식 프로세스 감시기

// 자식 프로세스 pid 리스트. 맨 마지막 인덱스는 항상 0으로 고정 (무한 생성 방지)
extern pid_t pid_array[MAX_CHILD_PROCESS_COUNT];
extern uint32_t crash_count;

// Process Manager : (자식)프로세스 관리자
class Pmanager{
private:
    unsigned int idx_child_process;
    int c_process_count;    // 초기에 자식 프로세스를 MAX_CHILD_PROCESS_COUNT-1개 만큼 생성하기 위한 변수
    void (*mutator_main)(); // 실제 퍼징의 기능을 수행할 뮤테이터의 메인 함수 주소 
public:
    Pmanager(void (*mutator_main)()); // 뮤테이터 함수 포인터 인자로 전달
    unsigned int watch_child_process(int create_child_process_count); // watcher
    void run();
};

// keyboard interrupt (ctrl+c)
// 자식 프로세스들 종료
void sigint_handler(int signum);
