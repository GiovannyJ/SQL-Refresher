import time
import sqlite3

#create connection to sqlite db
connection = sqlite3.connect('Employee_info.db')
cursor = connection.cursor()

#! change length for id
cursor.execute("CREATE TABLE IF NOT EXISTS EMPLOYEES_PY(id n(5), fname text, lname text, pnum n(10), title text);")

# check if id is already used 
def check_id(id):
    executeStatement = 'select * from EMPLOYEES_PY where id=?'
    exist = cursor.execute(executeStatement, (id,)).fetchall()

    # returns bool
    return len(exist) == 1

# create unique id that not in databse yet
#! fix later
def create_id():
    id = time.time()
    time.sleep(0.01)
    if check_id(id) == False:
        return id
    else: 
        create_id()
        
# simple employee class
class employee:
    def __init__(self, first_name: str, last_name: str, phone_number: int, title: str) -> None:
        self.fname = first_name
        self.lname = last_name
        self.email = self.fname + self.lname + "@company.com"
        self.pnum = phone_number
        self.id = create_id()
        self.title = title

    def get_fname(self):
        return self.fname

    def get_lname(self):
        return self.lname

    def get_email(self):
        return self.email
    
    def get_pnum(self):
        return self.pnum

    def get_id(self):
        return self.id
    
    def get_title(self):
        return self.title

def add_employee(*e) -> None:
    #iterate over given values and add each one to db
    for arg in e:
        executeStatement = "INSERT INTO EMPLOYEES_PY VALUES (?, ?, ?, ?, ?)"
        values = [arg.get_id(), arg.get_fname(), arg.get_lname(), arg.get_pnum(), arg.get_title()]
        cursor.executemany(executeStatement, (values, ))
        connection.commit()

#! error handling if id dont exist
def remove_employee(*e) -> None:
    #iterate over values and remove each one
    for arg in e:
        # removing if arg is class type
        if type(arg) == employee:
            executeStatement = "DELETE FROM EMPLOYEES_PY WHERE id = ?"
            cursor.execute(executeStatement, (arg.get_id(), ))
            connection.commit()
        #rm if arg is number given by user
        elif type(arg) == int or float:
            executeStatement = "DELETE FROM EMPLOYEES_PY WHERE id = ?"
            cursor.execute(executeStatement, (arg, ))
            connection.commit()
        else:
            print("error user ID cannot be found: cannot remove")

def promote_employee(e, new_title: str) -> None:
    if type(e) == employee:
        executeStatement = "UPDATE EMPLOYEES_PY set title = ? where id = ?"
        cursor.execute(executeStatement, (new_title ,e.get_id()))
        connection.commit()
    elif type(e) == int or float:
        executeStatement = "UPDATE EMPLOYEES_PY set title = ? where id = ?"
        cursor.execute(executeStatement, (new_title ,e))
        connection.commit()
    else:
        print("error user ID cannot be found: cannot promote")

#?  add diff ways to search for user
def display_employee(e) -> str:
    if type(e) ==  employee:
        executionStatement = "SELECT * FROM EMPLOYEES_PY WHERE id = ?"
        cursor.execute(executionStatement, (e.get_id(), ))
        display = cursor.fetchone()
        return display
    elif type(e) == int or float:
        executionStatement = "SELECT * FROM EMPLOYEES_PY WHERE id = ?"
        cursor.execute(executionStatement, (e, ))
        display = cursor.fetchone()
        return display
    else:
        print("user ID not found: cannot display")



def main():
    employee1 = employee("Giovanny", "Joseph", 51739981, "Backend Dev")
    employee2 = employee("Nicole", "Joseph", 282130922, "Manager")
    employee3 = employee("Chris", "Lopez", 5168928777,  "Backend Dev")
    employee4 = employee("Sarah", "Pietrafesa", 5164453823, "Frontend Dev")
    employee5 = employee("Nikki", "Heat", 999999999, "CEO")
    employee6 = employee("Seb", "Joseph", 5162835777, "Janitor")

    add_employee(employee1, employee2, employee3, employee4, employee5, employee6)


if __name__ == '__main__':
    main()