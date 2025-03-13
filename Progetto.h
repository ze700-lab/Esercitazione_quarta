/*!
\file Progetto.h
\brief definizione della classe Progetto
\author G. Meini
\version 1.0
\date 01/07/2021
*/

#ifndef _PROGETTO
#define _PROGETTO

#include <cstring>
#include <cstdio>
#include "Azione.h"
#include "Spesa.h"
#include "Trasferimento.h"

#if defined(_WIN32) || defined(_WIN64)
#define DIRECTORY_PROGETTI ".\\progetti\\";
#else
#define DIRECTORY_PROGETTI "./progetti/";
#endif

const unsigned int NUMERO_MASSIMO_AZIONI_PROGETTO = 1000;

enum FILETYPE
{
	CSV,
	HTML
};

//! \brief struttura dello header del file binario che rappresenta un progetto
struct FILEHEADER
{
	char partecipanti[5][64];
	unsigned short numero_partecipanti;
};

//! \brief struttura del record del file binario che rappresenta un progetto
struct FILERECORD
{
	char descrizione[256];
	float importo;
	unsigned short giorno;
	unsigned short mese;
	unsigned short anno;
	unsigned short pagatore;
	unsigned short partecipanti[5];
	unsigned short numero_partecipanti;
};

//! \brief struttura che rappresenta il saldo di un partecipante ad un progetto
struct SALDO
{
	char partecipante[64];
	float saldo;
};

//! \brief classe per la rappresentazione di un progetto
class Progetto
{
 private:
	//! \brief denominazione del progetto (nome del file relativo al progetto)
	char denominazione[256];
	//! \brief nomi dei partecipanti al progetto (array di stringhe)
	char partecipanti[5][64];
	//! \brief numero dei partecipanti al progetto
	unsigned int numero_partecipanti;
	//! \brief elenco di spese/trasferimenti del progetto
	Azione* azioni[NUMERO_MASSIMO_AZIONI_PROGETTO];
	unsigned int numero_azioni;

 public:
	/*! \brief costruttore per la creazione di un nuovo progetto
		\param[in] denominazione denominazione del progetto (nome del file relativo al progetto)
		\param[in] partecipanti nomi dei partecipanti al progetto (array di stinghe)
		\note il numero dei partecipanti al progetto e' dato dal numero di stringhe non nulle e non vuote nelle posizioni iniziali dell'array dei partecipanti (massimo 5)
	*/
	Progetto(const char denominazione[], char* partecipanti[]);
	/*! \brief costruttore per l'apertura di un progetto esistente
		\param[in] denominazione denominazione del progetto (nome del file relativo al progetto)
	*/
	Progetto(const char denominazione[]);
	//! \brief distruttore
	~Progetto(void);
	/*! \brief acquisizione denominazione del progetto
		\param[out] denominazione denominazione del progetto
	*/
	void getDenominazione(char* denominazione);
	/*! \brief acquisizione del numero e dei nomi dei partecipanti al progetto
		\param[out] partecipanti nomi dei partecipanti al progetto (array di stinghe)
		\retval numero dei partecipanti al progetto
	*/
	unsigned int getPartecipanti(char* partecipanti[]);
	/*! \brief acquisizione del numero di azioni registrate nel progetto
		\retval numero di azioni registrate nel progetto
	*/
	unsigned int getNumeroAzioni(void);
	/*! \brief aggiunta nuova spesa al progetto
		\param[in] spesa spesa da aggiugere al progetto
		\retval VERO la spesa e' stata aggiunta al progetto
		\retval FALSO la spesa non e' stata aggiunta al progetto
	*/
	bool nuovaSpesa(Spesa spesa);
	/*! \brief aggiunta nuovo trasferimento al progetto
		\param[in] trasferimento trasferimento da aggiugere al progetto
		\retval VERO il trasferimento e' stato aggiunto al progetto
		\retval FALSO il trasferimento non e' stata aggiunto al progetto
	*/
	bool nuovoTrasferimento(Trasferimento trasferimento);
	/*! \brief eliminazione di un'azione dal progetto
		\param[in] indice indice sequenziale dell'azione da eliminare
		\retval VERO l'azione e' stata eliminata
		\retval FALSO l'azione non e' stata eliminata 
	*/
	bool eliminaAzione(unsigned int indice);
	/*! \brief aggiornamento di un'azione del progetto
		\param[in] azione spesa/trasferimento aggiornato (puntatore)
		\param[in] indice indice sequenziale dell'azione da aggiornare
		\retval VERO l'azione e' stata aggiornata
		\retval FALSO l'azione non e' stata aggiornata
	*/
	bool aggiornaAzione(unsigned int indice, Azione* azione);
	/*! \brief elenco delle azioni del progetto
		\param[out] elenco elenco delle azioni del progetto (array di puntatori)
		\retval numero di azioni presenti nell'elenco
	*/
	unsigned int elencaAzioni(Azione* elenco[]);
	/*! \brief elenco delle azioni del progetto con uno specifico pagatore
		\param[in] pagatore indice del pagatore
		\param[out] elenco elenco delle azioni del progetto (array di puntatori)
		\retval numero di azioni presenti nell'elenco
	*/
	unsigned int elencaAzioniPagatore(unsigned int pagatore, Azione* elenco[]);
	/*! \brief elenco delle azioni del progetto con uno specifico partecipante
		\param[in] partecipante indice del partecipante
		\param[out] elenco elenco delle azioni del progetto (array di puntatori)
		\retval numero di azioni presenti nell'elenco
	*/
	unsigned int elencaAzioniPartecipante(unsigned int partecipante, Azione* elenco[]);
	/*! \brief esportazione delle azioni del progetto su file
		\param[in] tipo_file tipo del file (CSV o HTML)
		\param[in] nome_file denominazione del file
		\retval VERO il file e' stato generato
		\retval FALSO il file non e' stato generato
	*/
	bool esportaAzioniSuFile(FILETYPE tipo_file, const char nome_file[]);
	/*! \brief esportazione delle azioni del progetto con uno specifico pagatore su file
		\param[in] tipo_file tipo del file (CSV o HTML)
		\param[in] nome_file denominazione del file
		\param[in] pagatore indice del pagatore
		\retval VERO il file e' stato generato
		\retval FALSO il file non e' stato generato
	*/
	bool esportaAzioniPagatoreSuFile(FILETYPE tipo_file, const char nome_file[], unsigned int pagatore);
	/*! \brief esportazione delle azioni del progetto con uno specifico partecipante su file
		\param[in] tipo_file tipo del file (CSV o HTML)
		\param[in] nome_file denominazione del file
		\param[in] partecipante indice del partecipante
		\retval VERO il file e' stato generato
		\retval FALSO il file non e' stato generato
	*/
	bool esportaAzioniPartecipanteSuFile(FILETYPE tipo_file, const char nome_file[], unsigned int partecipante);
	/*! \brief genera il bilancio delle spese e dei trasferimenti del progetto
		\param[out] saldi array dei saldi dei partecipanti
		\retval numero dei partecipanti al progetto
	*/
	unsigned int bilancio(SALDO saldo[5]);
};

#endif
