//Questa è la versione in cui calcolo la media del condensato 

#include<iostream> 
#include<fstream>  
#include "math.h"
#include "stdio.h"
#include<cstring>
#include<sstream>
#include<cstdio>
#include<new>
using namespace std;

//due routine per accedere ai vettori. Le avevo provate nell'altro file, ma non in questo
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
void read_par_analisys(int *ncopy, int *nconf) {
    ifstream in_par("input_analisys_lavanda.txt");
    in_par.ignore(1600,'\n');
    in_par >>  *(ncopy) >> *(nconf);
	in_par.close();
}

//routine per leggere e riempire il condensato chirale da lavanda
void read_output (double chi_re[], int ncopy, int nconf, int nflav) {
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

//funzione per fare la media del condensato chirale, da provare. L'ho confrontato il flavour u con quello di BigFra e più o meno torna. Per fare una prova migliore dovrei fare una piccola simulazione di prova 
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

int main () {
  
  //Attenzione: devo mettere nel read di buttare le conf per fare in modo che siano multiple di block
    int ncopy, nconf, nflav=3, block=2, iflav;	//Valore di prova per block
	int icopy, iconf;

    read_par_analisys(&ncopy,&nconf);
	cout <<"ncopy=" << ncopy << ", nconf=" << nconf << endl;

    //Alloco dinamicamente gli array
	double *chi_re, *chi_re_med, *chi_re_err;							//condensati chirali
	chi_re = new double[ncopy*nconf*nflav];
	chi_re_med = new double[nflav];
	chi_re_err = new double[nflav];

    //Leggo l'output e riempio gli array sopra
    read_output(chi_re,ncopy,nconf,nflav);	
	cout << "ho  letto i dati e riempito i vettori" << endl;

	//calcolo la media
    measure_mean_cond(chi_re_med,chi_re,ncopy,nconf,nflav);

	//for di prova
	cout << "chi_re_med è: " << endl;
	for(iflav=0;iflav<nflav;iflav++) cout << chi_re_med[iflav] <<endl;
    
	/*
    //Calcolo le medie e riempio i vettori med
    measure_mean_top(plaq_med,plaq,nmeas,ncopy,nconf);
    measure_mean_top(q_med,q,nmeas,ncopy,nconf);
    measure_mean_top(q2_med, q2, nmeas, ncopy, nconf);
    measure_mean_spin(tens_re_med,tens_re,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_im_med,tens_im,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_dens_re_med,tens_dens_re,nmeas,ncopy,nconf,nop,nflav);
    measure_mean_spin(tens_dens_im_med,tens_dens_im,nmeas,ncopy,nconf,nop,nflav);
	cout << "ho misurato le quantità di spin e topo" << endl;
	cout << " ho calcolato la media di chi_re" << endl;

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
	cout << "ho calcolato gli errori di spin e topo" << endl;
    calc_err_cond(chi_re_err,chi_re,nconf_lav,ncopy_lav,nflav,block);
	cout << "ho calcolato l'errore del condensato" << endl;

	cout << "sto per entrare nel calcolo di errore di c" << endl;
	cout << " nconf=" << nconf << " , ncopy=" << ncopy << endl;
    //Calcolo dell'errore di C_f, con il jackknife (di entrambe le parti reali e immaginarie)
    calc_err_c(c_f_re_err,c_f_im_err,q2,tens_re,tens_im,tens_dens_re,tens_dens_im,nmeas,nconf,ncopy,nop,nflav,block);

    //stampo l'output
	cout << "sono prima di file_output"<<endl;
    file_output(c_f_re,c_f_re_err,c_f_im,c_f_im_err,plaq_med,plaq_err,q_med,q_err,q2_med,q2_err,tens_re_med,tens_re_err,tens_im_med,tens_im_err,tens_dens_re_med,tens_dens_re_err,tens_dens_im_med,tens_dens_im_err,chi_re_med,chi_re_err,nconf,ncopy,nmeas,nop,nflav);

	//dealloco tutto
	delete plaq; 
	delete q; 
	delete q2; 
	delete tens_re; 
	delete tens_im; 
	delete tens_dens_re; 
	delete tens_dens_im;	
	delete plaq_med; 
	delete q_med; 
	delete q2_med; 
	delete tens_re_med; 
	delete tens_im_med; 
	delete tens_dens_re_med; 
	delete tens_dens_im_med; 	
	delete plaq_err; 
	delete q_err; 
	delete q2_err; 
	delete tens_re_err; 
	delete tens_im_err; 
	delete tens_dens_re_err; 
	delete tens_dens_im_err; 	
	delete chi_re; 
	delete chi_im; 
	delete chi_re_med; 
	delete chi_im_med; 
	delete chi_re_err; 
	delete chi_im_err;
	delete c_f_re; 
	delete c_f_im; 
	delete c_f_re_err; 
	delete c_f_im_err;		
    
    cout << "Fine!" << endl;
	*/
}
