/*!
\file Progetto.cpp
\brief implementazione della classe Progetto
\author G. Meini
\version 1.0
\date 01/07/2021
*/

#include "Progetto.h"

Azione::~Azione(void) {}

Progetto::Progetto(const char denominazione[], char* partecipanti[])
{
	FILE* file;
	FILEHEADER header;
	char nome_file[1024] = DIRECTORY_PROGETTI;

	numero_azioni = 0;
	// costruzione dell’array dei nomi dei partecipanti
	for (numero_partecipanti = 0; numero_partecipanti < 5; numero_partecipanti++)
		if (partecipanti[numero_partecipanti] != NULL)
		{
			if (strlen(partecipanti[numero_partecipanti]) > 0)
				strncpy(this->partecipanti[numero_partecipanti], partecipanti[numero_partecipanti], 64);
			else
				break;
		}
		else
			break;
	// creazione del file e scrittura dello header  
	if (numero_partecipanti > 0)
	{
		strncat(nome_file, denominazione, 256);
		file = fopen(nome_file, "wb");
		header.numero_partecipanti = numero_partecipanti;
		for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
			strncpy(header.partecipanti[indice], this->partecipanti[indice], 64);
		fwrite(&header, sizeof(FILEHEADER), 1, file);
		fclose(file);
	}
	strncpy(this->denominazione, denominazione, 256);
}

Progetto::Progetto(const char denominazione[])
{
	FILE* file;
	FILERECORD record;
	FILEHEADER header;
	Date data;
	char nome_file[1024] = DIRECTORY_PROGETTI;

	numero_azioni = 0;
	strncat(nome_file, denominazione, 256);
	file = fopen(nome_file, "rb");
	// apertura del file e lettura dello header  
	if (file != NULL)
	{
		if (fread(&header, sizeof(FILEHEADER), 1, file) == 1)
		{
			numero_partecipanti = (unsigned int)header.numero_partecipanti;
			for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
				strncpy(partecipanti[indice], header.partecipanti[indice], 64);
			// lettura dei record dal file e generazione delle spese/trasferimenti
			while (!feof(file) && numero_azioni < NUMERO_MASSIMO_AZIONI_PROGETTO)
			{
				if (fread(&record, sizeof(FILERECORD), 1, file) == 1)
				{
					// costruzione dell’array degli indici dei partecipanti alla
					// spesa/trasferimento
					unsigned int partecipanti[5];
					for (unsigned short indice = 0; indice < record.numero_partecipanti; indice++)
						partecipanti[indice] = (unsigned int)record.partecipanti[indice];
					if (record.importo >= 0)
					{
						// generazione spesa in caso di importo positivo
						data.setDate(record.giorno, record.mese, record.anno);
						azioni[numero_azioni] = new Spesa(record.descrizione, data, record.importo, (unsigned int)record.pagatore, (unsigned int)record.numero_partecipanti, partecipanti);
					}
					else
					{
						// generazione trasferimento in caso di importo negativo
						data.setDate(record.giorno, record.mese, record.anno);
						azioni[numero_azioni] = new Trasferimento(record.descrizione, data, -record.importo, (unsigned int)record.pagatore, (unsigned int)record.numero_partecipanti, partecipanti);
					}
					numero_azioni++;
				}
			}
		}
		fclose(file);
	}
	strncpy(this->denominazione, denominazione, 256);
}

Progetto::~Progetto(void)
{
	for (unsigned int indice = 0; indice < numero_azioni; indice++)
		delete azioni[indice];
}

void Progetto::getDenominazione(char* denominazione)
{
	strcpy(denominazione, this->denominazione);
}

unsigned int Progetto::getPartecipanti(char* partecipanti[])
{
	for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
		strncpy(partecipanti[indice], this->partecipanti[indice], 64);
	return numero_partecipanti;
}

unsigned int Progetto::getNumeroAzioni(void)
{
	return numero_azioni;
}

