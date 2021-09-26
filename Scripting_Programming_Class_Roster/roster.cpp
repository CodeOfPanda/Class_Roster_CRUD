#include "roster.h"
#include "student.h"
#include "networkStudent.h"
#include "securityStudent.h"
#include "softwareStudent.h"
#include <sstream>

/*Add method*/
void Roster::add(std::string studentID, std::string firstName, std::string lastName, std::string emailAddress, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3, Degree degreeTypes)
{
	// assigning a student id to a new user added student.
	if (studentID == "") {
		for (int i = 0; i < MAX; i++) {
			if (classRosterArray[i] == nullptr) {
				studentID = "A" + std::to_string(i + 1);
				break;
			}
		}
	}

	int daysInCourse[] = {daysInCourse1, daysInCourse2, daysInCourse3}; //assigning the three values (daysInCourse1 - 3) to the array daysInCourse.
	Student* student = nullptr;

	//when it hits the Degree parameter it will use this switch statement to determine which type of instance to create, or it defaults to nullptr if it is an unknown entry.
	switch (degreeTypes) {
	case Degree::NETWORK:
		student = new NetworkStudent(studentID,firstName, lastName, emailAddress, age, daysInCourse, degreeTypes);
		break;
	case Degree::SECURITY:
		student = new SecurityStudent(studentID, firstName, lastName, emailAddress, age, daysInCourse, degreeTypes);
		break;
	case Degree::SOFTWARE:
		student = new SoftwareStudent(studentID, firstName, lastName, emailAddress, age, daysInCourse, degreeTypes);
		break;
	default:
		student = nullptr;
		break;
	}

	//loops through the information and pushes each instance into the classRosterArray.
	for (int i = 0; i < 10; ++i) {
		if (classRosterArray[i] == nullptr) {
			classRosterArray[i] = student;
			break;
		}
	}
};

/*Remove method*/
void Roster::remove(std::string studentID) {
	std::cout << "Removing studentID: " << studentID << std::endl;
	bool found = false;

	for (int i = 0; i < MAX; i++) {
		//Checks if iteration of classRosterArray is NULL or is an object
		if (classRosterArray[i] != NULL) {
			//if not NULL, then check the paramter to the studentID of iteration of classRosterArray
			if (studentID == classRosterArray[i]->get_studentID())
			{
				found = true;
				classRosterArray[i] = nullptr;
				std::cout << "Student removed" << std::endl;
				break;
			}
		}
	}
	//if not found in loop above, studentID doesn't exist, print error
	if (found == false)
	{
		std::cout << "ERROR: No student with studentID: " << studentID << " was found." << std::endl;
	}
};

/*Print all*/
void Roster::printAll() {
	for (int i = 0; i < 10; i++)
	{
		if (classRosterArray[i] != nullptr)
		{
			classRosterArray[i]->Print();
		}

	}
};

/*Print days in course*/
void Roster::printDaysInCourse(std::string studentID)
{
	for (int i = 0; i < MAX; i++)
	{
		//checks if the iteration is not a nullptr and the studentID parameter matches the classRosterArray iteration, then calls the get_studentID method.
		if ((classRosterArray[i] != nullptr) && (studentID == classRosterArray[i]->get_studentID()))
		{
			//assigns the memory location of get_numDays for each classRosterArray iteration object to the pointer variable days. 
			int* days = classRosterArray[i]->get_numDays();
			
			//Calculate average number of days for data iteration by accessing the values of the pointer variable days.
			int sum = (days[0] + days[1] + days[2]) / 3;

			std::cout << std::endl << classRosterArray[i]->get_firstName() << " "
				<< classRosterArray[i]->get_lastName() << " ("
				<< classRosterArray[i]->get_studentID() << ")"
				<< " will need an average of " << sum << " days.";
		}
	}

};

/*Print invalid emails*/
void Roster::printInvalidEmails()
{
	for (int i = 0; i < MAX; i++)
	{
		//first have to access the email data and then assigning it to variable email.
		std::string email = classRosterArray[i]->get_emailAddress();

		//these are going to be my place holders.
		bool atSignFlag = false; //initializing to false.
		bool periodFlag = false;
		bool spaceFlag = false;

		//loops through each character of the input email.
		for (char& c : email)
		{
			if (c == ' ')
			{
				spaceFlag = true; // reassigning to true if they did have a space in the email.
			}
			else if (c == '.')
			{
				periodFlag = true; //reassigning to true is a period was found.
			}
			else if (c == '@')
			{
				atSignFlag = true; //reassigning to true is an @ symbol was found.
			}
		}

		if (atSignFlag == false || periodFlag == false || spaceFlag == true) //take this branch if they did not include an @ symbol or a period or had an empty space.
		{
			std::cout << "This is an invalid Email entry: " << email << std::endl;
		}
	}
};

