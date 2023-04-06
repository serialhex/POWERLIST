# POWERLIST

This is POWERLIST!
It takes a variable number of files as parameters, and then outputs a series of outputs which is the permutations of the lines in the files.

``` cmd
c:\> powerlist.exe words1.txt words2.txt words3.txt
wordsllama1
fordsllama1
mordsllama1
wordsalpaca1
fordsalpaca1
mordsalpaca1
wordsmoose1
fordsmoose1
mordsmoose1
...
```

There are some limitations:
  * Each line is limited to `max_str` (32) characters. (Memory corruption will occur if this is violated!!!)
  * You are limited to `max_lines` (1024) lines in each file
  * This memory is pre-allocated, so if you have a 3-line file and each line only has 1 character in it, that file is going to take up `32*1024=32768` bytes (32MB).
  * It outputs to standard out, and that's it.  You want a file?  Redirect to a file. (Be careful of Windows PowerShell and it's dumb `UTF-8 BOM` encoding!)

Yeah, that's about all... Happy Hacking!