bool Progetto::nuovaSpesa(Spesa spesa)
{
	FILE* file;
	FILERECORD record;
	char descrizione[256];
	unsigned int numero_partecipanti;
	unsigned int partecipanti[5];
	char nome_file[1024] = DIRECTORY_PROGETTI;

	// controlli di correttezza della richiesta
	if (numero_azioni >= NUMERO_MASSIMO_AZIONI_PROGETTO)
		return false;
	numero_partecipanti = spesa.getPartecipanti(partecipanti);
	if (numero_partecipanti > this->numero_partecipanti)
		return false;
	if (spesa.getPagatore() > this->numero_partecipanti)
		return false;
	for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
		if (partecipanti[indice] > this->numero_partecipanti)
			return false;
	// aggiunta nuova spesa nell’array delle azioni del progetto
	spesa.getDescrizione(descrizione);
	azioni[numero_azioni] = new Spesa(descrizione, spesa.getData(), spesa.getImporto(), spesa.getPagatore(), spesa.getNumeroPartecipanti(), partecipanti);
	numero_azioni++;
	// aggiornamento file
	strcpy(record.descrizione, descrizione);
	record.giorno = spesa.getData().getDay();
	record.mese = spesa.getData().getMonth();
	record.anno = spesa.getData().getYear();
	record.importo = spesa.getImporto();
	record.pagatore = (unsigned short)spesa.getPagatore();
	for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
		record.partecipanti[indice] = (unsigned short)partecipanti[indice];
	record.numero_partecipanti = (unsigned short)numero_partecipanti;
	strncat(nome_file, denominazione, 256);
	file = fopen(nome_file, "ab");
	fwrite(&record, sizeof(FILERECORD), 1, file);
	fclose(file);
	return true;
}

bool Progetto::nuovoTrasferimento(Trasferimento trasferimento)
{
	FILE* file;
	FILERECORD record;
	char descrizione[256];
	unsigned int numero_partecipanti;
	unsigned int partecipanti[5];
	char nome_file[1024] = DIRECTORY_PROGETTI;

	// controlli di correttezza della richiesta
	if (numero_azioni >= NUMERO_MASSIMO_AZIONI_PROGETTO)
		return false;
	numero_partecipanti = trasferimento.getPartecipanti(partecipanti);
	if (numero_partecipanti > this->numero_partecipanti)
		return false;
	if (trasferimento.getPagatore() > this->numero_partecipanti)
		return false;
	for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
		if (partecipanti[indice] > this->numero_partecipanti)
			return false;
	// aggiunta nuovo trasferimento nell’array delle azioni del progetto
	trasferimento.getDescrizione(descrizione);
	azioni[numero_azioni] = new Trasferimento(descrizione, trasferimento.getData(), trasferimento.getImporto(), trasferimento.getPagatore(), trasferimento.getNumeroPartecipanti(), partecipanti);
	numero_azioni++;
	// aggiornamento file
	strcpy(record.descrizione, descrizione);
	record.giorno = trasferimento.getData().getDay();
	record.mese = trasferimento.getData().getMonth();
	record.anno = trasferimento.getData().getYear();
	record.importo = -trasferimento.getImporto();
	record.pagatore = (unsigned short)trasferimento.getPagatore();
	for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
		record.partecipanti[indice] = (unsigned short)partecipanti[indice];
	record.numero_partecipanti = (unsigned short)numero_partecipanti;
	strncat(nome_file, denominazione, 256);
	file = fopen(nome_file, "ab");
	fwrite(&record, sizeof(FILERECORD), 1, file);
	fclose(file);
	return true;
}

