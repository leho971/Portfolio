import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class Main {
	public static void main(String args[]) {
		
		Figure a = new Point(21,12);
		a.Afficher();
		a.Translater(1, 1);
		a.Afficher();
		System.out.println(a.getCentre());
		System.out.println(" ");
		
		Figure b = new Point();
		String b1 = b.toString();
		Point b2 = (Point)b;
		System.out.println(b1);
		System.out.println(b2.Distance((Point)a));
		System.out.println(b.equals(b));
		System.out.println(" ");
		
		Figure c = a.clone();
		c.Afficher();
		
		
		Figure aa = new Segment((Point)a,(Point)b);
		aa.Afficher();
		Segment aa1 = (Segment)aa;
		System.out.println(aa1.getLongueur());
		System.out.println(" ");
		
		Figure bb = new Segment((Point)b,(Point)a);
		bb.Afficher();
		System.out.println(" ");
		
		
		Figure rond_a = new Cercle((Point)a,(Point)b);
		rond_a.Afficher();
		System.out.println(" ");
		
		//  ne Pas faire heriter de JFrame
		
		JFrame fen = new JFrame();
		fen.setSize(800,600);
		fen.setTitle("banane");
		fen.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel p1 = new JPanel();
		p1.setBackground(Color.CYAN);
		p1.setPreferredSize(new Dimension(250, 0));
		p1.setLayout(new FlowLayout());
		JButton btPoint = new JButton("Point");
		p1.add(btPoint);
		btPoint.setPreferredSize(new Dimension (230,45));
		JButton btSegment = new JButton("Segment");
		p1.add(btSegment);
		btSegment.setPreferredSize(new Dimension (230,45));
		JButton btCercle = new JButton("Cercle");
		p1.add(btCercle);
		btCercle.setPreferredSize(new Dimension (230,45));
		JPanel p2 = new JPanel();
		p2.setBackground(Color.BLUE);
		JTextField t = new JTextField();
		p1.add(t);
		t.setPreferredSize(new Dimension (230,45));
		
		
		Container contenu = fen.getContentPane();
		contenu.add(p1, BorderLayout.WEST);
		contenu.add(p2, BorderLayout.CENTER);
		
		fen.setVisible(true);
	}
}
