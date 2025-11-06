if ('serviceWorker' in navigator) {
	navigator.serviceWorker
		.register('/swapplication.js', { scope: '/' })
		.then(function (reg) {
			// suivre l'état de l'enregistrement du Service Worker : `installing`, `waiting`, `active`
			if (reg.installing) {
				console.log('Service worker en installation');
			}
			else if (reg.waiting) {
				console.log('Service worker installé');
			}
			else if (reg.active) {
				console.log('Service worker activé');
			}
		}).catch(function (error) {
			// registration failed
			console.log('Service worker non installé, erreur ' + error);
		});
}

let deferredPrompt;
window.addEventListener('beforeinstallprompt', (e) => {
	// Prevent Chrome 67 and earlier from automatically showing the prompt
	e.preventDefault();
	// Stash the event so it can be triggered later.
	deferredPrompt = e;
});

/* Suite du code */

function ajouter(d) {
	let resultat = document.querySelector("#ecran").innerHTML.trim();

	if (resultat == "0") resultat = "";

	if (d == "C") {
		resultat = "0";
	}
	else if (d == "cos") {
		resultat += "cos(";
		//resultat = Math.cos(resultat);
	}
	else if (d == "sin") {
		resultat += "sin(";
	}
	else if (d == "tan") {
		resultat += "tan(";
	}
	else if (d == "exp") {
		resultat += "exp(";
	}
	else if (d == "ln") {
		resultat += "ln(";
	}
	else if (d == "%") {
		try {
			resultat = eval(resultat) / 100;
		}
		catch (e) {
			resultat = "erreur";
		}
	}
	else if (d == "=") {

		resultat = ruler(resultat);

		try {
			resultat = eval(resultat);
		}
		catch (e) {
			resultat = "erreur";
		}
	}
	else {
		resultat += d;
	}
	document.querySelector("#ecran").innerHTML = resultat;
}


function ruler(cal) {

	let res;
	let res_array;

	resultat;

	res = cal;
	res_array = res.split();

	let i = 0;
	let nb = 0;
	while (i < res_array.length) {
		if (res_array[i] == "(") {
			nb++;
		}
		i++;
	}


	let count;
	let j;
	let count2;
	let j2;

	for (i = nb; i > 0; i--) {
		res_array = res.split();

		count = 0;
		j = 0;
		while (count != i) {
			if (res_array[j] == "(") {
				count++;
			}
			j++;
		}
		j--;

		count2 = 0;
		j2 = 0;
		while (count2 != nb - i - 1) {
			if (res_array[j2] == ")") {
				count2++;
			}
			j2++;
		}
		j2--;

		let k;
		let term = "";
		for (k = j + 1; k < j2; k++) {
			term += res_array[k];
		}

		if (res_array[j - 3] == "c" && res_array[j - 2] == "o" && res_array[j - 1] == "s") {
			term = eval(term);
			term = Math.cos(term);
			j -= 3;
		}
		else if (res_array[j - 3] == "s" && res_array[j - 2] == "i" && res_array[j - 1] == "n") {
			term = eval(term);
			term = Math.sin(term);
			j -= 3;
		}
		else if (res_array[j - 3] == "t" && res_array[j - 2] == "a" && res_array[j - 1] == "n") {
			term = eval(term);
			term = Math.tan(term);
			j -= 3;
		}
		else if (res_array[j - 3] == "e" && res_array[j - 2] == "x" && res_array[j - 1] == "p") {
			term = eval(term);
			term = Math.exp(term);
			j -= 3;
		}
		else if (res_array[j - 2] == "l" && res_array[j - 1] == "n") {
			term = eval(term);
			term = Math.log(term);
			j -= 2;
		} else {
			term = eval(term);
		}

		k = 0;
		res = "";
		while (k != j) {
			res += res_array[k];
			k++;
		}
		for (k = 0; k < term.length; k++) {
			res += term.charAt(k);
		}
		k = j2 + 1;
		while (k != res_array.length) {
			res += res_array[k];
			k++;
		}
	}
	return res;
}