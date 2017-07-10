#include "gtest/gtest.h"
#include "Regle.h"

using namespace tp1;

TEST(TestsSimplesRegle, NouvelleRegleSansPremisses) {
	Regle re;
	ASSERT_TRUE(re.GetPremisses().empty());
}

TEST(TestsSimplesRegle, AjoutDUnePremisse) {
	Regle re;
	re.GetPremisses().push_back("test");
	ASSERT_EQ(re.GetPremisses().size(), 1);
}

TEST(TestsSimplesRegle, NouvelleRegleSansConclusions) {
	Regle re;
	ASSERT_TRUE(re.GetConclusions().empty());
}

TEST(TestsSimplesRegle, AjoutDUneConclusion) {
	Regle re;
	re.GetConclusions().push_back("test");
	ASSERT_EQ(re.GetConclusions().size(), 1);
}

TEST(TestsSimplesRegle, ConstructeurCopieDeuxReglesIdentiques){
	Regle re1;
	re1.GetPremisses().push_back("testP1");
	re1.GetConclusions().push_back("testC1");
	Regle re2(re1);
	ASSERT_TRUE(re1 == re2);
}

TEST(TestsSimplesRegle, ComparaisonEgalDeuxReglesNonIdentiquesRetourneFaux) {
	Regle re1;
	re1.GetPremisses().push_back("testP1");
	re1.GetConclusions().push_back("testC1");
	Regle re2;
	re2.GetPremisses().push_back("testP2");
	re2.GetConclusions().push_back("testC2");
	ASSERT_FALSE(re1 == re2);
}

TEST(TestsSimplesRegle, ComparaisonEgalDeuxReglesIdentiquesRetourneVrai) {
	Regle re1;
	re1.GetPremisses().push_back("testP");
	re1.GetConclusions().push_back("testC");
	Regle re2;
	re2.GetPremisses().push_back("testP");
	re2.GetConclusions().push_back("testC");
	ASSERT_TRUE(re1 == re2);
}

TEST(TestsSimplesRegle, ComparaisonNonEgalDeuxReglesNonIdentiquesRetourneVrai) {
	Regle re1;
	re1.GetPremisses().push_back("testP1");
	re1.GetConclusions().push_back("testC1");
	Regle re2;
	re2.GetPremisses().push_back("testP2");
	re2.GetConclusions().push_back("testC2");
	ASSERT_TRUE(re1 != re2);
}

TEST(TestsSimplesRegle, ComparaisonNonEgalDeuxReglesIdentiquesRetourneFaux) {
	Regle re1;
	re1.GetPremisses().push_back("testP");
	re1.GetConclusions().push_back("testC");
	Regle re2;
	re2.GetPremisses().push_back("testP");
	re2.GetConclusions().push_back("testC");
	ASSERT_FALSE(re1 != re2);
}
