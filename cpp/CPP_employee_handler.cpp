#include <iostream>
#include <string>
#include <stdio.h>
#include <sqlite3.h>
#include <ctime>

using namespace std;

//immutable 
class Employee{
    private:
        string first_name;
        string last_name;
        string email;
        string phone_num;
        string id;
        string Title;

    //constructor
    public: 
        Employee(string fname, string lname, string pnum, string title){
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
            //! need to figure out how to compare variable with database
            static bool check_id(string id){
                //check if id is unique in database
                sqlite3* DB;
                char* msgErr;
                int exit = sqlite3_open("Employee_info.db", &DB);
                string checkIdStmt = "SELECT * FROM EMPLOYEES_CPP WHERE id = '"+id+"';";

                exit = sqlite3_exec(DB, checkIdStmt.c_str(), NULL, 0, &msgErr);
                
                if (exit != SQLITE_OK){
                    std::cerr << "Error finding values in the table" << std::endl;
                }
                sqlite3_close(DB);
                if(exit == 0){
                    return false;
                }
                else{
                    return true;
                }
            }

            static string create_id(){
                // using time create unique id and check if it exists > return it >> no = recursive
                time_t current_time;
                time(&current_time);
                //use check_id func if false return if true recursvie
                std::string id_s = std::to_string(current_time);

                cout<< "check id is here:";
                if(check_id(id_s) == false){
                    return id_s;
                }
                else{
                    create_id();
                }
                
            }
};

//getting all values from a column
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
    char* msgErr;
    int exit = sqlite3_open("Employee_info.db", &DB);
    
    string table = "CREATE TABLE IF NOT EXISTS EMPLOYEES_CPP(id text NOT NULL, fname text NOT NULL, lname text NOT NULL, pnum text NOT NULL, title text NOT NULL);";
    exit = sqlite3_exec(DB, table.c_str(), NULL, 0, &msgErr);

    if (exit != SQLITE_OK){
        std::cerr << "Error Creating the table" << std::endl;
    }else{
        std::cout<<"Table Created Successfully" << std::endl;
    }
    sqlite3_close(DB);
}

//interaction with database functions

//adds all employees given by input
void add_employee(Employee e){
    
    //init connection
    sqlite3* DB;
    char* msgErr;
    int exit = sqlite3_open("Employee_info.db", &DB);

    //assign var to getter methods
    string id = e.get_id();
    string fname = e.get_fname();
    string lname = e.get_lname();
    string pnum = e.get_phone_num();
    string title = e.get_title();
    
    //create querery statement
    string insertStmt = "INSERT INTO EMPLOYEES_CPP (id, fname, lname, pnum, title) VALUES('"+id+"','"+fname+"','"+lname+"','"+pnum+"','"+title+"');";
    exit = sqlite3_exec(DB, insertStmt.c_str(), NULL, 0, &msgErr);

    //light error handling
    if(exit != SQLITE_OK){
        std::cerr << "ERROR INSERTING VALUES" << std::endl;
        sqlite3_free(msgErr);
    }
    else{
        std::cout << "Records added successfully\n"; 
    }
    // end connection
    sqlite3_close(DB);
}

// checks database removes all employee given by input
void remove_employee(string id){
    sqlite3* DB;
    char* msgErr;
    int exit = sqlite3_open("Employee_info.db", &DB);

    string deleteStmt = "DELETE FROM EMPLOYEES_CPP WHERE id = '"+id+"';";
    exit = sqlite3_exec(DB, deleteStmt.c_str(), NULL, 0, &msgErr);

    if(exit != SQLITE_OK){
        std::cerr << "ERROR DELETING VALUES" << std::endl;
        sqlite3_free(msgErr);
    }
    else{
        std::cout << "Record Deleted successfully\n";
    }
    sqlite3_close(DB);
}

//checks database promotes empolyees to new title given
void promote_employee(string id, string new_title){
    sqlite3* DB;
    char* msgErr;
    int exit = sqlite3_open("Employee_info.db", &DB);

    string promoteStmt = "UPDATE EMPLOYEES_CPP set title = '"+new_title+"' where id = '"+id+"';";

    exit = sqlite3_exec(DB, promoteStmt.c_str(), NULL, 0, &msgErr);

    if(exit != SQLITE_OK){
        std::cerr << "ERROR PROMOTING EMPLOYEE" << std::endl;
        sqlite3_free(msgErr);
    }
    else{
        std::cout << "Record updated successfully\n";
    }
    sqlite3_close(DB);
}

//prints employee from database
void display_employee(string id){
    sqlite3* DB;
    char* msgErr;
    int exit = sqlite3_open("Employee_info.db", &DB);

    string displayStmt = "SELECT * FROM EMPLOYEES_CPP WHERE id = '"+id+"';";
    
    std::cout << "Employee:\n";
    exit = sqlite3_exec(DB, displayStmt.c_str(), callback, 0, &msgErr);

    if(exit != SQLITE_OK){
        std::cerr << "ERROR DISPLAYING EMPLOYEE" << std::endl;
        sqlite3_free(msgErr);
    }
    else{
        std::cout << exit;
    }
    sqlite3_close(DB);
}

int main(int argc, char** argv){
    //creating table
    init_employee_table();
    
    //creating employee objects
    Employee employee1("Gio", "Joseph", "215-632-5126", "Backend Dev");
    Employee employee2("Nicole", "Joseph", "893-246-0123", "CEO");
    Employee employee3("Some", "Dude", "999-000-1111", "Janitor");

    cout << employee1.get_email() << endl;
    cout << employee1.get_id() << endl;
    
    

    //adding employee
    add_employee(employee1);
    add_employee(employee2);
    add_employee(employee3);
    
    //deleting emplpoyee
    //remove_employee("41");

    //promoting employee
    //promote_employee("41", "Big Boss Man");
    
    //displaying employee
    display_employee("41");

    return(0);
}