#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class StudentEvaluation
{
	char rollNumber[9];
	char* studentName;
	int* quizMarks;
	int* assignmentMarks;
	int totalMarks;
	static int totalQuizes;
	static int totalAssignments;
	static int totalStudents;
	static int totalOverallMarks;
	static int* totalMarksOfAssignments;
	static int* totalMarksOfQuizes;
public:
	StudentEvaluation();
	~StudentEvaluation();
	StudentEvaluation(const StudentEvaluation&);
	const StudentEvaluation& operator=(const StudentEvaluation&);
	void Print();
	void loadFromTextFile(ifstream& inputObj);
	static int getTotalQuizes();
	static int getTotalAssignments();
	static int getTotalStudents();
	static int* getTotalMarksOfAssignments();
	static int* getTotalMarksOfQuizes();
	char* getRollNumber();
	char* getStudentName();
	int getQuizMarks(int);
	int getAssignmentMarks(int);
	int getTotalMarks();
	friend StudentEvaluation* ReadFromFile();
	friend void printStatistics(StudentEvaluation* studentsList);
};

//Helper class to avoid global functions, because they are considered bad practice in Object Oriented Programming.
class helperClass
{
public:
	static void deAllocateIntMemory(int*& toDelete)
	{
		if(toDelete != 0)
		{
			delete[] toDelete;
			toDelete = NULL;
		}

		return;
	}

	static void deAllocateCharMemory(char*& toDelete)
	{
		if(toDelete != 0)
		{
			delete[] toDelete;
			toDelete = NULL;
		}

		return;
	}

	static int sizeOfString(char* str)
	{
		int stringLen = 0;
		for (char* count = str; *count != '\0'; count++)
		{
			stringLen++;
		}

		return stringLen;
	}

	static char* GetStringFromBuffer(char* buffer)
	{
		int strSize = helperClass::sizeOfString(buffer);
		char* dataDestination = 0;

		if (strSize > 0)
		{
			dataDestination = new char[strSize+1];


			for(int i = 0; buffer[i] != '\0'; i++)
			{
				dataDestination[i] = buffer[i];
			}

			dataDestination[strSize] = '\0';
		}
		return dataDestination;
	}

	static char* StringConcatenate(char* str1, char* str2)
	{
		int sizeStr1 = sizeOfString(str1);
		int sizeStr2 = sizeOfString(str2);
		int sizeStr3 = sizeStr1 + sizeStr2 + 1;

		char* str3 = new char[sizeStr3];

		int counter = 0;
		for(; counter < sizeStr1; counter++)
		{
			str3[counter] = str1[counter];
		}

		for(int i = 0; i < sizeStr2; i++)
		{
			str3[counter++] = str2[i];
		}

		str3[counter] = '\0';

		return str3;
	}

	static bool SearchString(char* str1, char* searchString)
	{
		bool foundString, breakLoop;
		int sizeOfStr = sizeOfString(str1), sizeOfSearch = sizeOfString(searchString);
		for(int i = 0; i < sizeOfStr; i++)
		{
			if(str1[0] == searchString[0])
			{
				foundString = true;
				breakLoop = false;

				for(int j = 1; (j < sizeOfSearch) && (breakLoop == false); j++)
				{
					if(str1[i] != searchString[j])
					{
						foundString = false;
						breakLoop = true;
					}
				}

				if(foundString == true)
				{
					return true;
				}

			}
		}

		return false;


	}

	static void sortStudentsByMarks(StudentEvaluation*&);

	static StudentEvaluation* searchStudentsByRollNumber(StudentEvaluation*, char[]);

	static void printAllStudents(StudentEvaluation*);
};

//Intitializing Static variables/pointers once, so they can be used throughout the whole program
int StudentEvaluation::totalQuizes = 0;
int StudentEvaluation::totalAssignments = 0;
int StudentEvaluation::totalStudents = 0;
int StudentEvaluation::totalOverallMarks = 0;
int* StudentEvaluation::totalMarksOfAssignments = NULL;
int* StudentEvaluation::totalMarksOfQuizes = NULL;

//Just the definitions of functions so they can be used inside main(). The code of these functions is available after main(). 
//StudentEvaluation* searchStudentsByRollNumber(StudentEvaluation* studentList, char searchRoll[]);
//void sortStudentsByMarks(StudentEvaluation*& studentList);
//void printAllStudents(StudentEvaluation* studentList);

