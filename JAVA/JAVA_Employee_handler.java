package JAVA;
//imports
import java.util.Scanner;
import java.util.ArrayList;


//Class
final class Employee{
    private final String fname;
    private final String lname;
    private final String email;
    private final long pnum;
    private final int id;
    private final String Title;

    public Employee(String first_name, String last_name, long phone_num, String title){
        this.fname = first_name;
        this.lname = last_name;
        this.email = first_name.toLowerCase() + last_name.toLowerCase() + "@company.com";
        this.pnum = phone_num;
        this.id = createId();
        this.Title = title;
    }

    public String getfname(){
        return fname;
    }

    public String getlname(){
        return lname;
    }

    public String getemail(){
        return email;
    }

    public long getpnum(){
        return pnum;
    }

    public int getid(){
        return id;
    }

    public String getTitle(){
        return Title;
    }

// methods for creating ID
    private static boolean checkID(int id){
        //look at database and return true if id is in there and false if not
        return id == 10;
    }
    
    private static int createId(){
        int id = 9;
        if(checkID(id) == true){
            return 0;
        }else{
            return id;
        }
    }

}


//Main Driver
public class JAVA_Employee_handler{
    public static void main(String[] args){
        Employee employee1 = new Employee("Gio","Joseph", 516782334, "Backend Developer");
        System.out.println(employee1.getemail());
        Employee employee2 = new Employee("Nicole", "Joseph", 562312793, "CEO");
        
        ArrayList<Employee> employees = new ArrayList<>();
        employees.add(employee1);
        employees.add(employee2);
        addEmployee(employees);
        
    }

    static void addEmployee(ArrayList<Employee> employee_obj_list){
        for(Employee employee_obj : employee_obj_list){
            System.out.println(employee_obj.getfname() + ", ");
        }
    }

    static void deleteEmployee(long id){

    }

    static void promoteEmployee(long x, String newTitle){
        
    }
}
