import pandas as pd

#############################################################################################################
#                    Impotation des ficher necessaire a la creation du jeu de données                       #
############################################################################################################# 
boool = lambda x: x == "I"
types ={'Flux':'category','Trimestre':'int8','Année':'category','Code Departement':'category','Code Region':'category','A129':'category','CPF4':'category','Code Pays':'category', 'Valeur':'int32', 'Masse':'int32'}
Importation = pd.read_csv('Regional-2021-import/Region_2021_Import.txt', sep=";", header=None, dtype=types, names = ['Flux','Trimestre','Année','Code Departement','Code Region','A129','CPF4','Code Pays', 'Valeur', 'Masse'])
NomPays = pd.read_csv('Regional-2021-import/Libelle_PAYS.txt', sep=";", header=None, dtype = 'category')
types = {'NC8':'category'}
NC8 = pd.read_excel('Supp/TABLE_CORRESPONDANCES_2025.xlsx', dtype='category')
CPF4 = pd.read_csv('Regional-2021-import/Libelle_CPF4_rev2.1_2.txt', sep=";", header=None, dtype ='category')
A129 = pd.read_csv('Regional-2021-import/Libelle_A129.txt', sep=";", header=None, dtype ='category')
Douane = pd.read_csv('Pays_avec_douane.csv', dtype={'Code_Pays':'category','Nom_Pays':'category','UE':'bool','Antilles_UE':'bool','Taux_douane_moyen':'category'})



#############################################################################################################
#                                     Entrainement et sauvegarde du modele                                  #
#############################################################################################################
Res = Importation.copy()
Res = pd.merge(Res,NomPays, left_on='Code Pays', right_on=0)
Res['Code Pays'] = Res['Code Pays'].astype('category')
Res = Res.rename(columns={1:"Pays"})
Res = Res.drop(columns=[0,2,3])
Res = pd.merge(Res,Douane, left_on=['Code Pays','Pays'], right_on=['Code_Pays','Nom_Pays'])
Res['Code Pays'] = Res['Code Pays'].astype('category')
Res = Res.rename(columns={'Taux_douane_moyen':"Taux Douane"})
Res = Res.drop(columns=['Code_Pays','Nom_Pays','Antilles_UE'])
Res = pd.merge(Res,A129, left_on='A129', right_on=0)
Res['A129'] = Res['A129'].astype('category')
Res = Res.rename(columns={1:"Libel A129"})
Res = Res.drop(columns=[0,2,3])
Res = pd.merge(Res,CPF4, left_on='CPF4', right_on=0)
Res['CPF4'] = Res['CPF4'].astype('category')
Res = Res.rename(columns={1:'Libel CPF'})
Res = Res.drop(columns=[0,2,3])
Res = pd.merge(Res,NC8, on=['A129','CPF4'])
Res['A129'] = Res['A129'].astype('category')
Res['CPF4'] = Res['CPF4'].astype('category')
Res = Res.rename(columns={'Libelle':'Libel NC8'})
Res = Res.drop(columns=['Début','Fin'])
Res.to_parquet('Importation 2021.parquet',index=False)
print("File saved")