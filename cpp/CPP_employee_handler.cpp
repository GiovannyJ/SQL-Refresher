#include <iostream>
#include <string>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

// bool check_id(int id){
//  // get all cases with given id value and return bool of if it is 1 or nah   
// }

int create_id(){
    // using time create unique id and check if it exists > return it >> no = recursive
    return 10;
}

class Employee{
    private:
        string first_name;
        string last_name;
        string email;
        int phone_num;
        int id;
        string Title;

    public: 
        Employee(string fname, string lname, int pnum, string title){
            first_name = fname;
            last_name = lname;
            phone_num = pnum;
            email = fname + lname + "@company.com";
            id = create_id();
            Title = title;
        }

        string get_fname(){
            return first_name;
        }

        string get_lname(){
            return last_name;
        }

        string get_email(){
            return email;
        }

        int get_phone_num(){
            return phone_num;
        }

        int get_id(){
            return id;
        }

        string get_title(){
            return Title;
        }
};

// void add_employee(int *e){
//     //adds all employees given by input
// }

// void remove_employee(int *e){
//     //removes all employee given by input
// }

// void promote_employee(int e, string new_title){
//     //promotes empolyees to new title given
// }

// string display_employee(int e){
//     //prints employees
// }

int main(){
    Employee employee1("Gio", "Joseph", 2156325126, "Backend Dev");
    cout << employee1.get_email();

    return(0);
}