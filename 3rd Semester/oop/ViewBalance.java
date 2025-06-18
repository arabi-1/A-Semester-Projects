import java.awt.*;
import javax.swing.*;


class ViewBal extends JFrame {
    ViewBal(ATM atm) {

        JPanel p1 = new JPanel();
        p1.add(new JLabel("Balance: " +atm.getCurrentUser().getAccount().getBalance()));

        setLayout(new BorderLayout());
        add(p1, BorderLayout.CENTER);

        setTitle("View Balance");
        setSize(300,150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);

    }
}