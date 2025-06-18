import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.*;
import java.util.ArrayList;


class PaymentMenu extends JFrame {
    private JPanel p1;
    private JPanel p2;

    private JButton payment;
    private JLabel l1;
    private JTextField t1;
    private ATM atm;

    PaymentMenu(ATM atm) {
        this.atm = atm;
        payment = new JButton("Confirm Payment");
        l1 = new JLabel("Invoice Number");
        t1 = new JTextField(8);

        myHandler handler = new myHandler();

        payment.addActionListener(handler);
        
        p1 = new JPanel();
        p1.setLayout(new GridLayout(1,2));
        p1.add(l1);
        p1.add (t1);
        
        p2 = new JPanel();
        p2.setLayout(new GridLayout(1, 1));
        p2.add(payment);

        setLayout(new GridLayout(2, 1));
        add(p1);
        add(p2);

        setTitle("Payment");
        setSize(300,150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    class myHandler implements ActionListener {
        public void actionPerformed(ActionEvent a) {
            setVisible(false);
            Transaction trans = new Payment(atm.getCurrentUser(), t1.getText());

            if (!trans.getStatus()) {
                TransactionFailed TF = new TransactionFailed();
            }
            else {
                TransactionSuccessful TS = new TransactionSuccessful();
                atm.getCurrentUser().getAccount().addTransaction(trans);
            }
        }
    }
}
