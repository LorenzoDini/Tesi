//Questa è la versione che ho deciso sarà la principale, ed è la prima dopo il commit

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

//Legge i parametri di input dal file input_analysis.txt. FUNZIONA 
void read_par_analisys(int *nmeas, int *ncopy, int *nconf, int *nop, int *block) {
    ifstream in_par("input_analisys.txt");
    in_par.ignore(1600,'\n');
    in_par >> *(nmeas) >> *(ncopy) >> *(nconf) >> *(nop) >> *(block);
	cout << "ho letto nmeas = " << *(nmeas) << " ncopy = " << *(ncopy) << " nconf = " << *(nconf) << " nop = " << *(nop)<< " block= " << *(block) << endl;
}
	
//tenativi di scrivere il super-indice e la routine per accederci. Tutte queste dovrebbero funzionare, perché ho provato a stampare i risultati dei vettori negli indici scelti e mi restituisce quelli che ha letto
int index_tens (int imeas, int nmeas, int icopy, int ncopy, int iop, int nop, int iflav, int nflav, int iconf) {
    int i;
    i=imeas+nmeas*(iop+nop*(iflav+nflav*(icopy+ncopy*iconf)));
    return i;
}

int index_q (int imeas, int nmeas, int icopy, int ncopy, int iconf) {
    int i;
    i=imeas+nmeas*(icopy+ncopy*iconf);
    return i;
}

/*
//senza i_gauge non serve più
int index_q_med (int imeas, int nmeas, int i_gauge) {
    int i;
    i=imeas+nmeas*i_gauge;
    return i;
}
*/

int index_tens_med(int imeas, int nmeas, int iop, int nop, int iflav) {
    int i;
    i=imeas+nmeas*(iop+nop*iflav);
    return i;
}

int index_c(int imeas, int nmeas, int iflav) {
    int i;
    i=imeas+nmeas*iflav;
    return i;
}

int index_jack_c(int imeas, int nmeas, int iflav, int nflav, int iblock) {
    int i;
    i=imeas+nmeas*(iflav+nflav*iblock);
    return i;
}

int index_jack_top(int imeas,int nmeas,int iblock){
    int i;
    i=imeas+nmeas*iblock;
    return i;
}

int index_jack_tens(int imeas,int nmeas,int iop,int nop,int iflav,int nflav,int iblock){
    int i;
    i=imeas+nmeas*(iop+nop*(iflav+nflav*iblock));
    return i;
}

//Legge i risultati dal file pollo e riempie i vettori.Questa è l'unica modificata dal fatto che c'è un operatore in più. FUNZIONA (provata all'inizio e alla fine del file)
void read_output (double pl[], double q[], double q2[], double sigma_re[], double sigma_im[], double sigma_q_re[], double sigma_q_im[], int nmeas, int ncopy, int nconf, int nop, int nflav) {
    
    ifstream in_pollo("pollo");	
    int imeas, icopy, iconf, iop, iflav, iread, nread, pollo_conf_pr, pollo_conf;
    double plaq, top, top2, spinpol_re, spinpol_im, spin_dens_re, spin_dens_im;
    char next_char;

    //inizializzazione parametri
    nread=nconf*nmeas*ncopy*nop*nflav;
    iconf=0;

    //Il metodo eof dentro la classe ifstream ritorna true se ha raggiunto EOF. Tuttavia anche questo metodo dà il risultato analogo che avevo usato con la variabile end, anche se è decisamente più elegante
    for(iread=0;iread<nread;iread++) {
    	in_pollo >> pollo_conf >> icopy >> imeas >> iflav >> iop;
	//Nuovo modo per aggiornare iconf, considerando che l'indice andrà a caso 
	if(iread==0) pollo_conf_pr=pollo_conf;
	if(pollo_conf!=pollo_conf_pr) iconf++;
	pollo_conf_pr=pollo_conf;

	//Conversione da a (quello che leggo in pollo) a iop, che va da zero e nop-1 se sto facendo tutte le sigma possibili
	switch(iop) {
	    case 1: 
			iop=0;
		break;
	    case 3: 
	    	iop=1;
		break;
	    case 5: 
	    	iop=2;
		break;
	    case 6: 
	    	iop=3;
		break;
	    case 9: 
	    	iop=4;
		break;
	    case 10: 
	    	iop=5;
		break;
	    case 12: 
	    	iop=6;
		break;
	}
	in_pollo.ignore(1600,'0');
	//attenzione: spinpol è q\Sigma in accordo con nissa, mentre spin_dens è \Sigma
	in_pollo >> plaq >> top >> top2 >> spinpol_re >> spinpol_im >> spin_dens_re >> spin_dens_im ;
//Questo l'ho lasciato proprio per far andare il cursore sull'EOF. Tuttavia a quanto pare non lo raggiunge dopo l'ultimo carattere di spin_dens_im. Forse c'è un altro carattere prima di EOF? 
	next_char=in_pollo.get();	
	//Scrittura nei vettori
	pl[index_q(imeas,nmeas,icopy,ncopy,iconf)]=plaq;
	q[index_q(imeas,nmeas,icopy,ncopy,iconf)]=top;
	q2[index_q(imeas,nmeas,icopy,ncopy,iconf)]=top2;
	sigma_re[index_tens(imeas,nmeas,icopy,ncopy,iop,nop,iflav,nflav,iconf)]=spin_dens_re;
	sigma_im[index_tens(imeas,nmeas,icopy,ncopy,iop,nop,iflav,nflav,iconf)]=spin_dens_im;
	sigma_q_re[index_tens(imeas,nmeas,icopy,ncopy,iop,nop,iflav,nflav,iconf)]=spinpol_re ;
	sigma_q_im[index_tens(imeas,nmeas,icopy,ncopy,iop,nop,iflav,nflav,iconf)]=spinpol_im;

	}
}

