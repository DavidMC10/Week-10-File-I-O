/*
* Main.cpp
*
* Version information v0.1
* Author: Dr. Shane Wilson
* Date: 8/10/2017
* Description: Driver to test the student class
* Copyright notice
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "Student.h"
#include "Module.h"
#include "Person.h"
#include "Lecturer.h"

using namespace std;

bool WriteStudentDetails(std::vector<Student>& data);
std::vector<Student> ReadStudentDetails(std::string dataFile);

int main() {

	//ofstream outFile{};

	//outFile.open("data.txt", ios::binary);

	//// Check to see if the file exists
	//if (!outFile) {
	//	cerr << "File could not be opened" << endl;
	//	exit(EXIT_FAILURE);
	//}

	//// Write some text to the file

	//outFile << "Wenger" << endl;
	//outFile << "Out" << endl;


	//outFile.close();

	Student student1{ "David McElhinney", "B00716978", "BSc Hons Computer Science", 2 };
	student1.SetEmail("McElhinney-D1@ulster.ac.uk");
	student1.AddModule("OOM", "COM321", 20, 90);
	student1.AddModule("OOP", "COM326", 20, 90);
	student1.AddModule("VP", "COM134", 20, 90);

	Student student2{ "Arsene Wenger", "B00444444", "BSc Hons Computer Science 4", 4 };
	student1.SetEmail("Wenger444@ulster.ac.uk");
	student1.AddModule("OOM", "COM321", 44, 44);
	student1.AddModule("OOP", "COM326", 44, 44);
	student1.AddModule("VP", "COM134", 44, 4);

	Student student3{ "Sir Alex", "B001111111", "BSc Hons Computer Science 1", 1 };
	student1.SetEmail("Fergie111@ulster.ac.uk");
	student1.AddModule("OOM", "COM321", 11, 11);
	student1.AddModule("OOP", "COM326", 11, 11);
	student1.AddModule("VP", "COM134", 11, 11);

	vector<Student> studentDetails;

	studentDetails.push_back(student1);
	studentDetails.push_back(student2);
	studentDetails.push_back(student3);

	WriteStudentDetails(studentDetails);
	vector<Student> studentDetailsFile = ReadStudentDetails("data.txt");


	cout << endl << endl;

	//Loop through the vector and write student details out
	for (std::vector<Student>::iterator it = studentDetailsFile.begin(); it != studentDetailsFile.end(); it++) {
		//Write out the details of the student to screen
		cout << it->ToString();
		vector<Module> studentModules = it->GetModules();
		for (int i = 0; i < studentModules.size(); i++) {
			cout << studentModules[i].ToString();
		}
		cout << std::endl;
	}
	return 0;
}


bool WriteStudentDetails(std::vector<Student>& data) {

	//The issue is with writing student details out to the file. It adds a new line after the 
	//last record and therefore the read code doesn't reach eof after reading the last module.
	//As a result it reads the details again.

	cout << "Attempting to write student data to file" << endl;

	//Open a file for writing
	ofstream outFile{ "data.txt", ios::out };

	//Check to see if the file exists
	if (!outFile) {
		cerr << "File could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

	//Loop through the vector and write student details out
	for (std::vector<Student>::iterator it = data.begin(); it != data.end(); it++) {
		//Write out the details of the student
		outFile << quoted(it->GetName()) << " " << quoted(it->GetRegistrationID()) << " " << quoted(it->GetCourse()) << " " << it->GetYearofStudy() << std::endl;

		//Check to see if there is module data to write to file
		int numModules = it->GetNumberModules();
		if (numModules > 0) {
			//Write the number of modules for the student
			//outFile << numModules << std::endl; //remove don't add a new line after the number of modules
			outFile << numModules;
			for (int index = 0; index < numModules; index++) {
				//Write out the module details
				std::vector<Module> marks = it->GetModules();
				//outFile << quoted(marks[index].getModuleTitle()) << " " << quoted(marks[index].getModuleCode()) << " " << marks[index].getModuleCreditPoints() << " " << marks[index].getModuleMark() << std::endl;	
				outFile << "\n" << quoted(marks[index].getModuleTitle()) << " " << quoted(marks[index].getModuleCode()) << " " << marks[index].getModuleCreditPoints() << " " << marks[index].getModuleMark();
				//Start each module on a new line

			}
		}
		else {
			outFile << numModules << std::endl;
		}
	}
	outFile.close();

	return true;
}


std::vector<Student> ReadStudentDetails(std::string dataFile) {

	//Open a file for writing
	ifstream inFile{ "studentData.txt", ios::in };

	//Check to see if the file exists
	if (!inFile) {
		cerr << "File could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

	//We know the file format is:
	//"Student name" "ID" "COURSE" Year of study
	//number of modules
	//"module title" "code" credit points mark

	std::string name, ID, course, moduleTitle, code;
	int numModules, creditPoints, yearStudy;
	float mark;
	std::vector<Student> students;

	//Keep reading data until we get to the end of the file
	while (!inFile.eof()) {
		inFile >> quoted(name) >> quoted(ID) >> quoted(course) >> yearStudy >> numModules;
		//Create a sutdent 
		Student tempStudent{ name, ID, course, yearStudy };
		if (numModules > 0) {
			for (int index = 0; index < numModules; index++) {
				inFile >> quoted(moduleTitle) >> quoted(code) >> creditPoints >> mark;
				tempStudent.AddModule(moduleTitle, code, creditPoints, mark);
			}
			//Add the tempstudent to the vector
			students.push_back(tempStudent);
		}
	}
	inFile.close();

	return students;
}
