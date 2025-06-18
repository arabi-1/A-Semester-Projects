import java.awt.*;
import javax.swing.*;


class TransactionSuccessful extends JFrame {

    TransactionSuccessful() {
        
        JPanel p1 = new JPanel();
        p1.add(new JLabel("Transaction Succesful."));

        setLayout(new BorderLayout());
        add(p1, BorderLayout.CENTER);

        setTitle("Withdraw Cash");
        setSize(300,150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);

    }
}