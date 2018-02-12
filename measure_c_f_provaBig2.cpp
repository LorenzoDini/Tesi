//Questa è la versione che dovrebbe funzionare dopo tutti i test che ho fatto all'elba, con tutte le stampe di prova cancellate, più pulita. la versione "prova" invece ha tutte le stampe commentate da cui prenderle eventualmente.

/*
Le variabili in questione le prendo in questo modo, dall'inputfile:

nmeas=FlowTime (divisione intera=/) MeasEach, se ho capito bene il significato di queste. 
ncopy = NCopies
nconf=  va dedotto dall'output. Non è che sia prorio facile.... Si può contare le righe e dividere per il prodotto del numero totale massimo di tutti gli altri indici del loop. Alle brutte si può passare come input del programma.
nop= si conta da operators in qualche modo (magari contando le coppie di graffe), se non c'è scritto esplicito da qualche parte, cosa che non credo
nflav=3 semplice

*/

#include<iostream> 
#include<fstream>  
#include "math.h"
#include "stdio.h"
#include<cstring>
#include<sstream>
#include<cstdio>
using namespace std;

/*
//Questa routine è una prova (da compilare e provare per leggere tutti i parametri dall'input file, indipendentemente dal suo numero di righe
void read_par(int *meas, int *copy, int *conf, int *op) {
	
    ifstream in_par("input");	
    stringstream str_par;
    char *point; 	//La c-string non è che un vettore di caratteri che termina con null_character. Dunque così dovrei averla definita
    char next_char;
    int end=0; 	//variabile per capire quando sono a fondo riga per nop
    str_par << "MeasureSpinPol";

   //Devo fare un primo ciclo iniziale per MeasureSpinPol, perché è l'unica che prende una sola riga e non ha lo spazio davanti 
    do {
    	point[0]='\0';
	in_par.getline(point,1500);	//questo prende tutta la linea
    }
    //strcmp è una funzione di <cstring>, che compara carattere per carattere due c-string. Dunque converto str_par in una c-str mentre uso getline per leggere point, che viene messa già come una c-string, in base a quello che dice cplusplus.com
    while(strcmp(point,str_par.str().c_str()) != 0);

    str_par.str("NCopies");

    //sono all'inizio della riga sotto MeasureSpinPol
    do {
	point[0]='\0';	//Questa è veramente una roba tragica per cancellare una stringa. Sembra cancellata, ma la memoria rimane lì.
	in_par.ignore();	//salto il primo spazio della linea, perché sennò sballa tutto
    	in_par.getline(point,300,' ');	//Legge la prima parola
	if(strcmp(point,str_par.str().c_str()) != 0) in_par.ignore(1500,'\n');	// se non l'ha trovata va avanti fino alla fine della linea
    }
    while(strcmp(point,str_par.str().c_str()) != 0); 
    //All'uscita dal ciclo sono alla fine della parola dentro str_par

    in_par.ignore(1500,'=');
    in_par >> *(copy);
    in_par.ignore(1500,'\n'); 	//Vado avanti fino alla fine della riga, se serve (?)
    str_par.str("Operators");	//Questo dovrebbe settare la str_par alla stringa tra parentesi, cancellando il vecchio contenuto

    //Questo è il ciclo che uso per skippare, solo la prima volta è commentato
    //sono all'inizio della riga sotto il parametro che ho preso
    do {
	point[0]='\0';	
	in_par.ignore();	
    	in_par.getline(point,300,' ');	
	if(strcmp(point,str_par.str().c_str()) != 0) in_par.ignore(1500,'\n');	
    }
    while(strcmp(point,str_par.str().c_str()) != 0); 
    //All'uscita dal ciclo sono alla fine della parola dentro str_par

    //Conto gli operatori nel formato {(a,b),(c,d)}
    *(op)=0;
    while(end!=1) {
    	in_par.ignore(1500,')');	//ignora fino a chiusa tonda 
	*(op)++;			//aggiorna il conto degli operatori
	next_char=in_par.get();		//guardo qual'è il prossima carattere
	if(next_char=='}') end=1;	//se il carattere successivo è la parentesi graffa chiusa ho finito gli operatori
    }
    
    in_par.ignore(1500,'\n'); 	//Vado avanti fino alla fine della riga
    str_par.str("FlowTime");
    
    //sono all'inizio della riga sotto il parametro che ho preso
    do {
	point[0]='\0';	
	in_par.ignore();	
    	in_par.getline(point,300,' ');	
	if(strcmp(point,str_par.str().c_str()) != 0) in_par.ignore(1500,'\n');	
    }
    while(strcmp(point,str_par.str().c_str()) != 0); 
    //All'uscita dal ciclo sono alla fine della parola dentro str_par
	
    in_par.ignore(1500,'=');
    in_par >> *(meas);
    in_par.ignore(1500,'\n'); 	//Vado avanti fino alla fine della riga, se serve (?)
    str_par.str("MeasEach");	//Questo dovrebbe settare la str_par alla stringa tra parentesi, cancellando il vecchio contenuto

     //sono all'inizio della riga sotto il parametro che ho preso
    do {
	point[0]='\0';	
	in_par.ignore();	
    	in_par.getline(point,300,' ');	
	if(strcmp(point,str_par.str().c_str()) != 0) in_par.ignore(1500,'\n');	
    }
    while(strcmp(point,str_par.str().c_str()) != 0); 
    //All'uscita dal ciclo sono alla fine della parola dentro str_par

    //calcolo nmeas
    int each;
    int flow;
    in_par.ignore(1500,'=');
    in_par >> each;
    in_par.ignore(1500,'\n'); 	//Vado avanti fino alla fine della riga, se serve (?)
    flow=*(meas);
    *(meas)=*(meas)/each;

    in_par.close();	

    ifstream in_nconf("input");

    //conto le righe e calcolo nconf
    end=0;
    while(end!=1) {
    	in_nconf.ignore(1500,'\n');	
	*(conf)++;
	next_char=in_nconf.get();
	if(next_char==EOF) end=1;	//Se sono arrivato in fondo al file mi fermo
    }
    *(conf)=*(conf)/(3*(*(op))*2*flow*(*(copy)));
}
*/

