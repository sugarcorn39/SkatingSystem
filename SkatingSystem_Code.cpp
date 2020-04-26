#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Setting.h"

// 新規言語をスケーティングで勉強する

// まだできていないこと
// 同着処理未完成
// スケーティング処理の関数化
// ファイルからの入出力
// サーバ・クライアント処理
// アプリケーション化


void QSort(int x[], int left, int right);
void Swap(int x[], int i, int j);
void ShowData(int x[], int n);

/* クイックソートを行う */
void QSort(int x[], int left, int right)
{
	int i, j;
	int pivot;

	i = left;                      /* ソートする配列の一番小さい要素の添字 */
	j = right;                     /* ソートする配列の一番大きい要素の添字 */

	pivot = x[(left + right) / 2]; /* 基準値を配列の中央付近にとる */

	while (1) {                    /* 無限ループ */

		while (x[i] < pivot)       /* pivot より大きい値が */
			i++;                   /* 出るまで i を増加させる */

		while (pivot < x[j])       /* pivot より小さい値が */
			j--;                   /*  出るまで j を減少させる */
		if (i >= j)                /* i >= j なら */
			break;                 /* 無限ループから抜ける */

		Swap(x, i, j);             /* x[i] と x[j]を交換 */
		i++;                       /* 次のデータ */
		j--;
	}
	//ShowData(x, 10);               /* 途中経過を表示 */

	if (left < i - 1)              /* 基準値の左に 2 以上要素があれば */
		QSort(x, left, i - 1);     /* 左の配列を Q ソートする */
	if (j + 1 <  right)            /* 基準値の右に 2 以上要素があれば */
		QSort(x, j + 1, right);    /* 右の配列を Q ソートする */
}

/* 配列の要素を交換する */
void Swap(int x[], int i, int j)
{
	int temp;

	temp = x[i];
	x[i] = x[j];
	x[j] = temp;
}


