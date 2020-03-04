//Assignment 4a: 1-D array processing - Data set analysis written by Melinda Sterne

/*
	This program gives the user a menu of ten options.  It will input from the keyboard ten integers to store in an
	array, read 10 numbers from a file, display the current data set, display the median, display the mode, check
	if the array is or is not sorted, sort the array with a selection sort, randomly generate 10 new values for 
	the array, perform a binary search, and exit the program.

	INPUT: This program will read in 10 integers from the console, and from an external file, it will accept input
		for a value for a binary search
	OUTPUT: This program will output to the console the array values, the median, the mode, if it is or is not sorted, 			and a number and its subscript in the sorted array for a bianry search.
	VALIDATION: This program will validates when openening an external file the file is not in fail state.
*/

#include <iostream>
#include <fstream>
#include<iomanip>
#include<cstdlib> //srand and ran
#include <ctime> //time for seed

using namespace std;

// Function prototypes
void initNumbers(/*out*/ int [], /*in*/int);
void readNumbers(/*inout*/ifstream &, /*out*/int [], /*in*/int);
void getNumbers(/*out*/int [],/*in*/ int);
void displayNumbers(/*out*/const int [],/*in*/ int);
void median(/*out*/ int values[], /*in*/ int size);
void mode(/*out*/ int values[], /*in*/ int size);
void isSorted(/*out*/ int values[], /*in*/ int size);
void selectionSort(/*out*/ int [], /*in*/ int);
void randomNumbers(/*out*/ int values[], /*in*/ int size);
void binarySearch(/*out*/ int values[], /*in*/ int size);
void arrayCopy(/*in*/ int values[], /*out*/ int valuesCopy[], /*in*/ int size);

int main()
{
	//variable declarations
	const int ARRAY_SIZE = 10;

    	cout<<fixed<<showpoint<<setprecision(2); //manipulators set for output format

	// File stream object
	ifstream inFile;

	// Array to hold the scores
	int numbers[ARRAY_SIZE];
	//initialize the array with 0's
	initNumbers(numbers, ARRAY_SIZE);

	int choice;

	do
	{
        	//user interface used to call individual functions
        	cout << "---------------------------------------------------------------------" << endl;
        	cout << "1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS" << endl;
        	cout << "---------------------------------------------------------------------" << endl;
        	cout << "1. New data set: Keyboard input(10 numbers from user)" << endl;
        	cout << "2. New data set: File data read(10 numbers from the file, numbers.txt.)" << endl;
        	cout << "3. Data set:     Display current data set." << endl;
        	cout << "4. Data set:     Display median. " <<endl;
        	cout << "5. Data set:     Display mode. " <<endl;
        	cout << "6. Data set:     Check array elements - sorted or unsorted." << endl;
        	cout << "7. Data set:     Ascending sort - Selection Sort."<<endl;
        	cout << "8. New data set: Random numbers(10 numbers in range of values 1 - 200). " <<endl;
        	cout << "9. Data set:     Binary Search for data item - found, not found and position"<<endl;
        	cout <<"10.Exit program\n"<<endl;

        	cout << "Enter your choice: ";

        	cin >> choice;

        	// a sample validation routine to try catch input error
        	while (!cin || choice > 10 || choice < 1) 
		{
            		cout<<"INVALID CHOICE ...please retype"<<endl;
            		cin.clear();
            		cin.ignore();
            		cin >> choice;
        	}
        	// switch cases contain various function calls to process a data set in an array based list
        	switch (choice)
        	{
	      		case 1: cout<<endl;
                    		// Function call for user input for a new data set to be stored in  array.
                    		getNumbers(numbers, ARRAY_SIZE);
                    		cout<<endl;
                    		displayNumbers(numbers, ARRAY_SIZE); //function call to display current data set
                    		break;
          		case 2: cout<<endl;
                    		// Function call to read file data for a new data set to be stored in  array.
                    		readNumbers(inFile, numbers, ARRAY_SIZE);
                    		cout<<endl;
                    		displayNumbers(numbers, ARRAY_SIZE); //function call to display current data set
                    		break;
          		case 3: cout<<endl;
                    		displayNumbers(numbers, ARRAY_SIZE); //function call to display current data set
                    		break;
          		case 4:  cout<<endl;
                    		// Function call to display the median
				median(numbers, ARRAY_SIZE);
                    		break;
          		case 5:  cout<<endl;
                   		// Function call to display mode
				mode(numbers, ARRAY_SIZE);
                    		break;
          		case 6: cout<<endl;
				// Function call to display current data set
				displayNumbers(numbers, ARRAY_SIZE);
                    		// Function call to determine if array is sorted or unsorted
				isSorted(numbers, ARRAY_SIZE);
                    		break;
          		case 7: cout<<endl;
                   		// Function call to performe a selectin sort on the array
		 		selectionSort(numbers, ARRAY_SIZE);
				displayNumbers(numbers, ARRAY_SIZE); //function call to display current sorted data set 
   	                	break;
          		case 8: cout<<endl;
                    		// Function call to generate new element values at random of type int for array
				randomNumbers(numbers, ARRAY_SIZE);
				// Function call to display current data set
				displayNumbers(numbers, ARRAY_SIZE);
                    		break;
          		case 9: cout<<endl;
                   		// Function call to do a binary search on the data set
				binarySearch(numbers, ARRAY_SIZE);
                   		break;
          		case 10:cout<<endl;
                    		cout<<"Array processing test now concluded. Exiting program ....."<<endl;
                    		break;
	      		default:cout<<"INVALID CHOICE ...please retype"<<endl;
                    		break;
	    	}
	}while(choice!=10);

	return 0;
}


