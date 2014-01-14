import hangman
import random
import time
import os

def main():
    os.system('clear')
    print "Welcome to Hangman."
    level = raw_input("""Select a difficulty level:
    Enter 1 for easy.
    Enter 2 for medium.
    Enter 3 for hard.
    -> """)
    
    #if it is a number, cast input value to an int. else catch the error and exit the program
    try:
        level = int(level)
        os.system('clear')
    except ValueError:
        print "That is not a valid entry"
        print "Exiting Hangman............"
        time.sleep(1)
        os.system('clear')
        return
    
    
    while True:

        #read in a word from the appropriate text file based on the selected difficulty level and remove the new line character
        if level == 1:
            temp = random.choice(open("hangman_easy.txt").readlines())
        elif level == 2:
            temp = random.choice(open("hangman_medium.txt").readlines())
        elif level == 3:
            temp = random.choice(open("hangman_hard.txt").readlines())
        else:
            print "That is not a valid entry"
            print "Exiting Hangman............"
            time.sleep(1)
            os.system('clear')
            return
        hangman.hangman(temp)
        
        os.system('clear')
        level = raw_input("""If you would like to play again, select a difficulty level.
Otherwise, you may quit the game now:
        Enter 1 for easy.
        Enter 2 for medium.
        Enter 3 for hard.
        Enter 4 to quit.
        -> """)
        
        #if it is a number, cast input value to an int. else catch the error and exit the program
        try:
            level = int(level)
            os.system('clear')
        except ValueError:
            print "That is not a valid entry"
            print "Exiting Hangman............"
            time.sleep(1)
            os.system('clear')
            return

        if level == 4:
            print "Exiting Hangman............"
            time.sleep(1)
            os.system('clear')
            return
        
main()