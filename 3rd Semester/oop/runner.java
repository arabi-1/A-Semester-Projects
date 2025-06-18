import java.util.ArrayList;

public class runner {
    public static void main(String[] args) {
        Account account = new Account("1234", 125521.23);
        User user = new User("ABCD", 1234, account);

        ArrayList<User> users = new ArrayList<>();
        users.add(user);

        BankDatabase db = new BankDatabase(users);
        ATM atm = new ATM(db);

        SignIn SI = new SignIn(atm);
    }
}