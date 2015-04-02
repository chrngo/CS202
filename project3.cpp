/***************************************************************/
/* PROGRAM: Project 3 CS 202                                   */
/*                                                             */
/* AUTHOR:Christopher Ngo                                      */
/*                                                             */
/* DATE: 02/15/15                                           */
/*                                                             */
/*                                                             */
/* PURPOSE: Build from project 2 and use pointers. 
Cut some functions down of the project. But for extra
challenge include them from last weeks' assingment.                                                
/*                                                             */
/***************************************************************/


//header files //////////////////////
#include <iostream> 
#include <fstream> 
#include <ctime>
#include <stdlib.h> 

using namespace std; 

//global constants 
	//none 

//structs/////////////////////////////////
struct symbols{
char name[20]; 
int bonusVal; 
bool bonusTrue; 
};


struct reel{
symbols reelSymbol[20];
int payline; 
};



//function prototypes//////////////////// 

/**************************************************************/
/* FUNCTION: displayMainMenu                                    
/*                                                           
/* PURPOSE: Prints main menu for user. And prompts user for 
input. This function using a reference parameter to pass 
user input respose. 
/**************************************************************/
void displayMainMenu(int& );


/**************************************************************/
/* FUNCTION: uploadToArray                                    
/*                                                           
/* PURPOSE: Uploads data from input file "symbols" 
to a 3D array. 
/**************************************************************/
void uploadToArray(symbols*, symbols*); 


/**************************************************************/
/* FUNCTION: printToScreen                                    
/*                                                           
/* PURPOSE: Prints the data from the array to the screen. 

/**************************************************************/
void printToScreen(reel* );


/**************************************************************/
/* FUNCTION: printToFile                                    
/*                                                           
/* PURPOSE: Print the data from the array to the user 
desired output file. The output file is a parameter. 
/**************************************************************/
void printToFile(reel* , char* ); 

/**************************************************************/
/* FUNCTION: printOptions                                    
/*                                                           
/* PURPOSE: Displays the user differnet options
of how they want to print the slot machines. Screen or to file. 
/**************************************************************/
void printOptions(reel*); 

/**************************************************************/
/* FUNCTION: uploadFromPrevious                                    
/*                                                           
/* PURPOSE: Upload previous slot machine config. 
/**************************************************************/
void uploadFromPrevious(reel* , bool &);

/**************************************************************/
/* FUNCTION: displaySelectedInput                                    
/*                                                           
/* PURPOSE: Displays the value and symbol of a certain
spot as specified by the user. 
/**************************************************************/
void displaySelectedInput(reel*, symbols*, symbols*);

/**************************************************************/
/* FUNCTION: randomSymbols                                    
/*                                                           
/* PURPOSE: Generates random
order of the symbols for the slot machine 
/**************************************************************/
void randomSymbols(symbols*, symbols*, reel* ); 

/**************************************************************/
/* FUNCTION: decodeValue                                    
/*                                                           
/* PURPOSE: decodes the symbol and matches it with the correct value. 
/**************************************************************/
int decodeValue(symbols*, symbols*, int, int, symbols*);

/**************************************************************/
/* FUNCTION: strCopy                                    
/*                                                           
/* PURPOSE: string copy. Copies from one string to another. 
Or array. 
/**************************************************************/
void strCopy(char*, char*);

/**************************************************************/
/* FUNCTION: strcmp                                    
/*                                                           
/* PURPOSE: string compare. compares two strings that are 
taken in as parameters. Returns 1 if false.
Otherwise if it's true it equals 0
/**************************************************************/
int strcmp(char*, char*);

/**************************************************************/
/* FUNCTION: displayPay                                    
/*                                                           
/* PURPOSE: displays the random payline by using the random number 
generator. In addition it displays the bonus values of 
all the symbols that were displayed on the payline for user. 
/**************************************************************/
void displayPay(reel*, symbols*, bool, symbols* );


////////////////////////main program ///////////////////////////////////////////////////////////

