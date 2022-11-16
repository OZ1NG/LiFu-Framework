// clang++ save.cpp -o save -no-pie -lstdc++fs
#include "save.h" // 디렉토리 생성 및 디렉토리 확인 등등

// 저장할 데이터 타입, 저장할 데이터 주소, 저장할 데이터 크기
void Save::append(string data_type, uint64_t data_size, void * data_addr){
    save_data_info tmp;
    tmp.type = data_type;
    tmp.size = data_size;
    tmp.addr = data_addr;
    this->save_data.push_back(tmp);
}

void Save::create_dir(string dirname){
    fs::path p(dirname);

    // 존재 체크
    if(!fs::exists(p) && !fs::is_directory(p)){
        fs::create_directory(p);
        cout << "Create " << p << endl;
    }else{
        cout << p << " is already exist." << endl; // test
    }
}

// <vector idx>_<type> 형식으로 입력 값이 저장됨.
void Save::save(){
    #ifdef DEBUG
    show(); // test
    #endif

    FILE * fp;
    fs::path save_filepath1;
    fs::path save_filepath2;
    // TODO : set real save dir name
    // 디렉토리 하나 더 만듦
    fs::path save_i_dir = this->input_dirname / nowtime2path();
    create_dir(save_i_dir); // 디렉토리가 없으면 생성

    // [save input value]
    uint32_t size = this->save_data.size();
    #ifdef DEBUG
    cout << "[DEBUG]size:" << size << endl; // test
    #endif
    for (int i = 0; i < size; i++){
        save_filepath1 = save_i_dir;
        save_filepath2 = to_string(i) + "_" + this->save_data.at(i).type;
        save_filepath1 /= save_filepath2; // "path1 -> "D:\\Lecture\\examples"
        #ifdef DEBUG
        cout << "[DEBUG]save_filepath1:" <<  save_filepath1 << endl; // test
        #endif
        if ((fp = fopen(save_filepath1.c_str(), "w")) == 0) {
            printf("[CRASH-ERROR] Save g_sample_buf Failed : %s open fail.", save_filepath1.c_str());
            continue ;
        }
        fwrite(this->save_data.at(i).addr, this->save_data.at(i).size, 1, fp);
        fclose(fp);
        save_filepath1.clear();
        save_filepath2.clear();   
    }
    this->save_data.clear();
    // Done
}

void Save::set_input_dirname(string input_dirname){
    this->input_dirname = input_dirname;
}

// 현재 시간을 fs::path 타입으로 리턴
// format : YYYY.MM.DD-hh:mm:ss.uuuuuu
fs::path Save::nowtime2path(){
    struct timeval val;
    struct tm *ptm;
    
    gettimeofday(&val, NULL);
    ptm = localtime(&val.tv_sec);
    
    string now = to_string(ptm->tm_year + 1900) + "." + 
                 to_string(ptm->tm_mon + 1) + "." + 
                 to_string(ptm->tm_mday) + "-" + 
                 to_string(ptm->tm_hour) + ":" + 
                 to_string(ptm->tm_min) + ":" + 
                 to_string(ptm->tm_sec) + "." +
                 to_string(val.tv_usec);
    fs::path result = now;
    return result;
}

// for test
void Save::show(){
    int size = this->save_data.size();
    for (int i = 0; i < size; i++){
        cout << "[show]type:" << this->save_data.at(i).type << endl;
        cout << "[show]size:" <<this->save_data.at(i).size << endl;
        cout << "[show]addr:" <<this->save_data.at(i).addr << endl;
        cout << "[show]data:";
        write(1, this->save_data.at(i).addr, this->save_data.at(i).size);
        cout << endl;
    }
}

// Save::Save(){
//     signal(SIGABRT, sigabrt_handler);
// }

Save sd;

// 입력값 저장 모듈은 자식 프로세스 안에서 실행해야함.
void sigabrt_handler(int signum){
    cout << "[!] Crash! " << endl;
    sd.save();
    exit(0);
}