void main()
{
	StudentEvaluation* studentList =  ReadFromFile();


	if(ReadFromFile == NULL)
	{
		cout << "ERROR in Loading Data: Please make sure the text file is available\n";
	}
	else
	{
		cout << "-------------------------------------------------Data Read from File----------------------------------------------\n\n";

		helperClass::printAllStudents(studentList);



		cout << "\n\n\n-------------------------------------------------Sorted List-------------------------------------------------------\n\n";

		helperClass::sortStudentsByMarks(studentList);
		helperClass::printAllStudents(studentList);



		cout << "\n\n\n-------------------------------------------------Student Information----------------------------------------------\n\n";

		char searchRoll1[9] = {'1', '5', 'L', '-', '1', '2', '3', '4', '\0'}, searchRoll2[9] = {'1', '5', 'L', '-', '4', '0', '2', '3', '\0'};
		StudentEvaluation* firstStudent =  helperClass::searchStudentsByRollNumber(studentList, searchRoll1);
		if(firstStudent == NULL)
		{
			cout << "\nStudent not found\n";
		}
		else
		{
			firstStudent->Print();
		}



		StudentEvaluation* secondStudent = helperClass::searchStudentsByRollNumber(studentList, searchRoll2);
		if(secondStudent == NULL)
		{
			cout << "\nStudent not found\n";
		}
		else
		{
			secondStudent->Print();
		}



		cout << "\n\n\n-------------------------------------------------Class Statistics-------------------------------------------------\n\n";

		printStatistics(studentList);
		delete[] studentList;
	}

	system("pause>0");
}

//Static Getters. Required, as many functions aren't allowed to made friend of the StudentEvaluation :(
int StudentEvaluation::getTotalQuizes()
{
	return totalQuizes;
}

int StudentEvaluation::getTotalAssignments()
{
	return totalAssignments;
}

int StudentEvaluation::getTotalStudents()
{
	return totalStudents;
}

int* StudentEvaluation::getTotalMarksOfAssignments()
{
	return totalMarksOfAssignments;
}

int* StudentEvaluation::getTotalMarksOfQuizes()
{
	return totalMarksOfQuizes;
}


//Getters for Private Data. Again, required due to the lack of friend functions :/
char* StudentEvaluation::getRollNumber()
{
	return rollNumber;
}

char* StudentEvaluation::getStudentName()
{
	return studentName;
}

int StudentEvaluation::getQuizMarks(int i)
{
	return quizMarks[i];
}

int StudentEvaluation::getAssignmentMarks(int i)
{
	return assignmentMarks[i];
}

int StudentEvaluation::getTotalMarks()
{
	return totalMarks;
}



//Just a default constructor. It initializes every "Field" to 0/NULL
StudentEvaluation::StudentEvaluation()
{
	rollNumber[0] = '\0';
	studentName = NULL;
	quizMarks = NULL;
	assignmentMarks = NULL;
	totalMarks = 0;
}

//Destructor. De-Allocates all the "Fields" (to prevent memory leakage)
StudentEvaluation::~StudentEvaluation()
{
	helperClass::deAllocateCharMemory(studentName);
	helperClass::deAllocateIntMemory(quizMarks);
	helperClass::deAllocateIntMemory(assignmentMarks);

}

//Overloaded assignment operator. It De-Allocates all the Fields of "this", creates new dynamic memory on Heap. Deep Copies data from rightHandStudent to "this". Return class of "this".
const StudentEvaluation& StudentEvaluation::operator=(const StudentEvaluation& rightHandStudent)
{
	if( this != &rightHandStudent)
	{
		helperClass::deAllocateCharMemory(studentName);
		helperClass::deAllocateIntMemory(quizMarks);
		helperClass::deAllocateIntMemory(assignmentMarks);

		for(int i = 0; i < 9; i++)
		{
			rollNumber[i] = rightHandStudent.rollNumber[i];
		}


		int nameLength = helperClass::sizeOfString(rightHandStudent.studentName);
		char* newStudentName = new char[nameLength + 1];
		for(int i = 0; i < nameLength; i++)
		{
			newStudentName[i] = rightHandStudent.studentName[i];
		}
		newStudentName[nameLength] = '\0';
		studentName = newStudentName;


		int* newQuizMarks = new int[totalQuizes];
		for(int i = 0; i < totalQuizes; i++)
		{
			newQuizMarks[i] = rightHandStudent.quizMarks[i];
		}
		quizMarks = newQuizMarks;


		int* newAssignmentMarks = new int[totalAssignments];
		for(int i = 0; i < totalAssignments; i++)
		{
			newAssignmentMarks[i] = rightHandStudent.assignmentMarks[i];
		}
		assignmentMarks = newAssignmentMarks;


		totalMarks = rightHandStudent.totalMarks;
	}



	return *this;
}

