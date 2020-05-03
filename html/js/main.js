

// 繰り返しの数は選手の数に一致する
// 今回はベタで6人
const PLAYER_NUM = 6;

// 重複を確認するメソッド
const getDuplicateValues = ([...array]) => {
    return array.filter((value, index, self) => self.indexOf(value) === index && self.lastIndexOf(value) !== index);
}
/*
function makeTable(data, tableId){
    var rows=[];
    var table = document.createElement("table");
    for(i = 0; i < data.length; i++){
        rows.push(table.insertRow(-1));
        for(j = 0; j < data[0].length; j++){
            cell=rows[i].insertCell(-1);
            cell.appendChild(document.createTextNode(data[i][j]));
            if(i==0){
                cell.style.backgroundColor = "#bbb";
            }else { 
                cell.style.backgroundColor = "#ddd";
            }
        }
    }
    document.getElementById(tableId).appendChild(table); 
}
*/
/*
function func1() {
    var player1 = document.getElementsByName("player1");
    var player2 = document.getElementsByName("player2");
    var player3 = document.getElementsByName("player3");
    var player4 = document.getElementsByName("player4");
    var player5 = document.getElementsByName("player5");
    var player6 = document.getElementsByName("player6");
    for(var i = 0; i < player1.length; i++){
        if(player1[i].checked) {
            console.log("player1選択された値：", player1[i].value);
        }

        if(player2[i].checked) {
            console.log("player2選択された値：", player2[i].value);
        }

        if(player3[i].checked) {
            console.log("player3選択された値：", player3[i].value);
        }
    }
}
func1();
 */

function checkNumber(){
    // 設定開始（チェックする項目を設定してください）
    var elements = [];

    for(i = 1 ; i <= PLAYER_NUM; i++){
        for(j = 1 ; j <= PLAYER_NUM; j++){
            // 要素を取得し、格納する
            elements.push(document.getElementById("player" + i + "-rank" + j));
        }
    }

    // 選択されている順位をリストに格納。
    var check_number_list = [];
    for(i = 0 ; i < PLAYER_NUM * PLAYER_NUM; i++){
        if(elements[i].checked){
            check_number_list.push(elements[i].value);
            console.log("player"+  Math.floor(i/PLAYER_NUM+1) +"-rank"+ (i%PLAYER_NUM+1)+ ":" + elements[i].value);
        }
    }

    // リスト内になる重複を取得する
    var duplicate_values = getDuplicateValues(check_number_list);

    // 重複があれば、ダイアログを表示する。
	if(duplicate_values.length > 0){
        window.alert('重複があります。評価内容を見直してください。'); // 重複がある場合、警告ダイアログを表示
        
        // TODO どの順位に重複があるのか知らせる 色の変化を追加する

        // 送信を中止する
		return false;
	}
	else{
        // 入力内容を表示する
		return true; // 送信を実行
	}
}



/*ページ(DOM)読み込み後に実行*/
window.onload = function(){

    //tbodyのIDを取得(この中で処理します)
    var tbody = document.getElementById('tbodyID');

    // 背番号のランダム表示のために使用。
    const min = 100;
    const max = 999;

    // TODO 選手の背番号リストが欲しいな

    for (i = 1; i <= PLAYER_NUM; i++){
        //tr エレメントを新規作成(ただ生成するだけ)
        var tr = document.createElement('tr');
        //列(td)用のループ
        for (j = 0; j <= PLAYER_NUM; j++){
            //tdエレメントをを生成
            var td = document.createElement('td');

            if(j == 0){
                // 最初は選手名を格納する
                var number = Math.floor( Math.random() * (max + 1 - min) ) + min ;
                td.innerHTML = '背番号 ' + number;
                tbody.appendChild(td);
                continue;
            }
            //tdの中に入れたいモノをセット
            if(j == 1){
                // 1位の場合はcheckedにする
                td.innerHTML = '<input type="radio" name="player'+ i + '" value="' + j + '" id="player'+ i + '-rank' + j + '" checked="checked"><label for="player' + i + '-rank' + j + '" class="label">' + j + '位</label>';
            } else{
                // そうでない場合はcheckedはつけない
                td.innerHTML = '<input type="radio" name="player'+ i + '" value="' + j + '" id="player'+ i + '-rank' + j + '"><label for="player' + i + '-rank' + j + '" class="label">' + j + '位</label>';
            }
            //生成したtdをtrにセット
            tbody.appendChild(td);
        }//列用のループ閉じ
        //tr エレメントをtbody内に追加(ここではじめて表示される)
        tbody.appendChild(tr);
    }//行用のループ閉じ

}
