#include <stdio.h>
#include <string.h>
#include "header.h"

extern int display_board(char *,int);
int input(void);
extern int reverce(char *,int,int);
extern int count_reverce(char *,int,int);
extern int next(char *);
int result_judge(int);
//extern node_t *history[];
//extern int read_history(node_t *);
extern int confirm(char *,int);
extern int fcreat(char *);
extern int record(char *,int,int);
extern char fname[];
#define COMP 1
#define YOU  2

/* 
char board[]={
			  0,0,2,2,2,2,0,0,
			  2,0,2,2,2,2,0,0,
			  2,2,2,2,2,2,2,2,
			  2,2,2,1,1,2,2,2,
			  2,1,2,2,1,2,2,2,
			  2,1,1,1,2,2,2,2,
			  0,0,1,1,2,1,0,2,
			  0,1,0,0,0,2,0,0,
			 };
*/

char board[]={
			  0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,
			  0,0,0,1,2,0,0,0,
			  0,0,0,2,1,0,0,0,
			  0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0,0,0,
			 };

int	set_depth;
int flag_record;
int	flag_score;

int main(int argc,char *argv[]){
	int result=0;		//0:yet 1:you win 2:computer win 
	int xy;
	int x;
	int y;
	int rev;				//reverce
	int player = 2;			//1:computer , 2:you
							//Opening mover is You.	
	int status=0;
	flag_score = 0;
	flag_record = 0;
	set_depth=5;
	
	char in[4];


	printf("\n");
	printf("OTHELLO Ver0.83(Debian GNU/Linux) by k.abe\n");
	printf("\n");
	
	for(int i=0;i<argc;i++){
		if(*argv[i]=='r'){
			flag_record=1;
			fcreat(board);
			printf("Game record enable.Filename:%s\n",fname);
		}
		if(*argv[i]=='s'){
			flag_score=1;
			printf("Computer evaluation on screen enable.\n");
		}
		if((*argv[i]>='2')&&(*argv[i]<='8')){
			set_depth=*argv[i]-'0';
			printf("Depth level:%d set.\n",set_depth);
		}
	}

	printf("\n");
	printf("- - - - - - - - - - - - - ");
	printf("\n");
	display_board(board,1);

	do{
		switch(player){
			case 1:					//Player is Computer.	
				printf("Computer \x1b[36mo \x1b[0m\n");
				xy=next(board);
				if(xy<0){
					printf("SAM system error,error no.%d\n",xy);
					return xy;
				}
				switch(xy){
					case 0: case 1: case 2: case 3: case 4:
					case 5: case 6: case 7: case 8: case 9:
					case 10: case 11: case 12: case 13: case 14:
					case 15: case 16: case 17: case 18: case 19:
					case 20: case 21: case 22: case 23: case 24:
					case 25: case 26: case 27: case 28: case 29:
					case 30: case 31: case 32: case 33: case 34:
					case 35: case 36: case 37: case 38: case 39:
					case 40: case 41: case 42: case 43: case 44:
					case 45: case 46: case 47: case 48: case 49:
					case 50: case 51: case 52: case 53: case 54:
					case 55: case 56: case 57: case 58: case 59:
					case 60: case 61: case 62: case 63:
						printf("COMPUTER STONE  %c%c\n",'0'+xy/8+1,'a'+(xy-(xy/8)*8));
						confirm(board,xy);
						printf("Confirm Ok?(Anykey:Ok)\n");
						fgets(in,2,stdin);
						rev=reverce(board,xy,1);
						if(flag_record == 1){
							record(board,COMP,xy);	//file write.
						}
						player = 2;		//Player switch next you.
						status=0;
						break;
					case 100:					//pass
						printf("Computer Passed! \n");
						if(flag_record == 1){
							record(board,COMP,xy);	//file write.
						}
						status++;
						player = 2;		//Player switch next you.
						break;
					case 101:					//Computer Giveup
						status = 20;			//You are winner.
						break;
					default:
						printf("SAM system error,error no.%d\n",xy);
						return xy;
				}
				break;
			case 2:						//Players is You.	
				printf("You \x1b[33mo \x1b[0m ");; 
				xy=input();
//				printf("xy=%d\n",xy);
				switch(xy){
					case 0: case 1: case 2: case 3: case 4:
					case 5: case 6: case 7: case 8: case 9:
					case 10: case 11: case 12: case 13: case 14:
					case 15: case 16: case 17: case 18: case 19:
					case 20: case 21: case 22: case 23: case 24:
					case 25: case 26: case 27: case 28: case 29:
					case 30: case 31: case 32: case 33: case 34:
					case 35: case 36: case 37: case 38: case 39:
					case 40: case 41: case 42: case 43: case 44:
					case 45: case 46: case 47: case 48: case 49:
					case 50: case 51: case 52: case 53: case 54:
					case 55: case 56: case 57: case 58: case 59:
					case 60: case 61: case 62: case 63:
						confirm(board,xy);
						printf("Are You sure?(r:Redo/other:Ok)\n");
						fgets(in,2,stdin);
						if(in[0]=='r'||in[0]=='R'){
							break;
						}
						rev=count_reverce(board,xy,2);
						if(rev!=0){
							rev=reverce(board,xy,2);
							if(flag_record == 1){
								record(board,YOU,xy);	//file write.
							}
							player = 1;		//Player switch next is  computer.
							status=0;
							break;
						}
						else{
							printf("Miss input! Please again\n");
							break;
						}
					case 100:
						rev=0;
						for(int xy=0;xy<64;xy++){
							rev=rev+count_reverce(board,xy,2);
						}
						if(rev==0){
							if(flag_record == 1){
								record(board,YOU,xy);	//file write.
							}
							player = 1;		//Player switch to computer.
							status++;
							break;		//pass true
						}
						else{
							printf("You can't PASS,Please again\n");
							break;
						}
					case 150:
						printf("Are You sure(y/n)?\n");
						fgets(in,2,stdin);
						if(in[0]=='y'||in[0]=='Y'){
							printf("Abort!\n");
							status = 10;
						}
						break;	
					case 160:
//						for(int i=0;history[i]!=NULL;i++){
//							read_history(history[i]);
//						}
						break;
					case 200:
						printf("Miss input! Please again\n");
						break;
					default:
						break;
				}
			default:
				break;
		}
		display_board(board,1);
		result=result_judge(status);
	} while(result == 0);
	if(result ==1){
		printf("Computer win! \n");
	}else if(result == 2){
		printf("You are win. Congrats.\n");
	}else if(result == 3){
		printf("Draw!\n");
	}else if(result == 4){
		printf("Both player Passed!\n");
	}else if(result == 5){
		printf("Game aboated!\n");
	}else if(result == 6){
		printf("Computer Giveup!\n");
	}else{
		printf("Unknown end.\n");
	}

	return 0;
}

