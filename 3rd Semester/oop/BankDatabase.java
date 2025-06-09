import java.time.LocalDateTime;
abstract class Transactions{
    private LocalDateTime date;
    private double amount;

    //details Method
    public abstract String getDetails(); 
}