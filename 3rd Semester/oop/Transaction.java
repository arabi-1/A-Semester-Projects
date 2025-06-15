import java.time.LocalDateTime;
import java.util.*;

abstract class Transaction{
    protected LocalDateTime date;
    protected double amount;
    protected String type;    //declares what type of transaction (withdrawal, transfer, payment)
    protected boolean status;   //if false then transaction is not added to the list, if true then transaction is added to the list

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public double getAmount() {
        return amount;
    }

    public void setAmount(double amount) {
        this.amount = amount;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public boolean getStatus() {
        return status;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }

    abstract String getDetails();
}

class Withdraw extends Transaction{
    Withdraw(double am, User u) {
        if (u.getAccount().getBalance() < am) {     //checks if user has enough balance
            System.out.println("Not enough balance! Transaction failed");
            status = false;
        }

        else {
            date = LocalDateTime.now();
            amount = am;
            type = "Withdraw";
            status = true;

            u.getAccount().setBalance(u.getAccount().getBalance() - am);    //updates user's account balance
        }
    }

    @Override
    public String getDetails() {
        return "Date: " +date +"\nAmount: " +amount +"\nType: " +type;
    }
}

class Transfer extends Transaction{
    private String accountNumber;

    Transfer(double am, User u, String accountNumber) {     //accoutNumber of recieving account
        if (u.getAccount().getBalance() < am) {     //checkes user's balance
            System.out.println("Not enough Balance! Transaction failed");
            status = false;
        }
        else {
            BankDatabase bankdb = new BankDatabase();
            ArrayList<User> users = bankdb.getUsers();    //imports all users from BankDatabase
            Account receiver;   //temporary variable to make code more readable

            for (int i = 0, size = users.size(); i < size; i++){    //itterates through the arrayList of users and checks if receiving account exists in database
                receiver = users.get(i).getAccount();
                if (receiver.getAccountNumber().equals(accountNumber)) {    //account exists
                    u.getAccount().setBalance(u.getAccount().getBalance() - am);       //balance subtracted from users account
                    receiver.setBalance(receiver.getBalance() + am);        //balance added to the receiving account (transfer success)

                    date = LocalDateTime.now();
                    amount = am;
                    type = "Transfer";
                    this.accountNumber = accountNumber;
                    status = true;
                }
                status = false;     //means receiving account does not exist  
            }
        }
    }

    @Override
    public String getDetails() {
        return "Date: " +date +"\nAmount: " +amount +"\nType: " +type +"\nTransfered To: " +accountNumber;
    }
}

class Payment extends Transaction {
    private String invoice;
    private int am;

    Payment (User u, String invoice) {
        am = 1500 + (int)(Math.random() * 5000);       //generates random amount for the bill kyunkay hmaray pass koi actual bill ki database to he nahi

        if (u.getAccount().getBalance() < am) {     //checks if user has enough balance
            System.out.println("Not enough balance! Transaction failed");
            status = false;
        }

        else {
            date = LocalDateTime.now();
            amount = am;
            type = "Payment";
            this.invoice = invoice;
            status = true;

            u.getAccount().setBalance(u.getAccount().getBalance() - am);    //updates user's account balance
        }
    }

    @Override
    public String getDetails() {
        return "Date: " +date +"\nAmount: " +amount +"\nType: " +type +"\nInvoice Number: " +invoice;
    }
}