bool Progetto::eliminaAzione(unsigned int indice)
{
	FILE* file;
	FILERECORD record;
	char descrizione[256];
	unsigned int partecipanti[5];
	char nome_file[1024] = DIRECTORY_PROGETTI;
	
	// eliminazione spesa/trasferimento dall’array delle azioni del progetto
	if (indice >= numero_azioni)
	  return false;
	delete azioni[indice];
	for (unsigned int _indice = indice + 1; _indice < numero_azioni; _indice++)
		azioni[_indice - 1] = azioni[_indice];
	numero_azioni--;
	// riscrittura completa dei record del file
	strncat(nome_file, denominazione, 256);
	file = fopen(nome_file, "r+");
	fseek(file, sizeof(FILEHEADER), SEEK_SET);
	for (unsigned int _indice = 0; _indice < numero_azioni; _indice++)
	{
		azioni[_indice]->getDescrizione(descrizione);
		strncpy(record.descrizione, descrizione, 256);
		record.giorno = azioni[_indice]->getData().getDay();
		record.mese = azioni[_indice]->getData().getMonth();
		record.anno = azioni[_indice]->getData().getYear();
		// definizione del segno dell’importo in base al tipo di azione
		if (dynamic_cast<Spesa*>(azioni[_indice]))
			record.importo = azioni[_indice]->getImporto();
		else
			record.importo = -azioni[_indice]->getImporto();
		record.pagatore = (unsigned short)azioni[_indice]->getPagatore();
		record.numero_partecipanti = (unsigned short)azioni[_indice]->getPartecipanti(partecipanti);
		for (unsigned int __indice = 0; __indice < record.numero_partecipanti; __indice++)
			record.partecipanti[__indice] = (unsigned short)partecipanti[__indice];
		fwrite(&record, sizeof(FILERECORD), 1, file);
	}
	fclose(file);
	return true;
}

bool Progetto::aggiornaAzione(unsigned int indice, Azione* azione)
{
	FILE* file;
	FILERECORD record;
	char descrizione[256];
	unsigned int partecipanti[5];
	unsigned int numero_partecipanti;
	char nome_file[1024] = DIRECTORY_PROGETTI; 
	
	if (indice >= numero_azioni)
		return false;
	numero_partecipanti = azione->getPartecipanti(partecipanti);
	if (numero_partecipanti > this->numero_partecipanti)
		return false;
	if (azione->getPagatore() > this->numero_partecipanti)
		return false;
	for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
		if (partecipanti[indice] > this->numero_partecipanti)
			return false;
	azione->getDescrizione(descrizione);
	delete azioni[indice];
	if (dynamic_cast<Spesa*>(azione))
		azioni[indice] = new Spesa(descrizione, azione->getData(), azione->getImporto(), azione->getPagatore(), azione->getNumeroPartecipanti(), partecipanti);
	else
		azioni[indice] = new Trasferimento(descrizione, azione->getData(), azione->getImporto(), azione->getPagatore(), azione->getNumeroPartecipanti(), partecipanti);
	// aggiornamento file
	strncpy(record.descrizione, descrizione, 256);
	record.giorno = azioni[indice]->getData().getDay();
	record.mese = azioni[indice]->getData().getMonth();
	record.anno = azioni[indice]->getData().getYear();
	if (dynamic_cast<Spesa*>(azioni[indice]))
		record.importo = azioni[indice]->getImporto();
	else
		record.importo = -azioni[indice]->getImporto();
	record.pagatore = (unsigned short)azioni[indice]->getPagatore();
	record.numero_partecipanti = (unsigned short)azioni[indice]->getPartecipanti(partecipanti);
	for (unsigned int _indice = 0; _indice < record.numero_partecipanti; _indice++)
		record.partecipanti[_indice] = (unsigned short)partecipanti[_indice];
	strncat(nome_file, denominazione, 256);
	file = fopen(nome_file, "r+");
	fseek(file, sizeof(FILEHEADER)+indice*sizeof(FILERECORD), SEEK_SET);
	fwrite(&record, sizeof(FILERECORD), 1, file);
	fclose(file);
	return true;
}


unsigned int Progetto::elencaAzioni(Azione* elenco[])
{
	for (unsigned int indice = 0; indice < numero_azioni; indice++)
		elenco[indice] = azioni[indice];
	return numero_azioni;
}

unsigned int Progetto::elencaAzioniPagatore(unsigned int pagatore, Azione* elenco[])
{
	unsigned int conteggio = 0;

	for (unsigned int indice = 0; indice < numero_azioni; indice++)
		if (azioni[indice]->getPagatore() == pagatore)
		{
		 elenco[conteggio] = azioni[indice];
		 conteggio++;
		}	
	return conteggio;
}

