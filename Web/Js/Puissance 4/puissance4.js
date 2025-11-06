/*
JS | Activité 2
*/

document.querySelector('#jeu').style.visibility='hidden';

var j1 = new Object();
var j2 = new Object();

var current_player = 1;

j1.ins = false;
j2.ins = false;


//Rempli le plateau de pions
function init_plateau() {
	var plateau = document.querySelector('#plateau');
	/* Remplir le plateau */
	for (var i = 0; i < 49; i++) {
		/* Remplir le plateau des balises div ayant la class pion -> <div class="pion"></div> */
		document.querySelector('#plateau').innerHTML += '<div class="pion" onclick="touch('+i+');"></div>';
	}
	document.querySelector('#jeu').style.visibility = 'visible';
}


//Fontion d'inscription
function ins(player) {

	// Completer pour vérifier l'inscription
	if (player==1) {
		j1.ins = true;
		var x = document.getElementsByName('j1')
		x = x[0];
		/* Mettre le nom du joueur dans la balise #j1-name */
		document.querySelector('#j1-name').innerHTML = x.value;
		x.disabled = true;
	}
	else{
		j2.ins = true;
		var x = document.getElementsByName('j2');
		x = x[0];
		/* Mettre le nom du joueur dans la balise #j2-name */
		document.querySelector('#j2-name').innerHTML = x.value;
		x.disabled = true;
	}
	
	if (j1.ins && j2.ins) {

		// Retirer le panneau d'inscription
		var ins = document.getElementById('ins').style.visibility='hidden';
		/* retirer la balise div #ins du html */

		//Initialise le plateau
		init_plateau();

		//lien avec les logo
		j1.logo = document.querySelector('.fas.fa-user.j1');
		j2.logo = document.querySelector('.fas.fa-user.j2');

		//Instruction de jeu
		/* Mettre le nom du joueur dans la balise player-name */
		if(current_player = 1){
			let tour_j1 = document.querySelector("#j1-name").innerHTML;
			document.querySelector('#player-name').innerHTML = tour_j1;
		}
		else{
			let tour_j2 = document.querySelector("#j2-name").innerHTML;
			document.querySelector('#player-name').innerHTML = tour_j2;
		}
		

		//ne joue pas pour le moment
		j2.logo.classList.toggle("fas");
		j2.logo.classList.toggle("far");

	}
}

