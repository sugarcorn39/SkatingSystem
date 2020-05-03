#include "setting.h"
#include "skatingModules.h"

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
							break;
						}
					}
				}
			}
		}
	}
}

// 過半数チェック(特定人数比較用) 未実装
/*
現在実装済みの過半数チェック関数は、
テーブル全体を渡す必要がある。
これは効率的ではない。（すでに順位が決まっている人は見る必要がない。）
実際に確認したいのは、中央の値が一致しているとき(3位の人が2人、3人いる時)に、
そのうちの誰が上位か判断する。
この部分のみ実装するように、関数を作成し、モジュール化することを目標とする
・戻り値
　1:過半数で決定あり
　0:過半数で決定なし
・引数
　1:選手の結果情報(人数が不定なので、工夫する必要がある)
　2:決定したい順位
　3:
int majority_(int _Table[PLAYER_NUMBER][JUDGE_NUMBER + 1]){
	// TODO
	return 0;
}
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
