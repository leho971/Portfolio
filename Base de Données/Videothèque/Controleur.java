package controleur;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JLabel;

import modele.Acteur;
import modele.Film;
import vue.Vue;

public class Controleur implements ActionListener {
	Vue Ecran;
	String chaine;
	String chaine1;
	String chaine2;
	int nb1;
	int nb2;
	int var;

	public Controleur(Vue a, int b) {
		Ecran = a;
		var = b;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		switch (var) {
		case -1:
			Ecran.getRes().setText("Fuck");
			break;
		case 0:
			Ecran.removeAll();
			Ecran.getChText().setText("Accueil");
			Ecran.add(Ecran.getChText());
			Ecran.add(Ecran.getBtFilms());
			Ecran.getBtFilms().addActionListener(new Controleur(Ecran, 1));
			Ecran.add(Ecran.getBtActeurs());
			Ecran.getBtActeurs().addActionListener(new Controleur(Ecran, 2));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 1:
			Ecran.removeAll();
			Ecran.getChText().setText("Films");
			Ecran.add(Ecran.getChText());
			Ecran.add(Ecran.getBtFilmsAdd());
			Ecran.getBtFilmsAdd().addActionListener(new Controleur(Ecran, 3));
			Ecran.add(Ecran.getBtFilmsSupp());
			Ecran.getBtFilmsSupp().addActionListener(new Controleur(Ecran, 5));
			Ecran.add(Ecran.getBtFilmsInfo());
			Ecran.getBtFilmsInfo().addActionListener(new Controleur(Ecran, 7));
			Ecran.add(Ecran.getBtback());
			Ecran.getBtback().addActionListener(new Controleur(Ecran, 0));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 2:
			Ecran.removeAll();
			Ecran.getChText().setText("Acteurs");
			Ecran.add(Ecran.getChText());
			Ecran.add(Ecran.getBtActeursAdd());
			Ecran.getBtActeursAdd().addActionListener(new Controleur(Ecran, 4));
			Ecran.add(Ecran.getBtActeursSupp());
			Ecran.getBtActeursSupp().addActionListener(new Controleur(Ecran, 6));
			Ecran.add(Ecran.getBtFilmsInfo());
			Ecran.getBtFilmsInfo().addActionListener(new Controleur(Ecran, 8));
			Ecran.add(Ecran.getBtback());
			Ecran.getBtback().addActionListener(new Controleur(Ecran, 0));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 3:
			Ecran.removeAll();
			Ecran.getChText().setText("     Ajouter un film    ");
			Ecran.add(Ecran.getChText());
			Ecran.getChText1().setText("titre");
			Ecran.add(Ecran.getChText1());
			Ecran.add(Ecran.getText1());
			Ecran.getChText2().setText("annee");
			Ecran.add(Ecran.getChText2());
			Ecran.add(Ecran.getText2());
			Ecran.getChText3().setText("nom realisateur");
			Ecran.add(Ecran.getChText3());
			Ecran.add(Ecran.getText3());
			Ecran.getChText4().setText("prenom realisateur");
			Ecran.add(Ecran.getChText4());
			Ecran.add(Ecran.getText4());
			Ecran.getChText5().setText("score");
			Ecran.add(Ecran.getChText5());
			Ecran.add(Ecran.getText5());
			Ecran.getChText6().setText("nombre de votant");
			Ecran.add(Ecran.getChText6());
			Ecran.add(Ecran.getText6());
			Ecran.add(Ecran.getRes());
			Ecran.add(Ecran.getBtValid());
			Ecran.getBtValid().addActionListener(new Controleur(Ecran, 9));
			Ecran.add(Ecran.getBtback());
			Ecran.getBtback().addActionListener(new Controleur(Ecran, 0));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 4:
			Ecran.removeAll();
			Ecran.getChText().setText("     Ajouter un Acteur   ");
			Ecran.add(Ecran.getChText());
			Ecran.getChText1().setText("nom");
			Ecran.add(Ecran.getChText1());
			Ecran.add(Ecran.getText1());
			Ecran.getChText2().setText("prenom");
			Ecran.add(Ecran.getChText2());
			Ecran.add(Ecran.getText2());
			Ecran.getChText3().setText("film jouer");
			Ecran.add(Ecran.getChText3());
			Ecran.getText3().setSize(10, 10);
			Ecran.add(Ecran.getText3());
			Ecran.add(Ecran.getBtValid());
			Ecran.getBtValid().addActionListener(new Controleur(Ecran, 10));
			Ecran.add(Ecran.getBtback());
			Ecran.getBtback().addActionListener(new Controleur(Ecran, 0));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 5:
			Ecran.removeAll();
			Ecran.getChText().setText("     Supprimer un film    ");
			Ecran.add(Ecran.getChText());
			Ecran.getChText1().setText("titre");
			Ecran.add(Ecran.getChText1());
			Ecran.add(Ecran.getText1());
			Ecran.getChText2().setText("annee");
			Ecran.add(Ecran.getChText2());
			Ecran.add(Ecran.getText2());
			Ecran.getChText3().setText(" nom realisateur");
			Ecran.add(Ecran.getChText3());
			Ecran.add(Ecran.getText3());
			Ecran.getChText4().setText("prenom realisateur");
			Ecran.add(Ecran.getChText4());
			Ecran.add(Ecran.getText4());
			Ecran.add(Ecran.getRes());
			Ecran.add(Ecran.getBtValid());
			Ecran.getBtValid().addActionListener(new Controleur(Ecran, 11));
			Ecran.add(Ecran.getBtback());
			Ecran.getBtback().addActionListener(new Controleur(Ecran, 0));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 6:
			Ecran.removeAll();
			Ecran.getChText().setText("     Supprimer un acteur    ");
			Ecran.add(Ecran.getChText());
			Ecran.getChText1().setText("nom");
			Ecran.add(Ecran.getChText1());
			Ecran.add(Ecran.getText1());
			Ecran.getChText2().setText("prenom");
			Ecran.add(Ecran.getChText2());
			Ecran.add(Ecran.getText2());
			Ecran.add(Ecran.getRes());
			Ecran.add(Ecran.getBtValid());
			Ecran.getBtValid().addActionListener(new Controleur(Ecran, 12));
			Ecran.add(Ecran.getBtback());
			Ecran.getBtback().addActionListener(new Controleur(Ecran, 0));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 7:
			Ecran.removeAll();
			Ecran.getChText().setText("     Chercher un film    ");
			Ecran.add(Ecran.getChText());
			Ecran.getChText1().setText("titre");
			Ecran.add(Ecran.getChText1());
			Ecran.add(Ecran.getText1());
			Ecran.add(Ecran.getRes());
			Ecran.add(Ecran.getBtValid());
			Ecran.getBtValid().addActionListener(new Controleur(Ecran, 13));
			Ecran.add(Ecran.getBtback());
			Ecran.getBtback().addActionListener(new Controleur(Ecran, 0));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 8:
			Ecran.removeAll();
			Ecran.getChText().setText("     Chercher un Acteur    ");
			Ecran.add(Ecran.getChText());
			Ecran.getChText1().setText("nom");
			Ecran.add(Ecran.getChText1());
			Ecran.getChText2().setText("prenom");
			Ecran.add(Ecran.getChText2());
			Ecran.add(Ecran.getBtValid());
			Ecran.add(Ecran.getText());
			Ecran.getBtValid().addActionListener(new Controleur(Ecran, 14));
			Ecran.add(Ecran.getBtback());
			Ecran.getBtback().addActionListener(new Controleur(Ecran, 0));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 9:
			if (Ecran.getText1().getText().isBlank() || Ecran.getText2().getText().isBlank()
					|| Ecran.getText3().getText().isBlank() || Ecran.getText4().getText().isBlank()
					|| Ecran.getText5().getText().isBlank()) {
				Ecran.getRes().setText("Remplir tout les champs !");
			} else {
				boolean b;
				String titre = Ecran.getText1().getText();
				int annee = Integer.valueOf(Ecran.getText2().getText());
				String nom_realisateur = Ecran.getText3().getText();
				String prenom_realisateur = Ecran.getText4().getText();
				int score = Integer.valueOf(Ecran.getText5().getText());
				int nbvotant = Integer.valueOf(Ecran.getText6().getText());
				Film A = new Film();
				try {
					b = A.ExistFilm(titre, annee, nom_realisateur, prenom_realisateur);
				} catch (Exception e1) {
					b = true;
				}
				if (b) {
					Ecran.getRes().setText("Film existant !");
				} else {
					int id;
					try {
						id = A.IdRealisateur(nom_realisateur, prenom_realisateur);
					} catch (Exception e1) {
						id = 0;
					}
					boolean val;
					try {
						val = A.addFilms(titre, annee, id, score, nbvotant);
					} catch (Exception e1) {
						val = false;
					}
					if (val == true) {
						Ecran.getRes().setText("Films ajouter !");
					} else {
						Ecran.getRes().setText("Erreur ! : id = " + id);
					}
				}
			}
			break;
		case 10:
			if (Ecran.getText1().getText().isBlank() || Ecran.getText2().getText().isBlank()
					|| Ecran.getText3().getText().isBlank()) {
				Ecran.getRes().setText("Remplir tout les champs !");
			} else {
				String nom = Ecran.getText1().getText();
				String prenom = Ecran.getText2().getText();
				String titres = Ecran.getText3().getText();
				Acteur A = new Acteur();
				boolean a;
				try {
					a = A.ExistActeur(nom, prenom);
				} catch (Exception e1) {
					a = true;
				}
				if (!a) {
					int b;
					try {
						b = A.AddActeurs(nom, prenom);
					} catch (Exception e1) {
						b = -1;
					}
					if (b > 0) {
						int id;
						try {
							id = A.IdActeur(nom, prenom);
						} catch (Exception e1) {
							id = -1;
						}
						nb1 = id;
						String[] list = titres.split(",");
						for (int i = 0; i < list.length; i++) {
							Film c = new Film();
							int d;
							try {
								d = c.Idfilm2(list[i]);
							} catch (Exception e1) {
								d = -1;
							}
							nb2 = d;
							if (d > 0) {
								Ecran.removeAll();
								Ecran.getChText().setText(list[i]);
								Ecran.add(Ecran.getChText());
								Ecran.getChText1().setText("rang ?");
								Ecran.add(Ecran.getChText1());
								Ecran.add(Ecran.getText1());
								Ecran.add(Ecran.getRes());
								Ecran.add(Ecran.getBtValid());
								Ecran.getBtValid().addActionListener(new Controleur(Ecran, 15));
								Ecran.revalidate();
								Ecran.repaint();
							}
						}
					} else {
						Ecran.getRes().setText("Erreur b = " + b);
					}
				} else {
					Ecran.getRes().setText("Acteur deja existant !");
				}
			}
			Ecran.removeAll();
			Ecran.getChText().setText("Accueil");
			Ecran.add(Ecran.getChText());
			Ecran.add(Ecran.getBtFilms());
			Ecran.getBtFilms().addActionListener(new Controleur(Ecran, 1));
			Ecran.add(Ecran.getBtActeurs());
			Ecran.getBtActeurs().addActionListener(new Controleur(Ecran, 2));
			Ecran.revalidate();
			Ecran.repaint();
			break;
		case 11:
			if (Ecran.getText1().getText().isBlank() || Ecran.getText2().getText().isBlank()
					|| Ecran.getText3().getText().isBlank() || Ecran.getText4().getText().isBlank()) {
				Ecran.getRes().setText("Remplir tout les champs !");
			} else {
				boolean b;
				String titre = Ecran.getText1().getText();
				int annee = Integer.valueOf(Ecran.getText2().getText());
				String nom_realisateur = Ecran.getText3().getText();
				String prenom_realisateur = Ecran.getText4().getText();
				Film A = new Film();
				try {
					b = A.ExistFilm(titre, annee, nom_realisateur, prenom_realisateur);
				} catch (Exception e1) {
					b = true;
				}
				if (b) {
					int idreal;
					try {
						idreal = A.IdRealisateur(nom_realisateur, prenom_realisateur);
					} catch (Exception e1) {
						idreal = -1;
					}
					int idfilm;
					try {
						idfilm = A.Idfilm(titre, annee, idreal);
					} catch (Exception e1) {
						idfilm = -1;
					}
					boolean val;
					try {
						val = A.DltFilms(idfilm);
					} catch (Exception e1) {
						val = false;
					}
					if (val == true) {
						Ecran.getRes().setText("Films supprimer !");
					} else {
						Ecran.getRes().setText("Erreur ! : id = " + idfilm);
					}
				} else {
					Ecran.getRes().setText("Film inexistant !");
				}
			}
			break;
		case 12:
			if (Ecran.getText1().getText().isBlank() || Ecran.getText2().getText().isBlank()) {
				Ecran.getRes().setText("Remplir tout les champs !");
			} else {
				String nom = Ecran.getText1().getText();
				String prenom = Ecran.getText2().getText();
				Acteur A = new Acteur();
				boolean b;
				try {
					b = A.ExistActeur(nom, prenom);
				} catch (Exception e1) {
					b = false;
				}
				if (b) {
					int c;
					try {
						c = A.AddActeurs(nom, prenom);
					} catch (Exception e1) {
						c = -1;
					}
					if (c > 0) {
						Ecran.getRes().setText("Erreur c = " + c);
					}
				} else {
					Ecran.getRes().setText("Acteur inexistant !");
				}

			}
			break;
		case 13:
			if (Ecran.getText1().getText().isBlank()) {
				Ecran.getRes().setText("Remplir tout les champs !");
			} else {
				String titre = Ecran.getText1().getText();
				String res;
				Film A = new Film();
				try {
					res = A.InfoFilms(titre);
				} catch (Exception e1) {
					res = null;
				}
				Ecran.getRes().setText(res);
			}
			break;
		case 14:
			if (Ecran.getText1().getText().isBlank() || Ecran.getText1().getText().isBlank()) {
				Ecran.getRes().setText("Remplir tout les champs !");
			} else {
				String nom = Ecran.getText1().getText();
				String prenom = Ecran.getText2().getText();
				String res;
				Acteur A = new Acteur();
				try {
					res = A.filmsActeur(nom, prenom);
				} catch (Exception e1) {
					res = null;
				}
				Ecran.getRes().setText(res);
			}
			break;
		case 15:
			if (Ecran.getText1().getText().isBlank()) {
				Ecran.getRes().setText("Remplir tout les champs !");
			} else {
				int rang = Integer.valueOf(Ecran.getText1().getText());
				Acteur A = new Acteur();
				try {
					A.AddFilmActeur(nb1, nb2, rang);
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
			break;
		}
	}

}
