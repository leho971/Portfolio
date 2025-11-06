import java.awt.Graphics;

public class Point extends Figure {

	
	private double x;
	private double y;

	
	
	public Point(Point p) {
		this.x = p.x;
		this.y = p.y;
	}
	public Point(double x, double y) {
		this.x = x;
		this.y = y;
	}
	public Point(){
		this.x = 0;
		this.y = 0;
	}
	
	
	
	public double getX() {
		return x;
	}
	public void setX(double x) {
		this.x = x;
	}
	public double getY() {
		return y;
	}
	public void setY(double y) {
		this.y = y;
	}
	
	
	
	public String toString() {
		return("Le point a pour coordonnée : (" + x + ";" + y + ")");
	}
		
	public void Afficher() {
		System.out.println(toString());
	}

	public void Translater(double x, double y) {
		this.x += x;
		this.y += y;
	}
	
	public Point getCentre(){
		Point PgC_a = new Point();
		PgC_a.x = getX();
		PgC_a.y = getY();
		return(PgC_a);
	}
	
	public double Distance(Point p){
		double a = Math.sqrt(Math.pow(this.x-p.x, 2) + Math.pow(this.y-p.y, 2));
		return(a);
	}
	@Override
	public boolean equals(Figure comp) {
		Point p = (Point)comp;
		try {
			p = (Point)comp;
			return this.x == p.x && this.y == p.y;
		}
		catch(Exception e){
			return false;
		}
	}
	@Override
	public Point clone() {
		Point P2 = (Point)super.clone();
		return P2;
	}
	@Override
	public void paint(Graphics g) {
		int taille = 10;
		g.fillOval((int)x-taille/2, (int)y-taille/2, taille, taille);
	}
	

}
