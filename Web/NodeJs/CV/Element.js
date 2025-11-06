exports.traitement1 = function () {
    return "OK";
};

page1 = function () {
    return "<!DOCTYPE html> <span> acceuil </span> <img src = http://localhost:1337/Lettre_de_motivation.jpg >";
};

exports.traitement = function (p) {
    if (p == "") {
        return page1();
    }
    if (p == "acceuil") {
        return page1();
    }
};