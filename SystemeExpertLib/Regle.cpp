/////////////////////////////////////////////////////////////////////////////
//Fichier Regle.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Regle.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Regle
 * \author Olivier Léveillé-Gauvin
 * \version 1.0
 * \date mai 2017
 *
 */

#include "Regle.h"
#include "AssertionException.h"

namespace tp1 {
//Mettez l'implantation de vos méthodes ici.
/*
 * \brief Constructeur
 * \post Une instance de la classe Regle est initialisée
 */
tp1::Regle::Regle() :
		premisses(), conclusions() {
}
/*
 * \brief Destructeur
 * \post L'instance de la classe Regle est détruite
 */
tp1::Regle::~Regle() {
}

/*
 * \brief Constructeur de copie
 * \param[in] r La Regle à copier
 * \post La Regle passée en paramètre est copiée
 */
Regle::Regle(const Regle& r) {
	*this = r;
}

/*
 * \brief Surcharge de l'opérateur =
 * \param[in] r La Regle à copier
 * \post Toutes les prémisses et conclusions sont copiées
 */
Regle& Regle::operator =(const Regle& r) {
	if (this == &r)
		return *this;

	auto nbPremisses = 0;
	premisses.clear();
	for (auto itr = r.premisses.begin(); itr != r.premisses.end(); ++itr) {
		premisses.push_back(*itr);
		nbPremisses++;
	}
	auto nbConclusions = 0;
	conclusions.clear();
	for (auto itr = r.conclusions.begin(); itr != r.conclusions.end(); ++itr) {
		conclusions.push_back(*itr);
		nbConclusions++;
	}
	ASSERTION(premisses.size() == nbPremisses);
	ASSERTION(conclusions.size() == nbConclusions);
	return *this;

}
/*
 * \brief Surcharge de l'opérateur ==
 * \param[in] r La Regle à comparer
 */
bool Regle::operator ==(const Regle& r) {
	return (premisses == r.premisses and conclusions == r.conclusions);
}

/*
 * \brief Surcharge de l'opérateur !=
 * \param[in] r La Regle à comparer
 */
bool Regle::operator !=(const Regle& r) {
	return (premisses != r.premisses or conclusions != r.conclusions);
}
} // namespace tp1

