#include <stdio.h>
#include <iostream>
#include <csignal>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <cstring>
#include <vector>
#include <fcntl.h>

// 총 자식 프로세스의 개수
#define MAX_CHILD_PROCESS_COUNT 10

// DEBUG 모드용 - 필요 없으면 주석처리할 것
// #define DEBUG 

using namespace std;

size_t get_rand_seed();
size_t get_rand(size_t max);