function touch(id){
	var pions = document.querySelectorAll('.pion');
	var col = id % 7;
	console.log(col);
	/* Completer... */
	let fin = 49-(7-col);
	
	while(pions[fin].classList[1]=='playing' && fin>= 0){
		fin-=7;
	}

	if(current_player == 1){
		pions[fin].setAttribute("class","pion playing j1");
		current_player = 2;
		
		
		if(col < 4 && col >= 0 && id < 25 && id >= 0){
			if(pions[fin + 8].classList[2]==pions[fin].classList[2]){
				if(pions[fin + 16].classList[2]==pions[fin].classList[2]){
					if(pions[fin + 24].classList[2]==pions[fin].classList[2]){
						//bas - droite
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(id < 28 && id >= 0){
			if(pions[fin + 7].classList[2]==pions[fin].classList[2]){
				if(pions[fin + 14].classList[2]==pions[fin].classList[2]){
					if(pions[fin + 21].classList[2]==pions[fin].classList[2]){
						//bas
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 6 && col >= 3 && id < 28 && id >= 0){
			if(pions[fin + 7].classList[2]==pions[fin].classList[2]){
				if(pions[fin + 14].classList[2]==pions[fin].classList[2]){
					if(pions[fin + 21].classList[2]==pions[fin].classList[2]){
						//bas - gauche
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 6 && col >= 3 && id < 49 && id >= 0){
			if(pions[fin - 1].classList[2]==pions[fin].classList[2]){
				if(pions[fin - 2].classList[2]==pions[fin].classList[2]){
					if(pions[fin - 3].classList[2]==pions[fin].classList[2]){
						//gauche
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 6 && col >= 3 && id < 49 && id >= 25){
			if(pions[fin - 8].classList[2]==pions[fin].classList[2]){
				if(pions[fin - 16].classList[2]==pions[fin].classList[2]){
					if(pions[fin - 24].classList[2]==pions[fin].classList[2]){
						//haut - gauche
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 6 && col >= 0 && id < 49 && id >= 29){
			if(pions[fin - 7].classList[2]==pions[fin].classList[2]){
				if(pions[fin - 14].classList[2]==pions[fin].classList[2]){
					if(pions[fin - 21].classList[2]==pions[fin].classList[2]){
						//haut
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 4 && col >= 0 && id < 46 && id >= 29){
			if(pions[fin - 6].classList[2]==pions[fin].classList[2]){
				if(pions[fin - 12].classList[2]==pions[fin].classList[2]){
					if(pions[fin - 18].classList[2]==pions[fin].classList[2]){
						//haut - droite
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 4 && col >= 0 && id < 46 && id >= 0){
			if(pions[fin + 1].classList[2]==pions[fin].classList[2]){
				if(pions[fin + 2].classList[2]==pions[fin].classList[2]){
					if(pions[fin + 3].classList[2]==pions[fin].classList[2]){
						//droite
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		
		
		let tour_j2 = document.querySelector("#j2-name").innerHTML;
		document.querySelector('#player-name').innerHTML = tour_j2;
	}
	else{
		pions[fin].setAttribute("class","pion playing j2");
		current_player = 1;
		
		if(col < 4 && col >= 0 && id < 25 && id >= 0){
			if(pions[fin + 8].classList[2]==pions[fin].classList[2]){
				if(pions[fin + 16].classList[2]==pions[fin].classList[2]){
					if(pions[fin + 24].classList[2]==pions[fin].classList[2]){
						//bas - droite
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(id < 28 && id >= 0){
			if(pions[fin + 7].classList[2]==pions[fin].classList[2]){
				if(pions[fin + 14].classList[2]==pions[fin].classList[2]){
					if(pions[fin + 21].classList[2]==pions[fin].classList[2]){
						//bas
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 6 && col >= 3 && id < 28 && id >= 0){
			if(pions[fin + 7].classList[2]==pions[fin].classList[2]){
				if(pions[fin + 14].classList[2]==pions[fin].classList[2]){
					if(pions[fin + 21].classList[2]==pions[fin].classList[2]){
						//bas - gauche
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 6 && col >= 3 && id < 49 && id >= 0){
			if(pions[fin - 1].classList[2]==pions[fin].classList[2]){
				if(pions[fin - 2].classList[2]==pions[fin].classList[2]){
					if(pions[fin - 3].classList[2]==pions[fin].classList[2]){
						//gauche
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 6 && col >= 3 && id < 49 && id >= 25){
			if(pions[fin - 8].classList[2]==pions[fin].classList[2]){
				if(pions[fin - 16].classList[2]==pions[fin].classList[2]){
					if(pions[fin - 24].classList[2]==pions[fin].classList[2]){
						//haut - gauche
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 6 && col >= 0 && id < 49 && id >= 29){
			if(pions[fin - 7].classList[2]==pions[fin].classList[2]){
				if(pions[fin - 14].classList[2]==pions[fin].classList[2]){
					if(pions[fin - 21].classList[2]==pions[fin].classList[2]){
						//haut
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 4 && col >= 0 && id < 46 && id >= 29){
			if(pions[fin - 6].classList[2]==pions[fin].classList[2]){
				if(pions[fin - 12].classList[2]==pions[fin].classList[2]){
					if(pions[fin - 18].classList[2]==pions[fin].classList[2]){
						//haut - droite
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		if(col < 4 && col >= 0 && id < 46 && id >= 0){
			if(pions[fin + 1].classList[2]==pions[fin].classList[2]){
				if(pions[fin + 2].classList[2]==pions[fin].classList[2]){
					if(pions[fin + 3].classList[2]==pions[fin].classList[2]){
						//droite
						for (var i = 0; i < 49; i++) {
							document.querySelectorAll('.pion')[i].removeAttribute('onclick');
						}
					
						document.getElementById('ins').style.visibility='visible';
						document.querySelector('#ins-panel').innerHTML ='<h1>VA TE FAIRE FOUTRE</h1>';
					}
				}
			}
		}
		
		
		let tour_j1 = document.querySelector("#j1-name").innerHTML;
		document.querySelector('#player-name').innerHTML = tour_j1;
	}
	
	
	
}