//O uso questa routine semplice, cambiando via via lìinput_analisys, oppure provo ad usare l'altra che ho scritto, che non ha bisogno di file ulteriori ed è più elegante, anche se molto più difficile. FUNZIONA 
void read_par_analisys(int *nmeas, int *ncopy, int *nconf, int *nop) {
    ifstream in_par("input_analisys.txt");
    in_par.ignore(1600,'\n');
    in_par >> *(nmeas) >> *(ncopy) >> *(nconf) >> *(nop);
}
	
//tenativi di scrivere il super-indice e la routine per accederci. Tutte queste dovrebbero funzionare, perché ho provato a stampare i risultati dei vettori negli indici scelti e mi restituisce quelli che ha letto
int index_tens (int imeas, int nmeas, int icopy, int ncopy, int iconf, int nconf, int iop, int nop, int iflav, int nflav, int i_gauge) {
    int i;
    i=imeas+nmeas*(iop+nop*(iflav+nflav*(icopy+ncopy*(iconf+nconf*i_gauge))));
    return i;
}

int index_q (int imeas, int nmeas, int icopy, int ncopy, int iconf, int nconf, int i_gauge) {
    int i;
    i=imeas+nmeas*(icopy+ncopy*(iconf+nconf*i_gauge));
    return i;
}

int index_q_med (int imeas, int nmeas, int i_gauge) {
    int i;
    i=imeas+nmeas*i_gauge;
    return i;
}

int index_tens_med(int imeas, int nmeas, int iop, int nop, int iflav, int nflav, int i_gauge) {
    int i;
    i=imeas+nmeas*(iop+nop*(iflav+nflav*i_gauge));
    return i;
}

int index_c(int imeas, int nmeas, int iflav, int nflav, int i_gauge) {
    int i;
    i=imeas+nmeas*(iflav+nflav*i_gauge);
    return i;
}

int index_jack_c(int imeas, int nmeas, int iflav, int nflav, int iblock, int nblock, int i_gauge) {
    int i;
    i=imeas+nmeas*(iflav+nflav*(iblock+nblock*i_gauge));
    return i;
}

int index_jack_top(int imeas,int nmeas,int iblock,int nblock,int i_gauge){
    int i;
    i=imeas+nmeas*(iblock+nblock*i_gauge);
    return i;
}

int index_jack_tens(int imeas,int nmeas,int iblock,int nblock,int iop,int nop,int iflav,int nflav,int i_gauge){
    int i;
    i=imeas+nmeas*(iop+nop*(iflav+nflav*(iblock+nblock*i_gauge)));
    return i;
}