//Calcola la media per le grandezze topologiche. FUNZIONA (provata su plaq con tre misure a imeas=0,1)
void measure_mean_top(double top_med[], double top[], int nmeas, int ncopy, int nconf) {
    int copy_sum, conf_sum,imeas;

    //media a zero
    for(int i_0=0;i_0<nmeas;i_0++) top_med[i_0]=0;

    //sommo su iconf e su icopy
	for(imeas=0;imeas<nmeas;imeas++)
	    for(copy_sum=0;copy_sum<ncopy;copy_sum++) 
			for(conf_sum=0;conf_sum<nconf;conf_sum++) 
				top_med[imeas]+=top[index_q(imeas,nmeas,copy_sum,ncopy,conf_sum)];
		
    //normalizzazione della media
	for(imeas=0;imeas<nmeas;imeas++) 
		top_med[imeas]=top_med[imeas]/(double(nconf*ncopy));
}

//Calcola la media per grandezze spinoriali. FUNZIONA (provata su spin_q a imeas=1 e con tre conf)
void measure_mean_spin(double spin_med[], double spin[], int nmeas, int ncopy, int nconf, int nop, int nflav) {
    int copy_sum, conf_sum,imeas,iop,iflav;

    //media a zero
    for(int i_0=0;i_0<nmeas*nop*nflav;i_0++) spin_med[i_0]=0;

    //sommo su iconf e su icopy
	for(imeas=0;imeas<nmeas;imeas++)
		for(iop=0;iop<nop;iop++)
			for(iflav=0;iflav<nflav;iflav++)
				for(copy_sum=0;copy_sum<ncopy;copy_sum++) 
					for(conf_sum=0;conf_sum<nconf;conf_sum++) 
						spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav)]+=spin[index_tens(imeas,nmeas,copy_sum,ncopy,iop,nop,iflav,nflav,conf_sum)];

    //normalizzazione della media
	for(imeas=0;imeas<nmeas;imeas++)
		for(iop=0;iop<nop;iop++)
			for(iflav=0;iflav<nflav;iflav++)
				spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav)]=spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav)]/(double(nconf*ncopy));
}

