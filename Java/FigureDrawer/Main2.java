import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class Main2 {
	public static void main(String args[]) {
	
		
		//Figure a = new Point(21,12);
		//Figure b = new Point();
		Figure c = new Cercle(50,50,50);
		
		
		
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
		
		
		Editeur p3 = new Editeur();
		p3.addMouseListener(p3);
		//btPoint.addMouseListener(p3);
		//btSegment.addMouseListener(p3);
		//btCercle.addMouseListener(p3);
		//p3.liste.add(new Point(250,250));
		//p3.liste.add(new Segment((Point)a,(Point)b));
		p3.liste.add(c);
		
		
		Container contenu = fen.getContentPane();
		contenu.add(p1, BorderLayout.WEST);
		contenu.add(p3, BorderLayout.CENTER);
		
		fen.setVisible(true);
	}
}

