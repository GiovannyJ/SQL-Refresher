#include <iostream>
#include <string>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

//immutable 
class Employee{
    private:
        string first_name;
        string last_name;
        string email;
        long phone_num;
        int id;
        string Title;

    //constructor
    public: 
        Employee(string fname, string lname, long pnum, string title){
            first_name = fname;
            last_name = lname;
            phone_num = pnum;
            email = fname + lname + "@company.com";
            id = create_id();
            Title = title;
        }

        //getter methods
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
        //private methods for the class
        private:
            static bool check_id(int id){
                //check if id is unique in database
                return id == 9;
            }

            static int create_id(){
                // using time create unique id and check if it exists > return it >> no = recursive
                return 10;
            }
};

//interaction with database functions
void add_employee(Employee e){
    //adds all employees given by input
    cout << "Employee " + e.get_fname() + " has been added to the database";
}

// void remove_employee(int *e){
//     // checks database removes all employee given by input
// }

// void promote_employee(int e, string new_title){
//     //checks database promotes empolyees to new title given
// }

// string display_employee(int e){
//     //prints employee from database
// }

int main(int argc, char** argv){
    //creating employee objects
    Employee employee1("Gio", "Joseph", 2156325126, "Backend Dev");
    Employee employee2("Nicole", "Joseph", 893246123, "CEO");

    cout << employee1.get_email() << endl;
    

    //connecting to database
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("Employee_info.db", &DB);

    if(exit){
        std:: cerr << "Error opening db " << sqlite3_errmsg(DB) << std::endl;
        return(-1);
    }
    else{
        std::cout << "opened database" << std::endl;
    }
    sqlite3_close(DB);
    
    return(0);
}