/*Print by degree program*/
void Roster::printByDegreeProgram(Degree degreeTypes)
{
	for (int i = 0; i < MAX; i++)
	{
		Student* degree = classRosterArray[i];
		
		//checks if the parameter is equal to the degree type returned by the getDegreeProgram method.
		if (degree->getDegreeProgram() == degreeTypes)
		{
			degree->Print(); //prints that students information to the user.
		}
		
	}
};

void createStudent(Roster& classRoster) {
	std::string fName;
	std::string lName;
	std::string email;
	std::string studentID = "";
	int age;
	int numDays[3];
	std::string degreeType;
	Degree degreeT;

	std::cout << "Please enter student information:" << std::endl;
	std::cout << "First name: ";
	std::cin >> fName;
	std::cout << "Last name: ";
	std::cin >> lName;
	std::cout << "email address: ";
	std::cin >> email;
	std::cout << "Student's age: ";
	std::cin >> age;
	for (int i = 0; i < 3; i++) {
		std::cout << "Remaining days per class (3 entries): ";
		std::cin >> numDays[i];
	}
	bool isTrue = true;
	while (isTrue) {
		std::cout << "Degree type:" << std::endl
			<< "	1) Network" << std::endl
			<< "	2) Security" << std::endl
			<< "	3) Software" << std::endl
			<< "> " << std::endl;
		std::cin >> degreeType;
		if (degreeType == "1") {
			degreeT = Degree::NETWORK;
			isTrue = false;
		}
		else if (degreeType == "2") {
			degreeT = Degree::SECURITY;
			isTrue = false;
		}
		else if (degreeType == "3") {
			degreeT = Degree::SOFTWARE;
			isTrue = false;
		}
		else {
			std::cout << "ERROR: invalid entry." << std::endl;
		}

	}
	std::cout << std::endl;
	classRoster.add(studentID, fName, lName, email, age, numDays[0], numDays[1], numDays[2], degreeT);

};

int getUserInput(Roster& classRoster) {
	std::string userInput = "";

	std::cout << "Please enter the numeric value for what you would like to do." << std::endl;
	std::cout << "	1) add" << std::endl
		<< "	2) modify" << std::endl
		<< "	3) delete" << std::endl
		<< "	4) view roster" << std::endl
		<< "	5) quit" << std::endl;
	std::cout << "> ";
	std::cin >> userInput;
	if (userInput == "5") {
		return 5;
	}
	else if (userInput == "1") {
		createStudent(classRoster);
		return 1;
	}
	else if (userInput == "2") {
		std::cout << "user typed modify" << std::endl;
		return 2;
	}
	else if (userInput == "3") {
		std::cout << "user typed delete" << std::endl;
		return 3;
	}
	else if (userInput == "4") {
		classRoster.printAll();
		std::cout << std::endl;
		return 4;
	}
	else {
		std::cout << "ERROR: invalid entry" << std::endl;
	}

};


/*Destructor*/
Roster::~Roster() 
{

};

int main()
{
	std::cout << "Scripting and Programming Applications - c867" << std::endl;
	std::cout << "Written in C++, " << "Student ID#: 001058808" << " - Maggie Leigland\n" << std::endl;

	//creating an instance of Roster and Degree.
	Roster classRoster;
	Degree degree{};

	std::string data;
	std::string data_in[COLUMNS];

	//parsing through the studentData array from roster.h.
	for (int i = 0; i < sizeof(studentData) / sizeof(studentData[0]); ++i)
	{
		std::istringstream input(studentData[i]);
		for (int j = 0; j < COLUMNS; ++j) {
			std::getline(input, data, ',');
			data_in[j] = data;
		}

		if (data_in[8] == "NETWORK") 
		{
			degree = Degree::NETWORK;
		} 
		else if (data_in[8] == "SECURITY") 
		{
			degree = Degree::SECURITY;
		} 
		else if (data_in[8] == "SOFTWARE") 
		{
			degree = Degree::SOFTWARE;
		}

		//std::stoi() converts a string into an int.
		classRoster.add(data_in[0], data_in[1], data_in[2], data_in[3], std::stoi(data_in[4]), std::stoi(data_in[5]), std::stoi(data_in[6]), std::stoi(data_in[7]), degree);
	}

	std::cout << std::endl;

	int input = getUserInput(classRoster);
	while (input != 5) {
		input = getUserInput(classRoster);
	}

	classRoster.~Roster();

	return 0;
}