//Legge i risultati dal file pollo e riempie i vettori. Funziona, a parte il problema dopo l'ultima riga 
void read_output (float pl[], float q[], float q2[], float sigma_re[], float sigma_im[], float sigma_q_re[], float sigma_q_im[], int nmeas, int ncopy, int nconf, int nop, int nflav) {
    
    ifstream in_pollo("tot_pollo");	
    int imeas, icopy, iconf, iop, iflav, i_gauge;
    float plaq, top, top2, spinpol_re, spinpol_im, spin_dens_re, spin_dens_im;
    char next_char;

    //Il metodo eof dentro la classe ifstream ritorna true se ha raggiunto EOF. Tuttavia anche questo metodo dà il risultato analogo che avevo usato con la variabile end, anche se è decisamente più elegante
    while(!in_pollo.eof()) {
	//Devo leggere anche icopy e i_gauge, da quello che ho scritto
    	in_pollo >> iconf >> icopy >> imeas >> i_gauge >> iflav >> iop;
	iconf=iconf-1;	//perché parte da 1 mentre iconf come ogni indice voglio che parta da zero e che sia minore di nconf
	//Conversione da a (quello che leggo in pollo) a iop, che va da zero e nop-1 se sto facendo tutte le sigma possibili
	switch(iop) {
	    case 3: 
	    	iop=0;
		break;
	    case 5: 
	    	iop=1;
		break;
	    case 6: 
	    	iop=2;
		break;
	    case 9: 
	    	iop=3;
		break;
	    case 10: 
	    	iop=4;
		break;
	    case 12: 
	    	iop=5;
		break;
	}
	in_pollo.ignore(1600,'0');
	in_pollo >> plaq >> top >> top2 >> spin_dens_re >> spin_dens_im >> spinpol_re >> spinpol_im;
//Questo l'ho lasciato proprio per far andare il cursore sull'EOF. Tuttavia a quanto pare non lo raggiunge dopo l'ultimo carattere di spin_dens_im. Forse c'è un altro carattere prima di EOF? 
	next_char=in_pollo.get();	
	//Scrittura nei vettori
	pl[index_q(imeas,nmeas,icopy,ncopy,iconf,nconf,i_gauge)]=plaq;
	q[index_q(imeas,nmeas,icopy,ncopy,iconf,nconf,i_gauge)]=top;
	q2[index_q(imeas,nmeas,icopy,ncopy,iconf,nconf,i_gauge)]=top2;
	sigma_re[index_tens(imeas,nmeas,icopy,ncopy,iconf,nconf,iop,nop,iflav,nflav,i_gauge)]=spinpol_re;
	sigma_im[index_tens(imeas,nmeas,icopy,ncopy,iconf,nconf,iop,nop,iflav,nflav,i_gauge)]=spinpol_im;
	sigma_q_re[index_tens(imeas,nmeas,icopy,ncopy,iconf,nconf,iop,nop,iflav,nflav,i_gauge)]=spin_dens_re;
	sigma_q_im[index_tens(imeas,nmeas,icopy,ncopy,iconf,nconf,iop,nop,iflav,nflav,i_gauge)]=spin_dens_im;
/*
	//Prova per vedere se adesso legge bene
	cout << "Questo è quello che ho letto nella riga. Rispettivamente: iconf,icopy,imeas,i_gauge_i_flav,iop,plaq,q,q2,sigma_re,sigma_im,sigma_q_re,sigma_q_im" << endl;
	cout  << iconf << " " << icopy << " " << imeas << " " << i_gauge << " " << iflav << " " << iop << " " << plaq << " " << top << " " << top2 << " " << spinpol_re << " " << spinpol_im << " " << spin_dens_re << " " << spin_dens_im << endl;
	//Faccio una prova per vedere se ha riempito bene i vettori
	cout << "q2 nell'indice " << imeas << " " << icopy << " " << iconf << " " << i_gauge << endl;
	cout << q2[index_q(imeas,nmeas,icopy,ncopy,iconf,nconf,i_gauge)] << endl;
	cout << "spin_q_re nell'indice " << imeas << " " << icopy << " " << iconf << " " << iop << " " << iflav << " " <<  i_gauge << endl;
	cout << sigma_q_re[index_tens(imeas,nmeas,icopy,ncopy,iconf,nconf,iop,nop,iflav,nflav,i_gauge)] << endl;
*/
    }
}

//Calcola la media per le grandezze topologiche. FUNZIONA (attenzione alle ultime righe che ci sono i problemi dovuti al read_output)
void measure_mean_top(float top_med[], float top[], int nmeas, int ncopy, int nconf) {
    int copy_sum, conf_sum,imeas,i_gauge;

    //sommo su iconf e su icopy
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++)
	    for(copy_sum=0;copy_sum<ncopy;copy_sum++) 
		for(conf_sum=0;conf_sum<nconf;conf_sum++) 
		    top_med[index_q_med(imeas,nmeas,i_gauge)]+=top[index_q(imeas,nmeas,copy_sum,ncopy,conf_sum,nconf,i_gauge)];
		
    //normalizzazione della media
    for(i_gauge=0;i_gauge<2;i_gauge++) 
	for(imeas=0;imeas<nmeas;imeas++) 
	    top_med[index_q_med(imeas,nmeas,i_gauge)]=top_med[index_q_med(imeas,nmeas,i_gauge)]/(float(nconf*ncopy));
}

//Calcola la media per grandezze spinoriali. FUNZIONA (Attenzione alla stessa cosa di cui sopra)
void measure_mean_spin(float spin_med[], float spin[], int nmeas, int ncopy, int nconf, int nop, int nflav) {
    int copy_sum, conf_sum,imeas,i_gauge,iop,iflav;

    //sommo su iconf e su icopy
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++)
	    for(iop=0;iop<nop;iop++)
		for(iflav=0;iflav<nflav;iflav++)
		    for(copy_sum=0;copy_sum<ncopy;copy_sum++) 
			for(conf_sum=0;conf_sum<nconf;conf_sum++) 
			    spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]+=spin[index_tens(imeas,nmeas,copy_sum,ncopy,conf_sum,nconf,iop,nop,iflav,nflav,i_gauge)];

    //normalizzazione della media
    for(i_gauge=0;i_gauge<2;i_gauge++) 
	for(imeas=0;imeas<nmeas;imeas++)
	    for(iop=0;iop<nop;iop++)
		for(iflav=0;iflav<nflav;iflav++)
		    spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]=spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]/(float(nconf*ncopy));
}

