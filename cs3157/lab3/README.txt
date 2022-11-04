This file should contain:

  - your name
  - your UNI
  - lab assignment number
  - description for each part
  
The description should indicate whether your solution for the part is
working or not.  You may also want to include anything else you would
like to communicate to the grader such as extra functionalities you
implemented or how you tried to fix your non-working code.

Yixuan Zou
yz4004
lab3

----------------------------part1 (a)--------------------------

yz4004@clac ~/cs3157/lab3/part1 $ valgrind --leak-check=yes ./main
==22154== Memcheck, a memory error detector
==22154== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==22154== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==22154== Command: ./main
==22154==
testing addFront(): 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0
testing flipSignDouble(): -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0
testing flipSignDouble() again: 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0
testing findNode(): OK
popped 9.0, the rest is: [ 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 8.0, the rest is: [ 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 7.0, the rest is: [ 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 6.0, the rest is: [ 5.0 4.0 3.0 2.0 1.0 ]
popped 5.0, the rest is: [ 4.0 3.0 2.0 1.0 ]
popped 4.0, the rest is: [ 3.0 2.0 1.0 ]
popped 3.0, the rest is: [ 2.0 1.0 ]
popped 2.0, the rest is: [ 1.0 ]
popped 1.0, the rest is: [ ]
testing addAfter(): 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0
popped 1.0, and reversed the rest: [ 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 ]
popped 9.0, and reversed the rest: [ 2.0 3.0 4.0 5.0 6.0 7.0 8.0 ]
popped 2.0, and reversed the rest: [ 8.0 7.0 6.0 5.0 4.0 3.0 ]
popped 8.0, and reversed the rest: [ 3.0 4.0 5.0 6.0 7.0 ]
popped 3.0, and reversed the rest: [ 7.0 6.0 5.0 4.0 ]
popped 7.0, and reversed the rest: [ 4.0 5.0 6.0 ]
popped 4.0, and reversed the rest: [ 6.0 5.0 ]
popped 6.0, and reversed the rest: [ 5.0 ]
popped 5.0, and reversed the rest: [ ]
==22154==
==22154== HEAP SUMMARY:
==22154==     in use at exit: 0 bytes in 0 blocks
==22154==   total heap usage: 19 allocs, 19 frees, 1,312 bytes allocated
==22154==
==22154== All heap blocks were freed -- no leaks are possible
==22154==
==22154== For counts of detected and suppressed errors, rerun with: -v
==22154== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)




----------------------------part1 (b)--------------------------

yz4004@clac ~/cs3157/lab3/part1 $ make clean
rm -f *.o a.out core main
yz4004@clac ~/cs3157/lab3/part1 $ clear
yz4004@clac ~/cs3157/lab3/part1 $ make
gcc -c mylist.c -o mylist.o
ar rcs libmylist.a mylist.o
gcc -c mylist-test.c -o  mylist-test.o
gcc  mylist-test.o -o main -L. -lmylist
yz4004@clac ~/cs3157/lab3/part1 $ valgrind --leak-check=yes ./main
==24171== Memcheck, a memory error detector
==24171== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==24171== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==24171== Command: ./main
==24171==
testing addFront(): 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0
testing flipSignDouble(): -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0
testing flipSignDouble() again: 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0
testing findNode(): OK
popped 9.0, the rest is: [ 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 8.0, the rest is: [ 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 7.0, the rest is: [ 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 6.0, the rest is: [ 5.0 4.0 3.0 2.0 1.0 ]
popped 5.0, the rest is: [ 4.0 3.0 2.0 1.0 ]
popped 4.0, the rest is: [ 3.0 2.0 1.0 ]
popped 3.0, the rest is: [ 2.0 1.0 ]
popped 2.0, the rest is: [ 1.0 ]
popped 1.0, the rest is: [ ]
testing addAfter(): 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0
popped 1.0, and reversed the rest: [ 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 ]
popped 9.0, and reversed the rest: [ 2.0 3.0 4.0 5.0 6.0 7.0 8.0 ]
popped 2.0, and reversed the rest: [ 8.0 7.0 6.0 5.0 4.0 3.0 ]
popped 8.0, and reversed the rest: [ 3.0 4.0 5.0 6.0 7.0 ]
popped 3.0, and reversed the rest: [ 7.0 6.0 5.0 4.0 ]
popped 7.0, and reversed the rest: [ 4.0 5.0 6.0 ]
popped 4.0, and reversed the rest: [ 6.0 5.0 ]
popped 6.0, and reversed the rest: [ 5.0 ]
popped 5.0, and reversed the rest: [ ]
==24171==
==24171== HEAP SUMMARY:
==24171==     in use at exit: 0 bytes in 0 blocks
==24171==   total heap usage: 19 allocs, 19 frees, 1,312 bytes allocated
==24171==
==24171== All heap blocks were freed -- no leaks are possible
==24171==
==24171== For counts of detected and suppressed errors, rerun with: -v
==24171== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

----------------------------part2 --------------------------  



yz4004@clac ~/cs3157/lab3/part2 $ valgrind --leak-check=yes ./main hello world dude
==19050== Memcheck, a memory error detector
==19050== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==19050== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==19050== Command: ./main hello world dude
==19050==
dude
world
hello

dude found==19050==
==19050== HEAP SUMMARY:
==19050==     in use at exit: 0 bytes in 0 blocks
==19050==   total heap usage: 4 allocs, 4 frees, 1,072 bytes allocated
==19050==
==19050== All heap blocks were freed -- no leaks are possible
==19050==
==19050== For counts of detected and suppressed errors, rerun with: -v
==19050== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)







