# aflplusplus-fpicker-frida

Binaries and so files are aarch64 (API Level 29)

Start frida server, copy libandroid-shmem.so to re.frida.server

Run with run.sh

P.S You might need to create socket in /data/local/tmp/mysocket

```
heroltexx:/data/local/tmp # ls -la mysocket                                    
srwxrwxrwx 1 root root 0 2021-05-10 15:37 mysocket
heroltexx:/data/local/tmp #
```

I think if you create a file and chnage the permissions (0777) it should be sufficient. If not try to run this, it should create it:

```
#include <sys/types.h>          
#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
  int return_value;
  const char *sock_path;
  struct sockaddr_un local;

  sock_path = "/data/local/tmp/mysocket";

  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("socket");
    exit(-1);
  }

  local.sun_family = AF_UNIX;
  strcpy(local.sun_path, sock_path);
  unlink(local.sun_path);
  int len = strlen(local.sun_path) + sizeof(local.sun_family);
  bind(sockfd, (struct sockaddr *)&local, len);

  chmod(sock_path, 0777);

  int retval = listen(sockfd,1);
  if (retval == -1)
  {
    perror("listen");
    exit(-1);
  }
}

```

## aarch64

set CC to NDK compiler (aarch64)

Make afl (AFLplusplus-aarch64) with

```
make all AFL_NO_X86=1
```

Make fpicker with (did in chroot linux env - termux)

```
make fpicker-linux

```

## x86_64


set CC to NDK compiler (x86_64)

Make afl (AFLplusplus-x86_64) with

```
make all AFL_NO_X86=1

```
Make fpicker with (did in chroot linux env - termux) (Not working yet)

```
make fpicker-linux

```

fpicker (Android x86_64)

```
$HOME/Downloads/android-ndk-r21e/toolchains/llvm/prebuilt/linux-x86_64/bin/clang -MMD -MP  -target x86_64-linux-android29 -fdata-sections -ffunction-sections -fstack-protector-strong -funwind-tables -no-canonical-prefixes  --sysroot $HOME/Downloads/android-ndk-r21e/toolchains/llvm/prebuilt/linux-x86_64/sysroot -g -Wno-invalid-command-line-argument -Wno-unused-command-line-argument  -D_FORTIFY_SOURCE=2 -fpic -O0 -UNDEBUG -fno-limit-debug-info  -I$HOME/Downloads/android-ndk-r21e/sysroot/usr/include -I.   -DANDROID -fPIC -m64 -ffunction-sections -fdata-sections -Wall -Wno-format -Os -pipe -g3 fpicker.c fp_communication.c fp_standalone_mode.c fp_afl_mode.c -ldl -lm -lresolv -lrt -Wl,--export-dynamic -Wl,--gc-sections,-z,noexecstack -pthread -Wl,-allow-multiple-definition -v -nostdinc++ -Wformat -Werror=format-security  -c  ./fpicker.c

```


```
$HOME/Downloads/android-ndk-r21e/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ -Wl,--gc-sections -Wl,-rpath-link=$HOME/Downloads/android-ndk-r21e/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/x86_64-linux-android/29  fpicker.o fp_communication.o fp_standalone_mode.o fp_afl_mode.o -lgcc -Wl,--exclude-libs,libgcc.a -Wl,--exclude-libs,libgcc_real.a -latomic -Wl,--exclude-libs,libatomic.a -target x86_64-linux-android29 -no-canonical-prefixes    -Wl,--build-id   -nostdlib++ -Wl,--no-undefined -Wl,--fatal-warnings -L. -lfrida-core-linux -lc -lm -o fpicker

```

For fpicker a NDK Andoird Project would be better. Maybe also for AFL++. VS building from chroot Clang12 (termux)

A folder with binaries and .so files for aarch64 and x86_64, respectively, for everything would be nice

-----
Compiling fpicker for aarch64 (A secondary approach)

  You need clang installed at the following path: /usr/lib/android-sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/bin/clang
  You need sysroot at the following location:     --sysroot /usr/lib/android-sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/sysroot
  You need to add the NDK include directory:      -I /usr/lib/android-sdk/ndk-bundle/sysroot/usr/include
  You need to include the working directory:      -I.
  You need to set the target:                     -target aarch64-none-linux-android29


1. Check out a copy of the fpicker repo


 ```
 git clone https://github.com/ttdennis/fpicker
 ```

2. Compile the code into object files.

