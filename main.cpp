// mutator + main
#include "common.h"     
#include "save.h"       // data save module
#include "pmanager.h"   // child process manager module
#include "mutator.h"

// ================ mutator code start ===================

extern unsigned char  * g_sample_buf;
extern unsigned char  * g_new_buf; 
extern unsigned int option_flag;

void mutator_main(){
    Initialize();
    signal(SIGABRT, sigabrt_handler); // 자식프로세스에 입력값 저장 모듈 등록
    // 저장할 입력값 설정
    sd.append("unsigned_int_option_flag", sizeof(unsigned int), &option_flag);
    sd.append("char_*_g_sample_buf", MAX_LEN, g_sample_buf); 
    while(1)
        fuzz_test1(1000); // 1000번 테스트 후 다시 진행
}

// ================ mutator code end ===================

int main(){
    // 입력값를 저장할 디렉토리 설정
    sd.create_dir("./Log"); 

    // 뮤테이터 설정
    Pmanager pmng(mutator_main); // 사용자는 mutator_main에 해당하는 것만 개발하면 됨.

    // 퍼징 시작
    pmng.run();

    return 0;
}