//Due funzioni per calcolare la parte reale e immaginaria di C_f. 
void measure_c_re (double c[], double spin_q_re[], double spin_q_im[], double q2[], double spin_re[], double spin_im[], int nmeas, int nop, int nflav) {
    int imeas,iflav;

    for(imeas=0;imeas<nmeas;imeas++)
		for(iflav=0;iflav<nflav;iflav++)
		//formulazza nei miei appunti 
		c[index_c(imeas,nmeas,iflav)]=((spin_q_re[index_tens_med(imeas,nmeas,4,nop,iflav)])*(spin_re[index_tens_med(imeas,nmeas,3,nop,iflav)]) + (spin_q_im[index_tens_med(imeas,nmeas,4,nop,iflav)])*(spin_im[index_tens_med(imeas,nmeas,3,nop,iflav)]))/((sqrt(q2[imeas])) * (pow(spin_re[index_tens_med(imeas,nmeas,3,nop,iflav)],2) + pow(spin_im[index_tens_med(imeas,nmeas,3,nop,iflav)],2)));
	    
}	

//Funzione per calcolare la parte immaginaria di im. 
void measure_c_im (double c[], double spin_q_re[], double spin_q_im[], double q2[], double spin_re[], double spin_im[], int nmeas, int nop, int nflav) {
    int imeas,iflav;

    for(imeas=0;imeas<nmeas;imeas++)
		for(iflav=0;iflav<nflav;iflav++)
	    //formulazza nei miei appunti 
			c[index_c(imeas,nmeas,iflav)]=((spin_q_im[index_tens_med(imeas,nmeas,4,nop,iflav)])*(spin_re[index_tens_med(imeas,nmeas,3,nop,iflav)]) - (spin_q_re[index_tens_med(imeas,nmeas,4,nop,iflav)])*(spin_im[index_tens_med(imeas,nmeas,3,nop,iflav)]))/((sqrt(q2[imeas])) * (pow(spin_re[index_tens_med(imeas,nmeas,3,nop,iflav)],2) + pow(spin_im[index_tens_med(imeas,nmeas,3,nop,iflav)],2)));
	    
}	

//Crea un singolo sottocampione, levando un blocco di configurazioni. FUNZIONA (provata su plaq a varie misure con 5 conf e block=2)
void resample_top(double resampled[], int i, double sample[], int nmeas, int nconf, int ncopy, int block) {
    int iconf, imeas, icopy, i_res;
    i_res=0;

    for(iconf=0;iconf<nconf;iconf++) {	//iconf scorre il vettore sample, i_res quello resampled 
//	cout << "iconf dentro il ciclo di iconf di resample " << iconf << endl;
    	if(iconf!=i) {	//Attenzione, i è già l'indice della configurazione da togliere per come l'ho mandato alla funzione
			for(icopy=0;icopy<ncopy;icopy++) 
				for(imeas=0;imeas<nmeas;imeas++) 
					resampled[index_q(imeas,nmeas,icopy,ncopy,i_res)]=sample[index_q(imeas,nmeas,icopy,ncopy,iconf)];
			i_res++;
	}
	else iconf=iconf+block-1;	//Perché all'uscita del for esterno fa iconf++
    }	

}
		
//dovrebbe essere uguale a sopra. FUNZIONA (provata su sigma con nconf=7 e block=2 a varie imeas)
void resample_spin(double *resampled, int i, double *sample, int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {
    int iconf, imeas, icopy, i_res, iop,iflav;
    i_res=0;

    for(iconf=0;iconf<nconf;iconf++) {	//iconf scorre il vettore sample, i_res quello resampled 
    	if(iconf!=i) {
		for(icopy=0;icopy<ncopy;icopy++) 
		    for(imeas=0;imeas<nmeas;imeas++) 
		    	for(iop=0;iop<nop;iop++)
					for(iflav=0;iflav<nflav;iflav++)
						resampled[index_tens(imeas,nmeas,icopy,ncopy,iop,nop,iflav,nflav,i_res)]=sample[index_tens(imeas,nmeas,icopy,ncopy,iop,nop,iflav,nflav,iconf)];
	    i_res++;
	}
	else iconf=iconf+block-1;
    }	
}

//funzione che calcola l'errore finale. FUNZIONA (provata con nblock=2 e gli stessi parametri di prova del resample_top)
void calc_jack_top(double err[], double top_i[], int nblock, int nmeas) {
    int imeas,iblock;

    double *E_j;	//Questo è l'array E_jack
    E_j = new double[nmeas*2];

    //Metto a zero tutto il vettore di E_jack e di err
	for(imeas=0;imeas<nmeas;imeas++) {
	    E_j[imeas]=0;
	    err[imeas]=0;
	}

    //Sommo su iblock
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iblock=0;iblock<nblock;iblock++) 
	    	E_j[imeas]+=top_i[index_jack_top(imeas,nmeas,iblock)];
		
    //normalizzazione della media
	for(imeas=0;imeas<nmeas;imeas++) 
	    E_j[imeas]=E_j[imeas]/nblock;

    //Calcolo della sommatoria dell'errore (delta^2)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iblock=0;iblock<nblock;iblock++) 
	    	err[imeas]+=pow(top_i[index_jack_top(imeas,nmeas,iblock)]-E_j[imeas],2);
	
    //Costante davanti e radice quadrata per ottenere l'errore
	for(imeas=0;imeas<nmeas;imeas++)
	    err[imeas]=sqrt(err[imeas]*(nblock-1)/nblock);

	//dealloco
	delete[] E_j;
}

