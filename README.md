# trec - time record
`time record` is a small application which lets you calculate the time you can leave your work place with consideration for breaks and over-/undertime.\
It was specifically made with a workday of 7 hours and 42 minutes.

## Usage
```sh
$ trec -b 11 -p -28 7:25
15:46

```

## Compile
Pretty much any compiler that supports simple macros:\
`$ gcc -o trec trec.c`

gcc 64bit specific:\
`$ gcc -m64 -o trec trec.c`

gcc 32bit specific:\
`$ gcc -m32 -o trec trec.c`

linux mingw-gcc 64bit specific:\
`$ x86_64-w64-mingw32-gcc -o trec trec.c`


linux mingw-gcc 32bit specific:\
`$ i686-w64-mingw32-gcc -o trec trec.c`

## License - MIT
See `LICENSE.txt` file in the root directory of this repository