// *********************************************************************************
// The readNumbers function reads numbers using the inFile reference parameter and *
// stores a new data set to an integer values array. The value parameter size is   *
// passed a valid array size via the last argument from the calling function       *                     *
// *********************************************************************************
void readNumbers(/*inout*/ifstream &inFile,/*out*/ int values[],/*in*/ int size)
// Precondition: Arguments in calling function has passed valid parameters
// Postcondition:
//   A new data set has read from file data and stored in the reference parameter array
{
	string fileName;
    	int count = 0;

    	cout<<"Please enter filename: ";
    	cin>>fileName;
    	inFile.open(fileName.c_str());// Open the file

    	//File not found validation routine
	while (!inFile) 
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Error opening the file.\n";
        	cout<<"Please enter filename: ";
        	cin>>fileName;

        	inFile.open(fileName.c_str());    // Open the file.
	}

        for (count = 0; count < size; count++)
        inFile >> values[count]; //file data read...note no validation for correct data items

        cout<<"File has successfully opened and "<< count <<" values have been read and stored."<<endl;
    	inFile.close();
    	inFile.clear();
}


// ***********************************************************************************
// The initNumbers function initializes the array passed to it by reference from the *
// calling function by setting all elements to 0. The value parameter size is passed *
// a valid array size via the last argument from the calling function                *                     *
// ***********************************************************************************
void initNumbers(/*out*/int values[],/*in*/int size)
// Precondition: Arguments in calling function has passed valid parameters
// Postcondition: All elements in the reference parameter array have been initialized with 0
{
	for (int i = 0; i < size; i++)
	{
      		values[i]=0;
	}
}


// *********************************************************************************
// The getNumbers function provides an interface to get numbers from keyboard input*
// to be stored as a new data set in the array passed to it by reference from the  *
// calling function. The value parameter size is passed a valid array size via the *
// last argument from the calling function                                         *
// *********************************************************************************
void getNumbers(/*out*/int values[],/*in*/ int size)
// Precondition: Arguments in calling function has valid parameters
// Postcondition: A new data set has read from user input and stored in the reference parameter array
{
	for (int i = 0; i < size; i++)
	{
      	cout<<"Enter value #"<<i+1<<": ";
      	cin >> values[i];
      	}
}


// ***********************************************************************************
// The displayNumbers function reads and displays elements from an array passed to it*
// by reference from the calling function. const key word used to prevent accidental *
// writes. The value parameter size is passed a valid array size via the last
// argument from the calling function                                                *
// ***********************************************************************************
void displayNumbers(/*in*/const int values[],/*in*/ int size)
// Precondition: Arguments in calling function has valid parameters
// Postcondition:
//   The current data set in the reference parameter array is displayed in a specific format
{
	cout << " *** Current elements in the array based list *** \n";
   	cout << "-------------------------------------------------------\n";
   	for (int i = 0; i < size; i++)
	{
      		cout<<"Element#"<<i+1<<":";
      		if(i==size-1)
        		cout<<setw (4) <<values[i]<<endl;
      		else
       			 cout<<setw (5) <<values[i]<<endl;
   	}
}


// ***********************************************************************************
// This function finds the median of an even sized int array.  It sorts the array    *
// then adds and divides the two middle numbers together and returns a statement to  *
// the screen with the median value displayed as a type double.                      *
// ***********************************************************************************
void median(/*in*/ int values[], /*in*/ int size)
// Precondition: The array is of type int, the array has been declared and initialized 
// the array is an even size
// Postcondition: The array has been sorted and the median has been outputed to the
// console as a type double
{
	int tempCopy[size];
	arrayCopy(values, tempCopy, size);
	
	selectionSort(tempCopy, size);
	
	int midSubscript = (size/2);
	double value1 = tempCopy[midSubscript];
	double value2 = tempCopy[midSubscript - 1];
	double median = ((value1 + value2) / 2);
	cout << "The median of the data set is: " << setprecision(2) << median << endl;
}


