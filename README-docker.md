# WSL

Under WSL/Ubuntu you can build testers and reference labs for Windows
using `mingw`.

Compile testers for Win32, stripped:
```
mkdir bw
( cd bw ; LDFLAGS=-s CFLAGS=-Os cmake .. -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc )
( cd bw ; make )
```

Compile a lab for Win32, stripped:
```
i686-w64-mingw32-gcc -Os lab4.c -s -o test/lab4.exe
```

# Dockering

Reference lab for Linux should be built for an old `libc`.
Use docker for this.

```
docker pull ubuntu:18.04
docker images
docker run --rm -it -v $PWD:/work -w /work dwim bash
docker ps
docker commit keen_feynman dwim
```
Compile a test for Ubuntu, stripped:
```
gcc -Os lab4.c -s -o test/lab4
```
