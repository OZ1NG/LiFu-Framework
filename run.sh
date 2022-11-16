# SIGABRT 발생 유도
echo "[+] RUN CURL FUZZER"
ASAN_OPTIONS="abort_on_error=1,log_path='./Log/'" ./bin/curl_fuzz
