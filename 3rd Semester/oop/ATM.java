import java.util.*;
class ATM {
    private BankDatabase bankDatabase;//atm "has-a" bankDatabase
    private User currentUser;

    ATM(BankDatabase db){
        this.bankDatabase=db;
    }

    void longin(String userId, int pin){
       User user= bankDatabase.authenticateUser(userId, pin);
        if(user!=null){
            currentUser=user;
            System.out.println("Success!, Welcome!"+ currentUser.getUserId());
        }
        else{
            System.out.println("Failed, Try again");
        }
        

    }
    void performTransaction(int option){
        if(currentUser==null){
            System.out.println("Kindly Login first");
            return;
        }
        Scanner sc= new Scanner(System.in);
        Transaction t= null;
        //Switch cases for displaying options

        switch(option){

            case 1:
            System.out.println("Enter amount for withdrawl");
            double wamt=sc.nextDouble();
            t = new Withdraw(wamt, currentUser);
            break;

            case 2:
            System.out.println("Enter amount to transfer: ");
            double tamt = sc.nextDouble();
            sc.nextLine();
            System.out.println("Enter account number of Recipient: ");
            String accNum=sc.nextLine();
            t = new Transfer(tamt, currentUser, accNum, bankDatabase);
            break;

            case 3:
            System.out.println("Enter invoice number: ");
            sc.nextLine();
            String inv=sc.nextLine();
            t = new Payment(currentUser, inv);
            break;

            case 4://to view history
            currentUser.getAccount().viewHistory();
            return;

            case 5://checking balance
            System.out.println("Your balance: "+ currentUser.getAccount().getBalance());
            return;

            default:
            System.out.println("Invalid Option");
            return;

        }
        if(t!= null && t.getStatus()){
            currentUser.getAccount().addTransaction(t);
            System.out.println("Transaction Successful");
        }
        else if( t!=null){
            System.out.println("Transaction failed");
        }
        
    }
}
