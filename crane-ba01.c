/* ########################################
   ### Rotary crane system 
   ### BA optimized by Bat algorithm method.
   ### Evolution simulation in 1 trial.
   ### Compile: gcc -O2 -o crane-ba01 crane-ba01.c myfopen.c 
   crane_3dmodel.c neural_network.c bat_algorithm.c crane_control.c -lm
   ### programmed by nakazono. [2023/01/20]
   ######################################## */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

#include "crane.h"
#include "nn.h"
#include "bat.h"

// my file strucure (myfopen.c)
extern FILE *myfopen(char *fname, char *mode);

// control simulation (crane_control.c)
extern float crane_control_simulation(NEURON_w NCw) ;
// initial weights (bat_argorithm.c)
extern INDIVIDUAL init_BA(void);
// Move to best BAT (bat_argorithm.c)
extern INDIVIDUAL move_best_bat(INDIVIDUAL BA1, INDIVIDUAL best_BA);
// Move to good BAT (bat_argorithm.c)
extern INDIVIDUAL move_good_bat(INDIVIDUAL good_BA, float ave_loud);
// convert BA into BA weights
extern NEURON_w convert_weight(INDIVIDUAL BA);
// Sorting (bat_argorithm.c)
extern void sort(INDIVIDUAL BA1[]);

int main(void)
{
	//*ファイルポインタの宣言*//
	FILE *fp1, *fp2;

	float aveLoud;
	NEURON_w  NCw;
	int i, j, k, r;
	int generation, p, z;
	INDIVIDUAL BA[P],new_BA[P], best_BA, new_BA1, new_BA2, new_BA3, tmp_BA;
	
	if((fp1=fopen("e-ba.dat","w"))==NULL) {
		printf("Can't open file¥n");
		exit(1);
	}

	if((fp2=fopen("w-ba.dat","w"))==NULL) {
		printf("Can't open file¥n");
		exit(1);
	}
	
	//seed値ごとの最適化(1000世代まで)を100回
	for(z=100;z<=8000;z+=100) {
		printf("Seed:%d\n", z);
		srand(z);
		for(p=0;p<P;p++) {
			BA[p]=init_BA();
			NCw=convert_weight(BA[p]);
			BA[p].E=crane_control_simulation(NCw);
			if(isnan(BA[p].E)) {
				BA[p].E=DBL_MAX;
			}
		} 
		sort(BA);
		best_BA=BA[0];
		//*-----世代数の繰り返し-----*//
		for(generation=0;generation<=T_MAX;generation++) {
			// 平均音量の計算
			aveLoud=0.0;
			for(p=0;p<P;p++) {
				aveLoud+=BA[p].loudness;
			}
			aveLoud/=P;
			//*-----個体数の繰り返し-----*//
			for(p=0;p<P;p++) {
				// 最良コウモリの方向への移動
				new_BA1 = move_best_bat(BA[p], best_BA);
				NCw = convert_weight(new_BA1);
				new_BA1.E=crane_control_simulation(NCw);	
				if(isnan(new_BA1.E)) {
					new_BA1.E=DBL_MAX;
				}
				// 良いコウモリの近傍に新しい移動先を生成
				r=lrand48()%(int)(P*Best_rate);
				if(drand48()>BA[p].pulse) {
					new_BA2 = move_good_bat(BA[r], aveLoud);
					NCw = convert_weight(new_BA2);
					new_BA2.E=crane_control_simulation(NCw);
				}
				if(isnan(new_BA2.E)) {
					new_BA2.E=DBL_MAX;
				}
				// ランダムに新しい移動先を生成
				new_BA3=init_BA();
				NCw=convert_weight(new_BA3);
				new_BA3.E=crane_control_simulation(NCw);
				if(isnan(new_BA3.E)) {
					new_BA3.E=DBL_MAX;
				}
				// 新しい移動先が良かったら，置換．パルス率と音量の更新
				if(((new_BA2.E < new_BA1.E)||(new_BA3.E < new_BA1.E)) && (drand48() < new_BA1.loudness)) {
					if(new_BA2.E < new_BA3.E ){
						tmp_BA=new_BA1;
						new_BA1=new_BA2;
						new_BA2=tmp_BA;
					} else {
						tmp_BA=new_BA1;
						new_BA1=new_BA3;
						new_BA3=tmp_BA;
					}
					new_BA1.pulse = Pulse_0*(1.0-exp(-Pulse_r*(float)generation));
					new_BA1.loudness*=Loud_r;
				}
				new_BA[p]=new_BA1;
			}
			// 個体群の更新
			for(p=0;p<P;p++){
				BA[p]=new_BA[p];
			}
			// コウモリを良い順に並べ替え
			sort(BA);
			// 最良個体の記録
			if(BA[0].E < best_BA.E) {
				best_BA = BA[0];
			}
			// 世代ごとの評価値をファイルに記録
			printf("%d: E=%f\n", generation, best_BA.E);
			fprintf(fp1, "%d, %f\n", generation, best_BA.E);
		} // 進化過程の終了
		// 最良コウモリの位置（NCの結合重みをファイルへ出力）
		for(j=0;j<J_MAX;j++) {
			for(i=0;i<I_MAX;i++) {
		 		fprintf(fp2,"%f\n", best_BA.pij[i][j]);
		 	}
		}
		for(k=0;k<K_MAX;k++) {
		 	for(j=0;j<J_MAX;j++) {
				fprintf(fp2,"%f\n", best_BA.pjk[j][k]);
		 	}
		}
	}
	fclose(fp1);
	fclose(fp2);

	return 0;
}