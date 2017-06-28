#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

vector<string> cards, player[100];
string name[100];
int score[100], status[100], playernum, drop_cnt=0, stand_cnt=0;

void swap(int i, int j);
void shuffle_cards(int num_decks);
string draw_card();
void give_name();
int add(string card);
void check(int num);
void print();
void print_score(int num);
void game_win(int num);
void game_win();
void compare(int max_player[]);
void hit(int num);
void stand(int num);

int main(int argc, char **argv) {
	int seed, max, max_cnt, max_player[100];
	char input;
	string temp;

	seed=atoi(argv[1]);
	playernum=atoi(argv[2]);
	srand(seed);
	shuffle_cards(4);
	give_name();
	playernum++;
	for(int i=0;i<100;i++) {
		max_player[i]=-1;
	}
	for(int i=0;i<2;i++) {
		for(int j=0;j<playernum;j++) {
			player[j].push_back(draw_card());
			temp=player[j].back();
			score[j]+=add(temp);
			check(j);
		}
	}
	print();
	while(1) {
		for(int i=0;i<playernum;i++) {
			if(i==1 && status[i]==0) {
				cin >> input;
				if(input=='s') stand(i);
				else if(input=='h') hit(i);
			}
			else if(status[i]==0) {
				if(score[i]<13) hit(i);
				else if(score[i]<17 && rand()%2==1) hit(i);
				else stand(i);
			}
			if(drop_cnt==playernum-1) game_win();
		}
		if(stand_cnt+drop_cnt==playernum) {
			max=0;
			max_cnt=0;
			for(int i=0;i<playernum;i++) {
				if(score[i]<21 && score[i]>max) {
					max=score[i];
					for(int j=0;max_player[j]!=-1;j++) {
						max_player[j]=-1;
					}
					max_cnt=0;
					max_player[max_cnt++]=i;
				}
				else if(score[i]<21 && score[i]==max) {
					max_player[max_cnt++]=i;
				}
			}
			if(max_cnt==1) game_win(max_player[0]);
			else compare(max_player);
		}
	}
}

void swap(int i, int j) {
	auto n=cards[i];

	cards[i]=cards[j];
	cards[j]=n;
}

string draw_card() {
	string str=cards.back();

	cards.pop_back();

	return str;
}

void shuffle_cards(int num_decks) {
	string temp;
	int i,j;

	for(i=0;i<13;i++) {
		for(j=0;j<num_decks;j++) {
			temp=to_string(i+1)+"c";
			cards.push_back(temp);
		}
		for(j=0;j<num_decks;j++) {
			temp=to_string(i+1)+"h";
			cards.push_back(temp);
		}
		for(j=0;j<num_decks;j++) {
			temp=to_string(i+1)+"d";
			cards.push_back(temp);
		}
		for(j=0;j<num_decks;j++) {
			temp=to_string(i+1)+"s";
			cards.push_back(temp);
		}
	}
	for(i=0;i<1000;i++) {
		swap(rand()%(52*num_decks), rand()%(52*num_decks));
	}
}

void give_name() {
	name[0]="House";

	for(int i=1;i<=playernum;i++) {
		name[i]="Player"+to_string(i);
	}
}

int add(string card) {
	if(isdigit(card[1])) return (card[0]-'0')*10+(card[1]-'0');
	else return card[0]-'0';
}

void check(int num) {
	if(score[num]==21) game_win(num);//player'num' wins
	else if(score[num]>21) {
		drop_cnt++;
		cout << name[num] << " DROP!" << endl;
		status[num]=-1; //if player drops, status changes to -1;
	}
}

void print() {
	for(int i=0;i<playernum;i++) {
		cout << name[i] << ": ";
		print_score(i);
	}
}

void print_score(int num) {
	for(int i=0;i<player[num].size();i++) {
		if(i!=0) cout << ", ";
		cout << player[num][i];
	}
	cout << " (" << score[num] << ")" << endl;
}

void game_win(int num) {
	print();
	cout << name[num] << " WON!" << endl;
	exit(0);
}

void game_win() {
	for(int i=0;i<playernum;i++) {
		if(status[i]==0) {
			print();
			cout << name[i] << " WON!" << endl;
			exit(0);
		}
	}
}

void compare(int max_player[]) {
	int temp[100][11], match[100], length, max_playernum, i, j, l;
	string tmp;

	for(int i=0;max_player[i]!=-1;i++) {
		for(int j=0;j<11;j++) {
			temp[i][j]=-1;
		}
		max_playernum=i;
	}
	max_playernum++;
	for(i=0;max_player[i]!=-1;i++) {
		for(j=0;j<player[max_player[i]].size();j++) {
			tmp=player[max_player[i]][j];
			if(tmp[tmp.length()-1]=='s') temp[i][j]=add(tmp)*10+3;
			else if(tmp[tmp.length()-1]=='d') temp[i][j]=add(tmp)*10+2;
			else if(tmp[tmp.length()-1]=='h') temp[i][j]=add(tmp)*10+1;
			else if(tmp[tmp.length()-1]=='c') temp[i][j]=add(tmp)*10;
		}
	}
	for(i=0;max_player[i]!=-1;i++) {
		for(j=0;j<11;j++) {
			if(temp[i][j]==-1) break;
		}
		length=j;
		for(j=0;j<length-1;j++) {
			for(l=j+1;temp[i][l]!=-1;l++) {
				if(temp[i][j]<temp[i][l]) {
					auto n=temp[i][j];
					temp[i][j]=temp[i][l];
					temp[i][l]=n;
				}
			}
		}
	}
	for(i=0;i<11;i++) {
		for(j=0;j<max_playernum;j++) {
			match[j]=j;
		}
		for(j=0;j<max_playernum-1;j++) {
			for(l=j+1;l<max_playernum;l++) {
				if(temp[j][i]<temp[l][i]) {
					auto n=match[j];
					match[j]=match[l];
					match[l]=n;
				}
			}
		}
		if(temp[match[0]][i]!=temp[match[1]][i]) game_win(max_player[match[0]]);
	}
}

void hit(int num) {
	string temp;

	player[num].push_back(draw_card());
	temp=player[num].back();
	score[num]+=add(temp);
	cout << name[num] << ": HIT - ";
	print_score(num);
	check(num);
}

void stand(int num) {
	stand_cnt++;
	cout << name[num] << ": STAND - ";
	print_score(num);
	status[num]=1; //if player stands, status is changed to 1
}
