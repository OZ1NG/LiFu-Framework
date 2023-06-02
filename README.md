# LiFu Framework

## 목적
- 라이브러리 함수들에 대한 퍼저 제작 속도를 향상시키기 위해 만든 퍼저 프레임워크
- 모니터, 자식 프로세스 생성기 & 종료 감시기, 입력값 저장기, 크래시 감지기, 빌더 제공
- 따라서 개발자는 대상 함수에 대한 뮤테이터만 개발하면 됨. (퍼저 개발 시간 감소)
- C++로 개발 (C/C++로 제작된 뮤테이트 코드에 대한 호환성 향상)

## requirements
- clang++ - ver15
- mutator는 사용자가 직접 개발 
    - 현재 올라간 코드를 사용하고 싶으면 radamsa 라이브러리 필요

## build & run
```sh
make

sh ./run.sh
```

## usage - code
```c
// main.cpp
...
#include "common.h"     
#include "save.h"       // data save module
#include "pmanager.h"   // child process manager module

// ================ mutator code start ===================
...

// example code
void mutator_main(){
    Initialize();
    while(1)
        fuzz_test1(1000); // 임시로 1000번 테스트 후 종료
}

// ================ mutator code end ===================

int main(){
    // 입력값를 저장할 디렉토리 설정 // sd는 save data의 준말로 save.h에 미리 정의 되어있음
    sd.create_dir("./Log"); 

    // 저장할 입력값 설정
    sd.append("char_*_g_sample_buf", MAX_LEN, g_sample_buf);
    sd.append("unsigned_int_option_flag", sizeof(unsigned int), &option_flag);

    // 뮤테이터 설정
    Pmanager pmng(mutator_main); // 사용자는 mutator_main에 해당하는 것만 개발하면 됨.

    // 퍼징 시작
    pmng.run();

    return 0;
}
```
and build & run

## mutator example
- 대상 : libcurl - curl_url_set 함수
- 뮤테이트 방식 : feedback guided fuzzing (with radamsa)
- 현재 뮤테이터에 대한 코드는 main.cpp에 정의되어 있음.

## version
- ver0.1 : 모듈화
    - 모니터, 자식 프로세스 생성기 & 종료 감시기, 입력값 저장기, 크래시 감지기, 빌더 모듈 개발 완료
    - 뮤테이터 : 테스트용으로 libcurl의 curl_url_set 함수 대상 뮤테이터 개발 및 적용 완료