int main()
	{

	//initalize variables 
	int input; 
	char exisFile[25];
	symbols slot[10]; 
	symbols uploadSlot[20]; 
	symbols numbers[10]; 
	reel slotMachine[10];

	reel *slotPtr = slotMachine; 
	symbols * symbolPtr = slot;  
	symbols *uploadPtr = uploadSlot; 
	symbols *numPtr = numbers; 

	ifstream fin; 
	bool flag = false; 
	bool endProgram = false; 
	
	//do while loop until user wants to quit 
	do
		{
		//display main menu
		displayMainMenu(input);

		//switch cases of user input
		switch(input)
			{

			//case 1 -- display new slot machine
			case 1:
				//upload files and put into random. 
				uploadToArray(uploadPtr, numPtr); 
 				randomSymbols(symbolPtr, uploadPtr, slotPtr);
				//set flag to true for uploaded data 
				flag = true; 
				break; 

			//case 2 -- print to screen or print to file
			case 2:

				//check if there is data uploaded flag
				if(!flag){
					cout << "ERROR: Please upload the file first. Select option 1 or 3 prior to this one!!! " 
						  << endl << endl << endl; 
					}		
		
				else{
					//output function
					printOptions(slotPtr);
					}

				break; 

			//case 3 -- read in existing machine
			case 3:

				//upload previous configuration; pass flag 
					//function: uploadFromPrevious 
				uploadFromPrevious(slotPtr, flag);

				break;

			//case 4 -- display certain spot depending on user input
			case 4: 

				//check if there is data uploaded flag
				if(!flag){
					cout << "ERROR: Please populate slot first. Select option 1 or 3 prior to this one!!! " 
						  << endl << endl << endl; 
					}		
		
				else{
					//prompt user for selection and display 
						//funciton: displaySelected 
					displaySelectedInput(slotPtr, uploadPtr, numPtr); 
					}
				break; 

			//case 5 -- display payline 
			case 5: 
				displayPay(slotPtr, uploadPtr, flag, numPtr);  
				break;

			//case 6 - end program 
			case 6:
				//set flag to end program 
				endProgram = true; 
			
			}
		}
	//end loop if user enters 5 to end program 
	while(!endProgram); 

	//print success that the program quit the menu loop. 
	cout << "Slot Machine Sucessfully Ended. Please play again! " << endl << endl ;

	return 0; 

	}


//function implementations 

void displayMainMenu(int &val)
	{

	//display main menu for user to decide
	cout << endl << endl << "Slot Machine Symbols" << endl
		  << "====================" << endl << endl; 

	cout << "1. Populate a new slot machine" << endl << endl; 

	cout << "2. Output configuration to screen OR output file." << endl << endl; 

	cout << "3. Read in existing machine. " << endl << endl; 

	cout << "4. Choose to display reel and stop number to screen." << endl << endl; 

	cout << "5. Display Payline. " << endl << endl; 

	cout << "6. End Program." << endl << endl; 

	//prompt user for input choice. 
	cout << "Please enter desired number choice: " ;
	cin >> val; 

	cout << endl; 

	}


void uploadToArray(symbols *uploadSlot, symbols *num)
	{
	//initalize variables  
	ifstream fin;
	char fileName[20]; 
	

	//prompt user for upload file since no hard coding!
	cout << "Please enter input symbol filename ('symbols') : " ; 
	cin >> fileName; 

	//clear and open file. Hard code symbol file. 
	fin.clear(); 
	fin.open(fileName); 
		
	if(!fin.good())
		cout << "ERROR: Please try again. File not found!" << endl; 

	else{
		//loop for each pair of items. 	  
		for(int i = 0; i < 6;  i++)
			{
			//read in symbol and number. 
			fin >> (*uploadSlot).name >> (*num).bonusVal;

		
			//increment pointers
			uploadSlot++; 
			num++;  
			}
		cout << "File has been uploaded. Thanks!" << endl << endl; 
 		}

	//close file and display status to user. 
	fin.close();
	
	}


void printToScreen( reel *slotMachine )
	{

	symbols *slot = (*slotMachine).reelSymbol; 

	//print title menu
	cout << "Slot Machine Reels with Symbols" << endl;
	cout << "===============================" << endl;

	
for(int l = 0; l < 10; l++ )
	{

	//loop through for rows 
	for(int j = 0; j < 3; j++)
		{

		//print symbols from array. 
		cout << (*slot).name << "	|	" ; 
		slot++; 

		}
	cout << endl; 

	//increment pointers
	slotMachine++; 
	}

	cout << endl << endl; 
	}


void printToFile(reel *slotMachine, char *output )
	{
	//initalize variables 
	ofstream fout; 
	symbols *slot = (*slotMachine).reelSymbol; 

	//clear and open output file that user wants. 
	fout.clear(); 
	fout.open(output);

	//display status message to user
	cout << "Writing Symbols to Output File. . . " << endl << endl;

	for(int k = 0; k<10; k++)
		{

		//iterate through columns
		for(int i = 0; i < 3; i++)
			{

			//output symbols to output file. 
			fout << (*slot).name << " " ; 
			slot++; 
			}		
		fout << endl; 

		//increment pointers
		slotMachine++; 
		}


	//print status and close output file. 
	cout << "Symbols have been written to filename " << output << '.' 
		  << endl << endl; 
	fout.close(); 

	}


