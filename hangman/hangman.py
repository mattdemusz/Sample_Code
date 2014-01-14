import os
import time
import hangman_image

def hangman(temp):
    length = (len(temp) - 1)    #subtract 1 is so the new line character isn't accounted for
    numIncorrect = 0    #starting the number of wrong letter guesses at zero
    word = ""
    answer = "" #the word mathching the formatting of the game output
    for x in range (0, length):
        word = word + temp[x]
        if x == 0:
            answer = temp[x]
        else:
            answer = answer + ' ' + temp[x]
        
    #create an empty string and then add in an underscore for each letter in the word to be guessed
    guessWord = ""
    for x in range(0, length):
        if x == length - 1:
            guessWord = guessWord + "_"
        else:
            guessWord = guessWord + "_ "
    
    #asks the user to guess letters or the entire word until they get the word correct or get 6 wrong guesses
    history = ""    #keeps track of the users previous guesses
    lettersCorrect = 0  #user wins when lettersCorrect equals the length of the word being guessed
    while True:
        print hangman_image.image(numIncorrect)
        print "your word -> " + guessWord
        letter = raw_input("\nGuess a letter or the entire word -> ")
        letter = letter.lower()
        if len(letter) > 1: #the user guessed the entire word
            if letter == word:
                time.sleep(1)
                os.system('clear')
                print hangman_image.image(numIncorrect)
                print "your word -> " + answer
                print "\nThat is correct."
                time.sleep(2)
                os.system('clear')
                print hangman_image.image(7)
                print "\nYou have escaped the gallows."
                time.sleep(4)
                os.system('clear')
                return
            else:
                numIncorrect += 1
                print "That is incorrect."
                time.sleep(2)
                os.system('clear')
        else:  #the user guessed a single letter
            indexes = []
            index = 0
            for x in word:  #get index(s) of guessed letter match(s)
                if x == letter:
                    indexes.append(index)
                index += 1
            if indexes == []:   #the guessed letter is not in the word
                numIncorrect += 1
                print "That letter is NOT in the word."
                time.sleep(2)
                os.system('clear')
            else:   #there was at least one instance of the guessed letter in the word
                if letter in history:
                    print "That letter is in the word, but has already been guessed."
                    time.sleep(2)
                    os.system('clear')
                else:
                    print "That letter IS in the word"
                    history = history + letter
                    time.sleep(2)
                    os.system('clear')
                    for i in indexes:   #replace underscores with correct letters where neccassary
                        if i ==0:
                            position = 0
                            temp = letter + guessWord[(position + 1):]
                            guessWord = temp
                        else:
                            position = (i * 2)
                            temp = guessWord[:position] + letter + guessWord[(position + 1):]
                            guessWord = temp
                    lettersCorrect += len(indexes)
                    if lettersCorrect == length:    #all letters in the word have been correctly guessed
                        print hangman_image.image(numIncorrect)
                        print "your word -> " + guessWord
                        time.sleep(2)
                        os.system('clear')
                        print hangman_image.image(7)
                        print "\nYou have escaped the gallows."
                        time.sleep(4)
                        os.system('clear')
                        return
                
        #user has no guesses remaining
        if numIncorrect == 6:
            print hangman_image.image(numIncorrect)
            print "You have fallen victim to the gallows. Game over..."
            print "The word was: ", word
            time.sleep(5)
            return
            