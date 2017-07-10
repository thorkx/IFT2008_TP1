/**
 * \file SystemeExpert.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe SystemeExpert
 * \author Olivier Léveillé-Gauvin
 * \version 1.0
 * \date juin 2017
 *
 */

#include "SystemeExpert.h"

namespace tp1 {

/**
 * \brief Constructeur par défaut
 */
tp1::SystemeExpert::SystemeExpert() :
		baseRegles(), baseFaits() {
}

/**
 * \brief Constructeur de copie
 * \param[in] se, le systeme expert à utiliser
 */
tp1::SystemeExpert::SystemeExpert(const SystemeExpert& se) {
	*this = se;
}

/**
 * \brief Surcharge de l'opérateur =
 *
 * \param[in] p_source La liste à copier
 */
tp1::SystemeExpert& SystemeExpert::operator =(const SystemeExpert& se) {
	if (this == &se)
		return *this;

	baseRegles = se.baseRegles;
	baseFaits = se.baseFaits;

	return *this;
}

/**
 * \brief Destructeur
 */
tp1::SystemeExpert::~SystemeExpert() {
}

/**
 * \brief Ajouter une règle déjà initialisée à la base de règles
 *
 * \pre La règle n'est pas déjà incluse dans la base de règles
 * \post La taille de la base de règles est incrémentée de 1
 * \param[in] tr, la règle à ajouter
 */
void tp1::SystemeExpert::ajouterRegleSE(const Regle& tr) {
	ASSERTION(!baseRegles.appartient(tr));

	auto nbReglesAvantAjout = baseRegles.taille();
	baseRegles.ajouter(tr, baseRegles.taille() + 1);

	ASSERTION(baseRegles.taille() == nbReglesAvantAjout + 1);
}

/**
 * \brief Ajouter un fait déjà initialisé à la base de faits
 *
 * \pre Le fait n'est pas déjà inclus dans la base de faits
 * \post La taille de la base de faits est incrémentée de 1
 * \param[in] tf, le fait à ajouter
 */
void SystemeExpert::ajouterFaitSE(const TypeFait& tf) {
	ASSERTION(!faitPresentSE(tf));

	auto nbFaitsAvantAjout = baseFaits.size();
	baseFaits.push_back(tf);

	ASSERTION(baseFaits.size() == nbFaitsAvantAjout + 1);
}

/**
 * \brief Vérifier si un fait est déjà présent dans le système expert
 *
 * \param[in] tf, le fait à vérifier
 * \param[out] bool, true si le fait est présent, false sinon
 */
bool SystemeExpert::faitPresentSE(const TypeFait& tf) const {
	return (std::find(baseFaits.begin(), baseFaits.end(), tf) != baseFaits.end());
}

/**
 * \brief Charger un système expert
 * \param[in] EntreeFichier, fichier texte déjà chargé en mémoire
 * \pre EntreeFichier est valide et non vide
 * \post Le nombre de faits et règles ajoutés est valide
 */
void SystemeExpert::chargerSE(std::ifstream& EntreeFichier) {
	ASSERTION(EntreeFichier.good());

	enum TypeLigne {
		premisse, conclusion, fait
	};

	TypeLigne tl = premisse;

	std::string ligne;
	Regle r;
	TypeFait t;
	auto nbRegles = 0;
	auto nbFaits = 0;

	while (EntreeFichier.good()) {
		std::getline(EntreeFichier, ligne);

		if (ligne == "!>"){
			tl = conclusion;
		} else if (ligne == "!%") {
			tl = premisse;
			if (!r.GetConclusions().empty() and !r.GetPremisses().empty()) {
				ajouterRegleSE(r);
				nbRegles++;
			}
			r.GetPremisses().clear();
			r.GetConclusions().clear();

		} else if (ligne == "!!") {
			ajouterRegleSE(r);
			nbRegles++;
			tl = fait;
		} else {
			switch (tl) {
			case premisse:
				r.GetPremisses().push_back(ligne);
				break;
			case conclusion:
				r.GetConclusions().push_back(ligne);
				break;
			case fait:
				t = ligne;
				ajouterFaitSE(t);
				nbFaits++;
			}
		}
	}
	ASSERTION(baseFaits.size() == nbFaits and baseRegles.taille() == nbRegles);

}
/**
 * \brief Sauvegarde le système expert dans un fichier
 *
 * \pre La base de règles et la base de faits ne sont pas vides
 * \param[in] SortieFichier, fichier texte déjà chargé en mémoire
 */
void SystemeExpert::sauvegarderSE(std::ofstream& SortieFichier) const {
	ASSERTION(!(baseRegles.estVide() and baseFaits.empty()));

	for (auto i = 1; i <= baseRegles.taille(); i++) {
		Regle r = baseRegles.element(i);

		for (auto itr = r.GetPremisses().begin(); itr != r.GetPremisses().end();
				++itr)
			SortieFichier << *itr << std::endl;
		SortieFichier << "!>" << std::endl;

		for (auto itr = r.GetConclusions().begin();
				itr != r.GetConclusions().end(); ++itr) {
			SortieFichier << *itr << std::endl;
			if (i != baseRegles.taille())
				SortieFichier << "!%" << std::endl;
		}
	}

	SortieFichier << "!!" << std::endl;
	unsigned int compteurFaits = 0;
	for (auto itr = baseFaits.begin(); itr != baseFaits.end(); ++itr) {
		SortieFichier << *itr;
		compteurFaits++;
		if (baseFaits.size() != compteurFaits)
			SortieFichier << std::endl;
	}
}
/**
 * \brief Sature la base de faits du système expert se en retrouvant
 *    les faits qui peuvent être déduits de la base de faits du système expert
 *    en question et en se basant sur les règles de celui-ci.
 *
 * \param[in] er, ListeCirculaire de règles à vérifier et saturer
 * \pre La base de règles et la base de faits ne sont pas vides
 */
void SystemeExpert::chainageAvant(ListeCirculaire<Regle>& er) {
	ASSERTION(!baseRegles.estVide() and !baseFaits.empty());
	bool toutesReglesVerifiees = false;

	while (!toutesReglesVerifiees) {
		toutesReglesVerifiees = true;
		for (auto i = 1; i <= baseRegles.taille(); i++) {
			Regle r = baseRegles.element(i);
			bool toutesPremissesSontFaits = false;
			unsigned int premissesVerifiees = 0;

			for (auto itrP = r.GetPremisses().begin();
					itrP != r.GetPremisses().end(); ++itrP) {
				for (auto itrF = baseFaits.begin(); itrF != baseFaits.end();
						++itrF) {
					if (*itrP == *itrF)
						premissesVerifiees++;
				}
			}
			if (premissesVerifiees == r.GetPremisses().size())
				toutesPremissesSontFaits = true;

			if (toutesPremissesSontFaits) {
				for (auto itrC = r.GetConclusions().begin();
						itrC != r.GetConclusions().end(); ++itrC) {
					if (!faitPresentSE(*itrC)) {
						baseFaits.push_back(*itrC);
						er.ajouter(r, er.taille() + 1);
						toutesReglesVerifiees = false;
					}

				}
			}
		}
	}
}
} //namespace tp1

