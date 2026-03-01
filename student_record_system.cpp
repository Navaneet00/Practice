#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <memory>
using namespace std;

// Student class
class Student{
    private:
    string name;
    int rollNum;
    vector<double> grades;

    public:
    Student(string studentName, int rollNumber, vector<double> studentGrades) : name(studentName), rollNum(rollNumber), grades(studentGrades){}

    // Get name
    string getName(){
        return name;
    }

    // Get Roll Number
    int getRollNum(){
        return rollNum;
    }

    // Get Student Details
    void getStudentDetails(){
        cout << "Student Details: " << endl;
        cout << "Name: " << name << endl << "Roll Number: " << rollNum << endl << "Grades: ";
        if(grades.empty()){ cout << "None"; }
        else{
            for (int i = 0; i < grades.size(); i++){
                cout << grades[i] << " ";
            }
        }
        cout << endl;
    }

    // Add grade
    void addGrade(double grade){
        grades.push_back(grade);
        cout << endl << "Grade added successfully!" << endl;
    }

    // Get average
    double getAverage(){
        if(grades.empty()){
            return 0.0;
        }
        else{
            return (accumulate(grades.begin(), grades.end(), 0.0) / grades.size());
        }
    }

    // Print average
    void printAverage(){
        if(grades.empty()){
            cout << name << " has no grades" << endl;
        }
        else{
            cout << "Average grades of " << name << ": " << (accumulate(grades.begin(), grades.end(), 0) / grades.size()) << endl;
        }
    }

    // Get highest grade
    void getHighest(){
        if(grades.empty()){
            cout << name << " has no grades" << endl;
        }
        else{
            cout << "Highest grade of " << name << " is: " << (*max_element(grades.begin(), grades.end())) << endl;
        }
    }

    // get lowest grade
    void getLowest(){
        if(grades.empty()){
            cout << name << " has no grades" << endl;
        }
        else{
            cout << "Lowest grade of " << name << " is: " << (*min_element(grades.begin(), grades.end())) << endl;
        }
    }
};

// Student Manager class
class StudentManager{
    vector<unique_ptr<Student>> students;

    public:

    // Add Student
    void addStudent(string name, int rollNum, vector<double> grades){
        students.push_back(make_unique<Student>(name, rollNum, grades));
        cout << name << " added!" << endl;
    }

    // Remove Student by roll number
    void removeStudentByRollNum(int rollNum){

        auto it = remove_if(students.begin(), students.end(), [&](const unique_ptr<Student>& student){
            return student->getRollNum() == rollNum;
        });

        if (it == students.end()) {
            cout << "Student not found.\n";
        } else {
            students.erase(it, students.end());
            cout << "Student removed.\n";
        }
    }

    // Find by name
    Student* findByName(string name){
        auto it = find_if(students.begin(), students.end(), [&](const unique_ptr<Student>& student){
            return student->getName() == name;
        });

        if(it != students.end()){
            (*it)->getStudentDetails();
            return it->get();
        }
        else{
            return nullptr;
        }
    }

    // Sort By Average
    void sortByAverage(){
        if(students.empty()){ return; }

        sort(students.begin(), students.end(), [](const unique_ptr<Student>& studentA, const unique_ptr<Student>& studentB){
            return studentA->getAverage() > studentB->getAverage();
        });
    }

    // Print all students and their details
    void printAll(){
        if(students.empty()){ 
            cout << "No students in the system!" << endl;
            return;
        }

        for (const auto& student : students){
            student->getStudentDetails();
            cout << endl;
        }
    }
};

int main(){
    StudentManager studentManager;

    studentManager.addStudent("Ajay", 178, {75.0, 99.2});
    studentManager.addStudent("Aditya", 145, {});
    studentManager.addStudent("Adarsh", 172, {66.7, 42.7});

    Student* student = studentManager.findByName("Aditya");
    student->addGrade(35.9);

    cout << endl << "Before sorting: " << endl;
    studentManager.printAll();
    
    studentManager.sortByAverage();

    cout << endl << "After sorting: " << endl;
    studentManager.printAll();

    studentManager.removeStudentByRollNum(178);
    studentManager.printAll();
    
    return 0;
}