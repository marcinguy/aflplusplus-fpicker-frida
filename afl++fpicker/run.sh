#!/bin/sh
AFL_SKIP_BIN_CHECK=1 LD_PRELOAD=/data/local/tmp/afl++fpicker/shmem/libandroid-shmem.so AFL_NO_AFFINITY=1  ./afl-fuzz -m none -i in -o out -- /data/local/tmp/afl++fpicker/fpicker/fpicker -v --fuzzer-mode afl -e attach -p test -f /data/local/tmp/afl++fpicker/fpicker/examples/test/fuzzer-agent.js  --communication=send
