// // Cuckoo parameters 
// #define ITERATION 10000  //iteration
// #define ABA_RATE 0.1      //abandon rate
// #define IND_SIZE 100    //INDIVIDUAL size
// #define ALPHA2 0.1        //step length parameter
// #define BETA2 1.5         //scaling index 
// #define XMAX 1.0

// // individual of cuckoo(NC)　INDIVIDUALという名前の構造体ここに必要な値変数を描く
// //最終的な評価値
#define P 100
#define T_MAX 10

#define Freq_Min 0.0
#define Freq_Max 1.0
#define Loud_0 1.0
#define Loud_01 1.0
#define Loud_r 0.9

#define Pulse_0 0.5
#define Pulse_r 1.0
#define Best_rate 0.2

typedef struct {
	float E;			// 評価値
	float pij[I_MAX][J_MAX], pjk[J_MAX][K_MAX];		// 評価重み　入力-中間 中間-出力
	float vij[I_MAX][J_MAX], vjk[J_MAX][K_MAX];		// 速度　入力-中間 中間-出力
	float freq;				// 周波数
	float pulse;				// パルス率
	float loudness;			// 音量
} INDIVIDUAL;