//come sopra. FUNZIONA (provata con gli stessi parametri del resample spin)
void calc_jack_spin(double err[], double spin_i[], int nblock, int nmeas, int nop, int nflav) {
    int imeas,iblock,iop,iflav;
    
    double *E_j;	//Questo è l'array E_jack
    E_j = new double[nmeas*nop*nflav*2];

    //Metto a zero tutto il vettore di E_jack ed err
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iop=0;iop<nop;iop++)
			for(iflav=0;iflav<nflav;iflav++) {
				E_j[index_tens_med(imeas,nmeas,iop,nop,iflav)]=0;
				err[index_tens_med(imeas,nmeas,iop,nop,iflav)]=0;
			}

    //Sommo su iblock
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iop=0;iop<nop;iop++)
			for(iflav=0;iflav<nflav;iflav++)
				for(iblock=0;iblock<nblock;iblock++)  
					E_j[index_tens_med(imeas,nmeas,iop,nop,iflav)]+=spin_i[index_jack_tens(imeas,nmeas,iop,nop,iflav,nflav,iblock)];
				
		
    //normalizzazione della media
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iop=0;iop<nop;iop++)
			for(iflav=0;iflav<nflav;iflav++) 
				E_j[index_tens_med(imeas,nmeas,iop,nop,iflav)]=E_j[index_tens_med(imeas,nmeas,iop,nop,iflav)]/double(nblock);
			

    //Calcolo della sommatoria dell'errore (delta^2)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iop=0;iop<nop;iop++)
			for(iflav=0;iflav<nflav;iflav++)
				for(iblock=0;iblock<nblock;iblock++) 
					err[index_tens_med(imeas,nmeas,iop,nop,iflav)]+=pow(spin_i[index_jack_tens(imeas,nmeas,iop,nop,iflav,nflav,iblock)]-E_j[index_tens_med(imeas,nmeas,iop,nop,iflav)],2);

	//Costante davanti e radice quadrata per ottenere l'errore
	for(imeas=0;imeas<nmeas;imeas++)
	    for(iop=0;iop<nop;iop++)
			for(iflav=0;iflav<nflav;iflav++)
				err[index_tens_med(imeas,nmeas,iop,nop,iflav)]=sqrt(err[index_tens_med(imeas,nmeas,iop,nop,iflav)]*(nblock-1)/double(nblock));

	//dealloco
	delete[] E_j;
}

//calcola l'errore finale 
void calc_jack_c(double err[], double c_i[], int nblock, int nmeas, int nflav) {
    int imeas,iflav,iblock;

    double *E_j;	//Questo è l'array E_jack
    E_j = new double[nmeas*nflav*2];

    //Metto a zero tutto il vettore di E_jack
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iflav=0;iflav<nflav;iflav++) {
			E_j[index_c(imeas,nmeas,iflav)]=0;
			err[index_c(imeas,nmeas,iflav)]=0;
	    }

    //Sommo su iblock
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iflav=0;iflav<nflav;iflav++)
			for(iblock=0;iblock<nblock;iblock++) 
				E_j[index_c(imeas,nmeas,iflav)]+=c_i[index_jack_c(imeas,nmeas,iflav,nflav,iblock)];
		
    //normalizzazione della media
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iflav=0;iflav<nflav;iflav++)
			E_j[index_c(imeas,nmeas,iflav)]=E_j[index_c(imeas,nmeas,iflav)]/nblock;


    //Calcolo della sommatoria dell'errore (delta^2)
	for(imeas=0;imeas<nmeas;imeas++) 
	    for(iflav=0;iflav<nflav;iflav++)
			for(iblock=0;iblock<nblock;iblock++) 
				err[index_c(imeas,nmeas,iflav)]+=pow(c_i[index_jack_c(imeas,nmeas,iflav,nflav,iblock)]-E_j[index_c(imeas,nmeas,iflav)],2);
	
    //Costante davanti e radice quadrata per ottenere l'errore
	for(imeas=0;imeas<nmeas;imeas++)
	    for(iflav=0;iflav<nflav;iflav++)
			err[index_c(imeas,nmeas,iflav)]=sqrt(err[index_c(imeas,nmeas,iflav)]*(nblock-1)/nblock);

	//dealloco
	delete[] E_j;
}

