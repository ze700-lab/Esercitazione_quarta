#ifndef _AZIONE
#define _AZIONE

/*!
\file Azione.h
\brief definizione e implementazione della classe astratta Azione
\author G. Meini
\version 1.0
\date 30/06/2021
*/

#include <cstring>
#include "Date.h"

/*!
\class Azione
\brief classe per la rappresentazione di una singola spesa o di un singolo trasferimento di un progetto
*/
class Azione
{
 protected:
	 //! \var descrizione
	 //! \brief descrizione della spesa o del trasferimento
	 char descrizione[256];
	 //! \var data
	 //! \brief data della spesa o del trasferimento
	 Date data;
	 //! \var importo
	 //! \brief importo della spesa o del trasferimento
	 float importo;
	 //! \var pagatore
	 //! \brief indice del pagatore della spesa o del trasferimento
	 //! \note l'indice riferisce l'array dei partecipanti al progetto
	 unsigned int pagatore;
	 //! \var partecipanti
	 //! \brief array degli indici dei partecipanti alla spesa o al trasferimento
	 //! \note gli indici riferiscono l'array dei partecipanti al progetto
	 unsigned int partecipanti[5];
	 //! \var numero_partecipanti
	 //! \brief numero dei partecipanti alla spesa o al trasferimento
	 unsigned int numero_partecipanti;

 public:
	 //! \fn ~Azione
	 //! \brief distruttore puramente virtuale
	 //! \note la definizione di un distruttore puramente virtuale da ridefinire in una classe derivata e' la tecnica C++ per definire una classe astratta
	 virtual ~Azione(void) = 0;
	 //! \fn getDescrizione
	 //! \brief acquisizione della descrizione della spesa o del trasferimento
	 //! \param[out] descrizione descrizione
	 void getDescrizione(char* descrizione) { strncpy(descrizione, this->descrizione, 256);  }
	 //! \fn getData
	 //! \brief acquisizione della data della spesa o del trasferimento
	 Date getData(void) { return data; }
	 //! \fn getImporto
	 //! \brief acquisizione dell'importo della spesa o del trasferimento
	 float getImporto(void) { return importo; }
	 //! \fn getPagatore
	 //! \brief acquisizione dell'indice del pagatore della spesa o del trasferimento
	 unsigned int getPagatore(void) { return pagatore; }
	 //! \fn getPartecipanti
	 //! \brief acquisizione degli indici dei partecipanti alla spesa o al trasferimento
	 //! \param[out] partecipanti array degli indici
	 //! \return numero dei partecipanti
	 unsigned int getPartecipanti(unsigned int partecipanti[5])
	 {
		 for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
			 partecipanti[indice] = this->partecipanti[indice];
		 return numero_partecipanti;
	 }
	 //! \fn getNumeroPartecipanti
	 //! \brief acquisizione del numero dei partecipanti alla spesa o al trasferimento
	 unsigned int getNumeroPartecipanti(void) { return numero_partecipanti; }
	 //! \fn setDescrizione
	 //! \brief impostazione della descrizione della spesa o del trasferimento
	 //! \param[in] descrizione descrizione
	 void setDescrizione(const char descrizione[]) { strncpy(this->descrizione, descrizione, 256); }
	 //! \fn setData
	 //! \brief impostazione della data della spesa o del trasferimento
	 //! \param[in] data data
	 void setData(Date data) { this->data = data; }
	 //! \fn setImporto
	 //! \brief impostazione dell'importo della spesa o del trasferimento
	 //! \param[in] importo importo
	 void setImporto(float importo) { if (importo > 0) this->importo = importo; }
	 //! \fn setPagatore
	 //! \brief impostazione dell'indice del pagatore della spesa o del trasferimento
	 //! \param[in] pagatore indice del pagatore
	 void setPagatore(unsigned int pagatore) { this->pagatore = pagatore; }
	 //! \fn setPartecipanti
	 //! \brief impostazione del numero e degli indici dei partecipanti alla spesa o al trasferimento
	 //! \param[in] numero numero dei partecipanti
	 //! \param[in] partecipanti array degli indici
	 void setPartecipanti(unsigned int numero, const unsigned int partecipanti[])
	 {
		 if (numero > 5)
			 return;
		 for (unsigned int indice = 0; indice < numero; indice++)
		    this->partecipanti[indice] = partecipanti[indice];
		 numero_partecipanti = numero;
	 }
};

#endif
