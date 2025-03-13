/*!
\file main.cpp
\brief programma principale dell'applicazione ExpenseManager
\author G. Meini
\version 1.0
\date 01/07/2021
\note realizza un'interfaccia non grafica per l'utente dell'applicazione
*/

#include <iostream>
#include <string>

#include "ExpenseManager.h"

using namespace std;

//! \brief costante che rappresenta il numero massimo di progetti gestiti dall'applicazione
const unsigned int NUMERO_MASSIMO_PROGETTI = 16;



//! \fn main
//! \brief main method
int main(void)
{
	//! \brief vettore dei nomi dei progetti
	char *progetti[NUMERO_MASSIMO_PROGETTI];
	//! \brief vettore delle azioni selezionate dal progetto attivo
	Azione* azioni[NUMERO_MASSIMO_AZIONI_PROGETTO];
	//! \brief puntatore ad un'istanza del progetto attivo
	Progetto *progetto = nullptr;
	//! numero di nomi di progetti presenti nel vettore progetti
	unsigned int numero_progetti = 0;
	//! numero di azioni presenti nel vettore azioni
	unsigned int numero_azioni = 0;
	//! indicatore di validita' del contenuto del vettore progetti
	bool vettore_progetti_valido = false;
	//! indicatore di validità del contenuto del vettore azioni
	bool vettore_azioni_valido = false;

	char nome_progetto[256], descrizione_azione[256], nome_file[1024];
	unsigned int indice_progetto, indice_azione, numero_partecipanti, pagatore, partecipante;
	int comando, giorno, mese, anno;
	Date data;
	const char* descrizione;
	char tipo_file;
	char* nomi_partecipanti[5];
	float importo;
	unsigned int partecipanti[5];
	SALDO saldi[5];
	string tmp;

	// allocazione memoria per vettore dei nomi dei progetti
	for (unsigned int _i=0; _i<NUMERO_MASSIMO_PROGETTI; _i++)
	   progetti[_i] = new char[1024];
	
	// ciclo di funzionamento dell'applicazione
	while (true)
	     {
#ifdef WIN32	 
			 system("CLS");
#else
			 system("clear");
#endif
			 if (progetto == nullptr)
			   {
				 // nessun progetto attivo: visualizzazione del menu' dei progetti
				 cout << "0:\tEsci" << endl;
				 cout << "1:\tElenco progetti" << endl;
				 cout << "2:\tNuovo progetto" << endl;
				 cout << "3:\tApri progetto" << endl;
				 cout << "4:\tElimina progetto" << endl;
				 cout << endl << "Comando? ";
				 cin >> comando;
				 // esecuzione comando digitato
				 switch (comando)
				       {
						case 0:	// uscita applicazione
								goto END;
						case 1:	// visualizzazione elenco progetti
								numero_progetti = ExpenseManager::elencaProgetti(NUMERO_MASSIMO_PROGETTI, progetti);
								if (numero_progetti == 0)
								  cout << "Nessun progetto" << endl;
								else
									{
										for (unsigned int _p = 0; _p < numero_progetti; _p++)
										   cout << "#" << _p + 1 << ":\t" << progetti[_p] << endl;
										vettore_progetti_valido = true;
									}
								break;
						case 2:	// creazione nuovo progetto
								cout << endl << "Nome progetto? ";
								cin >> nome_progetto;
								cout << "Numero partecipanti (1-5)?";
								cin >> numero_partecipanti;
								if (numero_partecipanti > 0 && numero_partecipanti <= 5)
								{
									nomi_partecipanti[0] = nullptr;
									nomi_partecipanti[1] = nullptr;
									nomi_partecipanti[2] = nullptr;
									nomi_partecipanti[3] = nullptr;
									nomi_partecipanti[4] = nullptr;
									for (unsigned int _p = 0; _p < numero_partecipanti; _p++)
									{
										cout << "Nome partecipante #" << _p << "?";
										cin >> tmp;
										nomi_partecipanti[_p] = new char[tmp.size() + 1];
										strcpy(nomi_partecipanti[_p], tmp.c_str());
									}
									if ((progetto = ExpenseManager::creaProgetto(nome_progetto, nomi_partecipanti)) != nullptr)
									{
										cout << "Progetto " << nome_progetto << " creato" << endl;
										vettore_progetti_valido = false;
									}
									else
										cout << "Errore creazione progetto " << nome_progetto << endl;
									for (unsigned int _p = 0; _p < numero_partecipanti; _p++)
										delete[] nomi_partecipanti[_p];
								}
								else
									cout << "Errore specificazione numero partecipanti" << endl;
								break;
						case 3:	// apertura progetto
								if (!vettore_progetti_valido)
								  {
									cout << "Visualizzare elenco progetti" << endl;
									break;
								  }
								cout << endl << "Numero progetto? ";
								cin >> indice_progetto;
								if (indice_progetto < 1 || indice_progetto > numero_progetti)
								  cout << "Progetto inesistente" << endl;
								else
									{
										strcpy(nome_progetto, progetti[indice_progetto - 1]);
										if ((progetto = ExpenseManager::selezionaProgetto(nome_progetto)) != nullptr)
										  cout << "Progetto " << nome_progetto << " aperto" << endl;
										else
											cout << "Errore apertura progetto " << nome_progetto << endl;
									}
								break;
						case 4:	// eliminazione progetto
								if (!vettore_progetti_valido)
								  {
									cout << "Visualizzare elenco progetti" << endl;
									break;
								  }
								cout << endl << "Numero progetto? ";
								cin >> indice_progetto;
								if (indice_progetto < 1 || indice_progetto > numero_progetti)
								  cout << "Progetto inesistente" << endl;
								else
									{
									 strcpy(nome_progetto, progetti[indice_progetto - 1]);
									 if (ExpenseManager::eliminaProgetto(nome_progetto))
									   {
										cout << "Progetto " << nome_progetto << " eliminato" << endl;
										vettore_progetti_valido = false;
									   }
									else
										cout << "Errore eliminazione progetto " << nome_progetto << endl;
								   }
								break;
						default:
								cout << "Comando errato" << endl;
								break;
					 }
			   }
			 else
				 {
					 // progetto attivo: visualizzazione del menu' delle attivita'
					 cout << "0:\tChiudi progetto" << endl;
					 cout << "1:\tElenco partecipanti" << endl;
					 cout << "2:\tElenco spese/trasferimenti" << endl;
					 cout << "3:\tElenco spese/trasferimenti pagatore" << endl;
					 cout << "4:\tElenco spese/trasferimenti partecipante" << endl;
					 cout << "5:\tEsporta elenco spese/trasferimenti" << endl;
					 cout << "6:\tEsporta elenco spese/trasferimenti pagatore" << endl;
					 cout << "7:\tEsporta elenco spese/trasferimenti partecipante" << endl;
					 cout << "8:\tAggiungi spesa" << endl;
					 cout << "9:\tAggiungi trasferimento" << endl;
					 cout << "10:\tAggiorna spesa/trasferimento" << endl;
					 cout << "11:\tElimina spesa/trasferimento" << endl;
					 cout << "12:\tSaldi partecipanti" << endl;
					 cout << endl << "Comando? ";
					 cin >> comando;
					 // esecuzione comando digitato
					 switch (comando)
						   {
							case 0:		// chiusura progetto
										delete progetto;
										progetto = nullptr;
										vettore_azioni_valido = false;
										break;
							case 1:		// visualizzazione partecipanti
										for (unsigned int _i = 0; _i < 5; _i++)
											nomi_partecipanti[_i] = new char[64];
										numero_partecipanti = progetto->getPartecipanti(nomi_partecipanti);
										for (unsigned int _p = 0; _p < numero_partecipanti; _p++)
										   cout << "#" << _p + 1 << " " << nomi_partecipanti[_p] << endl;
										for (unsigned int _i = 0; _i < 5; _i++)
										   delete[] nomi_partecipanti[_i];
										break;
							case 2:		// visualizzazione elenco spese/trasferimenti
										numero_azioni = progetto->elencaAzioni(azioni);
										if (numero_azioni == 0)
											cout << "Nessuna azione" << endl;
										else
											{
												for (unsigned int _a = 0; _a < numero_azioni; _a++)
												   {
													azioni[_a]->getDescrizione(descrizione_azione);
													cout << "#" << _a + 1 << " " << descrizione_azione << " " << azioni[_a]->getImporto() << " " << azioni[_a]->getData().getDay() << "-" << azioni[_a]->getData().getMonth() << "-" << azioni[_a]->getData().getYear() << " pagatore: " << azioni[_a]->getPagatore() << " " << azioni[_a]->getNumeroPartecipanti() << " partecipanti/destinatari" << endl;
												   }
												vettore_azioni_valido = true;
											}
										break;
							 case 3:	// visualizzazione elenco spese/trasferimenti per pagatore
										cout << endl << "Indice pagatore: ";
										cin >> pagatore;
										numero_azioni = progetto->elencaAzioniPagatore(pagatore - 1, azioni);
										if (numero_azioni == 0)
										  cout << "Nessuna azione con numero pagatore " << pagatore << endl;
										else
											{
												for (unsigned int _a = 0; _a < numero_azioni; _a++)
												{
													azioni[_a]->getDescrizione(descrizione_azione);
													cout << "#" << _a + 1 << " " << descrizione_azione << " " << azioni[_a]->getImporto() << " " << azioni[_a]->getData().getDay() << "-" << azioni[_a]->getData().getMonth() << "-" << azioni[_a]->getData().getYear() << " pagatore: " << azioni[_a]->getPagatore() << "\t" << azioni[_a]->getNumeroPartecipanti() << " partecipanti" << endl;
												}
												vettore_azioni_valido = false;
											}
										break;
							 case 4:	// visualizzazione elenco spese/trasferimenti per partecipante/destinatario
										cout << endl << "Indice partecipante/destinatario: ";
										cin >> partecipante;
										numero_azioni = progetto->elencaAzioniPartecipante(partecipante - 1, azioni);
										if (numero_azioni == 0)
											cout << "Nessuna azione con indice partecipante/destinatario " << partecipante << endl;
										else
											{
												for (unsigned int _a = 0; _a < numero_azioni; _a++)
												{
													azioni[_a]->getDescrizione(descrizione_azione);
													cout << "#" << _a + 1 << " " << descrizione_azione << " " << azioni[_a]->getImporto() << " " << azioni[_a]->getData().getDay() << "-" << azioni[_a]->getData().getMonth() << "-" << azioni[_a]->getData().getYear() << " pagatore: " << azioni[_a]->getPagatore() << " " << azioni[_a]->getNumeroPartecipanti() << " partecipanti/destinatari" << endl;
												}
												vettore_azioni_valido = false;
											}
										break;
							case 5:		// esportazione su file elenco spese/trasferimenti
										cout << endl << "Tipo del file (C per CSV, H per HTML)? ";
										cin >> tipo_file;
										if (tipo_file != 'C' && tipo_file != 'H' && tipo_file != 'c' && tipo_file != 'h')
											cout << "Tipo file errato" << endl;
										else
											{
												cout << endl << "Nome del file? ";
												cin >> nome_file;
												if (progetto->esportaAzioniSuFile(((tipo_file == 'H' || tipo_file == 'h') ? HTML : CSV), nome_file))
												  cout << "File " << nome_file << " generato" << endl;
												else
												    cout << "Errore generazione file " << nome_file << endl;
											}
										break;
							case 6:		// esportazione su file elenco spese/trasferimenti per pagatore
										cout << endl << "Tipo del file (C per CSV, H per HTML)? ";
										cin >> tipo_file;
										if (tipo_file != 'C' && tipo_file != 'H' && tipo_file != 'c' && tipo_file != 'h')
										  cout << "Tipo file errato" << endl;
										else
											{
											 cout << endl << "Indice pagatore: ";
											 cin >> pagatore;
											 cout << endl << "Nome del file? ";
											 cin >> nome_file;
											 if (progetto->esportaAzioniPagatoreSuFile(((tipo_file == 'H' || tipo_file == 'h') ? HTML : CSV), nome_file, pagatore - 1))
											   cout << "File " << nome_file << " generato" << endl;
											 else
												 cout << "Errore generazione file " << nome_file << endl;
											}
										break;
							case 7:		// esportazione su file elenco spese/trasferimenti per partecipante/destinatario
										cout << endl << "Tipo del file (C per CSV, H per HTML)? ";
										cin >> tipo_file;
										if (tipo_file != 'C' && tipo_file != 'H' && tipo_file != 'c' && tipo_file != 'h')
										  cout << "Tipo file errato" << endl;
										else
											{
												cout << endl << "Indice partecipante/destinatario: ";
												cin >> partecipante;
												cout << endl << "Nome del file? ";
												cin >> nome_file;
												if (progetto->esportaAzioniPartecipanteSuFile(((tipo_file == 'H' || tipo_file == 'h') ? HTML : CSV), nome_file, partecipante - 1))
												  cout << "File " << nome_file << " generato" << endl;
												else
													cout << "Errore generazione file " << nome_file << endl;
											}
										break;
							case 8:		// aggiunta nuova spesa al progetto
										cout << endl << "Data:" << endl;
										cout << endl << "Giorno? "; cin >> giorno;
										cout << "Mese? "; cin >> mese;
										cout << "Anno? "; cin >> anno;
										data.setDate(giorno, mese, anno);
										cout << endl << "Descrizione della spesa? ";
										getline(cin, tmp); // ?
										getline(cin, tmp);
										descrizione = tmp.c_str();
										cout << endl << "Importo della spesa? ";
										cin >> importo;
										cout << endl << "Indice pagatore? ";
										cin >> pagatore;
										cout << endl << "Numero partecipanti? ";
										cin >> numero_partecipanti;
										for (unsigned int _i = 0; _i < 5; _i++)
											nomi_partecipanti[_i] = new char[64];
										if (numero_partecipanti > 0 && numero_partecipanti <= progetto->getPartecipanti(nomi_partecipanti))
										{
											for (unsigned int _p = 0; _p < numero_partecipanti; _p++)
											{
												cout << "Indice partecipante: ";
												cin >> partecipante;
												partecipanti[_p] = partecipante - 1;
											}
											Spesa spesa = Spesa(descrizione, data, importo, pagatore - 1, numero_partecipanti, partecipanti);
											if (progetto->nuovaSpesa(spesa))
											{
												cout << "Azione aggiunta al progetto" << endl;
												vettore_azioni_valido = false;
											}
											else
												cout << "Errore aggiunta azione al progetto" << endl;
										}
										else
											cout << "Numero partecipanti errato" << endl;
										for (unsigned int _i = 0; _i < 5; _i++)
											delete[] nomi_partecipanti[_i];
										break;
							case 9:		// aggiunta nuovo trasferimento al progetto
										cout << endl << "Data:" << endl;
										cout << endl << "Giorno? "; cin >> giorno;
										cout << "Mese? "; cin >> mese;
										cout << "Anno? "; cin >> anno;
										data.setDate(giorno, mese, anno);
										cout << endl << "Descrizione del trasferimento? ";
										getline(cin, tmp); // ?
										getline(cin, tmp);
										descrizione = tmp.c_str();
										cout << endl << "Importo del trasferimento? ";
										cin >> importo;
										cout << endl << "Indice pagatore? ";
										cin >> pagatore;
										cout << endl << "Numero destinatari? ";
										cin >> numero_partecipanti;
										for (unsigned int _i = 0; _i < 5; _i++)
											nomi_partecipanti[_i] = new char[64];
										if (numero_partecipanti > 0 && numero_partecipanti <= progetto->getPartecipanti(nomi_partecipanti))
										{
											for (unsigned int _p = 0; _p < numero_partecipanti; _p++)
											{
												cout << "Indice destinatario: ";
												cin >> partecipante;
												partecipanti[_p] = partecipante - 1;
											}
											Trasferimento trasferimento = Trasferimento(descrizione, data, importo, pagatore - 1, numero_partecipanti, partecipanti);
											if (progetto->nuovoTrasferimento(trasferimento))
											{
												cout << "Azione aggiunta al progetto" << endl;
												vettore_azioni_valido = false;
											}
											else
												cout << "Errore aggiunta azione al progetto" << endl;
										}
										else
											cout << "Numero destinatari errato" << endl;
										for (unsigned int _i = 0; _i < 5; _i++)
											delete[] nomi_partecipanti[_i];
										break;
							case 10:	// aggiornamento spesa/trasferimento
										if (!vettore_azioni_valido)
										{
											cout << "Visualizzare elenco azioni" << endl;
											break;
										}
										cout << endl << "Indice dell'azione? ";
										cin >> indice_azione;
										if (indice_azione < 1 || indice_azione > numero_azioni)
											cout << "Azione inesistente" << endl;
										else
											{
												cout << endl << "Data:" << endl;
												cout << endl << "Giorno? "; cin >> giorno;
												cout << "Mese? "; cin >> mese;
												cout << "Anno? "; cin >> anno;
												data.setDate(giorno, mese, anno);
												cout << endl << "Descrizione del trasferimento? ";
												getline(cin, tmp); // ?
												getline(cin, tmp);
												descrizione = tmp.c_str();
												cout << endl << "Importo del trasferimento? ";
												cin >> importo;
												cout << endl << "Indice pagatore? ";
												cin >> pagatore;
												cout << endl << "Numero partecipanti/destinatari? ";
												cin >> numero_partecipanti;
												for (unsigned int _i = 0; _i < 5; _i++)
													nomi_partecipanti[_i] = new char[64];
												if (numero_partecipanti > 0 && numero_partecipanti <= progetto->getPartecipanti(nomi_partecipanti))
												{
													for (unsigned int _p = 0; _p < numero_partecipanti; _p++)
													{
														cout << "Indice partecipante/destinatario: ";
														cin >> partecipante;
														partecipanti[_p] = partecipante - 1;
													}
													if (dynamic_cast<Spesa*>(azioni[indice_azione - 1]))
													{
														Spesa spesa = Spesa(descrizione, data, importo, pagatore - 1, numero_partecipanti, partecipanti);
														if (progetto->aggiornaAzione(indice_azione - 1, &spesa))
															cout << "Spesa aggiornata" << endl;
														else
															cout << "Errore aggiornamento spesa" << endl;
													}
													else
													{
														Trasferimento trasferimento = Trasferimento(descrizione, data, importo, pagatore - 1, numero_partecipanti, partecipanti);
														if (progetto->aggiornaAzione(indice_azione - 1, &trasferimento))
															cout << "Trasferimento aggiornato" << endl;
														else
															cout << "Errore aggiornamento trasferimento" << endl;
													}
												}
												else
													cout << "Numero partecipanti/destinatari errato" << endl;
												for (unsigned int _i = 0; _i < 5; _i++)
													nomi_partecipanti[_i] = new char[64];
											}
										break;
							case 11:	// eliminazione azione
										if (!vettore_azioni_valido)
										  {
											cout << "Visualizzare elenco azioni" << endl;
											break;
										  }
										cout << endl << "Indice dell'azione? ";
										cin >> indice_azione;
										if (indice_azione < 1 || indice_azione > numero_azioni)
										  cout << "Azione inesistente" << endl;
										else
											{
											 if (progetto->eliminaAzione(indice_azione - 1))
											   {
												 cout << "Azione eliminata dal progetto" << endl;
												 vettore_azioni_valido = false;
											   }
											 else
												 cout << "Errore eliminazione azione dal progetto" << endl;
											}
										break;
							case 12:	// saldi partecipanti
										numero_partecipanti = progetto->bilancio(saldi);
										for (unsigned int _p = 0; _p < numero_partecipanti; _p++)
											cout << saldi[_p].partecipante << ": " << saldi[_p].saldo << endl;
										break;
							default:
										cout << "Comando errato" << endl;
										break;
						}
					 }
			cout << endl << "Premere <INVIO> per continuare...";
			cin.get(); cin.get();
		}

END:
	if (progetto != nullptr)
	  delete progetto;
	for (unsigned int _i=0; _i<NUMERO_MASSIMO_PROGETTI; _i++)
		delete[] progetti[_i];
	return 0;
}