unsigned int Progetto::elencaAzioniPartecipante(unsigned int partecipante, Azione* elenco[])
{
	unsigned int conteggio = 0;

	for (unsigned int indice = 0; indice < numero_azioni; indice++)
	{
		unsigned int partecipanti[5];
		unsigned int numero_partecipanti;
		numero_partecipanti = azioni[indice]->getPartecipanti(partecipanti);
		for (unsigned int _indice = 0; _indice < numero_partecipanti; _indice++)
			if (partecipanti[_indice] == partecipante)
			{
				elenco[conteggio] = azioni[indice];
				conteggio++;
			}
	}
	return conteggio;
}


static void writeHTMLheader(FILE* file, char progetto[])
{
	fprintf(file, "<!DOCTYPE HTML>\r\n");
	fprintf(file, "<html>\r\n");
	fprintf(file, "<head>\r\n");
	fprintf(file, "<title>Elenco azioni progetto %s</title>\r\n", progetto);
	fprintf(file, "</head>\r\n");
	fprintf(file, "<body>\r\n");
	fprintf(file, "<table border>\r\n");
	fprintf(file, "<caption><h1>Elenco azioni progetto %s</h1></caption>\r\n", progetto);
	fprintf(file, "<thead>\r\n<tr>\r\n<th>Tipo</th><th>Descrizione</th><th>Importo</th><th>Data</th><th>Pagatore</th><th>Partecipanti</th>\r\n</tr>\r\n</thead>\r\n");
	fprintf(file, "<tbody>\r\n");
}

static void writeHTMLfooter(FILE* file)
{
	fprintf(file, "</tbody>\r\n");
	fprintf(file, "</table>\r\n");
	fprintf(file, "</body>\r\n");
	fprintf(file, "</html>\r\n");
}

bool Progetto::esportaAzioniSuFile(FILETYPE tipo_file, const char nome_file[])
{
	FILE* file;
	char descrizione[256];
	char nome_file_completo[1024];
		
	switch (tipo_file)
	{
	case CSV:
		sprintf(nome_file_completo, "%s.csv", nome_file);
		file = fopen(nome_file_completo, "wt");
		if (file == NULL)
			return false;
		for (unsigned int indice = 0; indice < numero_azioni; indice++)
		{
			unsigned int partecipanti[5];
			unsigned int numero_partecipanti;
			azioni[indice]->getDescrizione(descrizione);
			numero_partecipanti = azioni[indice]->getPartecipanti(partecipanti);
			if (dynamic_cast<Spesa*>(azioni[indice]))
				fprintf(file, "S,");
			else
				fprintf(file, "T,");
			fprintf(file, "%s,%.02f,%u,%u,%u,%s,%u", descrizione,
					azioni[indice]->getImporto(),
					azioni[indice]->getData().getDay(),
					azioni[indice]->getData().getMonth(),
					azioni[indice]->getData().getYear(),
					this->partecipanti[azioni[indice]->getPagatore()],
					azioni[indice]->getNumeroPartecipanti());
			for (unsigned int _indice = 0; _indice < numero_partecipanti; _indice++)
				fprintf(file, ",%s", this->partecipanti[partecipanti[_indice]]);
			fprintf(file, "\r\n");
		}
		fclose(file);
		return true;

	case HTML:
		strncpy(nome_file_completo, nome_file, sizeof(nome_file_completo) - 1);
		strcat(nome_file_completo, ".html");
		file = fopen(nome_file_completo, "wt");
		if (file == NULL)
			return false;
		writeHTMLheader(file, this->denominazione);
		for (unsigned int indice = 0; indice < numero_azioni; indice++)
		{
			unsigned int partecipanti[5];
			unsigned int numero_partecipanti;
			azioni[indice]->getDescrizione(descrizione);
			numero_partecipanti = azioni[indice]->getPartecipanti(partecipanti);
			fprintf(file, "<tr>\r\n");
			if (dynamic_cast<Spesa*>(azioni[indice]))
				fprintf(file, "<td>Spesa</td>");
			else
				fprintf(file, "<td>Trasferimento</td>");
			fprintf(file, "<td>%s</td><td>%.02f&euro;</td><td>%u-%u-%u</td><td>%s</td><td>", descrizione,
																					azioni[indice]->getImporto(),
																					azioni[indice]->getData().getDay(),
																					azioni[indice]->getData().getMonth(),
																					azioni[indice]->getData().getYear(),
																					this->partecipanti[azioni[indice]->getPagatore()]);
			for (unsigned int _indice = 0; _indice < numero_partecipanti; _indice++)
			   fprintf(file, "%s ", this->partecipanti[partecipanti[_indice]]);
			fprintf(file, "</td></tr>\r\n");
		}
		writeHTMLfooter(file);
		fclose(file);
		return true;

	default:	return false;
	}

}

