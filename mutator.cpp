#include "mutator.h"

unsigned char  * g_sample_buf;
unsigned char  * g_new_buf; 
unsigned int option_flag;

char *scheme_list[] = {
    "http", "https", "chrome", "file", 
    "about", "blob", "content", "cid", 
    "data", "filesystem", "ftp", "gopher",  
    "javascript", "mailto", "ws", "wss", 
    "socks4", "socks4a", "socks5", "socks5h"
};
char * host_subdomain_list[1] = {"www"} ;
char * host_domain_list[6] = {
    "home.sch", "google", "naver", 
    "daum", "youtube", "example"
} ;
char * host_tld_list[3] = {"kr", "com", "co.kr"} ;
char * path_list[55] = {
    "test", "Test", "TEST", "A", "B", 
    "C", "D", "E", "F", "G", "H", "I", 
    "J", "K", "L", "M", "N", "O", "P", 
    "Q", "R", "S", "T", "U", "V", "W", 
    "X", "Y", "Z", "a", "b", "c", "d", 
    "e", "f", "g", "h", "i", "j", "k", 
    "l", "m", "n", "o", "p", "q", "r",
    "s", "t", "u", "v", "w", "x", "y", 
    "z"
} ;
char * parameter_list[55] = {
    "test", "Test", "TEST", "A", "B", 
    "C", "D", "E", "F", "G", "H", "I", 
    "J", "K", "L", "M", "N", "O", "P", 
    "Q", "R", "S", "T", "U", "V", "W", 
    "X", "Y", "Z", "a", "b", "c", "d", 
    "e", "f", "g", "h", "i", "j", "k", 
    "l", "m", "n", "o", "p", "q", "r",
    "s", "t", "u", "v", "w", "x", "y", 
    "z"
} ;
char * fragment_list[55] = {
    "test", "Test", "TEST", "A", "B", 
    "C", "D", "E", "F", "G", "H", "I", 
    "J", "K", "L", "M", "N", "O", "P", 
    "Q", "R", "S", "T", "U", "V", "W", 
    "X", "Y", "Z", "a", "b", "c", "d", 
    "e", "f", "g", "h", "i", "j", "k", 
    "l", "m", "n", "o", "p", "q", "r",
    "s", "t", "u", "v", "w", "x", "y", 
    "z"
} ;

// 온전한 형태의 url 값이 sample로 들어옴
// mode가 NORMAL인 경우 : sample_ 버퍼에 해당하는 값을 뮤테이트 후 new_buf에 저장 따라서 new_buf가 필수임
// mode가 INPLACE인 경우 : smaple_ 버퍼에 해당하는 값을 뮤테이트 후 sample_버퍼에 저장 따라서 new_buf는 null 이어도 됨.
size_t mutate(unsigned char * sample_, unsigned char * new_buf, int mode){
    if(sample_ == NULL){
        printf("[mutate] sample_ is NULL");
        return 0;
    }
    size_t len = 0;
    if(mode == NORMAL){
        if(new_buf == NULL){
            printf("[mutate - NORMAL Mode] new_buf is NULL");
            exit(0);
        }
        memset(new_buf, 0, MAX_LEN);
        len = radamsa(sample_, strlen((const char *)sample_), new_buf, MAX_LEN-1, get_rand_seed());
    }
    if(mode == INPLACE)
        len = radamsa_inplace(sample_, strlen((const char *)sample_), MAX_LEN-1, get_rand_seed());
    return len;
}

size_t mutate_n(unsigned char * sample_, unsigned char * new_buf, size_t n){
    if(sample_ == NULL){
        printf("[mutate_n] sample_ is NULL");
        return 0;
    }
    memset(new_buf, 0, n);
    size_t len = radamsa(sample_, strlen((const char *)sample_), new_buf, n-1, get_rand_seed());
    return len;
}


// free 필요
char * select_scheme(){
    size_t idx = get_rand(sizeof(scheme_list)/sizeof(char *)); 
    char * new_buf = (char *)calloc(1, STR_LEN+3); 
    strcat(new_buf, scheme_list[idx]);
    strcat(new_buf, "://");
    return new_buf;
}

// free 필요 // 50%의 가중치를 두고 생성
char * select_host_subdomain(){
    if(get_rand(2)){ // 만약 참이면 NULL 리턴 <= 생성 안함
        return NULL;
    }
    size_t idx = get_rand(sizeof(host_subdomain_list)/sizeof(char *)); 
    char * new_buf = (char *)calloc(1, STR_LEN+1); 
    strcat(new_buf, host_subdomain_list[idx]);
    strcat(new_buf, ".");
    return new_buf;
}

// free 필요
char * select_host_domain(){
    size_t idx = get_rand(sizeof(host_domain_list)/sizeof(char *)); 
    char * new_buf = (char *)calloc(1, STR_LEN+1); 
    strcat(new_buf, host_domain_list[idx]);
    strcat(new_buf, ".");
    return new_buf;
}

// free 필요
char * select_host_tld(){
    size_t idx = get_rand(sizeof(host_tld_list)/sizeof(char *)); 
    char * new_buf = (char *)calloc(1, STR_LEN+1); 
    strcat(new_buf, host_tld_list[idx]);
    return new_buf;
}