void printOptions(reel *slot)
	{
	//initalize variables 
	char printInput;
	char outputFile[20];  

	//display print options to user and have user enter their choice 
	cout << endl <<  "      1. Print to screen. " << endl; 
	cout << "      2. Print to file. " << endl; 
	cout << "      Enter number selection below: ";
	cin >> printInput; 

	//input 1 --- print to screen 
	if(printInput == '1')
		{
		//print to screen the slot machine
			//function: printToscreen
		printToScreen(slot); 
		}

	//else if input 2 --- print to oufile. 
	else if(printInput == '2')
		{
		//ask user to enter outfile. And use that file
		cout << endl <<  "Please enter an output file name: " ; 
		cin >> outputFile; 
		
		//print machine to output file. 
		printToFile(slot, outputFile); 
		}

	//otherwise not found and print error and have user try again 
	else{
		cout << "ERROR: Please try again. . ." << endl; 
		}
	}


void uploadFromPrevious(reel *slotMachine, bool &flag )
	{
	//initalize variables 
	char exisFile[20]; 
	ifstream fin; 
	symbols *slot = (*slotMachine).reelSymbol; 

	//prompt user for input file 
	cout << "Please enter an existing machine file name: " ;
	cin >> exisFile; 

	//open and clear file 
	fin.clear(); 
	fin.open(exisFile); 

	//display good if file found
	if(fin.good() )
		{

		symbols *slot = (*slotMachine).reelSymbol; 
		//display status message to user
		cout << "File is uploading. . . " << endl << endl; 

		//iterate through the columns 
		for(int i = 0; i < 10; i++)
		{
			//loop through for rows
			for(int j = 0; j < 3; j++)
			{

			//read in the slot machine 
			fin >> (*slot).name;
			slot++;
			
			}

		//increment pointers
		slotMachine++; 
		}


		//display status message to user and set flag to show data uploaded 
		cout << "SUCCESS: Previous machine configuration from file uploaded. " << endl;  
		flag = true; 
		}

	//else ask user to try again and return to main menu
	else{
		//display error
		cout << "ERROR: Existing machine file not found. . . Please try again! " << endl << endl; 
		}	
	
	//close input file
	fin.close(); 	

	}


void displaySelectedInput(reel *slotMachine, symbols *upload, symbols *num)
	{
	//initalize variables 
	int reelNum, stopNum, index; 
	symbols *slot = (*slotMachine).reelSymbol; 

	//prompt user for reel position
	cout << "Display reel and stop number at postiton" << endl; 
	cout << "Please enter a reel number wanted (1-3) : " ;
	cin >> reelNum; 

	//prompt user for stop position 
	cout << "Please enter a stop number (1-10): " ; 
	cin >> stopNum; 

	//check that user input is within bounds of machine
	if(stopNum <= 10 && reelNum <= 3 )
		{
		//print data of reel, stop, symbol, and points 
		cout << endl << "Reel Number: " << reelNum << endl 
			  << "Stop Number: " << stopNum << endl; 

		//loop up to stop and reel num and increment pointers 
		for(int l = 0; l < stopNum; l++)
			{		

			for(int i = 0; i < reelNum; i++)
				{
				slot++; 
				}

			slotMachine++; 

			}

		//print out the symbol to screen
		slot--; 
		cout << "Symbol: " << (*slot).name << endl; 

		//find value of wanted symbol and return value 
		index = decodeValue(slot, upload, reelNum, stopNum, num); 

		//loop up to the index and increment numPtr
		for(int m = 0; m < index; m++)
			{
			num++; 
			}

		//print bonus value of symbol to screen
		cout << "Bonus Value: " << (*num).bonusVal;  

		}

	//otherwise print error message and have user try again. 
	else{
		cout << endl << "Those numbers are out of the slot machine's range." 
			  << endl << "Please try again. . ." << endl << endl; 		
		}
	}


void randomSymbols(symbols* slot, symbols *uploadSlot, reel *slotMachine) 
	{
 	//initialize variables
	int rand1; 
	srand (time(NULL));
	symbols *homePtr = uploadSlot; 
	symbols *slotSide = (*slotMachine).reelSymbol; 

	reel *homePtr1 = slotMachine;

	//loop through the columns
	for(int i = 0; i < 10; i++)
		{
		slotMachine = homePtr1; 

		//loop through the rows 
		for(int j = 0; j < 3; j++)
			{

			//generate different random numbers
			rand1 =  rand() % 6;
			uploadSlot = homePtr; 		

			for(int m = 0; m < rand1; m++)
				{
				uploadSlot++; 
				}

			//copy from given file to slot machine array 
			strCopy((*slotSide).name, (*uploadSlot).name );
		
			//increment the slot
			slotSide++; 
			}

		//increment the slot machine reels 
		slotMachine++;

		}
	}


