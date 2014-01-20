Sample_Code
===========
This repository contains three different coding projects I have completed either as class projects, or on my own time.

1. Hangman game - Python: <br />
    This is a project I completed on my own time. I wanted to code a fun little game played right in the terminal and also
experiment with some python code, so I came up with this idea and brought it to life while learning some interesting things about python. <br />
How to use: <br />
    Once you are in the directory with the three .py files and the three .txt files, just simply enter "python main.py", and then follow the on screen instructions 
    
2. Inverted Index Search Tool - C: <br />
    This is a project that I completed for my Systems Progamming class at Rutgers University in the Fall of 2013. It reads in an "inverted index file" that was created by another program I wrote for the class. What this file is, is a collection of terms that appeared in one or more text files, and information about each term, including which file or files the term appeared in, and the frequency of the term in each of those files. This search tool reads in these terms and information and inserts it into a prefix tree. The user is then promted to perform a search for a single, or multiple terms. There is two options for searches. These optios are searching for files that contain all of the given terms, or searching for files that contain at least one of the given terms.   <br />
How to use:   <br />
    There is an example inverted index file in the folder titled "exampleInvertedIndex.txt". Once the SearchTool folder is on your computer, and you are in the dirctory, run "make", and then run "./SearchTool exampleInvertedIndex.txt". You will then be directed to either enter in a search, or quit the program. The example file doesn't contain a wide variety of words to be searched for. Try searching for "a", "rutgers", "zebra", "test", or combinations of those words.

3. Simplified Version of the Solitaire Encryption Algorithm - Java: <br />
    This is a project I did for my Data Structures class at Rutgers University in the Spring of 2013. It is a simplified version of the Solitaire Encryption algorithm. This simplified version only uses a 26 card deck plus the two jokers. The main concept of this project was to obtain a good understanding of linked lists and manipulating them.   <br />
How to use:   <br />
    A deck file (deck.txt) is provided in the folder with the .java files. After you run the code, you will be asked to first enter the name of a deck file. Enter the name of the provided deck file, then just follow the on screen instructions
