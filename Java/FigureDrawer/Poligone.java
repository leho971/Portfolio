import java.awt.Graphics;
import java.util.ArrayList;

public class Poligone extends Figure {

	
	 private ArrayList<Point> p;
	
	
	
	public Poligone(Point p) {
		if(this.deja(p)) {
			this.p.add(p);
		}
	}
	public Poligone(double x, double y) {
		if(this.deja(new Point(x,y))) {
			this.p.add(new Point(x,y));
		}
	}
	public Poligone(){
		if(this.deja(new Point())) {
			this.p.add(new Point());
		}
	}
	public Poligone(Segment s) {
		if(this.deja(new Point(s.getA().getX(),s.getA().getY()))) {
			this.p.add(new Point(s.getA().getX(),s.getA().getY()));
		}
		if(this.deja(new Point(s.getB().getX(),s.getB().getY()))) {
			this.p.add(new Point(s.getB().getX(),s.getB().getY()));
		}
	}
	
	
	
	public ArrayList<Point> getP() {
		return p;
	}
	public void setP(ArrayList<Point> p) {
		this.p = p;
	}

	
	
	
	public boolean deja(Point f) {
		boolean a = true; 
		for(int i = 0 ; i < p.size(); i++) {
			if(f.equals(p.get(i))){
				a = false;
			}
		}
		return a;
	}
	@Override
	public void Translater(double dx, double dy) {
		for(int i = 0 ; i < p.size(); i++) {
			Point a = p.get(i);
			a.Translater(dx, dy);
			p.set(i, a);
		}
	}
	@Override
	public void Afficher() {
		System.out.println(toString());
	}

	@Override
	public String toString() {
		String a =" le poligone possede " + p.size() + " point : ";
		for(int i = 0 ; i < p.size(); i++) {
			a += i + p.get(i).toString() +", ";
		}
		return a;
	}

	@Override
	public Point getCentre() {
		Point a = new Point();
		for(int i = 0 ; i < p.size(); i++) {
			a.setX(a.getX() + p.get(i).getX());
			a.setY(a.getY() + p.get(i).getY());
		}
		a.setX(a.getX()/p.size());
		a.setY(a.getY()/p.size());
		return a;
	}

	@Override
	public boolean equals(Figure y) {
		Poligone a;
		int b = 0;
		boolean c = false;
		try {
			for(int i = 0 ; i < p.size(); i++) {
				a = (Poligone)y;
				if(p.get(i) == a.p.get(i)) {
					b += 1;
				}
				if(b == p.size()) {
					c = true;
				}
			}
		}
		catch(Exception e){
			c = false;
		}
		return c;
	}

	@Override
	public Poligone clone() {
		Poligone o = (Poligone)super.clone();
		for(int i = 0 ; i < p.size(); i++) {
			o.p.set(i, this.p.get(i).clone());
		}
		return o;
	}
	@Override
	public void paint(Graphics g) {
		for(int i = 0 ; i < p.size(); i++) {
			
		}
		
	}

	
}
