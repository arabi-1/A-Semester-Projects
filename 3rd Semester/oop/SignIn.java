import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.*;

class SignIn extends JFrame {
    private JPanel p1;
    private JPanel p2;
    private JTextField t1;
    private JTextField t2;
    private JLabel l1;
    private JButton b;
    private ATM atm;

    SignIn(ATM atm) {
        this.atm = atm;

        p1 = new JPanel();
        p1.setLayout(new GridLayout(2,2));

        p1.add(new JLabel("User ID"));
        t1 = new JTextField(8);
        t1.setHorizontalAlignment(JTextField.CENTER);
        p1.add(t1);

        p1.add(new JLabel("PIN"));
        t2 = new JTextField(8);
        t2.setHorizontalAlignment(JTextField.CENTER);
        p1.add(t2);

        p2 = new JPanel();
        p2.setLayout(new GridLayout(2, 1));
        l1 = new JLabel("");
        p2.add(l1);
        
        b = new JButton("Sign in");
        b.addActionListener(new myHandler());
        p2.add(b);

        setLayout(new GridLayout(2, 1));
        add(p1);
        add(p2);
        setTitle("Sign In");
        setSize(300,150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);

    }

    class myHandler implements ActionListener {
        public void actionPerformed(ActionEvent a) {
            if (a.getSource() == b) {
                User u1 = atm.getBankDatabase().authenticateUser(t1.getText(), Integer.valueOf(t2.getText()));
                if (u1 != null) {
                    atm.setCurrentUser(u1);
                    dispose();
                    Menu ME = new Menu(atm);
                }
                else if (u1 == null) {
                    l1.setText("Sign in Failed. Invalid ID or PIN");
                }
            }
        }
    }
}