//Due funzioni per calcolare la parte reale e immaginaria di C_f. FUNZIONA
void measure_c_re (float c[], float spin_q_re[], float spin_q_im[], float q2[], float spin_re[], float spin_im[], int nmeas, int nop, int nflav) {
    int imeas,iflav,i_gauge;

    for(imeas=0;imeas<nmeas;imeas++)
	for(iflav=0;iflav<nflav;iflav++)
	    for(i_gauge=0;i_gauge<2;i_gauge++){
		//formulazza nei miei appunti 
	    	c[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=((spin_q_re[index_tens_med(imeas,nmeas,3,nop,iflav,nflav,i_gauge)])*(spin_re[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)]) + (spin_q_im[index_tens_med(imeas,nmeas,3,nop,iflav,nflav,i_gauge)])*(spin_im[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)]))/((sqrt(q2[index_q_med(imeas,nmeas,i_gauge)])) * (pow(spin_re[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)],2) + pow(spin_im[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)],2)));
	    }
}	

//Funzione per calcolare la parte immaginaria di im. E' identica a quella sopra, quindi dovrebbe funzionare
void measure_c_im (float c[], float spin_q_re[], float spin_q_im[], float q2[], float spin_re[], float spin_im[], int nmeas, int nop, int nflav) {
    int imeas,iflav,i_gauge;

    for(imeas=0;imeas<nmeas;imeas++)
	for(iflav=0;iflav<nflav;iflav++)
	    for(i_gauge=0;i_gauge<2;i_gauge++) {
	    //formulazza nei miei appunti 
	    	c[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=((spin_q_im[index_tens_med(imeas,nmeas,3,nop,iflav,nflav,i_gauge)])*(spin_re[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)]) - (spin_q_re[index_tens_med(imeas,nmeas,3,nop,iflav,nflav,i_gauge)])*(spin_im[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)]))/((sqrt(q2[index_q_med(imeas,nmeas,i_gauge)])) * (pow(spin_re[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)],2) + pow(spin_im[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)],2)));
	    }
}	

//Crea un singolo sottocampione, levando un blocco di configurazioni. Funziona, a parte che per qualche mistero all'uscita della funzione gli ultimi due valori ncopy e block vengono messi a caso e li devo rimettere (!)
void resample_top(float resampled[], int i, float sample[], int nmeas, int nconf, int ncopy, int block) {
    int iconf, imeas, icopy, i_res, i_gauge;
    i_res=0;

    for(iconf=0;iconf<nconf;iconf++) {	//iconf scorre il vettore sample, i_res quello resampled 
//	cout << "iconf dentro il ciclo di iconf di resample " << iconf << endl;
    	if(iconf!=i) {	//Attenzione, i è già l'indice della configurazione da togliere per come l'ho mandato alla funzione
	    for(i_gauge=0;i_gauge<2;i_gauge++) 
		for(icopy=0;icopy<ncopy;icopy++) 
		    for(imeas=0;imeas<nmeas;imeas++) 
			resampled[index_q(imeas,nmeas,icopy,ncopy,i_res,nconf-block,i_gauge)]=sample[index_q(imeas,nmeas,icopy,ncopy,iconf,nconf,i_gauge)];
	    i_res++;
	}
	else iconf=iconf+block-1;	//Perché all'uscita del for esterno fa iconf++
    }	
}
		
//dovrebbe essere uguale a sopra. FUNZIONA. Addirittura pare senza il problema dei parametri all'uscita (!)
void resample_spin(float *resampled, int i, float *sample, int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {
    int iconf, imeas, icopy, i_res, i_gauge,iop,iflav;
    i_res=0;

    for(iconf=0;iconf<nconf;iconf++) {	//iconf scorre il vettore sample, i_res quello resampled 
    	if(iconf!=i) {
	    for(i_gauge=0;i_gauge<2;i_gauge++) 
		for(icopy=0;icopy<ncopy;icopy++) 
		    for(imeas=0;imeas<nmeas;imeas++) 
		    	for(iop=0;iop<nop;iop++)
			    for(iflav=0;iflav<nflav;iflav++)
				resampled[index_tens(imeas,nmeas,icopy,ncopy,i_res,nconf-block,iop,nop,iflav,nflav,i_gauge)]=sample[index_tens(imeas,nmeas,icopy,ncopy,iconf,nconf,iop,nop,iflav,nflav,i_gauge)];
	    i_res++;
	}
	else iconf=iconf+block-1;
    }	
}

//Funziona: provata su plaq
void calc_jack_top(float err[], float top_i[], int nblock, int nmeas) {
    int i_gauge,imeas,iblock;
    float E_j[nmeas*2];	//Questo è l'array E_jack

    //Metto a zero tutto il vettore di E_jack e di err
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) {
	    E_j[index_q_med(imeas,nmeas,i_gauge)]=0;
	    err[index_q_med(imeas,nmeas,i_gauge)]=0;
	}

    //Sommo su iblock
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iblock=0;iblock<nblock;iblock++) 
	    	E_j[index_q_med(imeas,nmeas,i_gauge)]+=top_i[index_jack_top(imeas,nmeas,iblock,nblock,i_gauge)];
		
    //normalizzazione della media
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    E_j[index_q_med(imeas,nmeas,i_gauge)]=E_j[index_q_med(imeas,nmeas,i_gauge)]/nblock;

    //Calcolo della sommatoria dell'errore (delta^2)
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iblock=0;iblock<nblock;iblock++) 
	    	err[index_q_med(imeas,nmeas,i_gauge)]+=pow(top_i[index_jack_top(imeas,nmeas,iblock,nblock,i_gauge)]-E_j[index_q_med(imeas,nmeas,i_gauge)],2);
	
    //Costante davanti e radice quadrata per ottenere l'errore
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++)
	    err[index_q_med(imeas,nmeas,i_gauge)]=sqrt(err[index_q_med(imeas,nmeas,i_gauge)]*(nblock-1)/nblock);
}

