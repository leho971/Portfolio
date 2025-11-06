import java.awt.Graphics;

public class Cercle extends Figure {
	
	
	private double rayon;
	private Point milieu;
	
	
	
	public Cercle(double cx, double cy, double rx, double ry) {
		this.milieu.setX(cx);
		this.milieu.setY(cy);
		this.rayon = getLongueur(this.milieu, new Point(rx,ry));
	}
	public Cercle( double x, double y, double rayon) {
		this.milieu = new Point(x,y);
		this.rayon = rayon;
	}
	public Cercle(Point milieu, Point p2) {
		this.milieu = milieu;
		this.rayon = getLongueur(this.milieu, p2);
	}
	public Cercle(Point milieu, double rayon) {
		this.milieu = milieu;
		this.rayon = rayon;
	}
	public Cercle() {
		this.milieu = new Point();
		this.rayon = 0;
	}
	
	
	
	public double getRayon() {
		return rayon;
	}
	public void setRayon(double rayon) {
		this.rayon = rayon;
	}
	public void setMilieu(Point milieu) {
		this.milieu = milieu;
	}
	public Point getMilieu() {
		return milieu;
	}
	
	
	@Override
	public void Translater(double dx, double dy) {
		this.milieu.setX(this.milieu.getX() + dx);
		this.milieu.setY(this.milieu.getY() + dy);
	}
	@Override
	public void Afficher() {
		System.out.println("Les coordonnée du centre sont (" + this.milieu.getX() + ";" + this.milieu.getY() + ") et le rayon est de " + this.rayon + " cm");
		
	}
	@Override
	public String toString() {
		return("Les coordonnée du centre sont (" + this.milieu.getX() + ";" + this.milieu.getY() + ") et le rayon est de " + this.rayon + " cm");
	}
	@Override
	public Point getCentre() {
		return this.milieu;
	}
	public double getLongueur(Point pa, Point pb){
		double longueur = Math.sqrt(Math.pow(pa.getX()-pb.getX(),2) + Math.pow(pa.getY()-pb.getY(),2));
		if(longueur < 0) {
			longueur = longueur*(-1); 
		}
		return(longueur);
	}
	@Override
	public boolean equals(Figure y) {
		Cercle c = (Cercle)y;
		return this.rayon == c.rayon && this.milieu.equals(c.milieu);
	}
	@Override
	public Cercle clone() {
		Cercle c = (Cercle)super.clone();
		c.setMilieu(this.milieu.clone());
		return c;
	}
	@Override
	public void paint(Graphics g) {
		g.drawOval((int)this.milieu.getX()-(int)this.rayon/2, (int)this.milieu.getY()-(int)this.rayon/2, (int)this.rayon, (int)this.rayon);
	}
	
}
