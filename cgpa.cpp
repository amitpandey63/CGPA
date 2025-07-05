#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int totalSemesters;
    cout << "Enter number of semesters: ";
    cin >> totalSemesters;

    float grandTotalGradePoints = 0;
    int grandTotalCredits = 0;

    for (int sem = 1; sem <= totalSemesters; sem++) {
        cout << "\n--- Semester " << sem << " ---" << endl;
        int courseCount;
        cout << "Enter number of courses in semester " << sem << ": ";
        cin >> courseCount;

        string courseName[100];
        float grade[100];
        int credit[100];

        float semesterGradePoints = 0;
        int semesterCredits = 0;

        for (int i = 0; i < courseCount; i++) {
            cout << "\nEnter name of course " << i + 1 << ": ";
            cin >> courseName[i];

            cout << "Enter grade for " << courseName[i] << ": ";
            cin >> grade[i];

            cout << "Enter credit hours for " << courseName[i] << ": ";
            cin >> credit[i];

            semesterGradePoints += grade[i] * credit[i];
            semesterCredits += credit[i];
        }

        float semesterGPA = semesterGradePoints / semesterCredits;

        // Display individual course details
        cout << "\nCourse-wise Details for Semester " << sem << ":\n";
        for (int i = 0; i < courseCount; i++) {
            cout << "Course: " << courseName[i]
                 << " | Grade: " << grade[i]
                 << " | Credit Hours: " << credit[i] << endl;
        }

        cout << "Semester " << sem << " GPA: " << fixed << setprecision(2) << semesterGPA << endl;

        // Add to total for CGPA calculation
        grandTotalGradePoints += semesterGradePoints;
        grandTotalCredits += semesterCredits;
    }

    float overallCGPA = grandTotalGradePoints / grandTotalCredits;

    cout << "\n===" << endl;
    cout << "Total Credits (All Semesters): " << grandTotalCredits << endl;
    cout << "Total Grade Points: " << grandTotalGradePoints << endl;
    cout << "Overall CGPA: " << fixed << setprecision(2) << overallCGPA << endl;
    cout << "=========" << endl;

    return 0;
}
