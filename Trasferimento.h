#ifndef _TRASFERIMENTO
#define _TRASFERIMENTO

/*!
\file Trasferimento.h
\brief definizione e implementazione della classe Trasferimento
\author G. Meini
\version 1.0
\date 01/07/2021
*/

#include "Azione.h"

//! \brief classe per la rappresentazione di un singolo trasferimento di un progetto
class Trasferimento : public Azione
{
 public:
	 //! \brief costruttore
	 //! \param[in] descrizione descrizione del trasferimento
	 //! \param[in] data data del trasferimento
	 //! \param[in] importo importo del trasferimento
	 //! \param[in] pagatore indice del pagatore del trasferimento
	 //! \param[in] destinatari array degli indici dei destinatari del trasferimento
	 //! \param[in] numero_destinatari numero dei destinatari del trasferimento
	 //! \note gli indici riferiscono l'array dei partecipanti al progetto
	 Trasferimento(const char descrizione[], Date date, float importo, unsigned int pagatore, unsigned int numero_destinatari, unsigned int destinatari[])
	 {
		 strncpy(this->descrizione, descrizione, 256);
		 this->data = date;
		 if (importo > 0)
			 this->importo = importo;
		 else
			 this->importo = 0;
		 this->numero_partecipanti = (numero_destinatari > 5) ? 5 : numero_destinatari;
		 this->pagatore = pagatore;
		 for (unsigned int index = 0; index < this->numero_partecipanti; index++)
			this->partecipanti[index] = destinatari[index];
	 }
};

#endif