//FUNZIONA: provata su tens_re
void calc_jack_spin(float err[], float spin_i[], int nblock, int nmeas, int nop, int nflav) {
    int i_gauge,imeas,iblock,iop,iflav;
    float E_j[nmeas*nop*nflav*2];	//Questo è l'array E_jack

    //Metto a zero tutto il vettore di E_jack ed err
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iop=0;iop<nop;iop++)
		for(iflav=0;iflav<nflav;iflav++) {
		    E_j[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]=0;
		    err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]=0;
		}

    //Sommo su iblock
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iop=0;iop<nop;iop++)
		for(iflav=0;iflav<nflav;iflav++)
		    for(iblock=0;iblock<nblock;iblock++) 
			E_j[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]+=spin_i[index_jack_tens(imeas,nmeas,iblock,nblock,iop,nop,iflav,nflav,i_gauge)];
		
    //normalizzazione della media
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iop=0;iop<nop;iop++)
		for(iflav=0;iflav<nflav;iflav++)
		    E_j[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]=E_j[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]/nblock;

    //Calcolo della sommatoria dell'errore (delta^2)
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iop=0;iop<nop;iop++)
		for(iflav=0;iflav<nflav;iflav++)
		    for(iblock=0;iblock<nblock;iblock++) 
			err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]+=pow(spin_i[index_jack_tens(imeas,nmeas,iblock,nblock,iop,nop,iflav,nflav,i_gauge)]-E_j[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)],2);
	
    //Costante davanti e radice quadrata per ottenere l'errore
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++)
	    for(iop=0;iop<nop;iop++)
		for(iflav=0;iflav<nflav;iflav++)
		    err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]=sqrt(err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]*(nblock-1)/nblock);
}

//Dovrebbe essere uguale a quella di sopra, quindi funzionare
void calc_jack_c(float err[], float c_i[], int nblock, int nmeas, int nflav) {
    int i_gauge,imeas,iflav,iblock;
    float E_j[nmeas*nflav*2];	//Questo è l'array E_jack

    //Metto a zero tutto il vettore di E_jack
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iflav=0;iflav<nflav;iflav++) {
		E_j[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=0;
		err[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=0;
	    }

    //Sommo su iblock
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iflav=0;iflav<nflav;iflav++)
		for(iblock=0;iblock<nblock;iblock++) 
		    E_j[index_c(imeas,nmeas,iflav,nflav,i_gauge)]+=c_i[index_jack_c(imeas,nmeas,iblock,nblock,iflav,nflav,i_gauge)];
		
    //normalizzazione della media
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iflav=0;iflav<nflav;iflav++)
		E_j[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=E_j[index_c(imeas,nmeas,iflav,nflav,i_gauge)]/nblock;

    //Calcolo della sommatoria dell'errore (delta^2)
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iflav=0;iflav<nflav;iflav++)
		for(iblock=0;iblock<nblock;iblock++) 
		    err[index_c(imeas,nmeas,iflav,nflav,i_gauge)]+=pow(c_i[index_jack_c(imeas,nmeas,iblock,nblock,iflav,nflav,i_gauge)]-E_j[index_c(imeas,nmeas,iflav,nflav,i_gauge)],2);
	
    //Costante davanti e radice quadrata per ottenere l'errore
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++)
	    for(iflav=0;iflav<nflav;iflav++)
		err[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=sqrt(err[index_c(imeas,nmeas,iflav,nflav,i_gauge)]*(nblock-1)/nblock);
}

//La funzione che poi chiama le altre, ma che restituisce l'errore di una grandezza topologica. Provata su plaq, dovrebbe funzionare
void calc_err_top(float err[], float top[], int nmeas, int nconf, int ncopy, int block) {
    float top_i[nmeas*ncopy*nconf*2-block*nmeas*ncopy*2];	//Questo è il vettore di un sottocampione 
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block
    int iblock,i_gauge,imeas,iconf,icopy;
    float top_med_i[nmeas*2*nblock];	//Questo è il vettore di Ei secondo l'algoritmo del Jackknife
    float top_med[nmeas*2];		//La media di un singolo top_i

    //for sui blocchi
    for(iblock=0;iblock<nblock;iblock++) {
	resample_top(top_i,iblock*block,top,nmeas,nconf,ncopy,block);	

	//metto a zero la media
	for(unsigned int i_0=0;i_0<nmeas*2;i_0++) top_med[i_0]=0;
	//Secondo me così funziona, con quel valore di nconf. Funziona usata così
	measure_mean_top(top_med,top_i,nmeas,ncopy,nconf-block);  

	//riempio top_med_i
	for(i_gauge=0;i_gauge<2;i_gauge++)
	    for(imeas=0;imeas<nmeas;imeas++)
		top_med_i[index_jack_top(imeas,nmeas,iblock,nblock,i_gauge)]=top_med[index_q_med(imeas,nmeas,i_gauge)];
    }

    //Da scrivere o da fare qui, ora vedo
    calc_jack_top(err,top_med_i,nblock,nmeas);

}

