package JAVA;

import java.sql.*;

//Class immutable
final class Employee {
    private final String fname;
    private final String lname;
    private final String email;
    private final long pnum;
    private final int id;
    private final String Title;

    // constructor (cannot be accessed anywhere else)
    public Employee(String first_name, String last_name, long phone_num, String title) {
        this.fname = first_name;
        this.lname = last_name;
        this.email = first_name.toLowerCase() + last_name.toLowerCase() + "@company.com";
        this.pnum = phone_num;
        this.id = createId();
        this.Title = title;
    }

    // getter methods
    public String getfname() {
        return fname;
    }

    public String getlname() {
        return lname;
    }

    public String getemail() {
        return email;
    }

    public long getpnum() {
        return pnum;
    }

    public int getid() {
        return id;
    }

    public String getTitle() {
        return Title;
    }

    // ? start connection here since we need to check back with database
    // methods for creating ID
    private static boolean checkID(int id) {
        // look at database and return true if id is in there and false if not
        return id == 10;
    }

    private static int createId() {
        int id = 9;
        if (checkID(id) == true) {
            return 0;
        } else {
            return id;
        }
    }

}

// Main Driver
public class JAVA_Employee_handler {
    // initialize varibales for sql
    public static Connection c = null;
    public static Statement stmt = null;

    public static void main(String[] args) {
        // create employees
        Employee employee1 = new Employee("Gio", "Joseph", 516782334, "Backend Developer");
        Employee employee2 = new Employee("Nicole", "Joseph", 562312793, "CEO");

        // creating the table if it doesnt exist
        try {
            // connection to database
            // ! error here need help connecting java to SQL (drivers and downloads and
            // stuff idk)
            Class.forName("org.sqlite.JDBC");
            c = DriverManager.getConnection("jdbc:sqlite:Employee_info.db");

            stmt = c.createStatement();

            String createTableQ = "CREATE TABLE IF NOT EXIST EMPLOYEE_JAVA " +
                    "(id n(5), fname text, lname text, email text, pnum n(10), title text)";

            stmt.executeUpdate(createTableQ);
            stmt.close();
            c.close();

        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }

        // calling methods with created objs
        addEmployee(employee1);
        addEmployee(employee2);
    }

    // methods to interact with db
    static void addEmployee(Employee employee_obj) {
        try {
            c.setAutoCommit(false);
            stmt = c.createStatement();

            String insertQ = "INSERT INTO EMPLOYEES_JAVA VALUES (?, ?, ?, ?, ?)";
            PreparedStatement pst = c.prepareStatement(insertQ);

            pst.setInt(1, employee_obj.getid());
            pst.setString(2, employee_obj.getfname());
            pst.setString(3, employee_obj.getlname());
            pst.setString(4, employee_obj.getemail());
            pst.setLong(5, employee_obj.getpnum());
            pst.setString(6, employee_obj.getTitle());
            pst.executeUpdate();

            pst.close();
            c.close();

        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
    }

    static void deleteEmployee(long id) {

    }

    static void promoteEmployee(long x, String newTitle) {

    }

    static String displayEmployee(long id) {
        return "";
    }
}
