/* File:   main.cpp
 * Author: Kevin Ortega
 * Created on December 8, 2018, 11:39 AM
 * Purpose: To play Blackjack for Project 2.
 */

//System Libraries
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//Function prototypes
void whoWon(float p_total, float d_total, int p_card1, int p_card2, int d_card1, int d_card2, float wager, float & a); //Function Declarations
float dpcards(int dcard1, int dcard2, int pcard1, int pcard2, string cardFaceArray[], int wager, float ttlwgr);        //Function declarations
bool hadFun(); //Boolean 

//Program starts here
int main() {

        //Random Function for cards
	srand((unsigned)time(0));

        //Declare variables here
	int choices;       //How many times you'll play
	char y;	          //To start the game
	float ttlwgr = 0; //Total wager
	float wager = 0;  //Wager
	string Face[] = { "Ace", "Jack", "King", "Queen" }; //Array that holds names of the cards
	ofstream myfile;   //File Object
	ifstream myfile2;
        float marray [2][5] = {{0,0,0,0,0}, {0,0,0,0,0}}; //Array saved ttlwgr just in case print function fails
	string answer; //To ask if they enjoyed the game or not
        int rating; //To rate the game
	
        //Game starts here
	do {                      
		cout << "Welcome. Let's play some Blackjack! Press (y/n) to play: ";
		cin >> y;
	} while ( ( y != 'y' ) && ( y != 'n' ) ); //Input validation

        //Game ends if 'n' is entered
	if ( y == 'n' ) {
		cout << setfill('-') << "GAME OVER." << setfill('-');
	}
	else if ( y == 'y' ) { //Game starts if they enter y
		
		//How many games they'd like to play
		cout << "Enter the number of games you'll play: "; 
		cin >> choices;

		for (int i = 0; i < choices; i++) {
			
                        //Players wager
			cout << "Enter how much you want to wager: $";
			cin >> wager;

			int d_card1 = rand() % 13 + 1;     //Dealer card 1 value
			int d_card2 = rand() % 13 + 1;     //Dealer card 2 value
			int p_card1 = rand() % 13 + 1;     //Player card 1 value
			int p_card2 = rand() % 13 + 1;     //Player card 2 value

                        //Calls function. Determines who won/ Sends to whowon. Saves ttlwgr
			ttlwgr = dpcards(d_card2, d_card1, p_card1, p_card2, Face, wager, ttlwgr);	
                       
		}
			
	}
	else
		cout << "Invalid Response. Quitting Game. "; //Just in case

        //Saves ttlwgr
        for( int row = 0; row < 2; row++ )
        {
            for( int col = 0; col < 5; col++ )
                marray[row][col] = row * col;
        }
        
	//To write the output to a file called example.txt
	myfile.open("example.txt");
        
        //Exit function 
        if( myfile == NULL ){
            cout << "ERROR OPENING FILE";
            exit(EXIT_FAILURE); 
        }
        //Keeps total of earnings
	myfile << "Your total score is $" << ttlwgr << ".\n";
	myfile.close();

	//Open file to read
	string wonGame = "";
	myfile2.open("example.txt");
	getline(myfile2, wonGame); //File stream. Output to file
	cout << wonGame << endl;
	myfile2.close();	
	
        //Asks user if they had fun at the end of game
        cout << "Did you have fun? Enter 'yes' or 'no' to answer. ";
        cin >> answer;
        if ( answer == "yes" ){
            bool answer;
            answer = hadFun();
        }
        else 
            if ( answer != "yes" ){
                cout << "Sounds like a personal problem." << endl;              
            }                                
        
        //Bubble sort array
        int bubArra[] = { 5, 3, 1, 4, 2 };
        int swapHol = -1; //Swapholder
        int last = 5;
        int length = 5;
        
        for ( int counter = length - 1; counter >= 0; counter-- )
        {
            for ( int index = 0; index < last; index++ )
            {
                if ( bubArra[index] > bubArra[index + 1] )
                {
                    swapHol = bubArra[index + 1];
                    bubArra[index + 1] = bubArra[index];
                    bubArra[index] = swapHol;
                }
            }
            last--;
        }
        
        for ( int index = 0; index < 6; index++ )
        {
            cout << bubArra[index] << ", ";
        }
        cout << endl;
        cout << "Either way. I need you to rate me so I feel validated. The rating"
                " scale is above. 0 being the worst and 5 being the best." << endl;
        cin >> rating;
        if ( rating == 5 )
            cout << "Wow, thanks champ.\n";
        else
            if ( rating != 5 )
                cout << "You couldn't even give me a 5 huh?\n";
        
	//Exit
	return 0;
}

