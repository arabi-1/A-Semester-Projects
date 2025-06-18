import java.util.ArrayList;

class BankDatabase {    
    ArrayList<User> users = new ArrayList<>();

    BankDatabase() {
    }

    BankDatabase(ArrayList<User> initialUsers) {
        users = initialUsers;
    }

    public User authenticateUser(String userId, int pin){
        for(User u: users){
            if(u.getUserId().equals(userId) && u.validatePin(pin)){
                return u;
            }
            
        }
        return null;//if no match is found we will reuturn null 

    }

    public ArrayList<User> getUsers() {
        return users;
    }

}