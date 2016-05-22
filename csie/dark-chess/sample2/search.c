/*  DarkChess Search Engine V1.0 -- by Bo-Nian Chen, TA of Theory of Computer Games  professor: Tsan-sheng Hsu
	This source code cannot be used out of of the class unless asking for permission first.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define RED			0
#define BLACK		1

#define MOVE_PIECE		0
#define REVEAL_PIECE	1

#define BOARD_SIZE	60
#define PIECE_NUM	32
#define PIECE_TYPE	15
#define EMPTY		0
#define INVALID		-1
#define DARK		15
#define MAX_SCORE	32768
#define MAX_MOVE	72

//#define DEBUG

// 紅方 or 黑方
#define COLOR(x) ((x - 1) / 7)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int score_lower_bound, best_move_type, best_src, best_dest;
int board[BOARD_SIZE], temp_board[BOARD_SIZE];
int piece_num[PIECE_TYPE];
int reveal_piece_type[PIECE_TYPE];
int dark_num, red_num, black_num;
int max_depth;
clock_t clock_limit;
__int64 pos_key[32][16], piece_key[14][6], turn_key[3];
__int64 position[500];
int n_ply;
int src_seq[500];
int dest_seq[500];
int best_src_seq[500];
int best_dest_seq[500];
int z;



// 讀取盤面檔
int input_board(const char *board_file, int board[BOARD_SIZE], int piece_num[BOARD_SIZE], int *ply, int *turn, int *time_limit)
{
	int i, piece;
	FILE *fp;
	fp = fopen(board_file, "rt");
	if(fp == NULL){
		//printf("cannot open input file \"%s\"\n", board_file);
		return 0;
	}
	fscanf(fp, "%d %d", ply, turn);
	for(i = 0; i < PIECE_TYPE - 1; i++)
		fscanf(fp, "%d", &piece_num[i]);
	for(i = 0; i < BOARD_SIZE; i++)
		if(i % 6 == 0 || i % 6 == 5 || i / 6 == 0 || i / 6 == 9)
			board[i] = INVALID;
		else
			board[i] = EMPTY;
	for(i = 0; i < BOARD_SIZE; i++){
		if(board[i] == INVALID)
			continue;
		fscanf(fp, "%d", &piece);
		if(piece < 0 || piece > PIECE_TYPE){
			printf("board data error\n");
			exit(1);
		}
		board[i] = piece;
	}
	fscanf(fp, "%d", time_limit);
	fclose(fp);
	return 1;

}

// 計算蓋住棋子個數
int get_dark_num(int board[BOARD_SIZE])
{
	int i, dark = 0;
	for(i = 0; i < BOARD_SIZE; i++){
		if(board[i] == INVALID)
			continue;
		if(board[i] == DARK)
			dark++;
	}
	return dark;
}

// 計算各類棋子數
int get_piece_num(int color, int *piece_num)
{
	int i, num = 0;
	if(color == RED){
		for(i = 0; i < 7; i++)
			num += piece_num[i];
	}
	else{
		for(i = 7; i < 14; i++)
			num += piece_num[i];
	}
	return num;
}

// 判斷pce1是否可吃pce2
int valid_capture(int pce1, int pce2)
{
	int sort1 = (pce1 - 1) % 7;
	int sort2 = (pce2 - 1) % 7;
	if(sort1 == 0 && sort2 == 6)
		return 0;
	if(sort1 == 5)
		return 1;
	if(sort1 == 6){
		if(sort2 != 0 && sort2 != 6)
			return 0;
	}
	else if(sort1 > sort2)
		return 0;
	return 1;

}

// 走法產生器
// 走法排序: 吃子優先
// cap_src, cap_dest, m: 吃子走法
// src, dest, n: 一般走法
void move_gen(int board[BOARD_SIZE], int turn, int *src, int *dest, int *n, int *cap_src, int *cap_dest, int *m)
{
	int i, j, k, t;
	int dir[4] = {-1, 1, -6, 6};
	int place;

	*n = *m = 0;
	for(i = 0; i < BOARD_SIZE; i++){
		if(board[i] != INVALID && board[i] != EMPTY && board[i] != DARK && turn == COLOR(board[i])){
			// 產生一般棋子走法(移動至相鄰格子)
			for(j = 0; j < 4; j++){
				place = i + dir[j];
				if(board[place] == INVALID || board[place] == DARK)
					continue;
				if(board[place] != EMPTY){
					if((board[i] - 1) % 7 == 5)
						continue;
					if(COLOR(board[place]) == COLOR(board[i]))
						continue;
					if(!valid_capture(board[i], board[place]))
						continue;
					else{
						cap_src[*m] = i;
						cap_dest[*m] = place;
						(*m)++;
					}
				}
				else{
					src[*n] = i;
					dest[*n] = place;
					(*n)++;
				}
			}
			// 產生炮吃子走法(隔一子吃子)
			if((board[i] - 1) % 7 == 5){
				for(j = 0; j < 4; j++)
					for(t = 0, k = i + dir[j]; board[k] != INVALID; k += dir[j]){
						if(board[k] != EMPTY)
							t++;
						if(t == 2){
							if(board[k] != DARK && COLOR(board[i]) != COLOR(board[k]) && valid_capture(board[i], board[k])){
								cap_src[*m] = i;
								cap_dest[*m] = k;
								(*m)++;
							}
							break;
						}

					}
			}
		}
	}
}

// 產生所有可翻子走法
void reveal_gen(int board[BOARD_SIZE], int *reveal, int *k)
{
	int i;
	*k = 0;
	for(i = 0; i < BOARD_SIZE; i++)
		if(board[i] == DARK){
			reveal[*k] = i;
			(*k)++;
		}
}

// 走子
// 會記錄red_num, black_num以做為search的終止條件
// 記錄吃子, 在unmove時會用到
int move(int board[BOARD_SIZE], int piece_num[PIECE_TYPE], int *red_num, int *black_num, int src, int dest)
{
	int cap = board[dest];
	board[dest] = board[src];
	board[src] = EMPTY;
	if(cap != EMPTY){
		piece_num[cap - 1]--;
		if(COLOR(cap) == RED)
			(*red_num)--;
		else
			(*black_num)--;
	}
	return cap;
}

// 復原走子(將盤面恢復到未走子前)
// 會一併復原red_num與black_num
void unmove(int board[BOARD_SIZE], int piece_num[PIECE_TYPE], int *red_num, int *black_num, int src, int dest, int cap)
{
	board[src] = board[dest];
	board[dest] = cap;
	if(cap != EMPTY){
		piece_num[cap - 1]++;
		if(COLOR(cap) == RED)
			(*red_num)++;
		else
			(*black_num)++;
	}
}

// 審局函數(簡易的weighted-sum of piece value)
int eval(int piece_num[PIECE_TYPE])
{
	int w[14] = {2048, 512, 128, 32, 8, 128, 1, -2048, -512, -128, -32, -8, -128, -1};
	int i, score = 0;
	for(i = 0; i < 14; i++)
		score += w[i] * piece_num[i];
	return score;
}

// Nega-max演算法(recursive)
// board: 盤面資訊(0~59), 表示法如下(X:邊界, 0:棋盤格子):
// XXXXXX
// X0000X
// X0000X
// X0000X
// X0000X
// X0000X
// X0000X
// X0000X
// X0000X
// XXXXXX
//
// piece_num: 記錄各兵種之存活棋子數
// dark_num: 記錄可翻棋子數
// red_num, black_num: 紅黑存活棋子數
// turn: 輪走方
// depth: 目前深度
// max_depth: 最大深度
int search(int board[BOARD_SIZE], int piece_num[PIECE_TYPE], int dark_num, int red_num, int black_num, int turn, int depth, int max_depth, clock_t t)
{
	int s[MAX_MOVE], d[MAX_MOVE], cap_s[MAX_MOVE], cap_d[MAX_MOVE];
	int i, m, n;
	int curr_score, score, value;
	int src, dest, cap;
	int factor;

	// factor: 將分數轉換為相對於自己的分數
	factor = (turn == RED) ? 1 : -1;
	// 終止條件
	if(red_num == 0)
		return -(MAX_SCORE-depth-1) * factor;
	if(black_num == 0)
		return (MAX_SCORE-depth-1) * factor;
	if(depth == max_depth)
		return factor * eval(piece_num);

	src = 0;
	dest = 0;
	score = -MAX_SCORE;
	if(clock() > t)
		return score;
	// 產生走法
	move_gen(board, turn, s, d, &n, cap_s, cap_d, &m);
//	if(depth == 1)
//		printf("%d %d\n", n, m);
	// 對吃子步進行搜尋
	for(i = 0; i < m; i++){
		cap = move(board, piece_num, &red_num, &black_num, cap_s[i], cap_d[i]);
		value = -search(board, piece_num, dark_num, red_num, black_num, !turn, depth + 1, max_depth, t);
		if(value >= score){
			score = value;
			src = cap_s[i];
			dest = cap_d[i];
		}
		unmove(board, piece_num, &red_num, &black_num, cap_s[i], cap_d[i], cap);
//		if(depth == 1)
//			printf("%d %d %d\n", value, cap_s[i], cap_d[i]);
	}
	// 對走子步進行搜尋
	for(i = 0; i < n; i++){
		cap = move(board, piece_num, &red_num, &black_num, s[i], d[i]);
		value = -search(board, piece_num, dark_num, red_num, black_num, !turn, depth + 1, max_depth, t);
		if(value >= score){
			score = value;
			src = s[i];
			dest = d[i];
		}
		unmove(board, piece_num, &red_num, &black_num, s[i], d[i], cap);
//		if(depth == 1)
//			printf("%d %d %d\n", value, s[i], d[i]);
	}
	// 計算當前盤面之審局分數
	curr_score = eval(piece_num) * factor;
	// 判斷是否執行null move
	if(dark_num > 0 && score <= curr_score){
		value = -search(board, piece_num, dark_num, red_num, black_num, !turn, depth + 1, max_depth, t);
		if(value >= score){
			score = value;
			src = 0;
			dest = 0;
		}
//		if(depth == 1)
//			printf("%d 0 0\n", value);
	}
	if(depth == 1){
		best_src = src;
		best_dest = dest;
	}
	return score;
}

// 進行翻子動作
void reveal(int board[BOARD_SIZE])
{
	int reveal[MAX_MOVE];
	int k, r;
	reveal_gen(board, reveal, &k);
	if(k > 0){
		r = rand() % k;
		best_src = reveal[r];
		best_dest = -1;
	}
	else{
		best_src = -1;
		best_dest = -1;
	}
}

// 轉換為介面的坐標系統
int translate_position(int board[BOARD_SIZE], int place)
{
	int i, p = 0;
	for(i = 0; i < BOARD_SIZE && i != place; i++)
		if(board[i] != INVALID)
			p++;
	return p;

}

// 轉換坐標為字串形式
void get_place_str(int place, char *str)
{
	int ch[4] = {'a', 'b', 'c', 'd'};
	str[0] = '\0';
	if(place >= 0 && place <= 31)
		sprintf(str, "%c%d", ch[place % 4], 7 - place / 4 + 1);
	else
		strcpy(str, "0");
}

// 輸出走法檔
void output_move(const char *move_file, int move_type, int src, int dest, int score)
{
	char src_str[3], dest_str[3];
	FILE *fp;
	fp = fopen(move_file, "wt");
	if(fp == NULL){
		fprintf(fp, "cannot open output file \"%s\"\n", move_file);
		exit(1);
	}
	get_place_str(src, src_str);
	if(move_type == 0)
		get_place_str(dest, dest_str);
	else
		strcpy(dest_str, "0");
	fprintf(fp, "%d\n%s\n%s\n%d\n", move_type, src_str, dest_str, score);
	fclose(fp);
}

// 將棋子代碼轉成整數
int piece2int(char piece)
{
	int i;
	char pce_map[16] = {'-', 'K', 'G', 'M', 'R', 'N', 'C', 'P', 'k', 'g', 'm', 'r', 'n', 'c', 'p', 'X'};
	for(i = 1; i < 16; i++)
		if(piece == pce_map[i])
			return i;
	return -1;
}

// 讀取一手棋譜字串
int parse_record(const char *str, int *src, int *dest)
{
	if(str[0] < 'a' || str[0] > 'd')
		return -1;
	if(str[1] < '1' || str[1] > '8')
		return -1;
	*src = (str[1] - '1') * 4 + str[0] - 'a';
	if(str[2] == '('){
		*src += 100;
		*dest = piece2int(str[3]);
	}
	else{
		if(str[3] < 'a' || str[3] > 'd')
			return -1;
		if(str[4] < '1' || str[4] > '8')
			return -1;
		*dest = (str[4] - '1') * 4 + str[3] - 'a';
	}
	return 1;

}

// 讀取棋譜記錄檔
int load_game(const char *filename, int piece_type[PIECE_TYPE], int chsbrd[BOARD_SIZE], int *turn, int *time_limit)
{
	int ret;
	int i, j, k;
	int piece_limit[15] = {1, 2, 2, 2, 2, 2, 5, 1, 2, 2, 2, 2, 2, 5};
	int piece_check[15];
	int src, dest;
	int time_str[500];
	int first;
	int result;
	int ply = 0;
	char str1[500], str2[500], str3[500], str4[500];
	char player1[500], player2[500];
	FILE *fp;
	fp = fopen(filename, "rt");
	if(fp == NULL)
		return 0;
	fgets(str1, 500, fp);
	str1[strlen(str1) - 1] = '\0';
	strcpy(time_str, &str1[2]);
	fscanf(fp, "%s %s %s %s", str1, player2, str2, player2);
	fscanf(fp, "%s", str1);
	for(i = 0; i < 14; i++){
		fscanf(fp, "%d", &j);
		if(j < 0 || j > piece_limit[i])
			return -1;
		piece_type[i] = j;
		piece_check[i] = j;
	}
	for(i = 28; i >= 0; i -= 4){
		fscanf(fp, "%s", str1);
		for(j = i; j < i + 4; j++){
			fscanf(fp, "%s", str1);
			k = piece2int(str1[0]);
			if(k != EMPTY && k != DARK && k < 1 && k > 14)
				return -1;
			if(k != DARK && piece_check[k] == 0)
				return -1;
			chsbrd[j] = k;
			piece_check[k]--;
		}
	}
	fscanf(fp, "%s %s %d", str1, str2, &first);
	fscanf(fp, "%s %s %d", str1, str2, time_limit);
	*turn = first;
	n_ply = 0;
	while(1){
		if(feof(fp))
			break;
		str1[0] = '\0';
		i = fscanf(fp, "%s %s %s %s", str1, str2, str3, str4);
		if(str1[0] != '*')
			break;
		if(strcmp(str3, "wins") == 0){
			if(strcmp(str2, player1) == 0)
				result = 1;
			else if(strcmp(str2, player2) == 0)
				result = 2;
			break;
		}
		else if(strcmp(str2, "Draws") == 0){
			result = 3;
			break;
		}
		ret = parse_record(str3, &src, &dest);
		if(ret == -1)
			return -1;
		if(src >= 100)
			chsbrd[src - 100] = dest;
		else{
			if(chsbrd[dest] != EMPTY)
				piece_type[chsbrd[dest] - 1]--;
			chsbrd[dest] = chsbrd[src];
			chsbrd[src] = EMPTY;
		}
		*turn = 1 - *turn;
		ply++;
		if(i == 4){
			ret = parse_record(str4, &src, &dest);
			if(ret == -1)
				return -1;
			if(src >= 100)
				chsbrd[src - 100] = dest;
			else{
				if(chsbrd[dest] != EMPTY)
					piece_type[chsbrd[dest] - 1]--;
				chsbrd[dest] = chsbrd[src];
				chsbrd[src] = EMPTY;
			}
			*turn = 1 - *turn;
			ply++;
		}
		if(str4[0] == '*'){
			fscanf(fp, "%s %s", str1, str2);
			if(strcmp(str2, "wins") == 0){
				if(strcmp(str1, player1) == 0)
					result = 1;
				else if(strcmp(str1, player2) == 0)
					result = 2;
				break;
			}
			else if(strcmp(str2, "Draws") == 0){
				result = 3;
				break;
			}
		}
	}
	fclose(fp);
	//*turn = (ply % 2 == 0) ? first : 1 - first;
}

// 轉換棋盤
void transform_board(int board[BOARD_SIZE], int chsbrd[BOARD_SIZE])
{
	int i, j, k;
	for(i = 0; i < BOARD_SIZE; i++)
		if(i % 6 == 0 || i % 6 == 5 || i / 6 == 0 || i / 6 == 9)
			board[i] = INVALID;
		else
			board[i] = EMPTY;
	j = 28;
	k = j;
	for(i = 0; i < BOARD_SIZE; i++){
		if(board[i] == INVALID)
			continue;
		board[i] = chsbrd[k++];
		if(k == j + 4){
			j -= 4;
			k = j;
		}
	}
}

// 下一手棋
void play()
{

	int ret;
	int ply, turn, time_limit;
	int chsbrd[BOARD_SIZE];
	int score;
	int r, move_type;
	int MaxDepth;
	clock_t t;
	printf("inputting board\n");
	ret = load_game("board.txt", piece_num, chsbrd, &turn, &time_limit);
	transform_board(board, chsbrd);
	dark_num = get_dark_num(board);
	red_num = get_piece_num(RED, piece_num);
	black_num = get_piece_num(BLACK, piece_num);
	best_src = 0;
	best_dest = 0;
	if(dark_num == PIECE_NUM)
		move_type = REVEAL_PIECE;
	else
		move_type = MOVE_PIECE;

	if(move_type == MOVE_PIECE){
		printf("searching\n");
		clock_limit = clock() + time_limit * CLK_TCK;
		if(time_limit < 20)
			max_depth = 6;
		else
			max_depth = (int) (log(time_limit / 20) / log(3)) * 2 + 6;
		score = search(board, piece_num, dark_num, red_num, black_num, turn, 1, max_depth, clock_limit);
	}
	move_type = (best_dest == -1) ? 1 : 0;
	if(best_src == 0){
		move_type = REVEAL_PIECE;
		printf("revealing\n");
		reveal(board);
	}
	best_src = translate_position(board, best_src);
	best_dest = translate_position(board, best_dest);
	printf("outputing\n\n");
	output_move("move.txt", move_type, best_src, best_dest, score);
}

void main()
{
	play();
}
