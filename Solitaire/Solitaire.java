package solitaire;

import java.io.IOException;
import java.util.Scanner;
import java.util.Random;

// This class implements a simplified version of Bruce Schneier's Solitaire Encryption algorithm.
public class Solitaire {
	
	 // Circular linked list that is the deck of cards for encryption
	CardNode deckRear;
	
	/* Makes a shuffled deck of cards for encryption. The deck is stored in a circular
	 * linked list, whose last node is pointed to by the field deckRear
	 */
	public void makeDeck() {
		// start with an array of 1..28 for easy shuffling
		int[] cardValues = new int[28];
		// assign values from 1 to 28
		for (int i=0; i < cardValues.length; i++) {
			cardValues[i] = i+1;
		}
		
		// shuffles the array that represents the cards
		Random randgen = new Random();
 	        for (int i = 0; i < cardValues.length; i++) {
	            int other = randgen.nextInt(28);
	            int temp = cardValues[i];
	            cardValues[i] = cardValues[other];
	            cardValues[other] = temp;
	        }
	     
	    // create a circular linked list from this deck and make deckRear point to its last node
	    CardNode cn = new CardNode();
	    cn.cardValue = cardValues[0];
	    cn.next = cn;
	    deckRear = cn;
	    for (int i=1; i < cardValues.length; i++) {
	    	cn = new CardNode();
	    	cn.cardValue = cardValues[i];
	    	cn.next = deckRear.next;
	    	deckRear.next = cn;
	    	deckRear = cn;
	    }
	}
	
	
	//Makes a circular linked list deck out of values read from scanner.
	public void makeDeck(Scanner scanner) 
	throws IOException {
		CardNode cn = null;
		if (scanner.hasNextInt()) {
			cn = new CardNode();
		    cn.cardValue = scanner.nextInt();
		    cn.next = cn;
		    deckRear = cn;
		}
		while (scanner.hasNextInt()) {
			cn = new CardNode();
	    	cn.cardValue = scanner.nextInt();
	    	cn.next = deckRear.next;
	    	deckRear.next = cn;
	    	deckRear = cn;
		}
	}
	
	/* Implements Step 1 - Joker A - on the deck.
	 * Joker A (27) is located in the deck, and then its value is swapped
	 * with the card's value ahead of it
	 */
	void jokerA() {
		CardNode current;
		int temp;
		//checks to see if joker A (27) is the last card in the deck
		if (deckRear.cardValue == 27){
			temp = deckRear.cardValue;
			deckRear.cardValue = deckRear.next.cardValue;
			deckRear.next.cardValue = temp;
			return;
		}
		//locates joker A (27) in the deck if it's not the last card
		for (current = deckRear.next; current.next != deckRear.next; current = current.next){
			if (current.cardValue == 27){
				temp = current.next.cardValue;
				current.next.cardValue = current.cardValue;
				current.cardValue = temp;
				return;
			}
		}	
	}
	
	/* Implements Step 2 - Joker B - on the deck.
	 * Joker B (28) is located and then it's value is swapped with 
	 * the card's value two positions ahead of it
	 */
	void jokerB() {
		CardNode current;
		int temp;
		//checks to see if joker B (28) is the last card in the deck
		if (deckRear.cardValue == 28){
			temp = deckRear.next.next.cardValue;
			deckRear.next.next.cardValue = deckRear.cardValue;
			deckRear.cardValue = deckRear.next.cardValue;
			deckRear.next.cardValue = temp;
			return;
		}
		//locates joker B (28) in the deck if it's not the last card
		for (current = deckRear.next; current.next != deckRear.next; current = current.next){
			if (current.cardValue == 28){
				temp = current.next.next.cardValue;
				current.next.next.cardValue = current.cardValue;
				current.cardValue = current.next.cardValue;
				current.next.cardValue = temp;
				return;
			}
		}
	}
	
	/* Implements Step 3 - Triple Cut - on the deck.
	 * This takes the cards that are in front of the first joker,
	 * and swaps them with the cards after the second joker
	 * 
	 * small scale example:
	 * before the triple cut:	1 2 (front joker) 3 4 5 (back joker) 6 7 8 9
	 * after the triple cut:	6 7 8 9 (front joker) 3 4 5 (back joker) 1 2
	 */
	void tripleCut() {
		CardNode current;
		CardNode frontJoker = null;
		CardNode backJoker = null;
		CardNode deckFront = null;
		CardNode frontPrev = null;
		CardNode backNext = null;
		CardNode oldBack = null;
		// checks to see if the last card is a joker, and if so, sets it as the back joker
		if (deckRear.cardValue == 27 || deckRear.cardValue == 28){
			backJoker = deckRear;
			backNext = deckRear.next;
		}
		// runs through the deck to locate the jokers
		for (current = deckRear; current.next != deckRear; current = current.next){
			if (current == deckRear){
				deckFront = current.next;
				oldBack = current;
			}
			if (current.next.cardValue == 27 || current.next.cardValue == 28){
				if (frontJoker == null){	// first joker hasn't been located yet
					frontPrev = current;
					frontJoker = current.next;
				} 
				else if (backJoker == null){	// first joker has already been located
					backJoker = current.next;
					backNext = current.next.next;
				}
			}
		}
		if (frontJoker != deckRear.next && backJoker != deckRear){		// front and back jokers are somewhere in the middle of the deck
		backJoker.next = deckFront;
		deckRear = frontPrev;
		deckRear.next = backNext;
		oldBack.next = frontJoker;
		return;
		}
		else if (frontJoker != deckRear.next && backJoker == deckRear){		// back joker is the last card in the deck
			deckRear = frontPrev;
			deckRear.next = frontJoker;
		}
		else if (frontJoker == deckRear.next && backJoker != deckRear){		// front joker is the first card in the deck
			deckRear.next = backNext;
			oldBack.next = frontJoker;
			deckRear = backJoker;
		}
		else if (frontJoker == deckRear.next && backJoker == deckRear){		// back joker is the last card and the front joker is the first
			return;
		}
	}
	
