package modele;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class User {
	String login;

	public User(String L) {
		login = L;
	}

	public boolean ExistUser() throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Select * From [user] Where login='" + login + "'";
		Statement stmt = con.createStatement();
		ResultSet rslt = stmt.executeQuery(req);

		// 5.
		boolean a = rslt.next();
		if (a) {
			System.out.println("login déja existant !");
		} else {
			System.out.println("Ce login n'existe pas !");
		}

		con.close();
		return a;
	}

	public int AddUser(String mdp) throws Exception {

		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);

		String req = "Insert into [user](login,mdp)VALUES('" + login + "','" + mdp + "');";
		Statement stmt = con.createStatement();
		int a = stmt.executeUpdate(req);
		if (a == 1) {
			System.out.println("Utilisateur créé");
		} else {
			System.out.println("Erreur d'ajout");
		}
		con.close();
		return a;
	}
	
	public boolean ConnectUser(String mdp) throws Exception{
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);
		
		String req = "Select * From [user] Where login='" + login + "' and mdp = '"+mdp+ "'";
		Statement stmt = con.createStatement();
		ResultSet rslt = stmt.executeQuery(req);
		boolean a = rslt.next();
		if(a) {
			System.out.println("Connected ");
		}
		
		return a;
	}
	
	public int NewMdp(String mdp) throws Exception {
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);
		
		String req = "Update [user] Set mdp = '" + mdp + "' Where login='" + login + "'";
		Statement stmt = con.createStatement();
		int a = stmt.executeUpdate(req);
		if (a == 1) {
			System.out.println("Mot de passe changé ");
		}
		else {
			System.out.println("Erreur changement de mot de passe");
			}
		
		return a;
	}
	
	public int DltUser(String mdp) throws Exception{
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		String urlBD = "jdbc:sqlserver://localhost;databaseName=videotheque;integratedSecurity=true;encrypt=false;";
		Connection con = DriverManager.getConnection(urlBD);
		
		System.out.println("suppresion d'un utilisateur ");
		String req = "Delete From [user] where login ='" + login + "' and mdp ='" + mdp + "';";
		Statement stmt = con.createStatement();
		int a = stmt.executeUpdate(req);
		if (a == 1) {
			System.out.println("Utilisateur supprimer");
		} else {
			System.out.println("Erreur de suppression");
		}
		
		return a;
	}
}