int input(void){
	int x=0;
	int y=0;
	char xy[8];

	fgets(xy,5,stdin);

	switch((unsigned int)xy[0]){
		case (unsigned int)'1':
			x = 0;
			break;
		case (unsigned int)'2':
			x = 1;
			break;
		case (unsigned int)'3':
			x = 2;
			break;
		case (unsigned int)'4':
			x = 3;
			break;
		case (unsigned int)'5':
			x = 4;
			break;
		case (unsigned int)'6':
			x = 5;
			break;
		case (unsigned int)'7':
			x = 6;
			break;
		case (unsigned int)'8':
			x = 7;
			break;
		case (unsigned int)'p':
		case (unsigned int)'P':
			return 100;
		case (unsigned int)'a':
		case (unsigned int)'A':
		case (unsigned int)'q':
		case (unsigned int)'Q':
			return 150;
		case (unsigned int)'l':
		case (unsigned int)'L':
			return 160;
		default:
			return 200;
	}	
	switch((unsigned int)xy[1]){
		case (unsigned int)'a':
		case (unsigned int)'A':
			y = 0;
			break;
		case (unsigned int)'b':
		case (unsigned int)'B':
			y = 1;
			break;
		case (unsigned int)'c':
		case (unsigned int)'C':
			y = 2;
			break;
		case (unsigned int)'d':
		case (unsigned int)'D':
			y = 3;
			break;
		case (unsigned int)'e':
		case (unsigned int)'E':
			y = 4;
			break;
		case (unsigned int)'f':
		case (unsigned int)'F':
			y = 5;
			break;
		case (unsigned int)'g':
		case (unsigned int)'G':
			y = 6;
			break;
		case (unsigned int)'h':
		case (unsigned int)'H':
			y = 7;
			break;
		default:
			return 200;
	}
	return x*8+y;
}


/***  Result judgement  ***/
int result_judge(int status){
	
	if(status == 2){
		return 4;    //Both player passed.
	}
	if(status == 10){
		return 5;    //Abort.
	}
	if(status == 20){
		return 6;    //COMP Giveup.
	}

	int none=0,you=0,comp=0;
	for(int xy = 0; xy < 64; xy++){
		switch(board[xy]){
			case 0:
				none++;
				break;
			case 1:
				comp++;
				break;
			case 2:
				you++;
				break;
		}
	}

	if(none != 0){
		return 0;					//Not finish. 
	}else if(comp > you){
		return 1;					//Computer win.
	}else if(comp < you){
		return 2;					//You win.
	}
	return 3;						//Draw.
}
