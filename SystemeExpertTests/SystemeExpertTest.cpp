/*
 * SystemeExpertTest.cpp
 *
 *  Created on: 2017-05-30
 *      Author: etudiant
 */

#include "gtest/gtest.h"
#include "SystemeExpert.h"

using namespace tp1;

TEST(SystemeExpertTestsSimples, ConstructeurBase) {
	SystemeExpert se;
}

TEST(SystemeExpertTestsSimples, ConstructeurCopieDeuxFaitsIdentiquesOK) {
	SystemeExpert se1;
	TypeFait fait = "test";
	se1.ajouterFaitSE(fait);
	SystemeExpert se2(se1);
	ASSERT_EQ(se1.getBaseFaits().front(), se2.getBaseFaits().front());
}

TEST(SystemeExpertTestsSimples, ChargementSEOK) {
	SystemeExpert se;
	std::ifstream EntreeFichier;
	EntreeFichier.open("TestIN.txt", std::ios::in);
	se.chargerSE(EntreeFichier);
	ASSERT_TRUE(!se.getBaseRegles().estVide() and !se.getBaseFaits().empty());
}

TEST(SystemeExpertTestsSimples, SauvegarderSEOK) {
	SystemeExpert se;
	std::ifstream EntreeFichier;
	EntreeFichier.open("TestIN.txt", std::ios::in);
	se.chargerSE(EntreeFichier);
	EntreeFichier.close();
	std::ofstream SortieFichier;
	SortieFichier.open("TestOUT.txt", std::ios::out);
	se.sauvegarderSE(SortieFichier);
}

TEST(SystemeExpertTestsSimples, ChainageSEOK) {
	SystemeExpert se;
	std::ifstream EntreeFichier;
	EntreeFichier.open("TestIN.txt", std::ios::in);
	se.chargerSE(EntreeFichier);
	EntreeFichier.close();
	se.chainageAvant(se.getBaseRegles());
	std::ofstream SortieFichier;
	SortieFichier.open("TestOUT.txt", std::ios::out);
	se.sauvegarderSE(SortieFichier);
}

TEST(SystemeExpertTestsSimples, AjoutDUneRegleOK) {
	SystemeExpert se;
	Regle r;
	r.GetPremisses().push_back("test");
	se.ajouterRegleSE(r);
}

TEST(SystemeExpertTestsSimples, AjoutDeuxReglesDifferentesOK) {
	SystemeExpert se;
	Regle r1;
	r1.GetPremisses().push_back("test");
	Regle r2;
	r2.GetPremisses().push_back("test2");
	se.ajouterRegleSE(r1);
	se.ajouterRegleSE(r2);
	ASSERT_EQ(se.getBaseRegles().taille(), 2);
}

TEST(SystemeExpertTestsSimples, AjoutUneRegleDeuxFoisLanceException) {
	SystemeExpert se;
	Regle r1;
	r1.GetPremisses().push_back("test");
	se.ajouterRegleSE(r1);
	ASSERT_THROW(se.ajouterRegleSE(r1), AssertionException);
}

TEST(SystemeExpertTestsSimples, AjoutDeuxReglesIdentiqueLanceException) {
	SystemeExpert se;
	Regle r1;
	r1.GetPremisses().push_back("test");
	r1.GetConclusions().push_back("test");
	se.ajouterRegleSE(r1);
	Regle r2;
	r2.GetPremisses().push_back("test");
	r2.GetConclusions().push_back("test");
	ASSERT_THROW(se.ajouterRegleSE(r2), AssertionException);
}

TEST(SystemeExpertTestsSimples, AjoutDUnFaitOK) {
	SystemeExpert se;
	TypeFait fait;
	fait = "test";
	se.ajouterFaitSE(fait);
}

TEST(SystemeExpertTestsSimples, AjoutUnFaitDeuxFoisLanceException) {
	SystemeExpert se;
	TypeFait fait;
	fait = "test";
	se.ajouterFaitSE(fait);
	ASSERT_THROW(se.ajouterFaitSE(fait), AssertionException);
}

TEST(SystemeExpertTestsSimples, AjoutDeuxFaitsDifferentsOK) {
	SystemeExpert se;
	TypeFait fait1;
	fait1 = "test1";
	TypeFait fait2;
	fait2 = "test2";
	se.ajouterFaitSE(fait1);
	se.ajouterFaitSE(fait2);
}

TEST(SystemeExpertTestsSimples, AjoutDeuxFaitsIdentiquesLanceException) {
	SystemeExpert se;
	TypeFait fait1;
	fait1 = "test";
	TypeFait fait2;
	fait2 = "test";
	se.ajouterFaitSE(fait1);
	ASSERT_THROW(se.ajouterFaitSE(fait2), AssertionException);
}