/* n 個のデータを表示する */
void ShowData(int x[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		printf("%d  ", x[i]);
	printf("\n");
}

// 過半数チェック
void majority(int _Table[PLAYER_NUMBER][JUDGE_NUMBER + 1]){
	int center = PLAYER_NUMBER / 2;
	for (int i = 1; i < PLAYER_NUMBER; i++) {
		for (int j = 0; j <= i - 1; j++) {
			if (_Table[j][0] == _Table[i][0]) {
				//過半数
				int right = 0;
				int check_majority = _Table[i][center];
				while (right < JUDGE_NUMBER - center &&
				(_Table[j][center + (right)] == _Table[i][center + (right)])) {
					right++;
					if (_Table[i][center + (right - 1)] != _Table[i][center + (right)]) {
						if (_Table[j][center + (right - 1)] == _Table[j][center + (right)]) {
							_Table[i][0]++;
							break;
						}
					}
					if (_Table[j][center + (right - 1)] != _Table[j][center + (right)]) {
						if (_Table[i][center + (right - 1)] == _Table[i][center + (right)]) {
							_Table[j][0]++;
							break;//next 上位加算へ
						}
					}
				}
			}
		}
	}

}

// 上位加算メソッド
/* 
  _Table : 上位加算した結果を返却する
*/
void SumSuperior(int _Table[PLAYER_NUMBER][JUDGE_NUMBER + 1]){
	int center = PLAYER_NUMBER / 2;
	for (int i = 1; i < PLAYER_NUMBER; i++) {
		for (int j = 0; j <= i - 1; j++) {
//				fprintf(stdout, "処理前i=%d, j=%d, rank_i=%d, rank_j=%d", i, j, Table_sort[i][0], Table_sort[j][0]);
			if (_Table[j][0] == _Table[i][0]) {
				//上位加算
				int sum_i = 0;
				int sum_j = 0;
				for (int index = 1; index < center; index++) {
					sum_i += _Table[i][index];
					sum_j += _Table[j][index];
				}
				if (sum_j < sum_i) {
					_Table[i][0]++;
				}
				else if (sum_j > sum_i) {
					_Table[j][0]++;
				}
			}
//				fprintf(stdout, "	処理後i=%d, j=%d, rank_i=%d, rank_j=%d\n", i, j, Table_sort[i][0], Table_sort[j][0]);
		}
	}
}

// 下位比較
void SumSubordinate(int _Table[PLAYER_NUMBER][JUDGE_NUMBER + 1]){
	int center = PLAYER_NUMBER / 2;
	for (int i = 1; i < PLAYER_NUMBER; i++) {
		for (int j = 0; j <= i - 1; j++) {
			if (_Table[j][0] == _Table[i][0]) {
			//下位比較
			int right = 0;
				while (right < JUDGE_NUMBER - center &&
					(_Table[j][center + (right)] == _Table[i][center + (right)])) {
					right++;
					if (_Table[j][center + (right)] < _Table[i][center + (right)]) {
						_Table[i][0]++;
						break;
					}
					if (_Table[j][center + (right)] > _Table[i][center + (right)]) {
						_Table[j][0]++;
						break;
					}
				}
			//同着
			}
		}
	}
}

int output_console(int _Table[PLAYER_NUMBER][JUDGE_NUMBER + 1]){
	for (int i = 0; i < PLAYER_NUMBER; i++) {
		fprintf(stdout, "%d番　%d位\n", i, _Table[i][0]);
	}
}

int main(int argc, char** argv) {
/*
	int Table[PLAYER_NUMBER][JUDGE_NUMBER] = { {3,3,3,3,3},
												{1,2,4,4,1},
												{4,1,2,1,5},
												{5,5,5,5,4},
												{2,4,1,2,2},
												{6,6,6,6,6} };
*/
	int Table[PLAYER_NUMBER][JUDGE_NUMBER] = { {0} };

	int Table_sort[PLAYER_NUMBER][JUDGE_NUMBER + 1] = { {0} };

	int (*p_Table)[JUDGE_NUMBER] = NULL;
	int (*p_Table_sort)[JUDGE_NUMBER + 1] = NULL;

	p_Table = Table;
	p_Table_sort = Table_sort;

	/*
	{ 0, 3, 3, 3, 3, 6 },
	{ 0, 1, 1, 4, 4, 4 },
	{ 0, 1, 2, 4, 4, 6 },
	{ 0, 2, 2, 5, 5, 5 },
	{ 0, 1, 2, 5, 5, 6 },
	{ 0, 1, 2, 6, 6, 6 } };//0列を出力用の列とする
	*/
	//	int index_mark[PLAYER_NUMBER] = { 0 };
	//	int majority[PLAYER_NUMBER] = { 0 };
	//	int adding[PLAYER_NUMBER] = { 0 };
	//	int comprasion[PLAYER_NUMBER] = { 0 };

	int check_rank_all[PLAYER_NUMBER] = { 0 };
	char buf[10];
	int check_judge_num[JUDGE_NUMBER] = { 0 };
	int judge_num = 0;
	int check_judge_numall = 0;

	int output_mode=0;//出力方法をコマンドライン引数から設定する

	// コマンドライン引数チェック
	if(argc == 1){
		fprintf(stdout, "コマンドライン引数なし。コンソール画面で入出力を行います。");
	}
	else if(argc == 2){
		fprintf(stdout, "コマンドライン引数から、出力モードを読み込みます。");
		fprintf(stdout, "0:console、1:csv");
		output_mode = atoi(argv[1]);
		// 入力チェックなし
	}	else if(argc > 2){
		fprintf(stdout, "コマンドライン引数が多いです");
		fprintf(stdout, "コマンド実行フォーマット「[実行ファイル] 引数1」");
	}




	do{
		// 初期化
		check_judge_numall = 1;

		// コンソール
		fprintf(stdout, "ジャッジの最大人数は：%d\n", JUDGE_NUMBER);
		fprintf(stdout, "ジャッジ番号を半角数字で入力してください（Ａ：1，　Ｂ：2，　Ｃ：3，…）\nジャッジ番号：");
		fprintf(stdout, "// 現在無限ループ中。。。\n");

		// 入力読み込み
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), stdin);

		//入力が半角数字かチェック
		judge_num = atoi(buf) - 1;//「0」~「ジャッジの数-1」をとる(インデックスのため)
		
		if(judge_num < 0 || judge_num >= JUDGE_NUMBER) {
			fprintf(stdout, "ジャッジ番号に誤りがあります。");
			check_judge_numall = 0;
			continue;
		}


		// すでに値が設定されていれば、重複登録
		if(Table[0][judge_num] != 0) {
			fprintf(stdout, "重複して登録しようとしています！\n");
			check_judge_numall = 0;
			continue;
		}
		int judged_rank = 0;
		int check_input_rank = 0;

		do {
			//初期化
			check_input_rank = 0;
			memset(check_rank_all, 0, sizeof(check_rank_all));

			fprintf(stdout, "順位をを半角数字(1~7)で入力してください\n");
			for (int i = 0; i < PLAYER_NUMBER; i++) {
				fprintf(stdout, "\n%d番目に踊った人の順位は？\n順位：", i + 1);
				fgets(buf, sizeof(buf), stdin);
				judged_rank = atoi(buf);
				Table[i][judge_num] = judged_rank;
				check_rank_all[judged_rank - 1] += 1; // 使った順位をカウントアップする
				
				// 次のループのため初期化
				memset(buf, 0, sizeof(buf));
			}
			
			// TODO バグあり。計算による入力チェックはナンセンス。333444と順位を入れると、１～６の合計値と一致し0となるため
			// check_input_rank が0になる。すなわち入力に問題なしと判断されてしまう。
			for (int i = 0; i < PLAYER_NUMBER; i++) {
				if(check_rank_all[i] != 1) {
					check_input_rank = 1;
					break;
				}
			}
			if (check_input_rank != 0) {
				fprintf(stdout, "入力ミスあり！\n");
			}

		} while (check_input_rank != 0);
		
		// TODO 終了条件を検討する必要がある
		// テーブルに0があれば未入力状態のため、それを条件に繰り返しを抜ける
		for(int i = 0; i < JUDGE_NUMBER; i++){
			if(Table[0][i] == 0){
				check_judge_numall =0;
				break;
			}
		}
	} while (check_judge_numall == 0);

	//カンマで切る

	//それぞれの選手に割り当てる

	//ほんとは選手を構造体化し、tableと結びつける。
	//	int b[PLAYER_NUMBER + 1] = { 1,1,1,1,1,1 };
		//input
		//まずは初期値として入れてみる
		//check input

		//Tableの入力
