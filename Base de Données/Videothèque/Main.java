package main;

import javax.swing.JFrame;

import vue.Vue;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*User u = new User("Alexy");
		u.ExistUser();
		u.AddUser(null);
		u.DltUser(null);
		
		Acteur a = new Acteur();
		a.ExistActeur("Allen","Woody");*/
		
		JFrame fen = new JFrame();
		fen.setSize(250, 400);
		Vue Ecran = new Vue();
		fen.getContentPane().add(Ecran);
		fen.setVisible(true);
	}

}
