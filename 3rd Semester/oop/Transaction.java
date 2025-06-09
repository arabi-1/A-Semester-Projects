import java.time.LocalDateTime;
abstract class Transaction{
    LocalDateTime date;
    double amont;

    abstract String getDetails();

}