//La funzione che poi chiama le altre, ma che restituisce l'errore di una grandezza fermionica: FUNZIONA: provata su tens_re
void calc_err_spin(float err[], float spin[], int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {

    cout<<"sono entrato in calc_err_spin"<<endl;
    float dim=nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2;
    cout<<"la dimensione di spin_i è" << dim<<endl;

    float spin_i[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];	//Questo è il vettore di un sottocampione 
cout<<"spin,here"<<endl;
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block
    int iblock,i_gauge,imeas,iop,iflav,iconf,icopy;
    cout<<"sto per dichiarare spin_med_i"<<endl;
    float spin_med_i[nmeas*2*nop*nflav*nblock];	//Questo è il vettore di Ei secondo l'algoritmo del Jackknife
    float spin_med[nmeas*nop*nflav*2];		//La media di un singolo top_i

    cout<<"sto per entrare nel for dei blocchi"<<endl;

    //for sui blocchi
    for(iblock=0;iblock<nblock;iblock++) {
	resample_spin(spin_i,iblock*block,spin,nmeas,nconf,ncopy,nop,nflav,block);	
	cout<<"ho fatto il resample_spin"<<endl;

	//Metto a zero la media 
	for(unsigned int i_0=0;i_0<nmeas*2*nop*nflav;i_0++) spin_med[i_0]=0;
	measure_mean_spin(spin_med,spin_i,nmeas,ncopy,nconf-block,nop,nflav);  
	cout<<"ho fatto measure mean spin"<<endl;

	//Riempio spin_med_i
	for(i_gauge=0;i_gauge<2;i_gauge++)
	    for(imeas=0;imeas<nmeas;imeas++)
		for(iop=0;iop<nop;iop++)
		    for(iflav=0;iflav<nflav;iflav++)
			spin_med_i[index_jack_tens(imeas,nmeas,iblock,nblock,iop,nop,iflav,nflav,i_gauge)]=spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)];
			cout<<"ho riempito spin_med_i"<<endl;
    }

    //calcolo l'ultima parte di errori
    cout<<"sto per chiamare calc_jack_spin"<<endl;
    calc_jack_spin(err,spin_med_i,nblock,nmeas,nop,nflav);

}

