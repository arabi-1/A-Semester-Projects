class User {
    private String userId;
    private int pin;
    private Account account;//user "HAS-A" account

    //constructor
    User(String userId, int pin, Account account){
        this.userId=userId;
        this.pin=pin;
        this.account=account;
    }

    //getters
    public String getUserId(){
        return userId;
    }
    public int getPin(){
        return pin;
    }
    public Account getAccount(){
        return account;
    }

    public boolean validatePin(int pin){
        if(this.pin==pin){
            return true;
        }
        return false;
    }
    
}
