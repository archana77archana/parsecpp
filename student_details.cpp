#include <iostream>
#include <string>

using namespace std;

//include necessary headers / packages
class student_details
{
    public:
        string branch, reg_no, name;
        int sslc_marks, HSc_marks, ug_marks, pg_marks;
        // declare necessary variables / structures

        student_details(string b, string r, string n, int s, int h, int u, int p) {
            branch = b;
            r = reg_no;
            n = name;
            s = sslc_marks;
            h = HSc_marks;
            u = ug_marks;
            p = pg_marks;
        }

 // declare and define constructor with args for each detail of a student
 // branch, reg_no, name, sslc_marks, HSc_marks, ug_marks, pg_marks
};
    
//Main function
int main()
{
    //instantiate student_details for three students in each branch CSE, ECE and EEE
    //example:
    //ECE student objects
    student_details EC001("ECE", "11EC001", "Chandler", 85, 88, 80, 82);
    student_details EC002("ECE", "11EC002", "Phoebe", 81, 83, 85, 86);
    student_details EC003("ECE", "11EC003", "Ross", 92, 94, 96, 98);


    //CSE student objects
    student_details CS001("CSE", "11CS001", "Rachel", 65, 70, 66, 60);
    student_details CS002("CSE", "11CS002", "Monica", 91, 95, 97, 92);
    student_details CS003("CSE", "11CS003", "Joey", 54, 50, 51, 56);

    //EEE student objects
    student_details EE001("EEE", "11EE001", "Barney", 70, 71, 72, 73);
    student_details EE002("EEE", "11EE002", "Robin", 90, 92, 93, 94);
    student_details EE003("EEE", "11EE003", "Ted", 83, 86, 87, 89);
}
