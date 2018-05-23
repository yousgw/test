#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996)

/*
文字列入力部のエラー処理

仕様書提出後の変更点
ファイル入力で点数読み取り時にヌルを自動で打つように設定
ケース文で文字が入力されたときのための対処
*/

#define limit 50

int contents, members, i, j, cont;
unsigned int k;

void reset(), setting(), inputpoints(), inputfiles(), checkinputs();
void dels(), adds(), mods(), delmember(), delcontent(), addmember(), addcontent(), modmember(), modcontent(), modpoint(), culc();
void outputall(), outputfaults(), outputrep(), outputrank(), outputfiles();

int inputmenu(), outputmenu();

struct points {
	char content[limit][limit];
	int point[limit];
	int sum;
	float ave;
	int fault;
	int out;
};

struct	mates {
	char member[limit][limit];
	struct points grade[limit];
}data;

int main() {
	int choices;

	reset();
	for (;;) {
		for (;;) {
			choices = 0;

			choices = inputmenu();
			printf("---------------------------------------------------\n");
			switch (choices) {
			case 1:
				setting();
				inputpoints();
				checkinputs();
				break;
			case 2:
				inputfiles();
				checkinputs();
				break;
			case 3:
				adds();
				break;
			case 4:
				mods();
				break;
			case 5:
				dels();
				break;
			case 6:
				break;
			default:
				printf("入力された数値が不適切です。再入力してください。\n");
				break;
			}
			if (choices == 6) {
				break;
			}
			printf("---------------------------------------------------\n");
		}

		culc();

		for (;;) {
			choices = outputmenu();
			printf("---------------------------------------------------\n");
			switch (choices) {
			case 1:
				outputall();
				break;
			case 2:
				outputfaults();
				break;
			case 3:
				outputrep();
				break;
			case 4:
				outputrank();
				break;
			case 5:
				outputfiles();
				break;
			case 6:
				break;
			case 7:
				exit(0);
				break;
			default:
				printf("入力された数値が不適切です。再入力してください。\n");
				break;
			}
			if (choices == 6) {
				break;
			}
			printf("---------------------------------------------------\n");
		}
	}

	return 0;
}

void reset() {
	for (i = 0; i < limit; i++) {
		for (j = 0; j < limit; j++) {
			data.member[i][j] = '\0';
		}
		for (j = 0; j < limit; j++) {
			for (k = 0; k < limit; k++) {
				data.grade[i].content[j][k] = '\0';
			}
			data.grade[i].point[j] = 0;
		}
		data.grade[i].sum = 0;
		data.grade[i].ave = 0.0;
		data.grade[i].fault = 0;
		data.grade[i].out = 0;
	}
	contents = 0;
	members = 0;
	i = 0;
	j = 0;
	cont = 0;
	k = 0;
}

int inputmenu() {
	char  r[limit];
	printf("入力menu\n何をしますか？\n");
	printf("入力方法を選択してください。\n1:手動入力\n2:ファイル入力\n3:追加\n4:修正\n5:削除\n6:出力menuへ移動\n");
	printf("->");
	scanf("%s", r);
	if (strlen(r) == 1) {
		return r[0] - 48;
	}
	else {
		return 0;
	}
}

void setting() {
	char contname[limit];

	printf("入力したい人数を入力してください。\n");
	scanf("%d", &members);
	printf("入力する人の名前を順番に入力してください。\n");
	for (i = 0; i<members; i++) {
		scanf("%s", data.member[i]);
	}

	printf("入力したい科目数を入力してください。\n");
	scanf("%d", &contents);
	printf("入力する科目名を順番に入力してください。\n");
	for (i = 0; i<contents; i++) {
		scanf("%s", contname);
		for (j = 0; j < members; j++) {
			for (k = 0; k <= strlen(contname); k++) {
				data.grade[j].content[i][k] = contname[k];
			}
		}
	}
}