//La funzione che poi chiama le altre, ma che restituisce l'errore di una grandezza topologica. 
void calc_err_top(double err[], double top[], int nmeas, int nconf, int ncopy, int block) {
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block
    int iblock,imeas;

	cout << "sono dentro calc_err_top" << endl;

    //Alloco dinamicamente i vettori che userò
    double *top_i, *top_med, *top_med_i;		//rispettivamente il singolo sottocampione, media di un top_i (temporanea), Ei
    top_i = new double[nmeas*ncopy*nconf-block*nmeas*ncopy];
    top_med = new double[nmeas];
    top_med_i = new double[nmeas*nblock];

	cout << "allocato dentro calc_err" << endl;

    //for sui blocchi
    for(iblock=0;iblock<nblock;iblock++) {
		resample_top(top_i,iblock*block,top,nmeas,nconf,ncopy,block);	
		//Secondo me così funziona, con quel valore di nconf. Funziona usata così
		measure_mean_top(top_med,top_i,nmeas,ncopy,nconf-block);  

		//riempio top_med_i
		for(imeas=0;imeas<nmeas;imeas++)
			top_med_i[index_jack_top(imeas,nmeas,iblock)]=top_med[imeas];
    }

    //calcolo l'ultima parte di errori
    calc_jack_top(err,top_med_i,nblock,nmeas);

	//dealloco quelli che ho usato in questa routine
	delete[] top_i; 
	delete[] top_med; 
	delete[] top_med_i;		//rispettivamente il singolo sottocampione, media di un top_i (temporanea), Ei

}

//La funzione che poi chiama le altre, ma che restituisce l'errore di una grandezza fermionica: 
void calc_err_spin(double err[], double spin[], int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block
    int iblock,imeas,iop,iflav;

    //Alloco dinamicamente i vettori che userò
    double *spin_i, *spin_med, *spin_med_i; 	//rispettivamente il singolo sottocampione, media di un top_i (temporanea), Ei
    spin_i = new double[nmeas*ncopy*nconf*nop*nflav-block*nmeas*ncopy*nop*nflav];
    spin_med = new double[nmeas*nop*nflav];
    spin_med_i = new double[nmeas*nop*nflav*nblock];

    //for sui blocchi
    for(iblock=0;iblock<nblock;iblock++) {
		resample_spin(spin_i,iblock*block,spin,nmeas,nconf,ncopy,nop,nflav,block);	

		measure_mean_spin(spin_med,spin_i,nmeas,ncopy,nconf-block,nop,nflav);  

		//Riempio spin_med_i
		for(imeas=0;imeas<nmeas;imeas++)
			for(iop=0;iop<nop;iop++)
				for(iflav=0;iflav<nflav;iflav++)
					spin_med_i[index_jack_tens(imeas,nmeas,iop,nop,iflav,nflav,iblock)]=spin_med[index_tens_med(imeas,nmeas,iop,nop,iflav)];
    }

	//calcolo l'ultima parte di errori
    calc_jack_spin(err,spin_med_i,nblock,nmeas,nop,nflav);

	//dealloco
	delete[] spin_i; 
	delete[] spin_med; 
	delete[] spin_med_i;

}

