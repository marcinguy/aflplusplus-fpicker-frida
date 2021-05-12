# aflplusplus-fpicker-frida

Binaries and so files are aarch64

Start frida server, copy libandroid-shmem.so to re.frida.server

Run with run.sh

P.S You might need to create socket in /data/local/tmp/mysocket

## aarch64

set CC to NDK compiler (aarch64)

Make afl (AFLplusplus-aarch64) with 

make all AFL_NO_X86=1

Make fpicker with

make fpicker-linux (did in chroot linux env - termux)

## x86_64


set CC to NDK compiler (x86_64)

Make afl (AFLplusplus-x86_64) with 

make all AFL_NO_X86=1

Make fpicker with

make fpicker-linux (did in chroot linux env - termux) (Not working yet)


For fpicket a NDK Andoird Project would be better. Maybe also for AFL++. VS building from chroot Clang12 (termux)







