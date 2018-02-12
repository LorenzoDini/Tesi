//Questa è la versione in cui dovrebbe funzionare anche il calcolo dell'errore di c, l'ho provata a mano. Mi rimane da aggiungere la modifica III degli appunti e la lettura adattata al jackknife a blocchi


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
#include<new>
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
void read_output (double pl[], double q[], double q2[], double sigma_re[], double sigma_im[], double sigma_q_re[], double sigma_q_im[], int nmeas, int ncopy, int nconf, int nop, int nflav) {
    
    ifstream in_pollo("pollo");	
    int imeas, icopy, iconf, iop, iflav, i_gauge, iread, nread, pollo_conf_pr, pollo_conf;
    double plaq, top, top2, spinpol_re, spinpol_im, spin_dens_re, spin_dens_im;
    char next_char;

    //inizializzazione parametri
    nread=nconf*nmeas*ncopy*nop*nflav*2;
    iconf=0;

    //Il metodo eof dentro la classe ifstream ritorna true se ha raggiunto EOF. Tuttavia anche questo metodo dà il risultato analogo che avevo usato con la variabile end, anche se è decisamente più elegante
    for(iread=0;iread<nread;iread++) {
    	in_pollo >> pollo_conf >> icopy >> imeas >> i_gauge >> iflav >> iop;
	//Nuovo modo per aggiornare iconf, considerando che l'indice andrà a caso 
	if(iread==0) pollo_conf_pr=pollo_conf;
	if(pollo_conf!=pollo_conf_pr) iconf++;
	pollo_conf_pr=pollo_conf;

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

    }
}

//Calcola la media per le grandezze topologiche. FUNZIONA (attenzione alle ultime righe che ci sono i problemi dovuti al read_output)
void measure_mean_top(double top_med[], double top[], int nmeas, int ncopy, int nconf) {
    int copy_sum, conf_sum,imeas,i_gauge;

    //media a zero
    for(unsigned int i_0=0;i_0<nmeas*2;i_0++) top_med[i_0]=0;

    //sommo su iconf e su icopy
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++)
	    for(copy_sum=0;copy_sum<ncopy;copy_sum++) 
		for(conf_sum=0;conf_sum<nconf;conf_sum++) 
		    top_med[index_q_med(imeas,nmeas,i_gauge)]+=top[index_q(imeas,nmeas,copy_sum,ncopy,conf_sum,nconf,i_gauge)];
		
    //normalizzazione della media
    for(i_gauge=0;i_gauge<2;i_gauge++) 
	for(imeas=0;imeas<nmeas;imeas++) 
	    top_med[index_q_med(imeas,nmeas,i_gauge)]=top_med[index_q_med(imeas,nmeas,i_gauge)]/(double(nconf*ncopy));
}

//Calcola la media per grandezze spinoriali. FUNZIONA (Attenzione alla stessa cosa di cui sopra)
void measure_mean_spin(double spin_med[], double spin[], int nmeas, int ncopy, int nconf, int nop, int nflav) {
    int copy_sum, conf_sum,imeas,i_gauge,iop,iflav;

    //media a zero
    for(unsigned int i_0=0;i_0<nmeas*nop*nflav*2;i_0++) spin_med[i_0]=0;

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
		    spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]=spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]/(double(nconf*ncopy));
}

//Due funzioni per calcolare la parte reale e immaginaria di C_f. FUNZIONA (provato con il file lungo di file)
void measure_c_re (double c[], double spin_q_re[], double spin_q_im[], double q2[], double spin_re[], double spin_im[], int nmeas, int nop, int nflav) {
    int imeas,iflav,i_gauge;

    for(imeas=0;imeas<nmeas;imeas++)
	for(iflav=0;iflav<nflav;iflav++)
	    for(i_gauge=0;i_gauge<2;i_gauge++){
		//formulazza nei miei appunti 
	    	c[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=((spin_q_re[index_tens_med(imeas,nmeas,3,nop,iflav,nflav,i_gauge)])*(spin_re[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)]) + (spin_q_im[index_tens_med(imeas,nmeas,3,nop,iflav,nflav,i_gauge)])*(spin_im[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)]))/((sqrt(q2[index_q_med(imeas,nmeas,i_gauge)])) * (pow(spin_re[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)],2) + pow(spin_im[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)],2)));
	    }
}	