//L'ho guardata e controllata tutta per vedere se lancio tutte le funzioni in maniera corretta, e dopo averla corretta ora non ci sono più zeri nell'output. 
void calc_err_c(double err_re[], double err_im[], double top[], double spin_re[], double spin_im[], double spin_q_re[], double spin_q_im[], int nmeas, int nconf, int ncopy, int nop, int nflav, int block) {
    //Questa prima parte è essenzialmente la composizione di tutti i calc_err
    int iblock,imeas,iflav;
    int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block
    
    //Alloco dicìnamicamente i vettori che userò
    double *spin_re_i, *spin_re_med, *spin_im_i, *spin_im_med, *spin_q_re_i, *spin_q_re_med, *spin_q_im_i, *spin_q_im_med, *top_i, *top_med;
    double *c_re_med, *c_im_med, *c_re_med_i, *c_im_med_i;
    spin_re_i = new double[nmeas*ncopy*nconf*nop*nflav-block*nmeas*ncopy*nop*nflav];
    spin_re_med = new double[nmeas*nop*nflav];
    spin_im_i = new double[nmeas*ncopy*nconf*nop*nflav-block*nmeas*ncopy*nop*nflav];
    spin_im_med = new double[nmeas*nop*nflav];
    spin_q_re_i = new double[nmeas*ncopy*nconf*nop*nflav-block*nmeas*ncopy*nop*nflav];
    spin_q_re_med = new double[nmeas*nop*nflav];
    spin_q_im_i = new double[nmeas*ncopy*nconf*nop*nflav-block*nmeas*ncopy*nop*nflav];
    spin_q_im_med = new double[nmeas*nop*nflav];
    top_i = new double[nmeas*ncopy*nconf-block*nmeas*ncopy];
    top_med = new double[nmeas];
    c_re_med = new double[nmeas*nflav];
    c_re_med_i = new double[nmeas*nflav*nblock];
    c_im_med = new double[nmeas*nflav];
    c_im_med_i = new double[nmeas*nflav*nblock];

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
		for(imeas=0;imeas<nmeas;imeas++)
			for(iflav=0;iflav<nflav;iflav++) { 
				c_re_med_i[index_jack_c(imeas,nmeas,iflav,nflav,iblock)]=c_re_med[index_c(imeas,nmeas,iflav)];
				c_im_med_i[index_jack_c(imeas,nmeas,iflav,nflav,iblock)]=c_im_med[index_c(imeas,nmeas,iflav)];
			}
    }

    //Calcolo l'errore 
    calc_jack_c(err_re,c_re_med_i,nblock,nmeas,nflav);
    calc_jack_c(err_im,c_im_med_i,nblock,nmeas,nflav);

	//dealloco
	delete[] spin_re_i; 
	delete[] spin_re_med; 
	delete[] spin_im_i; 
	delete[] spin_im_med; 
	delete[] spin_q_re_i; 
	delete[] spin_q_re_med; 
	delete[] spin_q_im_i; 
	delete[] spin_q_im_med; 
	delete[] top_i; 
	delete[] top_med;
	delete[] c_re_med; 
	delete[] c_im_med; 
	delete[] c_re_med_i; 
	delete[] c_im_med_i;
}

