import java.awt.*;
import javax.swing.*;


class TransactionSuccessful extends JFrame {

    TransactionSuccessful() {
        
        JPanel p1 = new JPanel();
        p1.add(new JLabel("Transaction Failed."));

        setLayout(new BorderLayout());
        add(p1, BorderLayout.CENTER);

        setTitle("Withdraw Cash");
        setSize(300,150);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }
}