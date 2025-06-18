import java.awt.*;
import javax.swing.*;
import java.util.ArrayList;

class ViewHist extends JFrame {

    ViewHist(ATM atm) {

        ArrayList<Transaction> transactions = atm.getCurrentUser().getAccount().getTransaction();

        JPanel p1 = new JPanel();
        p1.setLayout(new GridLayout(100,100));

        for (int i = 0; i < transactions.size(); i++) {
            p1.add(new JLabel(transactions.get(i).getDetails()));
        }

        setTitle("History");
        setSize(1366, 1024);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);

    }
}