//Funzione per calcolare la parte immaginaria di im. FUNZIONA (provata anche questa con il file lungo di dati nella cartella Data)
void measure_c_im (double c[], double spin_q_re[], double spin_q_im[], double q2[], double spin_re[], double spin_im[], int nmeas, int nop, int nflav) {
    int imeas,iflav,i_gauge;

    for(imeas=0;imeas<nmeas;imeas++)
	for(iflav=0;iflav<nflav;iflav++)
	    for(i_gauge=0;i_gauge<2;i_gauge++) {
	    //formulazza nei miei appunti 
	    	c[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=((spin_q_im[index_tens_med(imeas,nmeas,3,nop,iflav,nflav,i_gauge)])*(spin_re[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)]) - (spin_q_re[index_tens_med(imeas,nmeas,3,nop,iflav,nflav,i_gauge)])*(spin_im[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)]))/((sqrt(q2[index_q_med(imeas,nmeas,i_gauge)])) * (pow(spin_re[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)],2) + pow(spin_im[index_tens_med(imeas,nmeas,2,nop,iflav,nflav,i_gauge)],2)));
	    }
}	

//Crea un singolo sottocampione, levando un blocco di configurazioni. Funziona 
void resample_top(double resampled[], int i, double sample[], int nmeas, int nconf, int ncopy, int block) {
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
		
//dovrebbe essere uguale a sopra. FUNZIONA. 
void resample_spin(double *resampled, int i, double *sample, int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {
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
void calc_jack_top(double err[], double top_i[], int nblock, int nmeas) {
    int i_gauge,imeas,iblock;

    double *E_j;	//Questo è l'array E_jack
    E_j = new double[nmeas*2];

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
void calc_jack_spin(double err[], double spin_i[], int nblock, int nmeas, int nop, int nflav) {
    int i_gauge,imeas,iblock,iop,iflav;
    
    double *E_j;	//Questo è l'array E_jack
    E_j = new double[nmeas*nop*nflav*2];

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

//FUNZIONA, provata a mano sulle quattro configurazioni di prova
void calc_jack_c(double err[], double c_i[], int nblock, int nmeas, int nflav) {
    int i_gauge,imeas,iflav,iblock;

    double *E_j;	//Questo è l'array E_jack
    E_j = new double[nmeas*nflav*2];

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
		    E_j[index_c(imeas,nmeas,iflav,nflav,i_gauge)]+=c_i[index_jack_c(imeas,nmeas,iflav,nflav,iblock,nblock,i_gauge)];
		
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
		    err[index_c(imeas,nmeas,iflav,nflav,i_gauge)]+=pow(c_i[index_jack_c(imeas,nmeas,iflav,nflav,iblock,nblock,i_gauge)]-E_j[index_c(imeas,nmeas,iflav,nflav,i_gauge)],2);
	
    //Costante davanti e radice quadrata per ottenere l'errore
    for(i_gauge=0;i_gauge<2;i_gauge++)
	for(imeas=0;imeas<nmeas;imeas++)
	    for(iflav=0;iflav<nflav;iflav++)
		err[index_c(imeas,nmeas,iflav,nflav,i_gauge)]=sqrt(err[index_c(imeas,nmeas,iflav,nflav,i_gauge)]*(nblock-1)/nblock);
}

//La funzione che poi chiama le altre, ma che restituisce l'errore di una grandezza topologica. Provata su plaq, dovrebbe funzionare
void calc_err_top(double err[], double top[], int nmeas, int nconf, int ncopy, int block) {
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block
    int iblock,i_gauge,imeas,iconf,icopy;

    //Alloco dicìnamicamente i vettori che userò
    double *top_i, *top_med, *top_med_i;		//rispettivamente il singolo sottocampione, media di un top_i (temporanea), Ei
    top_i = new double[nmeas*ncopy*nconf*2-block*nmeas*ncopy*2];
    top_med = new double[nmeas*2];
    top_med_i = new double[nmeas*2*nblock];

    //for sui blocchi
    for(iblock=0;iblock<nblock;iblock++) {
	resample_top(top_i,iblock*block,top,nmeas,nconf,ncopy,block);	

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
void calc_err_spin(double err[], double spin[], int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block
    int iblock,i_gauge,imeas,iop,iflav,iconf,icopy;

    //Alloco dicìnamicamente i vettori che userò
    double *spin_i, *spin_med, *spin_med_i; 	//rispettivamente il singolo sottocampione, media di un top_i (temporanea), Ei
    spin_i = new double[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];
    spin_med = new double[nmeas*nop*nflav*2];
    spin_med_i = new double[nmeas*2*nop*nflav*nblock];

    //for sui blocchi
    for(iblock=0;iblock<nblock;iblock++) {
	resample_spin(spin_i,iblock*block,spin,nmeas,nconf,ncopy,nop,nflav,block);	

	measure_mean_spin(spin_med,spin_i,nmeas,ncopy,nconf-block,nop,nflav);  

	//Riempio spin_med_i
	for(i_gauge=0;i_gauge<2;i_gauge++)
	    for(imeas=0;imeas<nmeas;imeas++)
		for(iop=0;iop<nop;iop++)
		    for(iflav=0;iflav<nflav;iflav++)
			spin_med_i[index_jack_tens(imeas,nmeas,iblock,nblock,iop,nop,iflav,nflav,i_gauge)]=spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)];
    }

    //calcolo l'ultima parte di errori
    calc_jack_spin(err,spin_med_i,nblock,nmeas,nop,nflav);

}

//L'ho guardata e controllata tutta per vedere se lancio tutte le funzioni in maniera corretta, e dopo averla corretta ora non ci sono più zeri nell'output. FUNZIONA, provata a mano sui dati con 4 configurazioni
void calc_err_c(double err_re[], double err_im[], double top[], double spin_re[], double spin_im[], double spin_q_re[], double spin_q_im[], int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {
    //Questa prima parte è essenzialmente la composizione di tutti i calc_err
    int iblock,i_gauge,imeas,iflav;
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block

int iconf, icopy;
    
    //Alloco dicìnamicamente i vettori che userò
    double *spin_re_i, *spin_re_med, *spin_im_i, *spin_im_med, *spin_q_re_i, *spin_q_re_med, *spin_q_im_i, *spin_q_im_med, *top_i, *top_med;
    double *c_re_med, *c_im_med, *c_re_med_i, *c_im_med_i;
    spin_re_i = new double[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];
    spin_re_med = new double[nmeas*nop*nflav*2];
    spin_im_i = new double[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];
    spin_im_med = new double[nmeas*nop*nflav*2];
    spin_q_re_i = new double[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];
    spin_q_re_med = new double[nmeas*nop*nflav*2];
    spin_q_im_i = new double[nmeas*ncopy*nconf*nop*nflav*2-block*nmeas*ncopy*nop*nflav*2];
    spin_q_im_med = new double[nmeas*nop*nflav*2];
    top_i = new double[nmeas*ncopy*nconf*2-block*nmeas*ncopy*2];
    top_med = new double[nmeas*2];
    c_re_med = new double[nmeas*nflav*2];
    c_re_med_i = new double[nmeas*nflav*nblock*2];
    c_im_med = new double[nmeas*nflav*2];
    c_im_med_i = new double[nmeas*nflav*nblock*2];

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

void file_output(double c_re[], double c_re_err[], double c_im[], double c_im_err[], double plaq[], double plaq_err[], double q[], double q_err[], double q2[], double q2_err[], double spin_re[], double spin_re_err[], double spin_im[], double spin_im_err[], double spin_q_re[], double spin_q_re_err[], double spin_q_im[], double spin_q_im_err[], int nconf,int ncopy, int nmeas, int nop, int nflav) {

    int imeas,i_gauge,iop,iflav;
    //Uso il metodo di C per creare lo stream, perché voglio usare fprintf
    FILE *out=fopen("analisi_c_f.txt", "w");
    fprintf(out,"imeas\ti_gauge\tiop\tiflav\tc_re\tc_re_err\tc_im\tc_im_err\tplaq\tplaq_err\tq\tq_err\tq2\tq2_err\tspin_re\tspin_re_err\tspin_im\tspin_im_err\tspin_q_re\tspin_q_re_err\tspin_q_im\tspin_q_im_err\n");

    for(int imeas=0;imeas<nmeas;imeas++)
	for(int i_gauge=0;i_gauge<2;i_gauge++) //smooth=0, ferm=1
	    for(int iop=0;iop<nop;iop++)
		for(int iflav=0;iflav<nflav;iflav++)
		    //guardare su c++.com la struttura dell'fprintf per capire cosa vogliono dire i vari flag e specificatori
		    fprintf(out,"%d\t%d\t%d\t%d\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\n",imeas,i_gauge,iop,iflav,c_re[index_c(imeas,nmeas,iflav,nflav,i_gauge)],c_re_err[index_c(imeas,nmeas,iflav,nflav,i_gauge)],c_im[index_c(imeas,nmeas,iflav,nflav,i_gauge)],c_im_err[index_c(imeas,nmeas,iflav,nflav,i_gauge)],plaq[index_q_med(imeas,nmeas,i_gauge)],plaq_err[index_q_med(imeas,nmeas,i_gauge)],q[index_q_med(imeas,nmeas,i_gauge)],q_err[index_q_med(imeas,nmeas,i_gauge)],q2[index_q_med(imeas,nmeas,i_gauge)],q2_err[index_q_med(imeas,nmeas,i_gauge)],spin_re[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)],spin_re_err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)],spin_im[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)],spin_im_err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)],spin_q_re[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)],spin_q_re_err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)],spin_q_im[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)],spin_q_im_err[index_tens_med(imeas,nmeas,iop,nop,iflav,nflav,i_gauge)]);

}