//L'ho guardata e controllata tutta per vedere se lancio tutte le funzioni in maniera corretta, e dopo averla corretta ora non ci sono più zeri nell'output
void calc_err_c(float err_re[], float err_im[], float top[], float spin_re[], float spin_im[], float spin_q_re[], float spin_q_im[], int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {
    //Questa prima parte è essenzialmente la composizione di tutti i calc_err
    int iblock,i_gauge,imeas,iflav;
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block
    
    float spin_re_i[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];	//Questo è il vettore di un sottocampione 
    float spin_re_med_i[nmeas*2*nop*nflav*nblock];	//Questo è il vettore di Ei secondo l'algoritmo del Jackknife, dei singoli pezzi
    float spin_re_med[nmeas*nop*nflav*2];		//La media di un singolo top_i

    float spin_im_i[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];
    float spin_im_med_i[nmeas*2*nop*nflav*nblock];	
    float spin_im_med[nmeas*nop*nflav*2];	

    float spin_q_re_i[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];
    float spin_q_re_med_i[nmeas*2*nop*nflav*nblock];	
    float spin_q_re_med[nmeas*nop*nflav*2];	

    float spin_q_im_i[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];
    float spin_q_im_med_i[nmeas*2*nop*nflav*nblock];	
    float spin_q_im_med[nmeas*nop*nflav*2];	

    float top_i[nmeas*ncopy*nconf*2-block*nmeas*ncopy*2];
    float top_med_i[nmeas*2*nblock];	
    float top_med[nmeas*2];	

    float c_re_med[nmeas*nflav*2],c_im_med[nmeas*nflav*2];	//media di un singolo sottocampione
    float c_re_med_i[nmeas*nflav*nblock*2],c_im_med_i[nmeas*nflav*nblock*2];	//il vettore Ei	

    //Creo il vettore c_med_i (parte reale e immaginaria)
    for(iblock=0;iblock<nblock;iblock++) {
	resample_spin(spin_re_i,iblock*block,spin_re,nmeas,nconf,ncopy,nop,nflav,block);	
	resample_spin(spin_im_i,iblock*block,spin_im,nmeas,nconf,ncopy,nop,nflav,block);	
	resample_spin(spin_q_re_i,iblock*block,spin_q_re,nmeas,nconf,ncopy,nop,nflav,block);	
	resample_spin(spin_q_im_i,iblock*block,spin_q_im,nmeas,nconf,ncopy,nop,nflav,block);	
	resample_top(top_i,iblock*block,top,nmeas,nconf,ncopy,block);	
	measure_mean_spin(spin_re_med,spin_re_i,nmeas,ncopy,nconf-block,nop,nflav);  
	measure_mean_spin(spin_im_med,spin_im_i,nmeas,ncopy,nconf-block,nop,nflav);  
	measure_mean_spin(spin_q_re_med,spin_q_re_i,nmeas,ncopy,nconf-block,nop,nflav);  
	measure_mean_spin(spin_q_im_med,spin_q_im_i,nmeas,ncopy,nconf-block,nop,nflav);  
	measure_mean_top(top_med,top_i,nmeas,ncopy,nconf-block);  
	measure_c_re(c_re_med,spin_q_re_med,spin_q_im_med,top_med,spin_re_med,spin_im_med,nmeas,nop,nflav);
	measure_c_im(c_im_med,spin_q_re_med,spin_q_im_med,top_med,spin_re_med,spin_im_med,nmeas,nop,nflav);

	//Creo il vettore c_med_i
	for(i_gauge=0;i_gauge<2;i_gauge++)
	    for(imeas=0;imeas<nmeas;imeas++)
		for(iflav=0;iflav<nflav;iflav++) { 
		    c_re_med_i[index_jack_c(imeas,nmeas,iflav,nflav,iblock,nblock,i_gauge)]=c_re_med[index_c(imeas,nmeas,iflav,nflav,i_gauge)];
		    c_im_med_i[index_jack_c(imeas,nmeas,iflav,nflav,iblock,nblock,i_gauge)]=c_im_med[index_c(imeas,nmeas,iflav,nflav,i_gauge)];
		}
    }

    //Calcolo l'errore 
    calc_jack_c(err_re,c_re_med_i,nblock,nmeas,nflav);
    calc_jack_c(err_im,c_im_med_i,nblock,nmeas,nflav);
}

void file_output(float c_re[], float c_re_err[], float c_im[], float c_im_err[], float plaq[], float plaq_err[], float q[], float q_err[], float q2[], float q2_err[], float spin_re[], float spin_re_err[], float spin_im[], float spin_im_err[], float spin_q_re[], float spin_q_re_err[], float spin_q_im[], float spin_q_im_err[], int nconf,int ncopy, int nmeas, int nop, int nflav) {

    int imeas,i_gauge,iop,iflav;
    ofstream out("analisi_c_f.txt");	
    out << "imeas" << "\t" << "i_gauge" << "\t" << "iop" << "\t" << "iflav" << "\t" << "c_re" << "\t" << "c_re_err" << "\t" << "c_im" << "\t" << "c_im_err" << "\t" << "plaq" << "\t" << "plaq_err" << "\t" << "q" << "\t" << "q_err" << "\t" << "q2" << "\t" << "q2_err" << "\t" << "spin_re" << "\t" << "spin_re_err" << "\t" << "spin_im" << "\t" << "spin_im_err" << "\t" << "spin_q_re" << "\t" << "spin_q_re_err" << "\t" << "spin_q_im" << "\t" << "spin_q_im_err" << endl;

    for(int imeas=0;imeas<nmeas;imeas++)
	for(int i_gauge=0;i_gauge<2;i_gauge++) //smooth=0, ferm=1
	    for(int iop=0;iop<nop;iop++)
		for(int iflav=0;iflav<nflav;iflav++)
		    //Questo è il modo di scrivere un tab? O devo usare le virgolette del carattere?
		    out << imeas << "\t" << i_gauge << "\t" << iop << "\t" << iflav << "\t" << c_re[index_c(imeas,nmeas,iflav,nflav,i_gauge)] << "\t" << c_re_err[index_c(imeas,nmeas,iflav,nflav,i_gauge)] << "\t" << c_im[index_c(imeas,nmeas,iflav,nflav,i_gauge)] << "\t" << c_im_err[index_c(imeas,nmeas,iflav,nflav,i_gauge)] << "\t" << plaq[index_q_med(imeas,nmeas,i_gauge)] << "\t" << plaq_err[index_q_med(imeas,nmeas,i_gauge)] << "\t" << q[index_q_med(imeas,nmeas,i_gauge)] << "\t" << q_err[index_q_med(imeas,nmeas,i_gauge)] << "\t" << q2[index_q_med(imeas,nmeas,i_gauge)] << "\t" << q2_err[index_q_med(imeas,nmeas,i_gauge)] << "\t" << spin_re[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)] << "\t" << spin_re_err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)] << "\t" << spin_im[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)] << "\t" << spin_im_err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)] << "\t" <<  spin_q_re[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)] << "\t" << spin_q_re_err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)] << "\t" << spin_q_im[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)] << "\t" << spin_q_im_err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)] << endl;
}