void inputfiles() {
	FILE *fi;
	char c, fname[limit], p[limit], string[limit*2];

	i = 0;
	j = 0;
	members = 0;
	contents = 0;

	printf("入力に使用するファイル名を入力してください。\n");
	for(;;){
		scanf("%s", );
		if()
		
		fi = fopen(fname, "r");
	 		if(fi == '\0'){
				printf("そのようなファイルは存在しません。\n");
				printf("再度ファイル名を入力してください。\n");
			}else break;
		}
	}
	
	for (;;) {//一行目の読み飛ばし
		c = fgetc(fi);
		if (c == '\n')break;
	}
	for (;;) {
		c = fgetc(fi);
		if (c != EOF) {
			fseek(fi, -1, 1);
			fscanf(fi, "%[^,]", data.member[members]);
			members++;
			for (;;) {//点数の読み飛ばし
				c = fgetc(fi);
				if (c == '\n')break;
			}
		}
		else {
			//printf("end\n");
			break;
		}
	}//membersの設定完了

	rewind(fi);

	for (;;) {//科目名までシーク
		c = fgetc(fi);
		if (c == ',')break;
	}
	for (;;) {//科目名の読み取り
		c = fgetc(fi);
		if (c == '\n')break;
		else if (c == ',') {
			k = 0;
			contents++;
		}
		else {
			for (j = 0; j < members; j++) {
				data.grade[j].content[contents][k] = c;
			}
			k++;
		}
	}
	contents++;
	//contentsの設定完了

	rewind(fi);

	for (;;) {
		c = fgetc(fi);
		if (c == '\n') {
			break;
		}
	}

	for (i = 0; i < members; i++) {
		for (;;) {//点数までシーク
			c = fgetc(fi);
			if (c == ',')break;
		}
		j = 0;
		for (;;) {
			c = fgetc(fi);	printf("%c", c);
			if (c == '-') {
				data.grade[i].point[j] = -1;
				fseek(fi, 1, 1);
			}
			else {
				k = 0;
				p[k] = c;
				for (;;) {
					c = fgetc(fi);	printf("%c", c);
					if (c == ',') {
						break;
					}
					else if (c == '\n') {
						break;
					}
					else {
						k++;
						p[k] = c;
					}
				}
				p[k + 1] = '\0';
				data.grade[i].point[j] = atoi(p);
			}
			j++;
			if (c == '\n') {
				break;
			}
		}
	}
	fclose(fi);
	printf("ファイルによる入力が終了しました。\n");
	outputall();
}

void checkinputs() {
	printf("入力された数値が適切かどうか確認します。\n");
	for (i = 0; i < members; i++) {
		for (j = 0; j < contents; j++) {
			if (100 < data.grade[i].point[j]) {
				printf("不適切な数値が見つかりました。\n修正してください。\n");
				printf("%s\n  不適切な数値:%d\n  %s:", data.member[i], data.grade[i].point[j], data.grade[i].content[j]);
				scanf("%d", &data.grade[i].point[j]);
			}
		}
	}
	printf("数値の確認が終了しました。\n");
}

void inputpoints() {
	for (i = 0; i < members; i++) {
		data.grade[i].sum = 0;
		data.grade[i].ave = 0.0;
		data.grade[i].fault = 0;
		data.grade[i].out = 0;
	}//全員の値をリセット

	printf("点数を入力します。(履修していない科目は負の数を入力してください。)\n");

	for (i = 0; i<members; i++) {
		printf("%s\n", data.member[i]);
		for (j = 0; j<contents; j++) {
			printf("%s:", data.grade[i].content[j]);
			scanf("%d", &data.grade[i].point[j]);
		}
	}
}

void adds() {
	int r;
	for (;;) {
		printf("どの項目を追加しますか？\n");
		printf("1:学生\n2:科目\n3:戻る\n");
		printf("->");
		scanf("%d", &r);
		switch (r) {
		case 1:
			addmember();
			break;
		case 2:
			addcontent();
			break;
		case 3:
			break;
		default:
			printf("入力された数値が不適切です。再入力してください。\n");
			break;
		}
		if (r == 3) {
			break;
		}
	}
}

void addmember() {
	int r;

	printf("追加したい人数を入力してください。\n");
	printf("->");
	scanf("%d", &r);
	printf("追加したい学生の名前を入力してください。\n");
	for (i = 0; i < r; i++) {
		scanf("%s", data.member[members + i]);
	}

	for (i = 0; i < contents; i++) {
		for (j = 0; j < r; j++) {
			for (k = 0; k <= strlen(data.grade[0].content[i]); k++) {
				data.grade[members + j].content[i][k] = data.grade[0].content[i][k];
			}
		}
	}

	printf("追加した学生の点数を入力してください。\n");
	for (i = 0; i < r; i++) {
		printf("%s\n", data.member[members + i]);
		for (j = 0; j < contents; j++) {
			printf("  %s:", data.grade[i].content[j]);
			scanf("%d", &data.grade[members + i].point[j]);
		}
	}
	members += r;
}