bool Progetto::esportaAzioniPagatoreSuFile(FILETYPE tipo_file, const char nome_file[], unsigned int pagatore)
{
	FILE* file;
	char descrizione[256];
	char nome_file_completo[1024];

	switch (tipo_file)
	{
	case CSV:
		sprintf(nome_file_completo, "%s.csv", nome_file);
		file = fopen(nome_file_completo, "wt");
		if (file == NULL)
			return false;
		for (unsigned int indice = 0; indice < numero_azioni; indice++)
		{
			if (azioni[indice]->getPagatore() == pagatore)
			{
				unsigned int partecipanti[5];
				unsigned int numero_partecipanti;
				azioni[indice]->getDescrizione(descrizione);
				numero_partecipanti = azioni[indice]->getPartecipanti(partecipanti);
				if (dynamic_cast<Spesa*>(azioni[indice]))
					fprintf(file, "S,");
				else
					fprintf(file, "T,");
				fprintf(file, "%s,%f,%u,%u,%u,%s,%u", descrizione,
					azioni[indice]->getImporto(),
					azioni[indice]->getData().getDay(),
					azioni[indice]->getData().getMonth(),
					azioni[indice]->getData().getYear(),
					this->partecipanti[azioni[indice]->getPagatore()],
					azioni[indice]->getNumeroPartecipanti());
				for (unsigned int _indice = 0; _indice < numero_partecipanti; _indice++)
					fprintf(file, ",%s", this->partecipanti[partecipanti[_indice]]);
				fprintf(file, "\r\n");
			}
		}
		fclose(file);
		return true;
	
	case HTML:
		strncpy(nome_file_completo, nome_file, sizeof(nome_file_completo) - 1);
		strcat(nome_file_completo, ".html");
		file = fopen(nome_file_completo, "wt");
		if (file == NULL)
			return false;
		writeHTMLheader(file, this->denominazione);
		for (unsigned int indice = 0; indice < numero_azioni; indice++)
		{
			if (azioni[indice]->getPagatore() == pagatore)
			{
				unsigned int partecipanti[5];
				unsigned int numero_partecipanti;
				azioni[indice]->getDescrizione(descrizione);
				numero_partecipanti = azioni[indice]->getPartecipanti(partecipanti);
				fprintf(file, "<tr>\r\n");
				if (dynamic_cast<Spesa*>(azioni[indice]))
					fprintf(file, "<td>Spesa</td>");
				else
					fprintf(file, "<td>Trasferimento</td>");
				fprintf(file, "<td>%s</td><td>%.02f&euro;</td><td>%u-%u-%u</td><td>%s</td><td>", descrizione,
					azioni[indice]->getImporto(),
					azioni[indice]->getData().getDay(),
					azioni[indice]->getData().getMonth(),
					azioni[indice]->getData().getYear(),
					this->partecipanti[azioni[indice]->getPagatore()]);
				for (unsigned int _indice = 0; _indice < numero_partecipanti; _indice++)
					fprintf(file, "%s ", this->partecipanti[partecipanti[_indice]]);
				fprintf(file, "</td></tr>\r\n");
			}
		}
		writeHTMLfooter(file);
		fclose(file);
		return true;

	default:	return false;
	}
}

