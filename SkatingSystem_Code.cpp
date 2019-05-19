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



int main() {
	int Table[Player_number][Judge_number] = { {3,3,3,3,3},
												{1,2,4,4,1},
												{4,1,2,1,5},
												{5,5,5,5,4},
												{2,4,1,2,2},
												{6,6,6,6,6} };
	int Table_sort[Player_number][Judge_number + 1] = { {0} };

	int (*p_Table)[Judge_number] = NULL;
	int (*p_Table_sort)[Judge_number + 1] = NULL;

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
	//	int index_mark[Player_number] = { 0 };
	//	int majority[Player_number] = { 0 };
	//	int adding[Player_number] = { 0 };
	//	int comprasion[Player_number] = { 0 };

	int check_rank_all[Player_number] = { 0 };
	char buf[10];
	int check_judge_num[Judge_number] = { 0 };
	int check_judge_numall = 0;
	int judge_num = 0;
	do{
		memset(buf, 0, sizeof(buf));
		fprintf(stdout, "ジャッジ番号を半角数字で入力してください（Ａ：1，　Ｂ：2，　Ｃ：3，…）\nジャッジ番号：");
		fgets(buf, sizeof(buf), stdin);
		//	fprintf(stdout, "数字を出力\n");
		//	fprintf(stdout, buf);

		//入力が半角数字かチェック

		judge_num = atoi(buf) - 1;//「0」~「ジャッジの数-1」をとる(インデックスのため)
		//	fprintf(stdout, "数値を出力\n");
		//	fprintf(stdout, "%d", judge_num);

		check_judge_num[judge_num] += 1;//登録済み
		if (check_judge_num[judge_num] > 1) {
			fprintf(stdout, "重複して登録しようとしています！\n");
			check_judge_num[judge_num] = 0;//重複を防いでも書き換えられてしまっている
			continue;
		}
		int judged_rank = 0;
		int check_input_rank = 0;

		do {
			check_input_rank = 0;//初期化
			for (int i = 0; i < Player_number; i++) {
				check_rank_all[i] = i + 1;
			}
			fprintf(stdout, "順位をを半角数字(1~7)で入力してください\n");
			for (int i = 0; i < Player_number; i++) {
				fprintf(stdout, "\n%d番目に踊った人の順位は？\n順位：", i + 1);
				fgets(buf, sizeof(buf), stdin);
				judged_rank = atoi(buf);
				memset(buf, 0, sizeof(buf));
				Table[i][judge_num] = judged_rank;
				check_rank_all[judged_rank - 1] -= judged_rank;
			}
			for (int i = 0; i < Player_number; i++) {
				check_input_rank += check_rank_all[i];
				//							fprintf(stdout, "%d", check_input_rank);
				//							fprintf(stdout, " %d\n", check_rank_all[i]);

			}
			if (check_input_rank == 0) {
				fprintf(stdout, "入力に問題なし\n");
			}
			else {
				fprintf(stdout, "入力ミスあり！\n");
			}

		} while (check_input_rank != 0);
		for (check_judge_numall = 0; check_judge_numall < Judge_number; check_judge_numall++) {
			if (check_judge_num[check_judge_numall] != 1) {
				fprintf(stdout, "check_judge_num[%d] = %d\n", check_judge_numall, check_judge_num[check_judge_numall]);
				break;
			}
		}
		fprintf(stdout, "check_judge_numall　%d\n", check_judge_numall);
	} while (check_judge_numall != Judge_number);

	//カンマで切る

	//それぞれの選手に割り当てる

	//ほんとは選手を構造体化し、tableと結びつける。
	//	int b[Player_number + 1] = { 1,1,1,1,1,1 };
		//input
		//まずは初期値として入れてみる
		//check input

		//Tableの入力
/*	int check = 0;
	do{
		fprintf(stdout, "Table input\n");
		fprintf(stdout, "Judge is 5 member\n");
		for (int j = 0; j < Judge_number; j++) {
			for (int i = 0; i < Player_number; i++) {
				fprintf(stdout, "%dジャッジの%d番の順位は？", j, i);
				fprintf(stdin, "%d", Table[i][j]);
			}
			fprintf(stdout, "\n");
		}
		fprintf(stdout, "OK? (Yes = 1 / No = 0)\n");
		fprintf(stdin, "%d", check);
	}while(check != 1);
*/
		//Tableの出力
		fprintf(stdout, "以下の内容で入力を受け付けました\n");
		fprintf(stdout, "A\tB\tC\tD\tE\tF\tG\tH\n");
		for (int i = 0; i < Player_number; i++) {
			for (int j = 0; j < Judge_number; j++) {
				fprintf(stdout, "%d\t", Table[i][j]);
			}
			fprintf(stdout, "\n");
		}
	//sort table
	for (int i = 0; i < Player_number; i++) {
		for (int j = 0; j < Judge_number; j++) {
			Table_sort[i][j + 1] = Table[i][j];
		}
	}//クイックソート
	for (int i = 0; i < Player_number; i++) {
		QSort(Table_sort[i], 1, Judge_number);
		Table_sort[i][0] = 1;//1位からどれだけ下がる（加算する）かでランキングするため1を入れている
	}
	//Table_sortの出力
	fprintf(stdout, "Table_sort \n");
	for (int i = 0; i < Player_number; i++) {
		for (int j = 1; j < Judge_number + 1; j++) {
			fprintf(stdout, "%d\t", Table_sort[i][j]);
		}
		fprintf(stdout,"\n");
	}

	int center_num = Player_number / 2;
	fprintf(stdout, "center = %d\n", center_num);
	fprintf(stdout, "中央値 \n");
	for (int i = 0; i < Player_number; i++) {
		fprintf(stdout, "%d番 %d\n", i, Table_sort[i][center_num]);
	}

	//skating開始
	int award_rank = 1;
	int check_rank = 1;

	//while (award_rank <= Player_number) {
		//center check
	fprintf(stdout, "単純にソート\n");

		for (int i = 1; i < Player_number; i++) {
			for (int j = 0; j <= i-1; j++) {
//				fprintf(stdout, "処理前i=%d, j=%d, rank_i=%d, rank_j=%d", i, j, Table_sort[i][0], Table_sort[j][0]);

				if (Table_sort[j][center_num] < Table_sort[i][center_num]) {
					Table_sort[i][0]++;
				}
				if (Table_sort[j][center_num] > Table_sort[i][center_num]) {
					Table_sort[j][0]++;
				}
//				fprintf(stdout, "	処理後i=%d, j=%d, rank_i=%d, rank_j=%d\n", i, j, Table_sort[i][0], Table_sort[j][0]);
			}
		}

		fprintf(stdout, "過半数でソート\n");

		for (int i = 1; i < Player_number; i++) {
			for (int j = 0; j <= i - 1; j++) {
//				fprintf(stdout, "処理前i=%d, j=%d, rank_i=%d, rank_j=%d", i, j, Table_sort[i][0], Table_sort[j][0]);
				if (Table_sort[j][0] == Table_sort[i][0]) {
					//過半数
					int right = 0;
					int check_majority = Table_sort[i][center_num];
					while (right < Judge_number - center_num &&
						(Table_sort[j][center_num + (right)] == Table_sort[i][center_num + (right)])) {

						right++;
						if (Table_sort[i][center_num + (right - 1)] != Table_sort[i][center_num + (right)]) {
							if (Table_sort[j][center_num + (right - 1)] == Table_sort[j][center_num + (right)]) {
								Table_sort[i][0]++;
								break;
							}
						}
						if (Table_sort[j][center_num + (right - 1)] != Table_sort[j][center_num + (right)]) {
							if (Table_sort[i][center_num + (right - 1)] == Table_sort[i][center_num + (right)]) {
								Table_sort[j][0]++;
								break;//next 上位加算へ
							}
						}
					}
				}
//				fprintf(stdout, "	処理後i=%d, j=%d, rank_i=%d, rank_j=%d\n", i, j, Table_sort[i][0], Table_sort[j][0]);
			}
		}
		fprintf(stdout, "上位加算\n");
		for (int i = 1; i < Player_number; i++) {
			for (int j = 0; j <= i - 1; j++) {
//				fprintf(stdout, "処理前i=%d, j=%d, rank_i=%d, rank_j=%d", i, j, Table_sort[i][0], Table_sort[j][0]);
				if (Table_sort[j][0] == Table_sort[i][0]) {
					//上位加算
					int sum_i = 0;
					int sum_j = 0;
					for (int index = 1; index < center_num; index++) {
						sum_i += Table_sort[i][index];
						sum_j += Table_sort[j][index];
					}
					if (sum_j < sum_i) {
						Table_sort[i][0]++;
					}
					else if (sum_j > sum_i) {
						Table_sort[j][0]++;
					}
				}
//				fprintf(stdout, "	処理後i=%d, j=%d, rank_i=%d, rank_j=%d\n", i, j, Table_sort[i][0], Table_sort[j][0]);
			}
		}
		fprintf(stdout, "下位比較\n");
		for (int i = 1; i < Player_number; i++) {
			for (int j = 0; j <= i - 1; j++) {
//				fprintf(stdout, "処理前i=%d, j=%d, rank_i=%d, rank_j=%d", i, j, Table_sort[i][0], Table_sort[j][0]);
				if (Table_sort[j][0] == Table_sort[i][0]) {
					//下位比較
					int right = 0;
					while (right < Judge_number - center_num &&
						(Table_sort[j][center_num + (right)] == Table_sort[i][center_num + (right)])) {
						right++;
						if (Table_sort[j][center_num + (right)] < Table_sort[i][center_num + (right)]) {
							Table_sort[i][0]++;
							break;
						}
						if (Table_sort[j][center_num + (right)] > Table_sort[i][center_num + (right)]) {
							Table_sort[j][0]++;
							break;
						}
					}
					//同着
				}
//				fprintf(stdout, "	処理後i=%d, j=%d, rank_i=%d, rank_j=%d\n", i, j, Table_sort[i][0], Table_sort[j][0]);
			}
		}
		//kekka
		fprintf(stdout, "結果 \n");
		for (int i = 0; i < Player_number; i++) {
			fprintf(stdout, "%d番　%d位\n", i, Table_sort[i][0]);
		}

		fprintf(stdout, "順位表　出力 \n");
		{
			int out_player_num = 0;
			for (int i = 1; i <= Player_number; i++) {
				for (int j = 0; j < Player_number;j++) {
					if (Table_sort[j][0] == i) {
						out_player_num = j;
					}
				}
				fprintf(stdout, "%d位　%d番\n", i, out_player_num);
			}

		}

		/*int i= 0;
		for (int index_player = 0; index_player < Player_number; index_player++) {
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
				while(j < Judge_number - center_num) {
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
				int check_sum[Player_number] = NULL;
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