// ***********************************************************************************
// This function determins if there is a mode in the array set.  First it will sort  *
// the array a copy of the array. Then it will check if there is a mode in the array.*  
//The function will then print the mode to the console. If there is no mode it will  *
//print a statement saying there is no mode to the console.                          *                                   
// ***********************************************************************************
void mode(/*out*/ int values[], /*in*/ int size)
// Precondition: An array of type int has been declared and initialized
// Postcondition: The array has been sorted and returned via reference and an out put 
// of the mode or a statement that there is no mode has been printed to the console
{
	int valueCounter = 1;
	int highValueCounter = 1;
	int mode = 0;

	int tempCopy[size];
	arrayCopy(values, tempCopy, size);

	selectionSort(tempCopy, size);
	
	for(int iterator = 0; iterator < (size - 1); iterator++)
	{
		int value = tempCopy[iterator];
		int newValue = tempCopy[iterator + 1];
		//update the high value counter and mode
		if(valueCounter > 1)
		{
			if(valueCounter > highValueCounter)
			highValueCounter = valueCounter;
			mode = value;
		}
	
		//check if a value occures more than once
		if(value == newValue)
		{
			valueCounter++;
			newValue = tempCopy[iterator+2];
		}
		else
		{
			value = newValue;
			valueCounter = 1;
			newValue = tempCopy[iterator+2];
		}
	}
	
	//output if there is or is not a mode
	if(highValueCounter > 1)
	{
		cout << "The mode of the data set is: " << mode << endl;
	}
	else
	{
		cout << "There is no mode in the data set" << endl;
	}			
}


// ***********************************************************************************
// This function takes an int array and determines if the array is sorted in         *
// ascending order and then prints a statement if it is or if it is not sorted to the*
// console.									     * 
// ***********************************************************************************
void isSorted(/*in*/ int values[], /*in*/ int size)
// Precondition: An int array has been declared and initialized
// Postcondition: An output stating if the array is or is not sorted in ascending order is printed to the console
{
	int counter = (size-1);
	bool sorted = 1;

	while(counter && sorted)
	{
		if(values[counter] >= values[counter-1])
		{
			counter--;
		}
		else
		{
			sorted = 0;
		}
	}
	
	if(sorted)
	{
		cout << "The data set in the array based list is sorted." << endl;
	}
	else
	{
		cout << "The data set in the array based list is not sorted." << endl;
	}
}


// ***********************************************************************************
// The selectionSort function iterates over an array and sorts it by comparing the   *
// first subscript to the rest of the array, finding if there is another number in   *
// the array which is smaller, then swaps the two numbers. It iterates through the   *
// entire array minus one in order to sort all values in ascending order             *
// ***********************************************************************************
void selectionSort(/*out*/ int values[], /*in*/ int size)
// Precondition: An int array and array size has been declared and initialized
// Postcondition: the array has been sorted and returned via reference in ascending order
{
	int currentElement = 0;
	int smallestElement = 0;
	int smallestSubscript = 0;
	
	for(int i = 0; i < (size - 1); i++)
	{
		currentElement = values[i];
		smallestElement = values[i];
		smallestSubscript = i;
		for(int j = (i+1); j < size; j++)
		{
			if(smallestElement > values[j])
			{
				smallestElement = values[j];
				smallestSubscript = j;
			}
		}
		
		values[i] = smallestElement;
		values[smallestSubscript] = currentElement;
	}
}


// ***********************************************************************************
// This random number generated was based off of Dylan Prindle's random number       *
// generator for our group project Algorithim Workbench #2.  Which was originally    *
// based off the Gaddis textbook "Starting out with C++". This function generates    *
// random numbers between the range of 1 and 200 then appends them to the array      *
// passed to it as an argument via reference.
// ***********************************************************************************
void randomNumbers(/*out*/ int values[], /*in*/ int size)
// Precondition: Receive int array thorugh reference along with size of array
// Postcondition: Returns new randomly generated values to the array via referance
{
	int randomNum = 0;
	//seed for random number generation
	unsigned seed = time(0);
	srand(seed);
	
	for(int subscript = 0; subscript < size; subscript++)
	{
		//range for random number 1 - 200
		randomNum = rand() % 200 + 1;
		values[subscript] = randomNum;
	}
}