	/* Implements Step 4 - Count Cut - on the deck.
	 * Takes the value of the last card in the deck and then counts that many
	 * positions from the first card in the deck. Those cards from the front of the deck
	 * are then moved in front of the last card in the deck
	 * 
	 * small scale example:
	 * before the count cut:	0 4 5 6 7 2 8 9 1 3
	 * after the count cut:		6 7 2 8 9 1 0 4 5 3
	 */
	void countCut() {	
		int value;
		int count = 0;
		CardNode current;
		CardNode last = null;
		CardNode rearPrev = null;
		CardNode deckFront = null;
		CardNode newFront = null;
		if (deckRear.cardValue == 28){	// if the last card is joker B (28), the value is just set to 27
			value = 27;
		} else {
			value = deckRear.cardValue;
		}
		if (value == 27){	// if the value is 27, the deck will remain unchanged, so it just returns
			return;
		}
		// counts up from the front of the deck the appropriate number of times and sets a pointer to the position
		for (current = deckRear.next; current.next != deckRear.next; current = current.next){
			count++;
			if (count == value){
				last = current;
				newFront = last.next;
			}
			if (current.next == deckRear){
				rearPrev = current;
			}
			if (current == deckRear.next){
				deckFront = current;			
			}
		}
		// rearranging pointers to move the X number of front cards to in front of the last card in the deck
		last.next = deckRear;
		rearPrev.next = deckFront;
		deckRear.next = newFront;
		return;
	}
	
   /* Gets a key. Calls the four steps - Joker A, Joker B, Triple Cut, Count Cut, then
    * counts down based on the value of the first card and extracts the next card value 
    * as key, but if that value is 27 or 28, repeats the whole process until a value
    * less than or equal to 26 is found
    * 
    * returns a key value between 1 and 26
    */
	int getKey() {
		int count = 0;
		int key = 0;
		int value;
		CardNode current;
		do {
			count = 0;
			jokerA();
			jokerB();
			tripleCut();
			countCut();
			if (deckRear.next.cardValue == 28){
				value = 27;
			} else {
				value = deckRear.next.cardValue;
			}
			for (current = deckRear.next; current.next != deckRear.next; current = current.next){
				count++;
				if (count == value){
					key = current.next.cardValue;
				}
			}
		} while (key == 27 || key == 28);	
	    return key;
	}
	
	/* Utility method that prints a circular linked list
	 * 
	 * takes in the decks rear pointer
	 */
	private static void printList(CardNode rear) {
		if (rear == null) { 
			return;
		}
		System.out.print(rear.next.cardValue);
		CardNode ptr = rear.next;
		do {
			ptr = ptr.next;
			System.out.print("," + ptr.cardValue);
		} while (ptr != rear);
		System.out.println("\n");
	}

	/* Encrypts a message, ignores all characters except upper case letters
	 * 
	 * takes in the message to be encrypted
	 * returns the encrypted message, a sequence of upper case letters only
	 */
	public String encrypt(String message) {	
		String encrypted = "";
		Character [] abc = new Character[]{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		int num;
		int letterVal = 0;
		for (int i = 0; i < message.length(); i++){
			Character letter = message.charAt(i);
			if (Character.isLetter(letter)){
				letter = Character.toUpperCase(letter);
				letterVal = letter - 'A' + 1;
				num = getKey();
				num += letterVal;
				if (num > 26){
					num -= 26;
				}
				encrypted += abc[num - 1];
			}
		}
	    return encrypted;
	}
	
	/* Decrypts a message, which consists of upper case letters only
	 * 
	 * takes in the message to be decrypted
	 * returns the decrypted message, which is a sequence of upper case letters only
	 */
	public String decrypt(String message) {	
		String decrypted = "";
		Character [] abc = new Character[]{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		int num;
		int letterVal = 0;
		for (int i = 0; i < message.length(); i++){
			Character letter = message.charAt(i);
			if (Character.isLetter(letter)){
				letter = Character.toUpperCase(letter);
				letterVal = letter - 'A' + 1;
				num = letterVal;
				num -= getKey();
				if (num < 1){
					num += 26;
				}
				decrypted += abc[num - 1];
			}
		}
	    return decrypted;
	}
}
