

#include "Progetto.h"
#include "ExpenseManager.h"

#include "gtest\gtest.h"


/* Test unitari classe Spesa */

TEST(Spesa, costruttore)
{
	unsigned int i, n;
	char descrizione[256];
	unsigned int partecipanti[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Date data(31, 12, 2021);
	Spesa spesa("spesa", data, 99.99, 0, 10, partecipanti);

	spesa.getDescrizione(descrizione);
	ASSERT_STREQ("spesa", descrizione);
	ASSERT_NEAR(spesa.getImporto(), 99.99, .001);
	ASSERT_TRUE(spesa.getData().getDay() == 31 && spesa.getData().getMonth() == 12 && spesa.getData().getYear() == 2021);
	ASSERT_EQ(0, spesa.getPagatore());
	ASSERT_EQ(5, spesa.getNumeroPartecipanti());
	n = spesa.getPartecipanti(partecipanti);
	for (i=0; i<n; i++)
		ASSERT_EQ(i, partecipanti[i]);
}

TEST(Spesa, setEget)
{
	int i, n;
	Date data0(31, 12, 2021), data1(1, 1, 2022);
	char descrizione[256];
	unsigned int partecipanti0[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	unsigned int partecipanti1[] = { 4, 3, 2, 1 };
	Date data(31, 12, 2021);
	Spesa spesa("spesa", data0, 99.99, 0, 10, partecipanti0);

	spesa.setDescrizione("SPESA");
	spesa.getDescrizione(descrizione);
	ASSERT_STREQ("SPESA", descrizione);
	spesa.setImporto(-9.99);
	ASSERT_NEAR(spesa.getImporto(), 99.99, .001);
	spesa.setImporto(9.99);
	ASSERT_NEAR(spesa.getImporto(), 9.99, .001);
	spesa.setData(data1);
	ASSERT_TRUE(spesa.getData().getDay() == 1 && spesa.getData().getMonth() == 1 && spesa.getData().getYear() == 2022);
	spesa.setPagatore(1);
	ASSERT_EQ(1, spesa.getPagatore());
	spesa.setPartecipanti(10, partecipanti0);
	ASSERT_EQ(5, spesa.getNumeroPartecipanti());
	spesa.setPartecipanti(4, partecipanti1);
	ASSERT_EQ(4, spesa.getNumeroPartecipanti());
	n = spesa.getPartecipanti(partecipanti0);
	for (i = 0; i < n; i++)
		ASSERT_EQ(n - i, partecipanti0[i]);
}

/* Test unitari classe Trasferimento */

TEST(Trafserimento, costruttore)
{
	unsigned int i, n;
	char descrizione[256];
	unsigned int partecipanti[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Date data(31, 12, 2021);
	Trasferimento trasferimento("trasferimento", data, 99.99, 0, 10, partecipanti);

	trasferimento.getDescrizione(descrizione);
	ASSERT_STREQ("trasferimento", descrizione);
	ASSERT_NEAR(trasferimento.getImporto(), 99.99, .001);
	ASSERT_TRUE(trasferimento.getData().getDay() == 31 && trasferimento.getData().getMonth() == 12 && trasferimento.getData().getYear() == 2021);
	ASSERT_EQ(0, trasferimento.getPagatore());
	ASSERT_EQ(5, trasferimento.getNumeroPartecipanti());
	n = trasferimento.getPartecipanti(partecipanti);
	for (i = 0; i < n; i++)
		ASSERT_EQ(i, partecipanti[i]);
}

TEST(Trasferimento, setEget)
{
	unsigned int i, n;
	Date data0(31, 12, 2021), data1(1, 1, 2022);
	char descrizione[256];
	unsigned int partecipanti0[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	unsigned int partecipanti1[] = { 4, 3, 2, 1 };
	Date data(31, 12, 2021);
	Trasferimento trasferimento("trasferimento", data0, 99.99, 0, 10, partecipanti0);

	trasferimento.setDescrizione("TRASFERIMENTO");
	trasferimento.getDescrizione(descrizione);
	ASSERT_STREQ("TRASFERIMENTO", descrizione);
	trasferimento.setImporto(-9.99);
	ASSERT_NEAR(trasferimento.getImporto(), 99.99, .001);
	trasferimento.setImporto(9.99);
	ASSERT_NEAR(trasferimento.getImporto(), 9.99, .001);
	trasferimento.setData(data1);
	ASSERT_TRUE(trasferimento.getData().getDay() == 1 && trasferimento.getData().getMonth() == 1 && trasferimento.getData().getYear() == 2022);
	trasferimento.setPagatore(1);
	ASSERT_EQ(1, trasferimento.getPagatore());
	trasferimento.setPartecipanti(10, partecipanti0);
	ASSERT_EQ(5, trasferimento.getNumeroPartecipanti());
	trasferimento.setPartecipanti(4, partecipanti1);
	ASSERT_EQ(4, trasferimento.getNumeroPartecipanti());
	n = trasferimento.getPartecipanti(partecipanti0);
	for (i = 0; i < n; i++)
		ASSERT_EQ(n - i, partecipanti0[i]);
}

/* Test unitari classe Progetto */

TEST(Progetto, costruttori)
{
	char nome_file[1024] = DIRECTORY_PROGETTI;
	char denominazione[64];
	char* partecipanti0[6];
	char* partecipanti1[6];
	SALDO saldo[5];
	
	// predisposizione test
	partecipanti0[0] = new char[64];
	strcpy(partecipanti0[0], "Primo");
	partecipanti0[1] = new char[64];
	strcpy(partecipanti0[1], "Secondo");
	partecipanti0[2] = new char[64];
	strcpy(partecipanti0[2], "Terzo");
	partecipanti0[3] = new char[64];
	strcpy(partecipanti0[3], "Quarto");
	partecipanti0[4] = nullptr;
	partecipanti1[0] = new char[64];
	partecipanti1[1] = new char[64];
	partecipanti1[2] = new char[64];
	partecipanti1[3] = new char[64];
	partecipanti1[4] = new char[64];

	// test costruttore nuovo progetto
	strcat(nome_file, "Progetto");
	remove(nome_file);
	Progetto progetto0("Progetto", partecipanti0);
	progetto0.getDenominazione(denominazione);
	ASSERT_STREQ("Progetto", denominazione);
	ASSERT_EQ(4, progetto0.getPartecipanti(partecipanti1));
	ASSERT_STREQ("Primo", partecipanti1[0]);
	ASSERT_STREQ("Secondo", partecipanti1[1]);
	ASSERT_STREQ("Terzo", partecipanti1[2]);
	ASSERT_STREQ("Quarto", partecipanti1[3]);
	ASSERT_EQ(0, progetto0.getNumeroAzioni());
	ASSERT_EQ(4, progetto0.bilancio(saldo));
	ASSERT_STREQ("Primo", saldo[0].partecipante);
	ASSERT_STREQ("Secondo", saldo[1].partecipante);
	ASSERT_STREQ("Terzo", saldo[2].partecipante);
	ASSERT_STREQ("Quarto", saldo[3].partecipante);
	ASSERT_FLOAT_EQ(0, saldo[0].saldo);
	ASSERT_FLOAT_EQ(0, saldo[1].saldo);
	ASSERT_FLOAT_EQ(0, saldo[2].saldo);
	ASSERT_FLOAT_EQ(0, saldo[3].saldo);

	// test costruttore progetto esistente
	Progetto progetto1("Progetto");
	progetto1.getDenominazione(denominazione);
	ASSERT_STREQ("Progetto", denominazione);
	ASSERT_EQ(4, progetto1.getPartecipanti(partecipanti1));
	ASSERT_STREQ("Primo", partecipanti1[0]);
	ASSERT_STREQ("Secondo", partecipanti1[1]);
	ASSERT_STREQ("Terzo", partecipanti1[2]);
	ASSERT_STREQ("Quarto", partecipanti1[3]);
	ASSERT_EQ(0, progetto1.getNumeroAzioni());
	ASSERT_EQ(4, progetto1.bilancio(saldo));
	ASSERT_STREQ("Primo", saldo[0].partecipante);
	ASSERT_STREQ("Secondo", saldo[1].partecipante);
	ASSERT_STREQ("Terzo", saldo[2].partecipante);
	ASSERT_STREQ("Quarto", saldo[3].partecipante);

	// pulizia test
	delete[] partecipanti0[0];
	delete[] partecipanti0[1];
	delete[] partecipanti0[2];
	delete[] partecipanti0[3];
	delete[] partecipanti1[0];
	delete[] partecipanti1[1];
	delete[] partecipanti1[2];
	delete[] partecipanti1[3];
	delete[] partecipanti1[4];
}


TEST(Progetto, gestioneSpeseTrasferimenti)
{
	char nome_file[1024] = DIRECTORY_PROGETTI;
	SALDO saldo[5];
	Azione* elenco[NUMERO_MASSIMO_AZIONI_PROGETTO];
	Date data0(31, 12, 2021), data1(1, 1, 2022);
	char descrizione[256];
	unsigned int partecipanti[] = { 0, 1, 2, 3 };
	unsigned int destinatari[] = { 0 };
	Date data(31, 12, 2021);
	Spesa spesa0("spesa 0", data0, 1000, 0, 4, partecipanti);
	Spesa spesa1("spesa 0", data0, 500, 0, 4, partecipanti);
	Trasferimento trasferimento0("rimborso 1", data1, 250, 1, 1, destinatari);
	Trasferimento trasferimento1("rimborso 2", data1, 250, 2, 1, destinatari);
	Trasferimento trasferimento2("rimborso 3", data1, 250, 3, 1, destinatari);

	Progetto progetto("Progetto");
	ASSERT_EQ(0, progetto.getNumeroAzioni());
	ASSERT_TRUE(progetto.nuovaSpesa(spesa0));
	ASSERT_EQ(1, progetto.getNumeroAzioni());
	ASSERT_EQ(4, progetto.bilancio(saldo));
	ASSERT_NEAR(-750, saldo[0].saldo, 0.001);
	ASSERT_NEAR(250, saldo[1].saldo, 0.001);
	ASSERT_NEAR(250, saldo[2].saldo, 0.001);
	ASSERT_NEAR(250, saldo[3].saldo, 0.001);
	ASSERT_TRUE(progetto.nuovoTrasferimento(trasferimento0));
	ASSERT_EQ(2, progetto.getNumeroAzioni());
	ASSERT_TRUE(progetto.nuovoTrasferimento(trasferimento1));
	ASSERT_EQ(3, progetto.getNumeroAzioni());
	ASSERT_TRUE(progetto.nuovoTrasferimento(trasferimento2));
	ASSERT_EQ(4, progetto.getNumeroAzioni());
	ASSERT_EQ(4, progetto.bilancio(saldo));
	ASSERT_NEAR(0, saldo[0].saldo, 0.001);
	ASSERT_NEAR(0, saldo[1].saldo, 0.001);
	ASSERT_NEAR(0, saldo[2].saldo, 0.001);
	ASSERT_NEAR(0, saldo[3].saldo, 0.001);
	
	ASSERT_EQ(4, progetto.elencaAzioni(elenco));
	elenco[0]->getDescrizione(descrizione);
	ASSERT_STREQ("spesa 0", descrizione);
	elenco[1]->getDescrizione(descrizione);
	ASSERT_STREQ("rimborso 1", descrizione);
	elenco[2]->getDescrizione(descrizione);
	ASSERT_STREQ("rimborso 2", descrizione);
	elenco[3]->getDescrizione(descrizione);
	ASSERT_STREQ("rimborso 3", descrizione);
	ASSERT_EQ(1, progetto.elencaAzioniPagatore(0, elenco));
	ASSERT_EQ(1, progetto.elencaAzioniPagatore(1, elenco));
	ASSERT_EQ(1, progetto.elencaAzioniPagatore(2, elenco));
	ASSERT_EQ(1, progetto.elencaAzioniPagatore(3, elenco));
	ASSERT_EQ(4, progetto.elencaAzioniPartecipante(0, elenco));
	ASSERT_EQ(1, progetto.elencaAzioniPartecipante(1, elenco));
	ASSERT_EQ(1, progetto.elencaAzioniPartecipante(2, elenco));
	ASSERT_EQ(1, progetto.elencaAzioniPartecipante(3, elenco));
	
	ASSERT_FALSE(progetto.eliminaAzione(4));
	ASSERT_EQ(4, progetto.getNumeroAzioni());
	ASSERT_TRUE(progetto.eliminaAzione(3));
	ASSERT_EQ(3, progetto.getNumeroAzioni());
	ASSERT_EQ(4, progetto.bilancio(saldo));
	ASSERT_NEAR(-250, saldo[0].saldo, 0.001);
	ASSERT_NEAR(0, saldo[1].saldo, 0.001);
	ASSERT_NEAR(0, saldo[2].saldo, 0.001);
	ASSERT_NEAR(250, saldo[3].saldo, 0.001);
	ASSERT_TRUE(progetto.aggiornaAzione(0, &spesa1));
	ASSERT_EQ(3, progetto.getNumeroAzioni());
	ASSERT_EQ(4, progetto.bilancio(saldo));
	ASSERT_NEAR(125, saldo[0].saldo, 0.001);
	ASSERT_NEAR(-125, saldo[1].saldo, 0.001);
	ASSERT_NEAR(-125, saldo[2].saldo, 0.001);
	ASSERT_NEAR(125, saldo[3].saldo, 0.001);
}

/* Test unitari classe ExpenseManager */

class TestExpenseManager : public testing::Test
{
public:
	char* progetti[16];
	char* partecipanti[3];

	virtual void SetUp(void)
	{
		for (int i = 0; i < 16; i++)
		  progetti[i] = new char[64];
		partecipanti[0] = new char[64];
		strcpy(partecipanti[0], "Primo");
		partecipanti[1] = new char[64];
		strcpy(partecipanti[1], "Secondo");
		partecipanti[2] = nullptr;
	}

	virtual void TearDown(void)
	{
		for (int i = 0; i < 16; i++)
		   delete[] progetti[i];
		delete[] partecipanti[0];
		delete[] partecipanti[1];
	}
};

TEST_F(TestExpenseManager, eliminaProgetto)
{
	unsigned int i, n;

	n = ExpenseManager::elencaProgetti(16, progetti);
	for (i = 0; i < n; i++)
	{
		ASSERT_TRUE(ExpenseManager::eliminaProgetto(progetti[i]));
		ASSERT_FALSE(ExpenseManager::eliminaProgetto(progetti[i]));
	}
	ASSERT_EQ(0, ExpenseManager::elencaProgetti(16, progetti));
}

TEST_F(TestExpenseManager, creazioneElencoProgetti)
{
	Progetto* progetto;
	char denominazione[64];

	// test creazione progetto
	ASSERT_TRUE(progetto = ExpenseManager::creaProgetto("Progetto1", partecipanti));
	progetto->getDenominazione(denominazione);
	ASSERT_STREQ("Progetto1", denominazione);
	delete progetto;
	ASSERT_FALSE(progetto = ExpenseManager::creaProgetto("Progetto1", partecipanti));
	ASSERT_TRUE(progetto = ExpenseManager::creaProgetto("Progetto2", partecipanti));
	progetto->getDenominazione(denominazione);
	ASSERT_STREQ("Progetto2", denominazione);
	delete progetto;
	
	// test elenco progetti
	ASSERT_EQ(2, ExpenseManager::elencaProgetti(16, progetti));
	ASSERT_STREQ("Progetto1", progetti[0]);
	ASSERT_STREQ("Progetto2", progetti[1]);
}

TEST_F(TestExpenseManager, selezioneProgetto)
{
	Progetto* progetto;
	char denominazione[64];

	// test selezione progetto
	ASSERT_FALSE(progetto = ExpenseManager::selezionaProgetto("Progetto0"));
	ASSERT_TRUE(progetto = ExpenseManager::selezionaProgetto("Progetto1"));
	progetto->getDenominazione(denominazione);
	ASSERT_STREQ("Progetto1", denominazione);
	delete progetto;
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}