```
/usr/lib/android-sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/bin/clang -MMD -MP -MF ./obj/local/arm64-v8a/objs-debug/fpicker/fpicker.o.d -target aarch64-none-linux-android29 -fdata-sections -ffunction-sections -fstack-protector-strong -funwind-tables -no-canonical-prefixes  --sysroot /usr/lib/android-sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/sysroot -g -Wno-invalid-command-line-argument -Wno-unused-command-line-argument  -D_FORTIFY_SOURCE=2 -fpic -O0 -UNDEBUG -fno-limit-debug-info  -I/usr/lib/android-sdk/ndk-bundle/sysroot/usr/include -I.   -DANDROID -fPIC -m64 -ffunction-sections -fdata-sections -Wall -Wno-format -Os -pipe -g3 fpicker.c fp_communication.c fp_standalone_mode.c fp_afl_mode.c -ldl -lm -lresolv -lrt -Wl,--export-dynamic -Wl,--gc-sections,-z,noexecstack -pthread -Wl,-allow-multiple-definition -v -nostdinc++ -Wformat -Werror=format-security  -c  ./fpicker.c
```

3. Link and output the executable.

```
/usr/lib/android-sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ -Wl,--gc-sections -Wl,-rpath-link=/usr/lib/android-sdk/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/29 -Wl,-rpath-link=./obj/local/arm64-v8a ./obj/local/arm64-v8a/objs-debug/fpicker/fpicker.o ./obj/local/arm64-v8a/objs-debug/fpicker/fp_communication.o ./obj/local/arm64-v8a/objs-debug/fpicker/fp_standalone_mode.o ./obj/local/arm64-v8a/objs-debug/fpicker/fp_afl_mode.o -lgcc -Wl,--exclude-libs,libgcc.a -Wl,--exclude-libs,libgcc_real.a -latomic -Wl,--exclude-libs,libatomic.a -target aarch64-none-linux-android29 -no-canonical-prefixes    -Wl,--build-id   -nostdlib++ -Wl,--no-undefined -Wl,--fatal-warnings -L. -lfrida-core -lc -lm -o fpicker
```

fpicker: ELF 64-bit LSB shared object, ARM aarch64, version 1 (SYSV), dynamically linked, interpreter /system/bin/linker64, BuildID[sha1]=311a8ad0497111630a5a581f2ba49d3b377f4e15, with debug_info, not stripped

-----

Compiling AFL++ Using the Soong build system (A secondary approach)

1. Follow repo sync instructions detailed here: https://source.android.com/setup/build/downloading

2. cd into root directory of AOSP and run: git clone https://github.com/AFLplusplus/AFLplusplus

3. Setup the build environment as detailed here: https://source.android.com/setup/build/building

   3a. lunch aosp_arm-eng

   P.S. You can select any CPU architecture available to the build system. Soong
        relies on Android.bp file to process the build.

4. Build with `m`

   4a. If you only want to build afl-fuzz and nothing else before you run `m` make
       sure to cd into AFLplusplus first.

5. Check the out subdirectory within the AOSP root directory for results. e.g.,

    -rw-r--r-- 1 level level      74 May 10 10:34 build_fingerprint.txt
    -rw-r--r-- 1 level level      53 May 10 10:34 build_thumbprint.txt
    -rw-r--r-- 1 level level  191034 May 10 10:33 clean_steps.mk
    -rw-r--r-- 1 level level      46 May 10 10:34 .copied_headers_list
    drwxr-xr-x 1 level level       8 May 10 10:34 gen
    -rw-r--r-- 1 level level 2791289 May 10 10:34 .installable_files.previous
    drwxr-xr-x 1 level level     154 May 10 10:38 obj
    drwxr-xr-x 1 level level     118 May 10 10:38 obj_arm
    -rw-r--r-- 1 level level      40 May 10 10:34 previous_build_config.mk
    drwxr-xr-x 1 level level      24 May 10 10:38 symbols
    drwxr-xr-x 1 level level      22 May 10 10:38 system
    drwxr-xr-x 1 level level      16 May 10 10:38 vendor

6. For example, the afl-fuzz is located at: ./system/bin/afl-fuzz

  $ file ./system/bin/afl-fuzz
  ./system/bin/afl-fuzz: ELF 64-bit LSB pie executable, ARM aarch64, version 1 (SYSV), dynamically linked, interpreter /system/bin/linker64, BuildID[md5/uuid]=7a9363e7af52681546f792da0fccfe1b, stripped

P.S. These instructions also work with LineageOS (https://www.lineageos.org/)

------ Building fpicker for x86_64 ------

1. Check out a copy of fpicker

```
git clone https://github.com/ttdennis/fpicker
cd fpicker
```

2. Download a copy of libfrida-core.a

```
wget https://github.com/frida/frida/releases/download/14.2.18/frida-core-devkit-14.2.18-linux-x86_64.tar.xz
xz -d frida-core-devkit-14.2.18-linux-x86_64.tar.xz
tar xvf frida-core-devkit-14.2.18-linux-x86_64.tar
ls -la libfrida-core-linux.a
```

3. Build the binary

```
make fpicker-linux
```

fpicker: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=6ee75db87f467f9e23447ce7717f9e32aae04101, for GNU/Linux 3.2.0, with debug_info, not stripped