/*	int check = 0;
	do{
		fprintf(stdout, "Table input\n");
		fprintf(stdout, "Judge is 5 member\n");
		for (int j = 0; j < JUDGE_NUMBER; j++) {
			for (int i = 0; i < PLAYER_NUMBER; i++) {
				fprintf(stdout, "%dジャッジの%d番の順位は？", j, i);
				fprintf(stdin, "%d", Table[i][j]);
			}
			fprintf(stdout, "\n");
		}
		fprintf(stdout, "OK? (Yes = 1 / No = 0)\n");
		fprintf(stdin, "%d", check);
	}while(check != 1);
*/

	// メソッド分割

	//Tableの出力
	fprintf(stdout, "以下の内容で入力を受け付けました\n");
	// このような宣言はできない⇒ for( char alpha = 'A',int i =0; i < JUDGE_NUMBER; ++i, ++alpha){
	char alpha='A';
	for(int i =0; i < JUDGE_NUMBER; ++i){
		fprintf(stdout, "%c\t", alpha++);
		if(i == JUDGE_NUMBER -1){
		fprintf(stdout, "\n");
		}
	}
	for (int i = 0; i < PLAYER_NUMBER; i++) {
		for (int j = 0; j < JUDGE_NUMBER; j++) {
			fprintf(stdout, "%d\t", Table[i][j]);
		}
		fprintf(stdout, "\n");
	}
	//sort table ここに順位と入れ替えたテーブルを作成する
	for (int i = 0; i < PLAYER_NUMBER; i++) {
		for (int j = 0; j < JUDGE_NUMBER; j++) {
			Table_sort[i][j + 1] = Table[i][j];
		}
	}//クイックソート
	for (int i = 0; i < PLAYER_NUMBER; i++) {
		QSort(Table_sort[i], 1, JUDGE_NUMBER);
		Table_sort[i][0] = 1;//1位からどれだけ下がる（加算する）かでランキングするため1を入れている
	}
	//Table_sortの出力
	fprintf(stdout, "Table_sort \n");
	for (int i = 0; i < PLAYER_NUMBER; i++) {
		for (int j = 1; j < JUDGE_NUMBER + 1; j++) {
			fprintf(stdout, "%d\t", Table_sort[i][j]);
		}
		fprintf(stdout,"\n");
	}

	int center_num = PLAYER_NUMBER / 2;
	fprintf(stdout, "ジャッジの過半数 = %d\n", center_num);
	fprintf(stdout, "中央値 \n");
	for (int i = 0; i < PLAYER_NUMBER; i++) {
		fprintf(stdout, "%d番 %d\n", i, Table_sort[i][center_num]);
	}

	//skating開始
	int award_rank = 1;
	int check_rank = 1;

	//while (award_rank <= PLAYER_NUMBER) {
		//center check
	fprintf(stdout, "単純にソート\n");

	for (int i = 1; i < PLAYER_NUMBER; i++) {
		for (int j = 0; j <= i-1; j++) {
			if (Table_sort[j][center_num] < Table_sort[i][center_num]) {
				Table_sort[i][0]++;
			}
			if (Table_sort[j][center_num] > Table_sort[i][center_num]) {
				Table_sort[j][0]++;
			}
		}
	}

	majority(Table_sort);

	SumSuperior(Table_sort);

	SumSubordinate(Table_sort);

	// 結果
	// 出力結果を分けれるようにする
	// 　コンソール出力
	// 　ファイル出力
	if(output_mode == 0) {
		// console出力
		output_console(Table_sort);
	}else if(output_mode == 1){
		fprintf(outputfile, "csvファイルに出力します。");
		FILE *outputfile;
		outputfile = fopen(FILE_PATH FILE_NAME, "w");
		if(outputfile == NULL){
			fprintf(stdout, "ファイルオープン失敗\n");
			return 1;
		}


		// ===出力内容===
		fprintf(outputfile, "背番号,順位\n");
		for (int i = 0; i < PLAYER_NUMBER; i++) {
			fprintf(outputfile, "%d,%d\n", i, Table_sort[i][0]);
		}
		fclose(outputfile);
	}


	fprintf(stdout, "順位表　出力 \n");
	{
		int out_player_num = 0;
		for (int i = 1; i <= PLAYER_NUMBER; i++) {
			for (int j = 0; j < PLAYER_NUMBER;j++) {
				if (Table_sort[j][0] == i) {
					out_player_num = j;
				}
			}
			fprintf(stdout, "%d位　%d番\n", i, out_player_num);
		}
	}

		/*int i= 0;
		for (int index_player = 0; index_player < PLAYER_NUMBER; index_player++) {
			if (Table_sort[index_player][center_num] == check_rank) {
				index_mark[i] = index_player;
				i++;
			}
		}
		int INDEX_MARK_LEN = i;
		//same number 1
		//未確定順位の上位を与える　*
		if (INDEX_MARK_LEN == 1) {
			Table_sort[index_mark[i]][0] = award_rank;
			//continue;//なくてもよさそう？
		}
		else if (INDEX_MARK_LEN != 1) {
			//多数決
			for (int i = 0; i <= INDEX_MARK_LEN; i++) {
				int j = 0;
				while(j < JUDGE_NUMBER - center_num) {
					if (Table_sort[index_mark[i]][center_num + (j + 1)] == check_rank) {
						j++;
					}
				}
				majority[i] = j;
			}
			//k[i]の長さ比較
			int i = 0;
			if (majority[i] < majority[i + 1]) {
				if () {
				}
				Table_sort[index_mark[i]][0] = award_rank;
			}
			else if (majority[i] > majority[i + 1]) {

			}
			else if (majority[i] = majority[i + 1]) {
				//上位加算
				int check_sum[PLAYER_NUMBER] = NULL;
				for (int i = 0;;i++) {
					check_sum[index_mark[i]] += Table_sort[index_mark[i]][i];
				}
			}

	}
		check_rank++;
		}

			
			//same any numbers
				//多数決
					//*
					//上位加算
						//*
						//下位比較
							//*
							//同着処理

		//end for rank+jはする(j人順位が決まった) check_rank++;
	//end skating 未確定順位なし

	//output
	*/
	return 0;
}
