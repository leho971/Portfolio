import java.awt.Graphics;

public class Segment extends Figure {
	
	
	private Point A;
	private Point B;
	
	
	
	public Segment(double xa, double ya, double xb, double yb){
		setA(new Point(xa, ya));
		setB(new Point(xb, yb));
	}
	public Segment(Point a, Point b) {
		setA(a);
		setB(b);
	}
	public Segment(){
		setA(new Point());
		setB(new Point());
	}
	
	
	
	public Point getA() {
		return A;
	}
	public void setA(Point a) {
		A = a;
	}
	public Point getB() {
		return B;
	}
	public void setB(Point b) {
		B = b;
	}
	
	
	
	@Override
	public void Translater(double dx, double dy) {
		this.A.Translater(dx, dy);
		this.B.Translater(dx, dy);
	}
	
	@Override
	public void Afficher() {
		System.out.println("coordonnée du 1er point sont (" + A.getX() + "," + A.getY() + ")") ;
		System.out.println("coordonnée du 2eme point sont (" + B.getX() + "," + B.getY() + ")") ;
	}
	
	@Override
	public String toString() {	
		return("Le ");
	}
	
	@Override
	public Point getCentre() {	
		return(getMilieu());
	}
	
	public double getLongueur(){
		double longueur = Math.sqrt(Math.pow(this.A.getX()-this.B.getX(),2) + Math.pow(this.A.getY()-this.B.getY(),2));
		if(longueur < 0) {
			longueur = longueur*(-1); 
		}
		return(longueur);
	}
	
	public Point getMilieu(){
		Point milieu = new Point();
		milieu.setX((this.A.getX()+this.B.getX())/2);
		milieu.setY((this.A.getY()+this.B.getY())/2);
		return(milieu);
	}
	@Override
	public boolean equals(Figure comp) {
		Segment s;
		try {
			s = (Segment)comp;
			return this.A.equals(s.A) && this.B.equals(s.B);
		}
		catch(Exception e){
			return false;
		}
	}
	@Override
	public Segment clone() {
		Segment s = (Segment)super.clone();
		s.setA(this.A.clone());
		s.setB(this.B.clone());
		return s;
	}
	@Override
	public void paint(Graphics g) {
		A.paint(g);
		B.paint(g);
		g.drawLine((int)A.getX(), (int)A.getY(), (int)B.getX(), (int)B.getY());
	}
	

}
