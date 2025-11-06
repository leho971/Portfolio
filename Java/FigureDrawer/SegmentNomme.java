
public class SegmentNomme extends Segment implements Nomme {
	
	public String nom;

	@Override
	public String getNom() {
		return this.nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}


}