void whoWon(float p_total, float d_total, int p_card1, int p_card2, int d_card1, int d_card2, float wager, float &ttlWagr) {

	const float value = 1.5; //How much they'll win
	int temp = ttlWagr;         

	//Conditions to check who wins
	if ((p_card1 == 1) && ((p_card1 == 10 || p_card1 == 11 || p_card1 == 12 ||
		p_card1 == 13))){
		cout << "Blackjack! You Win $ " << (wager*value) << "!" << endl; //Player wins
                }
        
	else
		if ((p_card2 == 1) && ((p_card2 == 10 || p_card2 == 11 || p_card2 == 12 ||
			p_card2 == 13))) {
			cout << "Blackjack! You Win $ " << (wager*value) << "!" << endl; //Player wins
                        }
		else {
			if (p_total > d_total) {
				cout << "\n" << "You Win $" << wager << "!" << endl; //Player wins
				temp += wager;
                                
			}
			else {
				cout << "\n" << "You lose." << endl;
				temp -= wager;
				//Player looses
			}
                }
        //ttlwagr being adjusted
	ttlWagr = temp;
       
	
}

float dpcards(int dcard1, int dcard2, int pcard1, int pcard2, string cardFaceArray[], int wager, float ttlwgr) {

	float ttlwagr = ttlwgr;
	int d_card1 = dcard1; //Dealer card 1
	int d_card2 = dcard2; //Dealer card 2
	int p_card1 = pcard1; //Player card 1
	int p_card2 = pcard2; //Player card 2	
        
	cout << "\n" << "The dealer has "; //To check what cards the dealer has
	switch (d_card1) {
	case 1: cout << cardFaceArray[0] << " and ";
		break;
	case 11: cout << cardFaceArray[1] << " and ";
		break;
	case 12: cout << cardFaceArray[2] << " and ";
		break;
	case 13: cout << cardFaceArray[3] << " and ";
		break;
	default: cout << d_card1 << " and ";
		break;
	}
	switch (d_card2) {
	case 1: cout << cardFaceArray[0];
		break;
	case 11: cout << cardFaceArray[1];
		break;
	case 12: cout << cardFaceArray[2];
		break;
	case 13: cout << cardFaceArray[3];
		break;
	default: cout << d_card2;
		break;
	}
       
	cout << "\n" << "\n" << "You have "; //To check what player has
	switch (p_card1) {
	case 1: cout << cardFaceArray[0] << " and ";
		break;
	case 11: cout << cardFaceArray[1] << " and ";
		break;
	case 12: cout << cardFaceArray[2] << " and ";
		break;
	case 13: cout << cardFaceArray[3] << " and ";
		break;
	default: cout << p_card1 << " and ";
		break;
	}
	switch (p_card2) {
	case 1: cout << cardFaceArray[0];
		break;
	case 11: cout << cardFaceArray[1];
		break;
	case 12: cout << cardFaceArray[2];
		break;
	case 13: cout << cardFaceArray[3];
		break;
	default: cout << p_card2;
		break;
	}

	cout << "\n";

	float d_total = d_card1 + d_card2; //Dealer total
	float p_total = p_card1 + p_card2; //Player total

        //Calls the function 'whowon'
	whoWon(d_total, p_total, p_card1, p_card2, d_card1, d_card2, wager, ttlwagr);
	return ttlwagr; //ttlwgr was adjusted in the whowon function
}

bool hadFun(){
    
    //Outputs if user had fun
    cout << "You better have.";
    cout << endl;
    return true;
}
