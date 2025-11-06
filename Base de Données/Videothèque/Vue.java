package vue;

import javax.swing.*;

import controleur.Controleur;

public class Vue extends JPanel {
	private JTextArea Text;
	private JTextArea Text1;
	private JTextArea Text2;
	private JTextArea Text3;
	private JTextArea Text4;
	private JTextArea Text5;
	private JTextArea Text6;
	private JLabel chText;
	private JLabel chText1;
	private JLabel chText2;
	private JLabel chText3;
	private JLabel chText4;
	private JLabel chText5;
	private JLabel chText6;
	private JButton btValid;
	private JButton btFilms;
	private JButton btFilmsAdd;
	private JButton btFilmsSupp;
	private JButton btFilmsInfo;
	private JButton btActeurs;
	private JButton btActeursAdd;
	private JButton btActeursSupp;
	private JButton btActeursInfo;
	private JLabel res;
	private JButton btback;
	
	public Vue(){
		super();
		btback = new JButton("Acceuil");
		chText = new JLabel("Acceuil");
		chText1 = new JLabel("");
		chText2 = new JLabel("");
		chText3 = new JLabel("");
		chText4 = new JLabel("");
		chText5 = new JLabel("");
		chText6 = new JLabel("");
		Text = new JTextArea(2, 8);
		Text1 = new JTextArea(2, 8);
		Text2 = new JTextArea(2, 8);
		Text3 = new JTextArea(2, 8);
		Text4 = new JTextArea(2, 8);
		Text5 = new JTextArea(2, 8);
		Text6 = new JTextArea(2, 8);
		btValid = new JButton("Valider");
		btFilms = new JButton("Films");
		btFilmsAdd = new JButton("Ajouter");
		btFilmsSupp = new JButton("Supprimer");
		btFilmsInfo = new JButton("Chercher");
		btActeurs = new JButton("Acteurs");
		btActeursAdd = new JButton("Ajouter");
		btActeursSupp = new JButton("Supprimer");
		btActeursInfo = new JButton("Chercher");
		res = new JLabel();
		
		add(chText);
		add(btFilms);
		add(btActeurs);
		add(res);
		//add(btback);
		
		btFilms.addActionListener(new Controleur(this, 1));
		btActeurs.addActionListener(new Controleur(this, 2));
	}

	public JTextArea getText6() {
		return Text6;
	}

	public void setText6(JTextArea text6) {
		Text6 = text6;
	}

	public JLabel getChText6() {
		return chText6;
	}

	public void setChText6(JLabel chText6) {
		this.chText6 = chText6;
	}

	public JButton getBtValid() {
		return btValid;
	}

	public void setBtValid(JButton btValid) {
		this.btValid = btValid;
	}

	public JTextArea getText1() {
		return Text1;
	}

	public void setText1(JTextArea text1) {
		Text1 = text1;
	}

	public JTextArea getText4() {
		return Text4;
	}

	public void setText4(JTextArea text4) {
		Text4 = text4;
	}

	public JTextArea getText5() {
		return Text5;
	}

	public void setText5(JTextArea text5) {
		Text5 = text5;
	}

	public JLabel getChText1() {
		return chText1;
	}

	public void setChText1(JLabel chText1) {
		this.chText1 = chText1;
	}

	public JLabel getChText4() {
		return chText4;
	}

	public void setChText4(JLabel chText4) {
		this.chText4 = chText4;
	}

	public JLabel getChText5() {
		return chText5;
	}

	public void setChText5(JLabel chText5) {
		this.chText5 = chText5;
	}

	public JLabel getChText3() {
		return chText3;
	}

	public void setChText3(JLabel chText3) {
		this.chText3 = chText3;
	}

	public JTextArea getText() {
		return Text;
	}

	public void setText(JTextArea text) {
		Text = text;
	}

	public JTextArea getText2() {
		return Text2;
	}

	public void setText2(JTextArea text2) {
		Text2 = text2;
	}

	public JTextArea getText3() {
		return Text3;
	}

	public void setText3(JTextArea text3) {
		Text3 = text3;
	}

	public JLabel getChText() {
		return chText;
	}

	public void setChText(JLabel chText) {
		this.chText = chText;
	}

	public JLabel getChText2() {
		return chText2;
	}

	public void setChText2(JLabel chText2) {
		this.chText2 = chText2;
	}

	public JButton getBtFilms() {
		return btFilms;
	}

	public void setBtFilms(JButton btFilms) {
		this.btFilms = btFilms;
	}

	public JButton getBtback() {
		return btback;
	}

	public void setBtback(JButton btback) {
		this.btback = btback;
	}

	public JButton getBtFilmsAdd() {
		return btFilmsAdd;
	}

	public void setBtFilmsAdd(JButton btFilmsAdd) {
		this.btFilmsAdd = btFilmsAdd;
	}

	public JButton getBtFilmsSupp() {
		return btFilmsSupp;
	}

	public void setBtFilmsSupp(JButton btFilmsSupp) {
		this.btFilmsSupp = btFilmsSupp;
	}

	public JButton getBtFilmsInfo() {
		return btFilmsInfo;
	}

	public void setBtFilmsInfo(JButton btFilmsInfo) {
		this.btFilmsInfo = btFilmsInfo;
	}

	public JButton getBtActeurs() {
		return btActeurs;
	}

	public void setBtActeurs(JButton btActeurs) {
		this.btActeurs = btActeurs;
	}

	public JButton getBtActeursAdd() {
		return btActeursAdd;
	}

	public void setBtActeursAdd(JButton btActeursAdd) {
		this.btActeursAdd = btActeursAdd;
	}

	public JButton getBtActeursSupp() {
		return btActeursSupp;
	}

	public void setBtActeursSupp(JButton btActeursSupp) {
		this.btActeursSupp = btActeursSupp;
	}

	public JButton getBtActeursInfo() {
		return btActeursInfo;
	}

	public void setBtActeursInfo(JButton btActeursInfo) {
		this.btActeursInfo = btActeursInfo;
	}

	public JLabel getRes() {
		return res;
	}

	public void setRes(JLabel res) {
		this.res = res;
	}

	
}
