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
lab4


######################################

part1 a):
Records nserted: 
229: {yixuan} said {My     OC OC [2~ OD OD }
230: {yixua  n } said {Hello AP}


######################################


part1 b):

yz4004@clac ~/cs3157/lab4/part1 $ valgrind --leak-check=yes ./mdb-lookup test_db
==14087== Memcheck, a memory error detector
==14087== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==14087== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==14087== Command: ./mdb-lookup test_db
==14087==
look up:
   1: {yixuan zou} said {hello}
   2: {uuu} said {he   OB OB hhhh sfesfe}
   3: {AP} said {im ap}
   4: {dfhjfhjssfsefjs} said {bbbbbbbbbbbbbbbbbbbbbbb}

look up: ==14087==
==14087== HEAP SUMMARY:
==14087==     in use at exit: 0 bytes in 0 blocks
==14087==   total heap usage: 13 allocs, 13 frees, 3,376 bytes allocated
==14087==
==14087== All heap blocks were freed -- no leaks are possible
==14087==
==14087== For counts of detected and suppressed errors, rerun with: -v
==14087== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
yz4004@clac ~/cs3157/lab4/part1 $ make
gcc -c  mdb-lookup.c -o  mdb-lookup.o -I../../lab3/solutions/part1
gcc  mdb-lookup.o -o mdb-lookup  -lmylist -L../../lab3/solutions/part1
yz4004@clac ~/cs3157/lab4/part1 $ valgrind --leak-check=yes ./mdb-lookup test_db
==15744== Memcheck, a memory error detector
==15744== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==15744== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==15744== Command: ./mdb-lookup test_db
==15744==
lookup:
   1: {yixuan zou} said {hello}
   2: {uuu} said {he   OB OB hhhh sfesfe}
   3: {AP} said {im ap}
   4: {dfhjfhjssfsefjs} said {bbbbbbbbbbbbbbbbbbbbbbb}

lookup: ee

lookup: yixuan
   1: {yixuan zou} said {hello}

lookup: hell
   1: {yixuan zou} said {hello}

lookup: iii

lookup: uu
   2: {uuu} said {he   OB OB hhhh sfesfe}

lookup: b
   4: {dfhjfhjssfsefjs} said {bbbbbbbbbbbbbbbbbbbbbbb}

lookup: ==15744==
==15744== HEAP SUMMARY:
==15744==     in use at exit: 0 bytes in 0 blocks
==15744==   total heap usage: 13 allocs, 13 frees, 3,376 bytes allocated
==15744==
==15744== All heap blocks were freed -- no leaks are possible
==15744==
==15744== For counts of detected and suppressed errors, rerun with: -v
==15744== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
yz4004@clac ~/cs3157/lab4/part1 $



