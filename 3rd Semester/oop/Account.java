import java.util.*;
class Account{
 private String accountNumber;
 private double balance;
 private ArrayList<Transaction> transaction=new ArrayList<>();//composition, Account owns the list of transaction objects. Without Account there will be no transactions

    public Account() {
    }

    public Account(String accountNumber, double balance) {
        this.accountNumber = accountNumber;
        this.balance = balance;
    }

   //Method to get balance/check balance
   public double getBalance(){
      return balance;
   }
   public void setBalance(double balance){
      this.balance=balance;
   }

   public String getAccountNumber(){
      return accountNumber;
   }

   //Method to add Balance/Transaction
   public void addTransaction(Transaction e){
      transaction.add(e);
   }

   //Method to view History
   public void viewHistory(){
      if(transaction.isEmpty()){
         System.out.println("No transactions available");
      }
      for(Transaction t : transaction){
         System.out.println(t.getDetails());
      }
   }
}
