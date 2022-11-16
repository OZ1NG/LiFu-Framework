#include "common.h"
#include <curl/curl.h>  
#include "radamsa.h"    // mutator

#define MAX_LEN 0x100
#define STR_LEN 0x100
#define MAX_PATH_LEN 5
#define MAX_PARAM_LEN 5

typedef enum Mutate_Mode {
    NORMAL,   // 뮤테이트한 값을 새로운 버퍼에 저장
    INPLACE   // 뮤테이트한 값을 기존 버퍼에 그대로 저장
} Mutate_Mode;

size_t mutate(unsigned char * sample_, unsigned char * new_buf, int mode);

size_t mutate_n(unsigned char * sample_, unsigned char * new_buf, size_t n);

char * select_scheme();

char * select_host_subdomain();

char * select_host_domain();

char * select_host_tld();

char * select_path();

char * select_parameter();

char * select_fragment();

char * gen_url();

void set_curl_url_set_flag();

void fuzz_test1(int count);

void Initialize();
