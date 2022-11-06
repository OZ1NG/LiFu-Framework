#include "common.h"

extern pid_t pid_array[MAX_CHILD_PROCESS_COUNT];
extern uint32_t crash_count;

class Monitor{
private:
    void move_cur(int x, int y);
    // 퍼징 시작 시간
    string getruntime();

public:
    // init
    Monitor(); 

    // 실행 시간, 크래시 개수, 테스트 케이스 개수, 실행중인 자식 프로세스의 pid 출력
    void update_moniter();
};
