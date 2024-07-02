# TextCompress
`TextCompress` was originally python script I made, that I know ported to C++. Its main "use" is to compress large text into a smaller file.

# Algorithm
Basically, it analyses the whole text and gets the 15 (*at most*) most used characters in the text, which it will encode within 4 bits instead of 8 bits. To help the decompressor parsing the compressed text, a header is written at the start of the output file.

# Usage
You can give the software either `-c` or `-d` as argument (the latest will override any former arguments):
```shell
$ ./textcomp -c sample.txt # To compress text.
$ ./textcomp compressed.txt -d # To decompress text.
```

For now, it still asks for input for a destination file.

# Compilation
To compile the repository, just run:
```shell
$ make
```

In case you have made changes to header files (`.hpp`), run:
```shell
$ make clean ; make
```

# TODO
- [ ] Whatever is marked with `@todo` in the code.
- [ ] Provide a way to not have to input a destination file.