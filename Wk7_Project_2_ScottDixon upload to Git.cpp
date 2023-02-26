// Wk7_Project_Scott_Dixon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/******************************************************************************

Week 7 Scott Dixon Sorting Algo for Course and Pre-requisites.
CS-300 Date 02/19/2023

*******************************************************************************/
/******************************************************************************

							  Online C++ Compiler.
			   Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Course
{				//Instantiate Course 
	string code;
	string name;
	vector < string > prerequisites;
};

void
readCSVFile(unordered_map < string, Course >& courses, string fileName)
{				// set up to read file
	ifstream file(fileName);

	if (file.is_open())
	{
		string line;

		// read course codes, course names, and prerequisites from file
		while (getline(file, line))
		{
			string courseCode, courseName, prerequisite;
			stringstream ss(line);
			getline(ss, courseCode, ',');
			getline(ss, courseName, ',');
			if (courses.find(courseCode) == courses.end())
			{
				courses[courseCode] = Course
				{
				courseCode, courseName, vector < string >() };
			}
			while (getline(ss, prerequisite, ','))
			{
				courses[courseCode].prerequisites.push_back(prerequisite);
			}
		}

		file.close();		// close file
	}
	else
	{
		cout << "Unable to open file" << endl;
		exit(1);			// return error message if file not found
	}
}

// create menu structure
void
printMenu()
{
	cout << "" << endl;
	cout << " Welcome to the course planner." << endl;
	cout << "" << endl;
	//cout << " What would you like to do?" << endl;
	cout << "" << endl;
	cout << "    1. Load data structure." << endl;
	cout << "    2. Print course list." << endl;
	cout << "    3. Find prerequisites for a course." << endl;
	cout << "    9. Exit" << endl;
	cout << "" << endl;
	cout << " What would you like to do?  ";
}

void
listAllCourseCodes(const unordered_map < string, Course >& courses)
{				// set up sorting structure for courses
	cout << "Here is a list of all course codes and course names:" << endl;
	cout << "" << endl;
	vector < Course > courseVector;
	for (const auto& entry : courses)
	{
		const Course& course = entry.second;
		courseVector.push_back(course);
	}

	sort(courseVector.begin(), courseVector.end(),
		[](const Course& a, const Course& b)
		{
			return a.code < b.code; }
	);

	for (const auto& course : courseVector)
	{
		cout << course.code << " - " << course.name << endl;
		if (!course.prerequisites.empty())
		{
			//  cout << "  Prerequisites: ";
			// for (const auto& prerequisite : course.prerequisites) {
			//    cout << prerequisite << " ";
			{
			}
			cout << endl;
		}
	}
}

//void listAllCourseCodes(const unordered_map<string, Course>& courses) {// code to list course info
	//cout << "All course codes, courses and prerequisites.:" << endl;
	//cout << "" << endl; // add space to output
	//for (const auto& entry : courses) {
	   // const Course& course = entry.second;
	   // cout << course.code << " - " << course.name << endl;
	   // if (!course.prerequisites.empty()) {
	//    cout << "  Prerequisites: ";
	   //     for (const auto& prerequisite : course.prerequisites) {
	   //         cout << prerequisite << " ";
	//    }
	//    cout << endl;
   //     }
 //   }
//}

void
findPrerequisites(const unordered_map < string, Course >& courses)
{
	string courseCode;
	cout << "  Enter a course code to see its prerequisites: ";
	cin >> courseCode;

	if (courses.count(courseCode) == 0)
	{
		cout << "  Incorrect course input - No record found: Please try again."
			<< endl;
		return;
	}

	const Course& course = courses.at(courseCode);

	cout << "   Course name: " << course.name << endl;
	cout << "   Prerequisites for " << course.code << ":" << endl;
	if (course.prerequisites.empty())
	{
		cout << "         None" << endl;
	}
	else
	{
		for (const auto& prerequisite : course.prerequisites)
		{
			cout << "  - " << prerequisite << endl;
		}
	}
}

int
main()
{
	unordered_map < string, Course > courses;
	string fileName = "Text.txt";
	readCSVFile(courses, fileName);

	int choice;
	do
	{
		printMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "" << endl;
			cout << "   Load courses into memory:" << endl;
			cout << "" << endl;

			listAllCourseCodes(courses);

			break;
		case 2:
			cout << "" << endl;
			cout << "   Here is a sample schedule:" << endl;
			cout << "" << endl;

			listAllCourseCodes(courses);

			break;
		case 3:
			cout << "" << endl;
			findPrerequisites(courses);
			break;
		case 9:
			cout << " Thank you for using the course planner!" << endl;
			break;
		default:
			cout << " Invalid input, please try again." << endl;
			break;
		}

		cout << endl;
	} while (choice != 9);

	return 0;
}