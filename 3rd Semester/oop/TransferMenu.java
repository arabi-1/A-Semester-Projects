import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.*;
import java.util.ArrayList;


class TransferMenu extends JFrame {
    private JPanel p1;
    private JPanel p2;

    private JButton transfer;
    private JLabel l1;
    private JLabel l2;
    private JTextField t1;
    private JTextField t2;
    private ATM atm;

    TransferMenu(ATM atm) {
        this.atm = atm;
        transfer = new JButton("Transfer");
        l1 = new JLabel("Amount");
        t1 = new JTextField(8);

        l2 = new JLabel("Account No");
        t2 = new JTextField(8);

        myHandler handler = new myHandler();

        transfer.addActionListener(handler);
        
        p1 = new JPanel();
        p1.setLayout(new GridLayout(2,2));
        p1.add(l1);
        p1.add (t1);
        p1.add(l2);
        p1.add(t2);
        
        p2 = new JPanel();
        p2.setLayout(new GridLayout(1, 1));
        p2.add(transfer);

        setLayout(new GridLayout(2, 1));
        add(p1);
        add(p2);

        setTitle("Transfer Cash");
        setSize(300,150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    class myHandler implements ActionListener {
        public void actionPerformed(ActionEvent a) {
            setVisible(false);

            Transaction trans = new Transfer(Double.valueOf(t1.getText()), atm.getCurrentUser(), t2.getText());

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
