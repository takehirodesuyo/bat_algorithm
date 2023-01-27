/*
######################################## 
### Bat argorithm method
### BA method  
### programmed by nakazono. [2023/01/20] 
######################################## */

#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>
#include<float.h>

#include "crane.h" 
#include "nn.h" 
#include "bat.h"

// Move to best BAT
INDIVIDUAL move_best_bat(INDIVIDUAL BA1, INDIVIDUAL best_BA)
{
    int i, j, k;
	INDIVIDUAL new_BA;

    new_BA=BA1;
	new_BA.freq = Freq_Min + (Freq_Max-Freq_Min)*drand48();
	for(j=0;j<J_MAX;j++) {
		for(i=0;i<I_MAX;i++) {
			new_BA.vij[i][j] += (best_BA.pij[i][j]-BA1.pij[i][j])*new_BA.freq;
			new_BA.pij[i][j] += new_BA.vij[i][j];
		}
	}
	for(k=0;k<K_MAX;k++) {
		for(j=0;j<J_MAX;j++) {
			new_BA.vjk[j][k] += (best_BA.pjk[j][k]-BA1.pjk[j][k])*new_BA.freq;
			new_BA.pjk[j][k] += new_BA.vjk[j][k];
		}
	}
    return new_BA;
}

// Move to good BAT
INDIVIDUAL move_good_bat(INDIVIDUAL good_BA, float ave_loud)
{
    int i, j, k;
	INDIVIDUAL new_BA;

	for(j=0;j<J_MAX;j++) {
		for(i=0;i<I_MAX;i++) {
			new_BA.pij[i][j] = good_BA.pij[i][j]+(2.0*drand48()-1.0)*ave_loud;
            new_BA.vij[i][j] = 0.0;
		}
	}
	for(k=0;k<K_MAX;k++) {
		for(j=0;j<J_MAX;j++) {
           new_BA.pjk[j][k] = good_BA.pjk[j][k]+(2.0*drand48()-1.0)*ave_loud;
           new_BA.vjk[j][k] = 0.0;
		}
	}
 	new_BA.freq=Freq_Min;
	new_BA.pulse=0.0;
	new_BA.loudness=Loud_0;
	new_BA.E=0.0;

    return new_BA;
}

// convert BA into BA weights
NEURON_w convert_weight(INDIVIDUAL BA)
{
	int i, j, k;
	NEURON_w NCw;

	for(j=0;j<J_MAX;j++)
		for(i=0;i<I_MAX;i++)
			NCw.n_ij[i][j]=BA.pij[i][j];
	for(j=0;j<J_MAX;j++){
		for(k=0;k<K_MAX;k++){
			NCw.n_jk[j][k]=BA.pjk[j][k];
		}
	}

	return NCw;
}

// Init BA weights
INDIVIDUAL init_BA(void)
{
	int i,j,k;
	INDIVIDUAL init_BA1;

	for(j=0;j<J_MAX;j++) {
		for(i=0;i<I_MAX;i++) {
			init_BA1.pij[i][j]=2.0*((float)rand()/RAND_MAX)-1.0;
			init_BA1.vij[i][j]=0.0;
		}
	}
	for(k=0;k<K_MAX;k++) {
		for(j=0;j<J_MAX;j++) {
			init_BA1.pjk[j][k]=2.0*((float)rand()/RAND_MAX)-1.0;
			init_BA1.vjk[j][k]=0.0;
		}
	}
	init_BA1.freq=0.0;
	init_BA1.pulse=0.0;
	init_BA1.loudness=Loud_0;
	init_BA1.E=0.0;
	
	return init_BA1;
}

// Sorting 
void sort(INDIVIDUAL BA1[])
{
	int m, n;
	INDIVIDUAL tmp;
	
	for(m=0;m<P;m++) {
		for(n=m+1;n<P;n++) {
			if(BA1[m].E>BA1[n].E) {
				tmp=BA1[m];
				BA1[m]=BA1[n];
				BA1[n]=tmp;
			}
		}
	}
}