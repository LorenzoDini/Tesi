//Questa è la versione in cui calcolo l'errore del condensato

#include<iostream> 
#include<fstream>  
#include "math.h"
#include "stdio.h"
#include<cstring>
#include<sstream>
#include<cstdio>
#include<new>
using namespace std;

//due routine per accedere ai vettori. Provate.
int index_chi(int icopy, int ncopy, int iconf, int iflav, int nflav) {
	int i;
	i=iflav+nflav*(icopy+ncopy*iconf);
	return i;
}

int index_jack_chi(int iflav, int nflav, int iblock) {
	int i;
	i=iflav+nflav*iblock;
	return i;
}

//legge da file creato apposta i parametri esterni. FUNZIONA
void read_par_analisys(int *ncopy, int *nconf, int *block) {
    ifstream in_par("input_analisys_lavanda.txt");
    in_par.ignore(1600,'\n');
    in_par >>  *(ncopy) >> *(nconf) >> *(block);
	in_par.close();
}

//routine per leggere e riempire il condensato chirale da lavanda. FUNZIONA, ha anche la versione che varia col block
void read_output (double chi_re[], int ncopy, int nconf, int nflav, int block) {
	int iflav, iread, nread, icopy, iconf;
	int lav_conf, lav_conf_pr;
	double cond_re;
    
	//inizializzazione parametri
	ifstream in_lav("lavanda");
	nread=nconf*ncopy;
	icopy=0;
	iconf=0;

	//for sulle righe
	for(iread=0;iread<nread;iread++) {
    	in_lav >> lav_conf;
		//Nuovo modo per aggiornare iconf, considerando che l'indice andrà a caso 
		if(iread==0) lav_conf_pr=lav_conf;
		if(lav_conf!=lav_conf_pr) iconf++;
		if(lav_conf!=lav_conf_pr) icopy=0;				//Se ho cambiato configurazione rimetto icopy a zero
		lav_conf_pr=lav_conf;
		
		for(iflav=0;iflav<nflav;iflav++) {
			in_lav >> cond_re;
			chi_re[index_chi(icopy,ncopy,iconf,iflav,nflav)]=cond_re;
		}

		icopy++;
	}
	in_lav.close();
}

//funzione per fare la media del condensato chirale. Provata a mano con 4 configurazioni, FUNZIONA
void measure_mean_cond(double chi_med[], double chi[], int ncopy, int nconf, int nflav) {
int copy_sum, conf_sum,iflav;

    //media a zero
    for(unsigned int i_0=0;i_0<nflav;i_0++) chi_med[i_0]=0;

    //sommo su iconf e su icopy
	for(iflav=0;iflav<nflav;iflav++)
		for(copy_sum=0;copy_sum<ncopy;copy_sum++) 
			for(conf_sum=0;conf_sum<nconf;conf_sum++) 
			    chi_med[iflav]+=chi[index_chi(copy_sum,ncopy,conf_sum,iflav,nflav)];

    //normalizzazione della media
	for(iflav=0;iflav<nflav;iflav++)
		chi_med[iflav]=chi_med[iflav]/(double(nconf*ncopy));
}

//funzione di resample per chi, da provare. Non l'ho provata direttamente, ma ho provato il risultato degli errori direttamente
void resample_chi(double resampled[], int i, double sample[], int nconf, int ncopy, int nflav, int block) {
	int iconf, icopy, i_res, iflav;
    i_res=0;

    for(iconf=0;iconf<nconf;iconf++) {	//iconf scorre il vettore sample, i_res quello resampled 
    	if(iconf!=i) {
		for(icopy=0;icopy<ncopy;icopy++) 
			for(iflav=0;iflav<nflav;iflav++)
				//faccio una prova a evitare di scrivere nconf-block, sennò devo cambiare l'ordine di index_chi
				resampled[index_chi(icopy,ncopy,i_res,iflav,nflav)]=sample[index_chi(icopy,ncopy,iconf,iflav,nflav)];
	    i_res++;
		}
		else iconf=iconf+block-1;
    }	
}