void addcontent() {
	int r;
	char contname[limit];

	printf("追加したい科目数を入力してください。\n");
	printf("->");
	scanf("%d", &r);
	printf("追加する科目名を順番に入力してください。\n");
	for (i = 0; i < r; i++) {
		scanf("%s", contname);
		for (j = 0; j < members; j++) {
			for (k = 0; k <= strlen(contname); k++) {
				data.grade[j].content[i + contents][k] = contname[k];
			}
		}
	}

	printf("追加した科目の点数を入力してください。\n");
	for (i = 0; i < members; i++) {
		printf("%s\n", data.member[i]);
		for (j = 0; j < r; j++) {
			printf("  %s:", data.grade[i].content[j + contents]);
			scanf("%d", &data.grade[i].point[j + contents]);
		}
	}
	contents += r;
}

void mods() {
	int r;
	for (;;) {
		printf("どの項目を修正しますか？\n");
		printf("1:学生\n2:科目\n3:点数\n4:戻る\n");
		printf("->");
		scanf("%d", &r);
		switch (r) {
		case 1:
			modmember();
			break;
		case 2:
			modcontent();
			break;
		case 3:
			modpoint();
			break;
		case 4:
			break;
		default:
			printf("入力された数値が不適切です。再入力してください。\n");
			break;
		}
		if (r == 4) {
			break;
		}
	}
}

void modmember() {
	int r;

	printf("修正したい学生を選んでください\n");
	for (i = 0; i < members; i++) {
		printf("%d:%s\n", i + 1, data.member[i]);
	}
	printf("->");
	scanf("%d", &r);

	printf("修正後の名前を入力してください。\n");
	printf("%s -> ", data.member[r - 1]);
	scanf("%s", data.member[r - 1]);
	printf("修正しました。\n");
}

void modcontent() {
	int r;
	char contname[limit];

	printf("修正したい科目を選んでください。\n");
	for (i = 0; i < contents; i++) {
		printf("%d:%s\n", i + 1, data.grade[0].content[i]);
	}
	printf("->");
	scanf("%d", &r);

	printf("修正後の科目名を入力してください。\n");
	printf("%s -> ", data.grade[0].content[r - 1]);
	scanf("%s", contname);

	for (j = 0; j < members; j++) {
		for (k = 0; k <= strlen(contname); k++) {
			data.grade[j].content[r - 1][k] = contname[k];
		}
	}

	printf("修正しました。\n");
}

void modpoint() {
	int r, s;

	printf("修正したい点数を持つ学生を選んでください。\n");
	for (i = 0; i < members; i++) {
		printf("%d:%s\n", i + 1, data.member[i]);
	}
	printf("->");
	scanf("%d", &r);

	printf("修正したい点数の科目を選んでください。\n");
	for (i = 0; i < contents; i++) {
		printf("%d:%s:", i + 1, data.grade[r - 1].content[i]);
		if (data.grade[r - 1].point[i] < 0) {
			printf("履修していません\n");
		}
		else {
			printf("%d点\n", data.grade[r - 1].point[i]);
		}
	}
	printf("->");
	scanf("%d", &s);

	printf("修正後の点数を入力してください。\n");
	printf("%s:%s:\n", data.member[r - 1], data.grade[r - 1].content[s - 1]);
	printf("  現在");
	if (data.grade[r - 1].point[s - 1] < 0) {
		printf("履修していません ");
	}
	else {
		printf("%d点 ", data.grade[r - 1].point[s - 1]);
	}
	printf("->");
	scanf("%d", &data.grade[r - 1].point[s - 1]);
	printf("修正しました。\n");
}

void dels() {
	int r;
	for (;;) {
		printf("どの項目を削除しますか？\n");
		printf("1:学生\n2:科目\n3:戻る\n");
		printf("->");
		scanf("%d", &r);
		switch (r) {
		case 1:
			delmember();
			break;
		case 2:
			delcontent();
			break;
		case 3:
			break;
		default:
			printf("入力された数値が不適切です。再入力してください。\n");
			break;
		}
		if (r == 3) {
			break;
		}
	}
}