int main () {

    //Attenzione: devo mettere nel read di buttare le conf per fare in modo che siano multiple di block
    int nmeas, ncopy, nconf, nop, nflav=3, block=2;	//Valore di prova per block
    int imeas, iop, iflav, i_gauge;

//    read_par(&nmeas, &ncopy, &nconf, &nop);	//Leggo i parametri di ingresso nell'input-file. Se non va darli in input al programma

    read_par_analisys(&nmeas,&ncopy,&nconf,&nop);

    //Dichiarazioni vettori con super-indice
    float plaq[nmeas*ncopy*nconf*2], q[nmeas*ncopy*nconf*2], q2[nmeas*ncopy*nconf*2], tens_re[nmeas*ncopy*nconf*nop*nflav*2], tens_im[nmeas*ncopy*nconf*nop*nflav*2], tens_dens_re[nmeas*ncopy*nconf*nop*nflav*2], tens_dens_im[nmeas*ncopy*nconf*nop*nflav*2]; 	

    float dim=nmeas*ncopy*nconf*nop*nflav*2;
    cout << "la dimensione delle grandezze spinoriali è" <<dim<< endl;
    
    //Dichiarazione dei vettori di medie
    float plaq_med[nmeas*2], q_med[nmeas*2], q2_med[nmeas*2], tens_re_med[nmeas*nop*nflav*2], tens_im_med[nmeas*nop*nflav*2], tens_dens_re_med[nmeas*nop*nflav*2],tens_dens_im_med[nmeas*nop*nflav*2]; 	

    cout << "here\n";

    //inizializzo tutte le medie a zero
    for(unsigned int i_0=0;i_0<nmeas*2;i_0++) plaq_med[i_0]=0;
    for(unsigned int i_0=0;i_0<nmeas*2;i_0++) q_med[i_0]=0;
    for(unsigned int i_0=0;i_0<nmeas*2;i_0++) q2_med[i_0]=0;
    for(unsigned int i_0=0;i_0<nmeas*nop*nflav*2;i_0++) tens_re_med[i_0]=0;
    for(unsigned int i_0=0;i_0<nmeas*nop*nflav*2;i_0++) tens_im_med[i_0]=0;
    for(unsigned int i_0=0;i_0<nmeas*nop*nflav*2;i_0++) tens_dens_re_med[i_0]=0;
    for(unsigned int i_0=0;i_0<nmeas*nop*nflav*2;i_0++) tens_dens_im_med[i_0]=0;

    float c_f_re[nmeas*nflav*2], c_f_im[nmeas*nflav*2], c_f_re_err[nmeas*nflav*2], c_f_im_err[nmeas*nflav*2];
    
    //Leggo l'output e riempio gli array sopra
    read_output(plaq,q,q2,tens_re,tens_im,tens_dens_re,tens_dens_im, nmeas, ncopy, nconf, nop, nflav);	//i nomi degli array sono già puntatori, basta che le referenzio nella funzione output

    cout<<"ho letto l'output"<<endl;
    
    //Calcolo le medie e riempio i vettori med
    measure_mean_top(plaq_med,plaq,nmeas,ncopy,nconf);
    measure_mean_top(q_med,q,nmeas,ncopy,nconf);
    measure_mean_top(q2_med, q2, nmeas, ncopy, nconf);
    measure_mean_spin(tens_re_med,tens_re,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_im_med,tens_im,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_dens_re_med,tens_dens_re,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_dens_im_med,tens_dens_im,nmeas,ncopy,nconf,nop,nflav);

    cout<<"ho  misurato le medie delle osservabili minori"<<endl;
  
    //Definisco gli errori
    float plaq_err[nmeas*2], q_err[nmeas*2], q2_err[nmeas*2], tens_re_err[nmeas*nop*nflav*2], tens_im_err[nmeas*nop*nflav*2], tens_dens_re_err[nmeas*nop*nflav*2], tens_dens_im_err[nmeas*nop*nflav*2];
    
    //Con le medie calcolate calcolo il valore di C_f
    measure_c_re(c_f_re,tens_dens_re_med,tens_dens_im_med,q2_med,tens_re_med,tens_im_med,nmeas,nop,nflav);
    measure_c_im(c_f_im,tens_dens_re_med,tens_dens_im_med,q2_med,tens_re_med,tens_im_med,nmeas,nop,nflav);

    cout << " Ho calcolato c" << endl;

    //Qui devo calcolare l'errore col Jackknife, delle osservabili secondarie
    calc_err_top(plaq_err,plaq,nmeas,nconf,ncopy,block);	
    calc_err_top(q_err,q,nmeas,nconf,ncopy,block);	
    calc_err_top(q2_err,q2,nmeas,nconf,ncopy,block);	
    cout<<"ho calcolato l'errore delle grandezze topologiche"<<endl;
    calc_err_spin(tens_re_err,tens_re,nmeas,nconf,ncopy,nop,nflav,block);
    cout << "ho calcolato l'errore della prima grandezza spinoriale"<<endl;
    calc_err_spin(tens_im_err,tens_im,nmeas,nconf,ncopy,nop,nflav,block);
    calc_err_spin(tens_dens_re_err,tens_dens_re,nmeas,nconf,ncopy,nop,nflav,block);
    calc_err_spin(tens_dens_im_err,tens_dens_im,nmeas,nconf,ncopy,nop,nflav,block);

    cout<<"ho calcolato gli errori delle osservabili minori"<< endl;

    //Calcolo dell'errore di C_f, con il jackknife (di entrambe le parti reali e immaginarie)
    calc_err_c(c_f_re_err,c_f_im_err,q2,tens_re,tens_im,tens_dens_re,tens_dens_im,nmeas,nconf,ncopy,nop,nflav,block);

    cout<<"ho calcolato gli errori di c"<< endl;

    //stampo l'output
    file_output(c_f_re,c_f_re_err,c_f_im,c_f_im_err,plaq_med,plaq_err,q_med,q_err,q2_med,q2_err,tens_re_med,tens_re_err,tens_im_med,tens_im_err,tens_dens_re_med,tens_dens_re_err,tens_dens_im_med,tens_dens_im_err,nconf,ncopy,nmeas,nop,nflav);
    
    cout << "Fine!" << endl;
}