// free 필요 // 50%의 가중치를 두고 생성
char * select_path(){
    if(get_rand(2)){ // 만약 참이면 NULL 리턴 <= 생성 안함
        return NULL;
    }
    size_t path_count = get_rand(MAX_PATH_LEN); // path 개수 설정 : 최대 MAX_PATH_LEN개
    if(path_count <= 0){
        return NULL;
    }
    char * new_buf = (char *)calloc(1, (STR_LEN+1)*MAX_PATH_LEN); 
    for(int i=0; i < path_count; path_count--){
        char * tmp_buf = (char *)calloc(1, STR_LEN+1); 
        size_t idx = get_rand(sizeof(path_list)/sizeof(char *)); 
        strcat(tmp_buf, path_list[idx]);
        strcat(tmp_buf, "/");
        strcat(new_buf, tmp_buf);
        free(tmp_buf);
    }
    return new_buf;    
}

// free 필요 // 50%의 가중치를 두고 생성
char * select_parameter(){
    if(get_rand(2)){ // 만약 참이면 NULL 리턴 <= 생성 안함
        return NULL;
    }
    size_t param_count = get_rand(MAX_PARAM_LEN); // parameter 개수 설정 : 최대 MAX_PATH_LEN개
    if(param_count <= 0){
        return NULL;
    }
    char * new_buf = (char *)calloc(1, (STR_LEN+1)*MAX_PARAM_LEN); 
    strcat(new_buf, "?");
    for(int i=0; i < param_count; param_count--){
        char * tmp_name = (char *)calloc(1, STR_LEN/2+1); 
        char * tmp_val = (char *)calloc(1, STR_LEN/2+1); 
        // gen tmp_name
        size_t idx = get_rand(sizeof(parameter_list)/sizeof(char *)); 
        strcat(tmp_name, parameter_list[idx]);
        strcat(tmp_name, "=");
        // gen tmp_value // tmp_name=의 값을 뮤테이트함
        idx = get_rand(sizeof(parameter_list)/sizeof(char *)); 
        strcat(tmp_val, parameter_list[idx]);
        strcat(tmp_name, tmp_val);

        if(param_count >= 2) // 마지막에 &가 붙는 것 방지
            strcat(tmp_name, "&");
        strcat(new_buf, tmp_name);
        free(tmp_name);
        free(tmp_val);
    }
    return new_buf;
}

// free 필요 // 50%의 가중치를 두고 생성
char * select_fragment(){
    if(get_rand(2)){ // 만약 참이면 NULL 리턴 <= 생성 안함
        return NULL;
    }
    size_t idx = get_rand(sizeof(fragment_list)/sizeof(char *)); 
    char * new_buf = (char *)calloc(1, STR_LEN); 
    strcat(new_buf, "#");
    strcat(new_buf, fragment_list[idx]);
    return new_buf;    
}

// free 필요
char * gen_url(){ 
    char * url = (char *)calloc(1, MAX_LEN); 
    // scheme://host_subdomain.host_domain.host_tld/path/parameter#fragment
    const char * scheme = select_scheme();
    if(scheme != NULL)
        strncat(url, scheme, strlen(scheme)); // bof 일어날 수도 있음

    // host
    const char * host_subdomain = select_host_subdomain();
    if(host_subdomain != NULL)
        strncat(url, host_subdomain, strlen(host_subdomain));
    const char * host_domain = select_host_domain();
    if(host_domain != NULL)
        strncat(url, host_domain, strlen(host_domain));
    const char * host_tld = select_host_tld();
    if(host_tld != NULL)
        strncat(url, host_tld, strlen(host_tld));

    strcat(url, "/");

    // path
    const char * path = select_path();
    if(path != NULL)
        strncat(url, path, strlen(path));
    
    // parameter
    const char * parameter = select_parameter();
    if(parameter != NULL)
        strncat(url, parameter, strlen(parameter));

    // fragment
    const char * fragment = select_fragment();
    if(fragment != NULL)
        strncat(url, fragment, strlen(fragment));

    // free // free(0)은 에러 없이 그냥 넘어감
    free((void *)scheme);
    free((void *)host_subdomain);
    free((void *)host_domain);
    free((void *)host_tld);
    free((void *)path);
    free((void *)parameter);
    free((void *)fragment);
    
    return url;
}

void set_curl_url_set_flag(){
    option_flag = (unsigned int)get_rand(0x1000); // 0~0xFFF(=4095) 범위의 값
}

void fuzz_test1(int count){
    #ifdef DEBUG
    puts("[DEBUG] fuzz_test1 : curl_url_set");
    #endif

    char * url = gen_url();
    #ifdef DEBUG
    printf("[DEBUG]origin url : %s\n", url);
    #endif

    // copy
    memset(g_sample_buf, 0, MAX_LEN);
    memcpy(g_sample_buf, url, strlen(url));

    CURLUcode rc;
    CURLU * url_handle;
    set_curl_url_set_flag();
    while(count){    
        mutate(g_sample_buf, NULL, INPLACE);
        #ifdef DEBUG
        printf("[DEBUG]mutate url : %s\n", g_sample_buf);
        #endif
        url_handle = curl_url();
        rc = curl_url_set(url_handle, CURLUPART_URL, (const char *)g_sample_buf, option_flag); 
        #ifdef DEBUG
        printf("[DEBUG]rc : %d\n", rc);
        #endif
        curl_url_cleanup(url_handle);
        count--;
    }
    free(url);    
}

void Initialize(){
    srand(time(NULL)); // 매번 다른 시드값 생성
    g_sample_buf = (unsigned char *)malloc(MAX_LEN);
    g_new_buf = (unsigned char *)malloc(MAX_LEN);
    radamsa_init();    
}