bool Progetto::esportaAzioniPartecipanteSuFile(FILETYPE tipo_file, const char nome_file[], unsigned int partecipante)
{
	FILE* file;
	char descrizione[256];
	char nome_file_completo[1024];

	switch (tipo_file)
	{
	case CSV:
		sprintf(nome_file_completo, "%s.csv", nome_file);
		file = fopen(nome_file_completo, "wt");
		if (file == NULL)
			return false;
		for (unsigned int indice = 0; indice < numero_azioni; indice++)
		{
			unsigned int partecipanti[5];
			unsigned int numero_partecipanti;
			numero_partecipanti = azioni[indice]->getPartecipanti(partecipanti);
			for (unsigned int _indice=0; _indice<numero_partecipanti; _indice++)
				if (partecipanti[_indice] == partecipante)
				{
					azioni[indice]->getDescrizione(descrizione);
					if (dynamic_cast<Spesa*>(azioni[indice]))
						fprintf(file, "S,");
					else
						fprintf(file, "T,");
					fprintf(file, "%s,%f,%u,%u,%u,%s,%u", descrizione,
						azioni[indice]->getImporto(),
						azioni[indice]->getData().getDay(),
						azioni[indice]->getData().getMonth(),
						azioni[indice]->getData().getYear(),
						this->partecipanti[azioni[indice]->getPagatore()],
						azioni[indice]->getNumeroPartecipanti());
					for (unsigned int __indice = 0; __indice < numero_partecipanti; __indice++)
						fprintf(file, ",%s", this->partecipanti[partecipanti[__indice]]);
					fprintf(file, "\r\n");
				}
		}
		fclose(file);
		return true;

	case HTML:
		strncpy(nome_file_completo, nome_file, sizeof(nome_file_completo) - 1);
		strcat(nome_file_completo, ".html");
		file = fopen(nome_file_completo, "wt");
		if (file == NULL)
			return false;
		writeHTMLheader(file, this->denominazione);
		for (unsigned int indice = 0; indice < numero_azioni; indice++)
		{
			unsigned int partecipanti[5];
			unsigned int numero_partecipanti;
			numero_partecipanti = azioni[indice]->getPartecipanti(partecipanti);
			for (unsigned int _indice = 0; _indice < numero_partecipanti; _indice++)
				if (partecipanti[_indice] == partecipante)
				{
					azioni[indice]->getDescrizione(descrizione);
					fprintf(file, "<tr>\r\n");
					if (dynamic_cast<Spesa*>(azioni[indice]))
						fprintf(file, "<td>Spesa</td>");
					else
						fprintf(file, "<td>Trasferimento</td>");
					fprintf(file, "<td>%s</td><td>%.02f&euro;</td><td>%u-%u-%u</td><td>%s</td><td>", descrizione,
						azioni[indice]->getImporto(),
						azioni[indice]->getData().getDay(),
						azioni[indice]->getData().getMonth(),
						azioni[indice]->getData().getYear(),
						this->partecipanti[azioni[indice]->getPagatore()]);
					for (unsigned int __indice = 0; __indice < numero_partecipanti; __indice++)
						fprintf(file, "%s ", this->partecipanti[partecipanti[__indice]]);
					fprintf(file, "</td></tr>\r\n");
				}
		}
		writeHTMLfooter(file);
		fclose(file);
		return true;

	default:	return false;
	}
}

unsigned int Progetto::bilancio(SALDO saldo[5])
{
	for (unsigned int indice = 0; indice < numero_partecipanti; indice++)
	{
		strncpy(saldo[indice].partecipante, partecipanti[indice], 64);
		saldo[indice].saldo = 0;
	}

	for (unsigned int indice = 0; indice < numero_azioni; indice++)
	{
		unsigned int numero_partecipanti;
		unsigned int partecipanti[5];
		numero_partecipanti = azioni[indice]->getPartecipanti(partecipanti);
		saldo[azioni[indice]->getPagatore()].saldo -= azioni[indice]->getImporto();
		for (unsigned int _indice = 0; _indice < numero_partecipanti; _indice++)
			saldo[partecipanti[_indice]].saldo += azioni[indice]->getImporto() / numero_partecipanti;
	}
	return numero_partecipanti;
}