int decodeValue(symbols* slot, symbols *uploadSlot, int reel, int stop, symbols* num)
	{
	//initalize variables 
	int index; 
	reel -= 1; 
	stop -= 1; 

	//compare the input with the data from symbol file - bar
	if(strcmp((*slot).name, (*uploadSlot).name) == 0 )
		{
		//set index for location of found 
		index = 0; 
		}

	//increment uploadSlot for next position
	uploadSlot++; 

	//compare the input with the data from symbol file - bell
	if(strcmp((*slot).name, (*uploadSlot).name) == 0 )
		{ 
		index = 1;
		}

	//increment uploadSlot for next position
	uploadSlot++; 
		
	//compare the input with the data from symbol file - cherry 
	if(strcmp((*slot).name, (*uploadSlot).name) == 0 )
		{
		index = 2;
		}

	//increment uploadSlot for next position
	uploadSlot++; 

	//compare the input with the data from symbol file - lemon 
	if(strcmp((*slot).name, (*uploadSlot).name) == 0 )
		{
		index = 3;
		}

	//increment uploadSlot for next position
	uploadSlot++; 

	//compare the input with the data from symbol file
	if(strcmp((*slot).name, (*uploadSlot).name) == 0 )
		{
		index = 4;
		}

	//increment uploadSlot for next position
	uploadSlot++; 

	//compare the input with the data from symbol file
	if(strcmp((*slot).name, (*uploadSlot).name) == 0 )
		{
		index = 5;
		}  
	
	//increment uploadSlot for next position
	uploadSlot++; 

	//loop up to the index to set the numPtr; 
	for(int i = 0; i < index; i++)
		{	
		num++; 
		}

	//set boolean value if bonus value isn't 0 
	if( (*num).bonusVal != 0)
		(*slot).bonusTrue = true; 
	
	//otherwise set the boolean value to false because val is 0
	else
		(*slot).bonusTrue = false; 
		
	//return found matched index 
	return index; 

	}

void displayPay(reel *slotMachine, symbols *upload, bool flag, symbols *num)
	{

	//initalize variables 
	int rand1, index = 0, val = 0; 
	srand (time(NULL));
	symbols *slot = (*slotMachine).reelSymbol; 
	symbols *homePtr = num; 

	//only display if symbols have been loaded 
	if(flag == true)
		{
		//display payline title 
		cout << "	Payline" << endl
			  << "	=======" << endl << endl; 

		//loop for each reel, starting from 1
		for(int i = 1; i < 4; i++)
			{
			//generate random number for spin
			rand1 = rand() % 10; 

			//loop up to the random number
			for(int j = 0; j < rand1; j++)
				{
				//loop up to i for the increments
				for(int k = 0; k < (i-1); k++)
					{
					//increment the slotPtr
					slot++; 
					} 
				//increment the slotMachine ptr (reels)
				slotMachine++; 

				} 

			//get bonus value of random symbol picked
			index = decodeValue(slot, upload, i, rand1 + 1, num); 

/*
//testing to show the boolean if bonus value is 0
//instructions didn't specify if it wanted it printed to screen 
if( (*slot).bonusTrue)
	cout  << endl << "TRUE" ;

else
	cout <<endl << "FALSE - No Bonus Value"; 
*/

			//display random symbol to screen
			cout << "	|	" << (*slot).name ;

			//set numPtr to home; 
			num = homePtr; 

			for(int l = 0; l < index; l++)
				{
				num++; 
				}

			//store bonus value 
			val += (*num).bonusVal; 

			}

		//print bonus value total from payline above. 
		cout << "	|" << endl << endl << "Total Bonus Value: " << val; 

		}
	//otherwise tell user to load in symbols first. Give an error
	else{
		cout << "ERROR: Please upload symbols first. . . Select option 1 or 3!" << endl << endl; 
		}
	
	num = homePtr; 

	}



void strCopy(char* dest, char* src)
   {
   //initalize function 

   //loop until the null char 
   while (*src != '\0' )
		{
		//str copy from source to destination 
		*dest = *src; 

		//increment the counters 
		dest++; 
		src++; 

		}
   //replace the null char at the end
   *dest = '\0' ; 
   }



int strcmp(char* str1, char* str2 )
	{

	//loop while they are similar 
	while (*str1 == *str2 )
		{
		//If null is reached 
		if(*str1 == '\0' )
			{
			//return sucess
			return 0; 
			}
		//increment counters 
		str1++;
		str2++;
		}

	//return other, not similar 
	return 1; 
	}



