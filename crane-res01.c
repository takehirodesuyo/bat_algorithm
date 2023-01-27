/* ###############################################
   ### Rotary crane control system using the optimized NC 
   ### Compile: gcc -O2 -o crane-res01 crane-res01.c myfopen.c crane_3dmodel.C neural_network.c crane_control_data.c -lm
   ### programmed by nakazono. [2023/01/20]
   ############################################### */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "crane.h"
#include "nn.h"

// my file strucure (myfopen.c)
extern FILE *myfopen(char *fname, char *mode);

// control simulation (crane_control_data.c)
extern float crane_control_simulation(NEURON_w NCw);

int main(void)
{
	FILE *fpw;
	int   i, j, k;
	float Err=0.0, weight;
	NEURON_w NCw;
	
	fpw=myfopen("w-ba.dat", "r");

	for(j=0;j<J_MAX;j++){
		for(i=0;i<I_MAX;i++) {
            fscanf(fpw, "%f\n", &weight);
			NCw.n_ij[i][j]=weight;
        }
    }
	for(j=0;j<J_MAX;j++){
		for(k=0;k<K_MAX;k++){
            fscanf(fpw, "%f\n", &weight);
			NCw.n_jk[j][k]=weight;
		}
	}
	// Control start
	Err = crane_control_simulation(NCw);
    printf("E=%f\n", Err);
	fclose(fpw);

	return 0;
} // end main