//scrive il file analisi_c_f.txt che è l'output dell'analisi
void file_output(double c_re[], double c_re_err[], double c_im[], double c_im_err[], double plaq[], double plaq_err[], double q[], double q_err[], double q2[], double q2_err[], double spin_re[], double spin_re_err[], double spin_im[], double spin_im_err[], double spin_q_re[], double spin_q_re_err[], double spin_q_im[], double spin_q_im_err[], int nconf,int ncopy, int nmeas, int nop, int nflav) {

    //Uso il metodo di C per creare lo stream, perché voglio usare fprintf
    FILE *out=fopen("analisi_c_f.txt", "w");
    fprintf(out,"imeas\tiop\tiflav\tc_re\tc_re_err\tc_im\tc_im_err\tplaq\tplaq_err\tq\tq_err\tq2\tq2_err\tspin_re\tspin_re_err\tspin_im\tspin_im_err\tspin_q_re\tspin_q_re_err\tspin_q_im\tspin_q_im_err\n");

    for(int imeas=0;imeas<nmeas;imeas++)
	    for(int iop=0;iop<nop;iop++)
			for(int iflav=0;iflav<nflav;iflav++)
		    //guardare su c++.com la struttura dell'fprintf per capire cosa vogliono dire i vari flag e specificatori
				fprintf(out,"%d\t%d\t%d\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\t%+16.16lg\n",imeas,iop,iflav,c_re[index_c(imeas,nmeas,iflav)],c_re_err[index_c(imeas,nmeas,iflav)],c_im[index_c(imeas,nmeas,iflav)],c_im_err[index_c(imeas,nmeas,iflav)],plaq[imeas],plaq_err[imeas],q[imeas],q_err[imeas],q2[imeas],q2_err[imeas],spin_re[index_tens_med(imeas,nmeas,iop,nop,iflav)],spin_re_err[index_tens_med(imeas,nmeas,iop,nop,iflav)],spin_im[index_tens_med(imeas,nmeas,iop,nop,iflav)],spin_im_err[index_tens_med(imeas,nmeas,iop,nop,iflav)],spin_q_re[index_tens_med(imeas,nmeas,iop,nop,iflav)],spin_q_re_err[index_tens_med(imeas,nmeas,iop,nop,iflav)],spin_q_im[index_tens_med(imeas,nmeas,iop,nop,iflav)],spin_q_im_err[index_tens_med(imeas,nmeas,iop,nop,iflav)]);

}

