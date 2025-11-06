package modele;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Scanner;

public class Acteur {

	public Acteur() {

	}

	public boolean ExistActeur(String nom, String prenom) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Select * From [acteurs] Where nom='" + nom + "' and premon'" + prenom + "'";
		Statement stmt = con.createStatement();
		ResultSet rslt = stmt.executeQuery(req);

		// 5.
		boolean a = rslt.next();

		con.close();
		return a;
	}
	
	public int IdActeur(String nom, String prenom) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Select id From [acteurs] Where nom='" + nom + "' and premon'" + prenom + "'";
		Statement stmt = con.createStatement();
		ResultSet rslt = stmt.executeQuery(req);

		int a = 0;
		// 5.
		if(rslt.next()) {
			a = rslt.getInt("id");
		}

		con.close();
		return a;
	}

	public int AddActeurs(String nom, String prenom) throws Exception {

		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Insert into [acteurs](login,mdp)VALUES('" + nom + "','" + prenom + "');";
		Statement stmt = con.createStatement();
		int a = stmt.executeUpdate(req);

		con.close();
		return a;
	}
	
	public int AddFilmActeur(int idacteur, int idfilm, int rang)throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);
		
		String req = "Insert into [jouer](idfilm, idacteur, rang)VALUES('" + idfilm + "','" + idacteur + "','"+ rang +"');";
		Statement stmt = con.createStatement();
		int a = stmt.executeUpdate(req);
		
		con.close();
		return a;
	}

	public int DltActeur(String nom, String prenom) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req0 = "Select id From [acteurs] Where nom='" + nom + "' and premon'" + prenom + "'";
		Statement stmt0 = con.createStatement();
		ResultSet rslt = stmt0.executeQuery(req0);
		int b = rslt.getInt("id");

		String req = "Delete From [jouer] where idacteur ='" + b + "'";
		Statement stmt = con.createStatement();
		int a = stmt.executeUpdate(req);
		int c = 0;
		if (a == 1) {
			System.out.println("Fait");
			String req1 = "Delete From [acteurs] where idacteur ='" + b + "'";
			Statement stmt1 = con.createStatement();
			c = stmt1.executeUpdate(req1);
			if (c == 1) {
				System.out.println("Fait*2");

			} else {
				System.out.println("Merde");
			}

		} else {
			System.out.println("Merde");
		}
		con.close();
		return c;
	}

	public String filmsActeur(String nom, String prenom) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		// 2. connexion a la bd
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		ArrayList<String> list = new ArrayList<String>();
		String ph;

		String req = "Select nom, prenom, count(jouer.idfilm) as nbfilm From acteurs join jouer on jouer.idacteur = acteurs.id join films on films.id = jouer.idfilm Where acteurs.prenom = '"
				+ prenom + "' and acteurs.nom = '" + nom + "' group by acteurs.nom, acteurs.prenom ";
		Statement stmt = con.createStatement();
		ResultSet rslt = stmt.executeQuery(req);

		ph = ("" + rslt.getString("nom") + " " + rslt.getString("prenom") + "  (a joué dans " + rslt.getString("nbfilm")
				+ " films)");
		list.add(ph);
		req = "select films.titre, films.annee from films join jouer on films.id = jouer.idfilm join acteurs on jouer.idacteur = acteurs.id where acteurs.nom = '"
				+ rslt.getString("nom") + "' and acteurs.prenom = '" + rslt.getString("prenom") + "'";
		stmt = con.createStatement();
		ResultSet rslt2 = stmt.executeQuery(req);
		while (rslt2.next()) {
			ph = ("       - " + rslt2.getString("titre") + ", " + rslt2.getString("annee"));
			list.add(ph);
		}

		ph = "<html>";
		for (int i = 0; i < list.size(); i++) {
			ph += list.get(i) + "<br>";
		}
		ph += "</html>";

		con.close();
		return ph;
	}
}