void delmember() {
	int r, s;

	printf("削除する学生を選んでください。\n");
	for (i = 0; i < members; i++) {
		printf("%d:%s\n", i + 1, data.member[i]);
	}
	printf("->");
	scanf("%d", &r);

	printf("本当に削除してもよろしいですか？\n1:はい\n2:いいえ\n");
	printf("->");
	scanf("%d", &s);

	switch (s) {
	case 1:
		for (i = r; i < members; i++) {
			for (k = 0; k <= strlen(data.member[i]); k++) {
				data.member[i - 1][k] = data.member[i][k];
			}//名前の移行
			for (j = 0; j < contents; j++) {
				data.grade[i - 1].point[j] = data.grade[i].point[j];
			}//点数の移行
		}
		members--;
		printf("削除しました。\n");
		break;
	case 2:
		break;
	default:
		printf("入力された数字が不適切です。\n");
		printf("作業を中断します。\n");
		break;
	}
}

void delcontent() {
	int r, s;

	printf("削除する科目を選んでください。\n");
	for (i = 0; i < contents; i++) {
		printf("%d:%s\n", i + 1, data.grade[0].content[i]);
	}
	printf("->");
	scanf("%d", &r);

	printf("本当に削除してもよろしいですか？\n1:はい\n2:いいえ\n");
	printf("->");
	scanf("%d", &s);

	switch (s) {
	case 1:
		for (i = r; i < contents; i++) {
			for (j = 0; j < members; j++) {
				for (k = 0; k <= strlen(data.grade[j].content[i]); k++) {
					data.grade[j].content[i - 1][k] = data.grade[j].content[i][k];
				}
			}//科目名の移行
			for (j = 0; j < members; j++) {
				data.grade[j].point[i - 1] = data.grade[j].point[i];
			}//点数の移行
		}
		contents--;
		printf("削除しました。\n");
		break;
	case 2:
		break;
	default:
		printf("入力された数字が不適切です。\n");
		printf("作業を中断します。\n");
		break;
	}
}

void culc() {
	for (i = 0; i < members; i++) {
		cont = contents;		//科目数リセット
		for (j = 0; j < contents; j++) {
			if (data.grade[i].point[j] >= 0) {
				data.grade[i].sum += data.grade[i].point[j];//履修した科目のみ合計点に加算
				if (30 <= data.grade[i].point[j] && data.grade[i].point[j] < 60) {
					data.grade[i].fault++;//欠点のカウント
				}
				else if (data.grade[i].point[j] < 30) {
					data.grade[i].out++;//失点のカウント
				}
			}
			else {
				cont--;		//履修していない科目数を除く
			}
		}
		data.grade[i].ave = (float)data.grade[i].sum / (float)cont;
	}
}

int outputmenu() {
	char  r[limit];
	printf("出力menu\n何をしますか？\n");
	printf("1:点数をすべて表示\n2:欠点数表示\n3:留年者表示\n4:順位表示\n5:ファイル出力\n6:入力menuへ移動\n7:終了\n");
	printf("->");
	scanf("%s", r);
	if (strlen(r) == 1) {
		return r[0] - 48;
	}
	else {
		return 0;
	}
}

void outputall() {
	printf("入力した点数をすべて出力します。\n");
	for (i = 0; i < members; i++) {
		printf("%s\n", data.member[i]);
		for (j = 0; j < contents; j++) {
			if (data.grade[i].point[j] < 0) {
				printf("  %s:履修していません\n", data.grade[i].content[j]);
			}
			else {
				printf("  %s:%d点\n", data.grade[i].content[j], data.grade[i].point[j]);
			}
		}
		printf("  平均点:%.1f点\n", data.grade[i].ave);
	}
}

void outputfaults() {
	int flag;

	flag = 0;
	printf("欠点所持者の欠点個数を表示します。\n");
	for (i = 0; i < members; i++) {
		if (data.grade[i].fault != 0) {
			printf("  %s:%d個\n", data.member[i], data.grade[i].fault);
			flag = 1;
		}
	}
	if (flag == 1) {
		printf("欠点所持者はいません。\n");
	}
}