//Copy Constructor. Creates new dynamic memory on Heap. Deep Copies data from rightHandStudent to the newly allocated memory of "this".
StudentEvaluation::StudentEvaluation(const StudentEvaluation& rightHandStudent)
{
	for(int i = 0; i < 9; i++)
	{
		rollNumber[i] = rightHandStudent.rollNumber[i];
	}


	int nameLength = helperClass::sizeOfString(rightHandStudent.studentName);
	char* newStudentName = new char[nameLength + 1];
	for(int i = 0; i < nameLength; i++)
	{
		newStudentName[i] = rightHandStudent.studentName[i];
	}
	newStudentName[nameLength] = '\0';
	studentName = newStudentName;



	int* newQuizMarks = new int[totalQuizes];
	for(int i = 0; i < totalQuizes; i++)
	{
		newQuizMarks[i] = rightHandStudent.quizMarks[i];
	}
	quizMarks = newQuizMarks;


	int* newAssignmentMarks = new int[totalAssignments];
	for(int i = 0; i < totalAssignments; i++)
	{
		newAssignmentMarks[i] = rightHandStudent.assignmentMarks[i];
	}
	assignmentMarks = newAssignmentMarks;

	totalMarks = rightHandStudent.totalMarks;

}

//Loads "Global" data. Allocates Dynamic Data the size of "Global" data. Once the memory has been allocated, 
//It fills the memory with total marks of Quiz and Assignments (so we can calculate overall statistics of the whole class). 
StudentEvaluation* ReadFromFile()
{
	ifstream inputObj("gradesheet.txt");
	if(!inputObj)
	{
		cout << "ERROR: Text file could NOT be opened\n";
		return NULL;
	}
	else
	{
		inputObj >> StudentEvaluation::totalStudents;

		StudentEvaluation* arrayOfStudents = new StudentEvaluation[StudentEvaluation::totalStudents];

		inputObj >> StudentEvaluation::totalQuizes;
		inputObj >> StudentEvaluation::totalAssignments;


		StudentEvaluation::totalMarksOfQuizes = new int[StudentEvaluation::totalQuizes];
		StudentEvaluation::totalOverallMarks = 0;
		for(int i = 0; i < StudentEvaluation::totalQuizes; i++)
		{
			inputObj >> StudentEvaluation::totalMarksOfQuizes[i];
			StudentEvaluation::totalOverallMarks += StudentEvaluation::totalMarksOfQuizes[i];
		}



		StudentEvaluation::totalMarksOfAssignments = new int[StudentEvaluation::totalAssignments];
		for(int i = 0; i < StudentEvaluation::totalAssignments; i++)
		{
			inputObj >> StudentEvaluation::totalMarksOfAssignments[i];
			StudentEvaluation::totalOverallMarks += StudentEvaluation::totalMarksOfAssignments[i];
		}


		for(int i = 0; i < StudentEvaluation::totalStudents; i++)
		{
			arrayOfStudents[i].loadFromTextFile(inputObj);
		}


		return arrayOfStudents;
	}

}

//A simple function that outputs "Fields" of "this". Also lists overall statistics of teh student for detailed information. Separates the data with a tab(\t) for some nice formatting.
void StudentEvaluation::Print()
{
	cout << "\n\n\n----------------------------------------------------Student Information--------------------------------------\n\n";
	cout << "Roll No:\t\t" << rollNumber << endl;
	cout << "Name:\t\t\t" << studentName << endl;

	cout << "Quizzes Marks:\n";
	for(int i = 0; i < totalQuizes; i++)
	{
		cout << "\t\tQ" << i + 1 << ": \t" << quizMarks[i] << "/" << totalMarksOfQuizes[i] << endl;
	}

	cout << "Assignment Marks:\n";
	for(int i = 0; i < totalAssignments; i++)
	{
		cout << "\t\tA" << i + 1 << ": \t" << assignmentMarks[i] << "/" << totalMarksOfAssignments[i] << endl;
	}
	cout << "Total:\t\t\t" << totalMarks << "/" << totalOverallMarks << endl;

}

