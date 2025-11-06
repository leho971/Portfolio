import java.awt.Graphics;

public abstract class Figure implements Cloneable{
	public String name;
	
	public abstract void Translater(double dx, double dy);
	
	public abstract void Afficher();
	
	public abstract String toString();
	
	public abstract Point getCentre();
	
	public abstract boolean equals(Figure x);
	
	public abstract void paint(Graphics g);
	
	public Figure clone() {
		Figure f = null;
		try {
			f = (Figure)super.clone();
		}
		catch(CloneNotSupportedException e){
			
		}
		return f;
	}
}