void outputrep() {
	int r, flag;

	flag = 0;
	printf("留年者を表示します。\n");
	printf("どちらの基準で判定しますか？\n");
	printf("1:高校課程\n2:大学課程\n->");
	scanf("%d", &r);
	printf("留年者は、\n");
	switch (r) {
	case 1:
		for (i = 0; i < members; i++) {
			if (data.grade[i].fault > 3 || data.grade[i].out != 0 || data.grade[i].ave < 60) {
				printf("  %s\n", data.member[i]);
				flag = 1;
			}
		}
		break;
	default:
		for (i = 0; i < members; i++) {
			if (data.grade[i].fault > 5 || data.grade[i].out != 0 || data.grade[i].ave < 60) {
				printf("  %s\n", data.member[i]);
				flag = 1;
			}
		}
		break;
	}
	if (flag == 1) {
		printf("です。\n");
	}
	else {
		printf("いません。\n");
	}
}

void outputrank() {
	int r, keep, number[limit];
	printf("成績を上位から順に表示します。\n");
	printf("どれを基準に表示しますか？\n");
	for (i = 0; i <= contents; i++) {
		if (i == contents) {
			printf("%d:平均点\n", i + 1);
			break;
		}
		printf("%d:%s\n", i + 1, data.grade[0].content[i]);
	}
	printf("->");
	scanf("%d", &r);
	for (i = 0; i <= contents; i++) {
		if (i == r - 1)break;
	}//選択した値をＩで記憶

	if (i == contents) {//平均点でのソート
		float keepf, rank[limit];
		for (j = 0; j < members; j++) {
			rank[j] = data.grade[j].ave;
			number[j] = j;
		}//0に点数、1に学生の番号
		for (i = 0; i < members; i++) {
			for (j = 0; j < members; j++) {
				if (rank[i] > rank[j]) {
					keepf = rank[i];
					rank[i] = rank[j];
					rank[j] = keepf;//点数の並び替え
					keep = number[i];
					number[i] = number[j];
					number[j] = keep;//番号の並び替え
				}
			}
		}

		for (i = 0; i < members; i++) {
			if (i == 0) {//１位の処理
				printf("%d位:%s,%.2f点\n", i + 1, data.member[number[i]], rank[i]);
				r = 0;
			}
			else if (rank[i - 1] == rank[i]) {//同率の処理
				printf("%d位:%s,%.2f点\n", i - r, data.member[number[i]], rank[i]);
				r++;
			}
			else {//通常の処理
				printf("%d位:%s,%.2f点\n", i + 1, data.member[number[i]], rank[i]);
				r = 0;
			}
		}
	}
	else {//教科でのソート
		int rank[limit];
		for (j = 0; j < members; j++) {
			rank[j] = data.grade[j].point[i];
			number[j] = j;
		}//0に点数、1に学生の番号
		for (i = 0; i < members; i++) {
			for (j = 0; j < members; j++) {
				if (rank[i] > rank[j]) {
					keep = rank[i];
					rank[i] = rank[j];
					rank[j] = keep;//点数の並び替え
					keep = number[i];
					number[i] = number[j];
					number[j] = keep;//番号の並び替え
				}
			}
		}

		for (i = 0; i < members; i++) {
			if (rank[i] < 0) {//履修していない場合の処理(平均点が負はないので不必要)
				break;
			}
			else if (i == 0) {//１位の処理
				printf("%d位:%s,%d点\n", i + 1, data.member[number[i]], rank[i]);
				r = 0;
			}
			else if (rank[i - 1] == rank[i]) {//同率の処理
				printf("%d位:%s,%d点\n", i - r, data.member[number[i]], rank[i]);
				r++;
			}
			else {//通常の処理
				printf("%d位:%s,%d点\n", i + 1, data.member[number[i]], rank[i]);
				r = 0;
			}
		}
	}
}

void outputfiles() {
	FILE *fo;
	char fname[limit];

	printf("出力するファイル名を入力してください。\n");
	scanf("%s", fname);
	fo = fopen(fname, "w");
	
	fprintf(fo, "name");
	for (i = 0; i<contents; i++) {//一行目に科目を出力
		fprintf(fo, ",");
		fprintf(fo, "%s", data.grade[0].content[i]);
	}
	fprintf(fo, "\n");
	for (i = 0; i<members; i++) {//二行目以降に名前,点数,点数,...のように表示
		fprintf(fo, "%s", data.member[i]);
		for (j = 0; j<contents; j++) {
			if (0 <= data.grade[i].point[j]) {
				fprintf(fo, ",%d", data.grade[i].point[j]);
			}
			else {
				fprintf(fo, ",-");
			}
		}
		fprintf(fo, "\n");
	}
	fclose(fo);
	printf("指定されたファイルへの出力が完了しました。\n");
}
