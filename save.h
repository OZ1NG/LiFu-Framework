#include "common.h"
#include <experimental/filesystem> // -lstdc++fs 필요

namespace fs = experimental::filesystem;

// 저장할 데이터 타입, 저장할 데이터 크기, 저장할 데이터 주소 
typedef struct save_data_info{
    string type; // 저장할 데이터 타입
    uint64_t size;
    void * addr; // 저장할 데이터 주소
}save_data_info;

class Save{
private:
    vector<save_data_info> save_data;
    //string log_dirname; // ASAN_OPTIONS 환경변수로 해결
    string input_dirname = "./Log"; // 입력값을 저장할 디렉토리의 이름 // 해당 디렉토리 내에 크래시 발견 시간을 이름으로 디렉토리가 생성되고 그 안에 지정한 입력값이 저장됨.
    fs::path nowtime2path(); // 현재 시간을 fs::path 타입으로 리턴
    
public:
    // 저장할 데이터 변수의 주소 등록. 
    // 저장할 데이터 변수의 주소는 vector에 순차적으로 저장.
    // save_data_info 구조체로 저장하여 관리
    void append(string data_type, uint64_t data_size, void * data_addr); 
    void create_dir(string dirname); // 디렉토리 존재 확인 후 없으면 디렉토리 생성 // save 및 main에서 사용 // main은 Log 디렉토리 체크
    void save();
    void set_input_dirname(string input_dirname);
    Save();
};

extern Save sd; // save data // 전역변수로 무조건 할당되고 sigabrt_handler와 연동되므로 해당 변수에 저장할 데이터 값을 셋팅하면 된다. // save.cpp에서 할당

void sigabrt_handler(int signum);
