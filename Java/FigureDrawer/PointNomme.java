
public class PointNomme extends Point implements Nomme {
	
	public String nom;
	
	
	
	public PointNomme(String n, double x, double y) {
		this.name = n;
		this.setX(x);
		this.setY(y);
	}
	public PointNomme(String n, Point p) {
		this.name = n;
		this.setX(p.getX());
		this.setY(p.getY());
	}
	public PointNomme(Point p, String n) {
		this.name = n;
		this.setX(p.getX());
		this.setY(p.getY());
	}
	public PointNomme() {
		this.name = "";
		this.setX(0);
		this.setY(0);
	}
	
	
	@Override
	public String getNom() {
		return this.nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	public String toString() {
		return("Le point " + getNom() + " a pour coordonnée : (" + getX() + ";" + getY() + ")");
	}

	
}
