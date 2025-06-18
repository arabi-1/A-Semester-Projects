import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.*;

//view history
//withdraw, payment, transfer
//view balance

class Menu extends JFrame {
    private JPanel p1;
    private JPanel p2;

    private JButton withdraw;
    private JButton transfer;
    private JButton payment;
    private JButton viewHist;
    private JButton viewBal;
    private ATM atm;

    Menu(ATM atm) {
        this.atm = atm;
        withdraw = new JButton("Withdraw");
        transfer = new JButton("Transfer");
        payment = new JButton("Payment");
        viewHist = new JButton("History");
        viewBal = new JButton("View Balance");

        myHandler handler = new myHandler();

        withdraw.addActionListener(handler);
        transfer.addActionListener(handler);
        payment.addActionListener(handler);
        viewHist.addActionListener(handler);
        viewBal.addActionListener(handler);
        
        p1 = new JPanel();
        p1.setLayout(new GridLayout(1,3));
        p1.add(withdraw);
        p1.add(transfer);
        p1.add(payment);
        
        p2 = new JPanel();
        p2.setLayout(new GridLayout(1, 2));
        p2.add(viewHist);
        p2.add(viewBal);

        setLayout(new GridLayout(2, 1));
        add(p1);
        add(p2);

        setTitle("Menu");
        setSize(300,150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    class myHandler implements ActionListener {
        public void actionPerformed(ActionEvent a) {
            if (a.getSource() == withdraw) {
                
            }
            else if(a.getSource() == transfer) {

            }
            else if (a.getSource() == payment) {

            }
            else if (a.getSource() == viewHist) {

            }
            else {

            }           
        }
    }
}