//Loads data for individual students into temp buffers. Uses GetStringFromBuffer to allocate exactly enough memory on heap and deep copies data to the allocated memory.
//Also keeps track of all the marks obtained in the Quizes in Assignmnets so we use this data while Sorting the students.
void StudentEvaluation::loadFromTextFile(ifstream& inputObj)
{
	inputObj >> rollNumber;
	char* firstName = new char[40];
	char* lastName = new char[30];

	inputObj >> firstName;
	inputObj >> lastName;

	//insert space before the last name to properly concatinate the two name
	int lastNameSize = helperClass::sizeOfString(lastName);
	for(int i = lastNameSize; i >= 0; i--)
	{
		lastName[i+1] = lastName[i];
	}
	lastName[0] = ' ';

	studentName = helperClass::GetStringFromBuffer(helperClass::StringConcatenate(firstName, lastName));

	totalMarks = 0;

	quizMarks = new int[totalQuizes];

	for(int i = 0; i < totalQuizes; i++)
	{
		inputObj >> quizMarks[i];
		totalMarks += quizMarks[i];
	}

	assignmentMarks = new int[totalAssignments];
	for(int i = 0; i < totalAssignments; i++)
	{
		inputObj >> assignmentMarks[i];
		totalMarks += assignmentMarks[i];
	}

	helperClass::deAllocateCharMemory(firstName);
	helperClass::deAllocateCharMemory(lastName);

	return;
}

//A simple function that outputs all the fields of every student. Separates the data with a tab(\t) for some nice formatting.
void helperClass::printAllStudents(StudentEvaluation* studentList)
{

	cout << "Roll No.\tName\t\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4\tTotal\n"; 

	for(int i = 0; i < StudentEvaluation::getTotalStudents(); i++)
	{
		cout << studentList[i].getRollNumber() << "\t"<< studentList[i].getStudentName() << "\t\t";
		for(int j = 0; j < StudentEvaluation::getTotalQuizes(); j++)
		{
			cout << studentList[i].getQuizMarks(j) << "\t";
		}

		for(int k = 0; k < StudentEvaluation::getTotalAssignments(); k++)
		{
			cout << studentList[i].getAssignmentMarks(k) << "\t";
		}

		cout << studentList[i].getTotalMarks() << "\n";
	}

}

//Looks for the roll number in studentList whose first digit matches with the first digit of searchRoll. Once a match is found, 
//it iterates a loop to determine if the reast of the 7 characters match as well. If all 8 characters match, it returns the current student. If no student matches, returns NULL
StudentEvaluation* helperClass::searchStudentsByRollNumber(StudentEvaluation* studentList, char searchRoll[])
{
	bool foundRoll, breakLoop = false;
	int matchedCharacters = 0;

	for(int i = 0; i < StudentEvaluation::getTotalStudents(); i++)
	{
		if(studentList[i].getRollNumber()[0] == searchRoll[0])
		{
			foundRoll = true;
			breakLoop = false;
			for(int j = 1; (j < 8) && (breakLoop == false); j++)
			{
				if(studentList[i].getRollNumber()[j] != searchRoll[j])
				{
					foundRoll = false;
					breakLoop = true;
				}
			}

			if(foundRoll == true)
			{
				return &studentList[i];
			}

		}
	}

	return NULL;

}