// ***********************************************************************************
// This function was taken from Gaddis textbook "C++ From Control Sturctures through *
// Objects" and modified so the value being searched for was called inside the       *
// instead of being an argument of the function. The binarySearch function performs  *
// a binary search on an integer array.  Array, which has a maximum of size elements *
// is searched for the number stored in value.  If the number is found, it's array   *
// subscript is returned with a statement, otherwise tehre is output to indicate the *
// value being searched for is not within the array.			             *
// ***********************************************************************************
void binarySearch(/*out*/ int values[], /*in*/ int size)
// Precondition: An int array has been declared and initialized
// Postcondition: The array has been sorted and returnd via reference and the user has been notified if the value is contained in the array
{
	int first = 0;		//First array element
	int last = size - 1;	//Last array element
	int middle;		//Midpoint of search
	int position = -1;	//Position of search value
	bool found = false;	//Flag
	int value;
	
	selectionSort(values, size);	//Sort the array

	cout << "Enter number to search for in data set: ";
	cin >> value;	
	while(!found && first <= last)
	{
		middle = (first + last) / 2;	//calculate midpoint
		if(values[middle] == value)	//If value is found at mid
		{
			found = true;
			position = middle;
		}
		else if (values[middle] > value)	//if value is in lower half
			last = middle - 1;
		else 
			first = middle + 1;	//if value in in upper half
	}

	// Function call to display current data set
	displayNumbers(values, size);
	if(value != -1)
	cout << value << " is listed in position " << position << " in current data set" <<  endl;
	else
	cout << value << " is not in the array" << endl;
}


// ***********************************************************************************
// This function copys the int elements of one array to another of the same size     *
// ***********************************************************************************
// Precondition: Two int arrays must be declared with the same number of elements
// Postcondition: The second array argument contains the values of the first array
void arrayCopy(/*in*/ int values[], /*out*/ int valuesCopy[], /*in*/ int size)
{
	for(int i = 0; i < size; i++)
	{
		valuesCopy[i] = values[i];
	}
}

/*
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 2

Please enter filename: srjc.txt
Error opening the file.
Please enter filename: numbers.txt
File has successfully opened and 10 values have been read and stored.

 *** Current elements in the array based list *** 
-------------------------------------------------------
Element#1:  106
Element#2:  102
Element#3:  109
Element#4:  104
Element#5:  105
Element#6:  100
Element#7:  107
Element#8:  105
Element#9:  101
Element#10: 103
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 4

The median of the data set is: 104.50
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 5

The mode of the data set is: 105
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 6

 *** Current elements in the array based list *** 
-------------------------------------------------------
Element#1:  106
Element#2:  102
Element#3:  109
Element#4:  104
Element#5:  105
Element#6:  100
Element#7:  107
Element#8:  105
Element#9:  101
Element#10: 103
The data set in the array based list is not sorted.
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 7

 *** Current elements in the array based list *** 
-------------------------------------------------------
Element#1:  100
Element#2:  101
Element#3:  102
Element#4:  103
Element#5:  104
Element#6:  105
Element#7:  105
Element#8:  106
Element#9:  107
Element#10: 109
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 6

 *** Current elements in the array based list *** 
-------------------------------------------------------
Element#1:  100
Element#2:  101
Element#3:  102
Element#4:  103
Element#5:  104
Element#6:  105
Element#7:  105
Element#8:  106
Element#9:  107
Element#10: 109
The data set in the array based list is sorted.
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 8

 *** Current elements in the array based list *** 
-------------------------------------------------------
Element#1:  159
Element#2:   77
Element#3:   62
Element#4:  182
Element#5:   30
Element#6:  107
Element#7:    2
Element#8:   58
Element#9:   30
Element#10: 105
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 58
INVALID CHOICE ...please retype
9

Enter number to search for in data set: 58
 *** Current elements in the array based list *** 
-------------------------------------------------------
Element#1:    2
Element#2:   30
Element#3:   30
Element#4:   58
Element#5:   62
Element#6:   77
Element#7:  105
Element#8:  107
Element#9:  159
Element#10: 182
58 is listed in position 3 in current data set
---------------------------------------------------------------------
1-D ARRAY PROCESSING MENU OPTIONS - ARRAY BASED LIST WITH 10 ELEMENTS
---------------------------------------------------------------------
1. New data set: Keyboard input(10 numbers from user)
2. New data set: File data read(10 numbers from the file, numbers.txt.)
3. Data set:     Display current data set.
4. Data set:     Display median. 
5. Data set:     Display mode. 
6. Data set:     Check array elements - sorted or unsorted.
7. Data set:     Ascending sort - Selection Sort.
8. New data set: Random numbers(10 numbers in range of values 1 - 200). 
9. Data set:     Binary Search for data item - found, not found and position
10.Exit program

Enter your choice: 10

Array processing test now concluded. Exiting program .....
*/