int main () {
  
  cout.precision(16);
  cerr.precision(16);
  double a=1.0;
  cout << a << "\n";
  printf("%.16lf\n",a);
  //Attenzione: devo mettere nel read di buttare le conf per fare in modo che siano multiple di block
    int nmeas, ncopy, nconf, nop, nflav=3, block=2;	//Valore di prova per block
    int imeas, iop, iflav, i_gauge;

int icopy, iconf;

//    read_par(&nmeas, &ncopy, &nconf, &nop);	//Leggo i parametri di ingresso nell'input-file. Se non va darli in input al programma

    read_par_analisys(&nmeas,&ncopy,&nconf,&nop);
   
    //Alloco dinamicamente gli array
    double *plaq, *q, *q2, *tens_re, *tens_im, *tens_dens_re, *tens_dens_im;	//array che leggo
    double *plaq_med, *q_med, *q2_med, *tens_re_med, *tens_im_med, *tens_dens_re_med, *tens_dens_im_med; 	//vettori delle medie
    double *plaq_err, *q_err, *q2_err, *tens_re_err, *tens_im_err, *tens_dens_re_err, *tens_dens_im_err; 	//vettori degli errori
    double *c_f_re, *c_f_im, *c_f_re_err, *c_f_im_err;		//c e i suoi errori
    plaq = new double[nmeas*ncopy*nconf*2];
    q = new double[nmeas*ncopy*nconf*2];
    q2 = new double[nmeas*ncopy*nconf*2];
    tens_re = new double[nmeas*ncopy*nconf*nop*nflav*2];
    tens_im = new double[nmeas*ncopy*nconf*nop*nflav*2];
    tens_dens_re = new double[nmeas*ncopy*nconf*nop*nflav*2];
    tens_dens_im = new double[nmeas*ncopy*nconf*nop*nflav*2]; 	
    plaq_med = new double[nmeas*2];
    q_med = new double[nmeas*2];
    q2_med = new double[nmeas*2];
    tens_re_med = new double[nmeas*nop*nflav*2];
    tens_im_med = new double[nmeas*nop*nflav*2];
    tens_dens_re_med = new double[nmeas*nop*nflav*2];
    tens_dens_im_med = new double[nmeas*nop*nflav*2]; 	
    plaq_err = new double[nmeas*2];
    q_err = new double[nmeas*2];
    q2_err = new double[nmeas*2];
    tens_re_err = new double[nmeas*nop*nflav*2];
    tens_im_err = new double[nmeas*nop*nflav*2];
    tens_dens_re_err = new double[nmeas*nop*nflav*2];
    tens_dens_im_err = new double[nmeas*nop*nflav*2]; 	
    c_f_re = new double[nmeas*nflav*2];
    c_f_im = new double[nmeas*nflav*2];
    c_f_re_err = new double[nmeas*nflav*2];
    c_f_im_err = new double[nmeas*nflav*2];

    cout << "sto per entrare nel read_output" << endl;
    //Leggo l'output e riempio gli array sopra
    read_output(plaq,q,q2,tens_re,tens_im,tens_dens_re,tens_dens_im, nmeas, ncopy, nconf, nop, nflav);	//i nomi degli array sono già puntatori, basta che le referenzio nella funzione output

cout << "ho  letto i dati e riempito i vettori" << endl;

/*
	cout << "Questo è quello che ho letto nella riga. Rispettivamente: iconf,icopy,imeas,i_gauge_i_flav,iop,plaq,q,q2,sigma_re,sigma_im,sigma_q_re,sigma_q_im" << endl;
	cout  << iconf << " " << icopy << " " << imeas << " " << i_gauge << " " << iflav << " " << iop << " " << plaq << " " << top << " " << top2 << " " << spinpol_re << " " << spinpol_im << " " << spin_dens_re << " " << spin_dens_im << endl;
	//Faccio una prova per vedere se ha riempito bene i vettori
	cout << "q2 nell'indice " << imeas << " " << icopy << " " << iconf << " " << i_gauge << endl;
	cout << q2[index_q(imeas,nmeas,icopy,ncopy,iconf,nconf,i_gauge)] << endl;
	cout << "spin_q_re nell'indice " << imeas << " " << icopy << " " << iconf << " " << iop << " " << iflav << " " <<  i_gauge << endl;
*/
for(iconf=0;iconf<nconf;iconf++)
	for(icopy=0;icopy<ncopy;icopy++){	
		cout << "siamo a icopy " << icopy << " iconf " << iconf << endl;
		cout << tens_dens_im[index_tens(5,nmeas,icopy,ncopy,iconf,nconf,3,nop,0,nflav,0)] << endl;
	}
    
    //Calcolo le medie e riempio i vettori med
    measure_mean_top(plaq_med,plaq,nmeas,ncopy,nconf);
    measure_mean_top(q_med,q,nmeas,ncopy,nconf);
    measure_mean_top(q2_med, q2, nmeas, ncopy, nconf);
    measure_mean_spin(tens_re_med,tens_re,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_im_med,tens_im,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_dens_re_med,tens_dens_re,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_dens_im_med,tens_dens_im,nmeas,ncopy,nconf,nop,nflav);

    //Con le medie calcolate calcolo il valore di C_f
    measure_c_re(c_f_re,tens_dens_re_med,tens_dens_im_med,q2_med,tens_re_med,tens_im_med,nmeas,nop,nflav);
    measure_c_im(c_f_im,tens_dens_re_med,tens_dens_im_med,q2_med,tens_re_med,tens_im_med,nmeas,nop,nflav);
    //cout << " Ho calcolato c" << endl;

    //Qui devo calcolare l'errore col Jackknife, delle osservabili secondarie
    calc_err_top(plaq_err,plaq,nmeas,nconf,ncopy,block);	
    calc_err_top(q_err,q,nmeas,nconf,ncopy,block);	
    calc_err_top(q2_err,q2,nmeas,nconf,ncopy,block);	
    calc_err_spin(tens_re_err,tens_re,nmeas,nconf,ncopy,nop,nflav,block);
    calc_err_spin(tens_im_err,tens_im,nmeas,nconf,ncopy,nop,nflav,block);
    calc_err_spin(tens_dens_re_err,tens_dens_re,nmeas,nconf,ncopy,nop,nflav,block);
    calc_err_spin(tens_dens_im_err,tens_dens_im,nmeas,nconf,ncopy,nop,nflav,block);

    //Calcolo dell'errore di C_f, con il jackknife (di entrambe le parti reali e immaginarie)
    calc_err_c(c_f_re_err,c_f_im_err,q2,tens_re,tens_im,tens_dens_re,tens_dens_im,nmeas,nconf,ncopy,nop,nflav,block);

    //stampo l'output
    file_output(c_f_re,c_f_re_err,c_f_im,c_f_im_err,plaq_med,plaq_err,q_med,q_err,q2_med,q2_err,tens_re_med,tens_re_err,tens_im_med,tens_im_err,tens_dens_re_med,tens_dens_re_err,tens_dens_im_med,tens_dens_im_err,nconf,ncopy,nmeas,nop,nflav);
    
    cout << "Fine!" << endl;
}