//funzione finale per l'errore. FUNZIONA, provata con 4 configurazioni
void calc_jack_chi(double err[], double chi_i[], int nblock, int nflav) {
    int iblock,iflav;
    
    double *E_j;	//Questo è l'array E_jack
    E_j = new double[nflav];

    //Metto a zero tutto il vettore di E_jack ed err
	for(iflav=0;iflav<nflav;iflav++) {
		E_j[iflav]=0;
		err[iflav]=0;
	}

    //Sommo su iblock
	for(iflav=0;iflav<nflav;iflav++)
		for(iblock=0;iblock<nblock;iblock++) 
			E_j[iflav]+=chi_i[index_jack_chi(iflav,nflav,iblock)];
		
    //normalizzazione della media
	for(iflav=0;iflav<nflav;iflav++)
		E_j[iflav]=E_j[iflav]/double(nblock);

    //Calcolo della sommatoria dell'errore (delta^2)
	for(iflav=0;iflav<nflav;iflav++)
		for(iblock=0;iblock<nblock;iblock++) 
			err[iflav]+=pow(chi_i[index_jack_chi(iflav,nflav,iblock)]-E_j[iflav],2);
	
    //Costante davanti e radice quadrata per ottenere l'errore
	for(iflav=0;iflav<nflav;iflav++)
		err[iflav]=sqrt(err[iflav]*(nblock-1)/double(nblock));

	//dealloco
	delete E_j;

}

//funzione madre che calcola l'errore. Non l'ho provata, ma ho provato direttamente quella madre, che torna
void calc_err_cond(double err[], double chi[], int nconf, int ncopy, int nflav, int block) {
	int nblock=nconf/block;	//nel read devo leggere nconf che siano multipli di block, anche per lavanda
    int iblock,iflav,iconf,icopy;

    //Alloco dicìnamicamente i vettori che userò
    double *chi_i, *chi_med, *chi_med_i; 	//rispettivamente il singolo sottocampione, media di un top_i (temporanea), Ei
    chi_i = new double[ncopy*nconf*nflav-block*ncopy*nflav];
    chi_med = new double[nflav];
    chi_med_i = new double[nflav*nblock];

    //for sui blocchi
    for(iblock=0;iblock<nblock;iblock++) {
		resample_chi(chi_i,iblock*block,chi,nconf,ncopy,nflav,block);	

		measure_mean_cond(chi_med,chi_i,ncopy,nconf-block,nflav);  

		//Riempio chi_med_i
		for(iflav=0;iflav<nflav;iflav++)
			chi_med_i[index_jack_chi(iflav,nflav,iblock)]=chi_med[iflav];
    }

    //calcolo l'ultima parte di errori
    calc_jack_chi(err,chi_med_i,nblock,nflav);

	//dealloco
	delete chi_i;
	delete chi_med;
	delete chi_med_i;
	
}

//FUNZIONA
void file_output(double chi[], double chi_err[], int nflav) {
    int imeas,i_gauge,iop,iflav;
    //Uso il metodo di C per creare lo stream, perché voglio usare fprintf
    FILE *out=fopen("analisi_chi.txt", "w");
    fprintf(out,"iflav\tchi_re\tchi_re_err\n");

	for(int iflav=0;iflav<nflav;iflav++)
		fprintf(out,"%d\t%+16.16lg\t%+16.16lg\n",iflav,chi[iflav],chi_err[iflav]);
}

int main () {
  
  //Attenzione: devo mettere nel read di buttare le conf per fare in modo che siano multiple di block
    int ncopy, nconf, nflav=3, block, iflav;	//Valore di prova per block
	int icopy, iconf;

    read_par_analisys(&ncopy,&nconf,&block);
	cout <<"ncopy=" << ncopy << ", nconf=" << nconf << ", block=" <<block << endl;
	nconf=nconf-nconf%block;

    //Alloco dinamicamente gli array
	double *chi_re, *chi_re_med, *chi_re_err;							//condensati chirali
	chi_re = new double[ncopy*nconf*nflav];
	chi_re_med = new double[nflav];
	chi_re_err = new double[nflav];

    //Leggo l'output e riempio gli array sopra
    read_output(chi_re,ncopy,nconf,nflav,block);	
	cout << "ho  letto i dati e riempito i vettori" << endl;

	//calcolo la media
    measure_mean_cond(chi_re_med,chi_re,ncopy,nconf,nflav);
	
	/*
	//for di prova
	cout << "chi_re_med è: " << endl;
	for(iflav=0;iflav<nflav;iflav++) cout << chi_re_med[iflav] <<endl;
	*/
	
	//calcolo l'errore
    calc_err_cond(chi_re_err,chi_re,nconf,ncopy,nflav,block);
	cout << "ho calcolato l'errore" << endl;

	/*
	//for di prova
	cout << "err è: " << endl;
	for(iflav=0;iflav<nflav;iflav++) cout << chi_re_err[iflav] <<endl;
	*/

	//output
	file_output(chi_re_med,chi_re_err,nflav);

	//dealloco tutto
		
	delete chi_re; 
	delete chi_re_med; 
	delete chi_re_err; 
    
    cout << "Fine!" << endl;
}