//A rather lengthy but simple function. It creates 6 dynamic arrays to hold 3 attributes per assessment (max, min, avg).
//Iterates a for loop till the last student and finds the max of a Quiz. Stores that in the corresponding index in the array created above.
//Repeats this process for all 6 attributes. By the time the functions exists, we have 6 arrays fully populated with stats of the whole class. 
//Prints the values stored in arrays with proper headings and formatting.
void printStatistics(StudentEvaluation* studentsList)
{
	int* maxOfQuiz = new int[StudentEvaluation::totalQuizes];
	int* minOfQuiz = new int[StudentEvaluation::totalQuizes];
	int* avgOfQuiz = new int[StudentEvaluation::totalQuizes];
	int* maxOfAssignments = new int[StudentEvaluation::totalAssignments];
	int* minOfAssignments = new int[StudentEvaluation::totalAssignments];
	int* avgOfAssignments = new int[StudentEvaluation::totalAssignments];
	int sumOfQuizes = 0, sumOfAssignments = 0;


	for(int j = 0; j < StudentEvaluation::totalQuizes; j++)
	{
		maxOfQuiz[j] = studentsList[0].quizMarks[j];
		minOfQuiz[j] = studentsList[0].quizMarks[j];
		sumOfQuizes += studentsList[0].quizMarks[j];

		for(int i = 1; i < StudentEvaluation::totalStudents; i++)
		{
			sumOfQuizes += studentsList[i].quizMarks[j];

			if(studentsList[i].quizMarks[j] > maxOfQuiz[j])
			{
				maxOfQuiz[j] = studentsList[i].quizMarks[j];
			}

			if(studentsList[i].quizMarks[j] < minOfQuiz[j])
			{
				minOfQuiz[j] = studentsList[i].quizMarks[j];
			}
		}

		avgOfQuiz[j] = sumOfQuizes / StudentEvaluation::totalStudents;
		sumOfQuizes = 0;
	}

	for(int j = 0; j < StudentEvaluation::totalAssignments; j++)
	{
		maxOfAssignments[j] = studentsList[0].assignmentMarks[j];
		minOfAssignments[j] = studentsList[0].assignmentMarks[j];
		sumOfAssignments   += studentsList[0].assignmentMarks[j];

		for(int i = 1; i < StudentEvaluation::totalStudents; i++)
		{
			sumOfAssignments += studentsList[i].assignmentMarks[j];

			if(studentsList[i].assignmentMarks[j] > maxOfAssignments[j])
			{
				maxOfAssignments[j] = studentsList[i].assignmentMarks[j];
			}

			if(studentsList[i].assignmentMarks[j] < minOfAssignments[j])
			{
				minOfAssignments[j] = studentsList[i].assignmentMarks[j];
			}
		}

		avgOfAssignments[j] = sumOfAssignments / StudentEvaluation::totalStudents;
		sumOfAssignments = 0;
	}
	for(int i = 0; i < StudentEvaluation::totalQuizes; i++)
	{
		if(i == 0)
		{
			cout << "\t\t\t";
		}

		cout << "Q" << i + 1 << "\t";
	}
	for(int i = 0; i < StudentEvaluation::totalAssignments; i++)
	{
		cout << "A" << i + 1 << "\t";
	}

	cout << "\nTotal:\t\t\t";
	for(int i = 0; i < StudentEvaluation::totalQuizes; i++)
	{
		cout << StudentEvaluation::totalMarksOfQuizes[i] << "\t";
	}
	for(int i = 0; i < StudentEvaluation::totalAssignments; i++)
	{
		cout << StudentEvaluation::totalMarksOfAssignments[i] << "\t";
	}

	cout << "\nMaximum:\t\t";
	for(int i = 0; i < StudentEvaluation::totalQuizes; i++)
	{
		cout << maxOfQuiz[i] << "\t";
	}
	for(int i = 0; i < StudentEvaluation::totalAssignments; i++)
	{
		cout << maxOfAssignments[i] << "\t";
	}

	cout << "\nMinimum:\t\t";
	for(int i = 0; i < StudentEvaluation::totalQuizes; i++)
	{
		cout << minOfQuiz[i] << "\t";
	}
	for(int i = 0; i < StudentEvaluation::totalAssignments; i++)
	{
		cout << minOfAssignments[i] << "\t";
	}

	cout << "\nAverage:\t\t";
	for(int i = 0; i < StudentEvaluation::totalQuizes; i++)
	{
		cout << avgOfQuiz[i] << "\t";
	}
	for(int i = 0; i < StudentEvaluation::totalAssignments; i++)
	{
		cout << avgOfAssignments[i] << "\t";
	}

	cout << endl;

	helperClass::deAllocateIntMemory(maxOfQuiz);
	helperClass::deAllocateIntMemory(minOfQuiz);
	helperClass::deAllocateIntMemory(avgOfQuiz);
	helperClass::deAllocateIntMemory(maxOfAssignments);
	helperClass::deAllocateIntMemory(minOfAssignments);
	helperClass::deAllocateIntMemory(avgOfAssignments);


	return;

}

//A simple Bubble sort agorithm which compares the total marks of the current student with the next student. If the current makrs are greater, swap the two students. 
//By the time function exists, the array has been sorted in ascending order.
void helperClass::sortStudentsByMarks(StudentEvaluation*& studentList)
{
	for(int i = 0; i < StudentEvaluation::getTotalStudents(); i++)
	{
		for(int j = i + 1; j < StudentEvaluation::getTotalStudents(); j++)
		{
			if (studentList[j].getTotalMarks() < studentList[i].getTotalMarks())
			{
				StudentEvaluation temp = studentList[i];
				studentList[i] = studentList[j];
				studentList[j] = temp;
			}

		}

	}

	return;
}