int main () {
  
	cout.precision(16);
	cerr.precision(16);
	/*
	double a=1.0;
	cout << a << "\n";
	printf("%.16lf\n",a);
	*/

	int nmeas, ncopy, nconf, nop, nflav=3, block;	

//    read_par(&nmeas, &ncopy, &nconf, &nop);	//Leggo i parametri di ingresso nell'input-file. Se non va darli in input al programma

    read_par_analisys(&nmeas,&ncopy,&nconf,&nop,&block);

	//modifico nconf in maniera da poter cambiare il blocking
	nconf=nconf-nconf%block;
   
    //Alloco dinamicamente gli array
    double *plaq, *q, *q2, *tens_re, *tens_im, *tens_dens_re, *tens_dens_im;	//array che leggo
    double *plaq_med, *q_med, *q2_med, *tens_re_med, *tens_im_med, *tens_dens_re_med, *tens_dens_im_med; 	//vettori delle medie
    double *plaq_err, *q_err, *q2_err, *tens_re_err, *tens_im_err, *tens_dens_re_err, *tens_dens_im_err; 	//vettori degli errori
    double *c_f_re, *c_f_im, *c_f_re_err, *c_f_im_err;		//c e i suoi errori
    plaq = new double[nmeas*ncopy*nconf];
    q = new double[nmeas*ncopy*nconf];
    q2 = new double[nmeas*ncopy*nconf];
    tens_re = new double[nmeas*ncopy*nconf*nop*nflav];
    tens_im = new double[nmeas*ncopy*nconf*nop*nflav];
    tens_dens_re = new double[nmeas*ncopy*nconf*nop*nflav];
    tens_dens_im = new double[nmeas*ncopy*nconf*nop*nflav]; 	
    plaq_med = new double[nmeas];
    q_med = new double[nmeas];
    q2_med = new double[nmeas];
    tens_re_med = new double[nmeas*nop*nflav];
    tens_im_med = new double[nmeas*nop*nflav];
    tens_dens_re_med = new double[nmeas*nop*nflav];
    tens_dens_im_med = new double[nmeas*nop*nflav]; 	
    plaq_err = new double[nmeas];
    q_err = new double[nmeas];
    q2_err = new double[nmeas];
    tens_re_err = new double[nmeas*nop*nflav];
    tens_im_err = new double[nmeas*nop*nflav];
    tens_dens_re_err = new double[nmeas*nop*nflav];
    tens_dens_im_err = new double[nmeas*nop*nflav]; 	
    c_f_re = new double[nmeas*nflav];
    c_f_im = new double[nmeas*nflav];
    c_f_re_err = new double[nmeas*nflav];
    c_f_im_err = new double[nmeas*nflav];

    cout << "sto per entrare nel read_output" << endl;
    //Leggo l'output e riempio gli array sopra
    read_output(plaq,q,q2,tens_re,tens_im,tens_dens_re,tens_dens_im, nmeas, ncopy, nconf, nop, nflav);	//i nomi degli array sono già puntatori, basta che le referenzio nella funzione output

	cout << "ho  letto i dati e riempito i vettori" << endl;
    
    //Calcolo le medie e riempio i vettori med
    measure_mean_top(plaq_med,plaq,nmeas,ncopy,nconf);
	//cout << "ho calcolato le media di plaq" << endl;
    measure_mean_top(q_med,q,nmeas,ncopy,nconf);
    measure_mean_top(q2_med, q2, nmeas, ncopy, nconf);
	//cout << "ho calcolato le medie topologiche" << endl;
    measure_mean_spin(tens_re_med,tens_re,nmeas,ncopy,nconf,nop,nflav);
	//cout << "ho calcolato la media di tens_re" << endl;
    measure_mean_spin(tens_im_med,tens_im,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_dens_re_med,tens_dens_re,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_dens_im_med,tens_dens_im,nmeas,ncopy,nconf,nop,nflav);
	//cout << "ho calcolato le medie fermioniche" << endl;

    //Con le medie calcolate calcolo il valore di C_f
    measure_c_re(c_f_re,tens_dens_re_med,tens_dens_im_med,q2_med,tens_re_med,tens_im_med,nmeas,nop,nflav);
    measure_c_im(c_f_im,tens_dens_re_med,tens_dens_im_med,q2_med,tens_re_med,tens_im_med,nmeas,nop,nflav);
    cout << " Ho calcolato c" << endl;

    //Qui devo calcolare l'errore col Jackknife, delle osservabili secondarie
    calc_err_top(plaq_err,plaq,nmeas,nconf,ncopy,block);	
	cout << "ho calcolato l'errore di plaq" << endl;
    calc_err_top(q_err,q,nmeas,nconf,ncopy,block);	
    calc_err_top(q2_err,q2,nmeas,nconf,ncopy,block);	
	cout << "ho calcolato l'errore delle grandezze topologiche" << endl;
    calc_err_spin(tens_re_err,tens_re,nmeas,nconf,ncopy,nop,nflav,block);
	cout << "fine calcolo errore sigma re" << endl;
    calc_err_spin(tens_im_err,tens_im,nmeas,nconf,ncopy,nop,nflav,block);
    calc_err_spin(tens_dens_re_err,tens_dens_re,nmeas,nconf,ncopy,nop,nflav,block);
    calc_err_spin(tens_dens_im_err,tens_dens_im,nmeas,nconf,ncopy,nop,nflav,block);
	cout << "ho calcolato l'errore delle grandezze fermioniche" << endl;

    //Calcolo dell'errore di C_f, con il jackknife (di entrambe le parti reali e immaginarie)
    calc_err_c(c_f_re_err,c_f_im_err,q2,tens_re,tens_im,tens_dens_re,tens_dens_im,nmeas,nconf,ncopy,nop,nflav,block);

    //stampo l'output
    file_output(c_f_re,c_f_re_err,c_f_im,c_f_im_err,plaq_med,plaq_err,q_med,q_err,q2_med,q2_err,tens_re_med,tens_re_err,tens_im_med,tens_im_err,tens_dens_re_med,tens_dens_re_err,tens_dens_im_med,tens_dens_im_err,nconf,ncopy,nmeas,nop,nflav);
    
	//dealloco tutto
	delete[] plaq; 
	delete[] q; 
	delete[] q2; 
	delete[] tens_re; 
	delete[] tens_im; 
	delete[] tens_dens_re; 
	delete[] tens_dens_im;	
	delete[] plaq_med; 
	delete[] q_med; 
	delete[] q2_med; 
	delete[] tens_re_med; 
	delete[] tens_im_med; 
	delete[] tens_dens_re_med; 
	delete[] tens_dens_im_med; 	
	delete[] plaq_err; 
	delete[] q_err; 
	delete[] q2_err; 
	delete[] tens_re_err; 
	delete[] tens_im_err; 
	delete[] tens_dens_re_err; 
	delete[] tens_dens_im_err; 	
	delete[] c_f_re; 
	delete[] c_f_im; 
	delete[] c_f_re_err; 
	delete[] c_f_im_err;		

    cout << "Fine!" << endl;
}
