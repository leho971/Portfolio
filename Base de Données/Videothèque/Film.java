package modele;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;

public class Film {

	public Film() {

	}

	public boolean ExistFilm(String titre, int annee, String nom, String prenom) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Select films.id From [films] join realisateurs on realisateurs.id = films.idrealisateur Where titre ='"
				+ titre + "' and annee ='" + annee + "' and realisateurs.nom = '" + nom
				+ "' and realisateurs.prenom = '" + prenom + "'";
		Statement stmt = con.createStatement();
		ResultSet rslt = stmt.executeQuery(req);

		// 5.
		boolean a = rslt.next();

		con.close();
		return a;
	}
	
	public int IdRealisateur(String nom, String prenom) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req0 = "Select id From [realisateurs] Where realisateurs.nom = '" + nom + "' and realisateurs.prenom = '"
				+ prenom + "'";
		Statement stmt0 = con.createStatement();
		ResultSet rslt = stmt0.executeQuery(req0);
		int b;
		if (rslt.next()) {
			b = rslt.getInt("id");
		} else {
			b = 0;
		}

		con.close();
		return b;
	}

	public boolean addFilms(String titre, int annee, int idrealisateur, int score, int nbvotant) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Insert into [films](titre, annee, idrealisateur, score, nbvotant) VALUES ('" + titre + "', '"
				+ annee + "', '" + idrealisateur + "', '" + score + "', '" + nbvotant + "')";
		Statement stmt = con.createStatement();
		int a = stmt.executeUpdate(req);
		System.out.print(a);
		boolean b = false;
		if (a >= 1) {
			b = true;
		}

		con.close();
		return b;
	}

	public int Idfilm(String titre, int annee, int idrealisateur) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Select id From [films] Where titre ='" + titre + "' and annee ='" + annee
				+ "' and idrealisateur = '" + idrealisateur + "'";
		Statement stmt = con.createStatement();
		ResultSet rslt = stmt.executeQuery(req);
		int b = 0;
		if (rslt.next()) {
			b = rslt.getInt("id");
		}
		con.close();
		return b;
	}
	
	public int Idfilm2(String titre) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Select id From [films] Where titre ='" + titre + "'";
		Statement stmt = con.createStatement();
		ResultSet rslt = stmt.executeQuery(req);
		int b = 0;
		if (rslt.next()) {
			b = rslt.getInt("id");
		}
		con.close();
		return b;
	}

	public boolean DltFilms(int idfilm) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Delete From [jouer] where idfilm = '" + idfilm + "'";
		Statement stmt = con.createStatement();
		int a = stmt.executeUpdate(req);

		String req1 = "Delete From [films] where id ='" + idfilm + "'";
		Statement stmt1 = con.createStatement();
		int c = stmt1.executeUpdate(req1);

		boolean d = false;
		if (c >= 1) {
			d = true;
		}

		con.close();
		return d;
	}

	public String InfoFilms(String titre) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req0 = "Select titre, annee, score, nbvotant, realisateurs.prenom as prenomreal, realisateurs.nom as nomreal, rang, acteurs.prenom as prenomac, acteurs.nom as nomac From [films] join realisateurs on realisateurs.id = films.idrealisateur join jouer on jouer.idfilm = films.id join acteurs on acteurs.id = jouer.idacteur where films.titre = '"+titre+"'";
		Statement stmt0 = con.createStatement();
		ResultSet rslt = stmt0.executeQuery(req0);
		
		String a;
		ArrayList<String> list = new ArrayList<String>();
		rslt.next();
		a = rslt.getString("titre") + " sortie en " + rslt.getString("annee") + " par " + rslt.getString("nomreal") + " " + rslt.getString("prenomreal") + " (score " + rslt.getString("score") + ", nombre de votant " + rslt.getString("nbvotant") + ", rang "+ rslt.getString("rang") + "):";
		list.add(a);
		a ="     - " + rslt.getString("nomac") + " " + rslt.getString("prenomac");
		list.add(a);
		while(rslt.next()) {
			a ="     - " + rslt.getString("nomac") + " " + rslt.getString("prenomac");
			list.add(a);
		}
		
		a = "<html>";
		for (int i = 0; i < list.size();i++) {
			a += list.get(i) + "<br>";
		}
		a += "</html>";
		con.close();
		return a;
	}
}
