#ifndef _EXPENSEMANAGER
#define _EXPENSEMANAGER

/*!
\file ExpenseManager.h
\brief definizione e implementazione della classe ExpenseManager
\author G. Meini
\version 1.0
\date 01/07/2021
*/

#include <cstring>
#include <cstdlib>
#include <cstdio>
#if defined(_WIN32) || defined(_WIN64)
#include "dirent.h"
#else
#include <dirent.h>
#endif
#include "Progetto.h"


/*!
\brief classe di metodi statici per la gestione dei progetti memorizzati su file
*/
class ExpenseManager
{
public:
	
	/*! \brief elenco dei nomi dei progetti
		\param[out] elenco vettore di puntatori alle stringhe dei nomi dei progetti
		\param[in] numero_massimo_progetti dimensione del vettore
		\return numero di progetti
		\note la memoria per la memorizzazione dei nomi dei progetti e' allocata dal codice che invoca il metodo
	*/
	static unsigned int elencaProgetti(unsigned int numero_massimo_progetti, char* elenco[])
	{
		DIR *directory;
		struct dirent *file;
		unsigned int numero_progetti = 0;
#if defined(_WIN32) || defined(_WIN64)	
		if ((directory = opendir(".\\progetti")) != NULL)	
#else
		if ((directory = opendir("./progetti")) != NULL)
#endif
		  {
			while ((file = readdir(directory))!=NULL && numero_progetti<numero_massimo_progetti)
			     {
					if (file->d_type == DT_REG)
					   {
						 strncpy(elenco[numero_progetti], file->d_name, 63);
						 numero_progetti++;
					   }
				 }
			closedir(directory);
		   }
		return numero_progetti;
	}

	/*! \brief selezione di un progetto esistente
		\param[in] denominazione nome del progetto da selezionare
		\return puntatore ad un'istanza del progetto selezionato (nullptr in caso di errore)
		\note la memoria allocata per il progetto dovrebbe essere liberata prima di riutilizzare il puntatore
	*/
	static Progetto* selezionaProgetto(const char denominazione[])
	{
#if defined(_WIN32) || defined(_WIN64)
		char nome_file[1024] = ".\\progetti\\";
#else
		char nome_file[1024] = "progetti/";
#endif
		FILE* file;

	strcat(nome_file, denominazione);
		file = fopen(nome_file, "rb");
		if (file == NULL)
		  {
			  return nullptr; // file di progetto inesistente
		  }
		else
		    {
			    fclose(file);
				return new Progetto(denominazione);
		    }
	}

	/*! \brief creazione di un nuovo progetto
		\param[in] denominazione nome del progetto da creare
		\param[in] partecipanti nomi dei partecipanti al progetto (array di stinghe)
		\return puntatore ad un'istanza del progetto creato (nullptr in caso di errore)
		\note la memoria allocata per il progetto dovrebbe essere liberata prima di riutilizzare il puntatore
		\note il numero dei partecipanti al progetto e' dato dal numero di stringhe non nulle e non vuote nelle posizioni iniziali dell'array dei partecipanti (massimo 5)
	*/
	static Progetto* creaProgetto(const char denominazione[], char* partecipanti[])
	{
#if defined(_WIN32) || defined(_WIN64)
		char nome_file[1024] = ".\\progetti\\";
#else
		char nome_file[1024] = "./progetti/";
#endif
		FILE* file;

		strcat(nome_file, denominazione);
		file = fopen(nome_file, "rb");
		if (file != NULL)
		{
			fclose(file);
			return nullptr; // file di progetto esistente
		}
		else
		{
			return new Progetto(denominazione, partecipanti);
		}
	}

	/*! \brief eliminazione di un nuovo progetto esistente
		\param[in] denominazione nome del progetto da creare
		\retval VERO progetto eliminato
		\retval FALSO progetto non eliminato
	*/
	static bool eliminaProgetto(char denominazione[])
	{
#if defined(_WIN32) || defined(_WIN64)
		char nome_file[1024] = ".\\progetti\\";
#else
		char nome_file[1024] = "./progetti/";
#endif

		strcat(nome_file, denominazione);
		if (remove(nome_file) == 0)
			return true;
		else
			return false;
	}
};

#endif
