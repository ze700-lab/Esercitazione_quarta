#ifndef _SPESA
#define _SPESA

/*!
\file Spesa.h
\brief definizione e implementazione della classe Spesa
\author G. Meini
\version 1.0
\date 01/07/2021
*/

#include "Azione.h"

//! \brief classe per la rappresentazione di una singola spesa di un progetto
class Spesa : public Azione
{
 public:
	 //! \brief costruttore
	 //! \param[in] descrizione descrizione della spesa
	 //! \param[in] data data della spesa
	 //! \param[in] importo importo della spesa
	 //! \param[in] pagatore indice del pagatore della spesa
	 //! \param[in] partecipanti array degli indici dei partecipanti alla spesa
	 //! \param[in] numero_partecipanti numero dei partecipanti alla spesa
	 //! \note gli indici riferiscono l'array dei partecipanti al progetto
	 Spesa(const char descrizione[], Date data, float importo, unsigned int pagatore, unsigned int numero_partecipanti, unsigned int partecipanti[])
	 {
		 strncpy(this->descrizione, descrizione, 256);
		 this->data = data;
		 if (importo > 0)
			 this->importo = importo;
		 else
			 this->importo = 0;
		 this->numero_partecipanti = (numero_partecipanti > 5) ? 5 : numero_partecipanti;
		 this->pagatore = pagatore;
		 for (unsigned int index = 0; index < this->numero_partecipanti; index++)
			this->partecipanti[index] = partecipanti[index];
	 }
};

#endif
