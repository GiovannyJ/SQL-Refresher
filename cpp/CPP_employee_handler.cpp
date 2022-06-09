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
        //! turn back into long 
        string phone_num;
        //! turn back into int
        string id;
        string Title;

    //constructor
    public: 
        Employee(string fname, string lname, string pnum, string title){
            first_name = fname;
            last_name = lname;
            phone_num = pnum;
            email = fname + lname + "@company.com";
            id = "10";//?create_id();
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
        //! should be type(long)
        string get_phone_num(){
            return phone_num;
        }
        //! should be type(int)
        string get_id(){
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

static int callback(void* data, int argc, char** argv, char** azColName){
    int i;
    fprintf(stderr, "%s:", (const char*)data);

    for(i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i]: "NULL");
    }
    printf("\n");
    return 0;
}

void init_employee_table(){
    sqlite3* DB;
    std::string table = "CREATE TABLE IF NOT EXISTS EMPLOYEES_CPP(id n(5), fname text, lname text, pnum n(10), title text);";

    int exit = 0;
    exit = sqlite3_open("Employee_info.db", &DB);
    char* msgErr;

    exit = sqlite3_exec(DB, table.c_str(), NULL, 0, &msgErr);

    if (exit != SQLITE_OK){
        std::cerr << "Error Creating the table" << std::endl;
    }else{
        std::cout<<"Table Created Successfully" << std::endl;
    }
    sqlite3_close(DB);
}

//interaction with database functions
void add_employee(Employee e){
    //adds all employees given by input
    sqlite3* DB;
    char* msgErr;
    int exit = sqlite3_open("Employee_info.db", &DB);
    
    string insert_string = ("INSERT INTO EMPLOYEES_CPP (id, fname, lname, pnum, title) VALUES(%s,%s,%s,%s,%s);", 
    e.get_id(), e.get_fname(), e.get_lname(), e.get_phone_num(), e.get_title());
    
    
    sqlite3_exec(DB, insert_string.c_str(), NULL, 0, &msgErr);

    if(exit != SQLITE_OK){
        std::cerr << "ERROR INSERTING VALUES" << std::endl;
        sqlite3_free(msgErr);
    }
    else{
        std::cout << "Records added successfully"; //<< std::end;
    }
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
    Employee employee1("Gio", "Joseph", "215-632-5126", "Backend Dev");
    // Employee employee2("Nicole", "Joseph", 893246123, "CEO");

    cout << employee1.get_email() << endl;
    cout << employee1.get_id() << endl;
    
    //creating table
    init_employee_table();

    //adding employee
    add_employee(employee1);
    //deleting emplpoyee

    //displaying employee
    
    return(0);
}