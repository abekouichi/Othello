#include <stdio.h>
#include <time.h>

#define COMP 1
#define YOU  2

char *copy_board(char *,char *, int);
int count_reverce(char *,int,int);
int reverce(char *,int,int);
int display_board(char *,int);
int count_stone(char *,int);
int confirm(char *,int);
int fcreat(char *);
int record(char *,int,int);
int filewrite(char *,char *);

char fname[64];
char strings[1024];

/***   count reversible stones board ***/
int count_reverce(char *board,int xy,int p){
	int count[8]; for(int i=0;i<8;i++){count[i]=0;}
	int x=xy/8;
	int y=xy-8*x;
	if(*(board+xy) != 0){
		return 0;   //umatteiru
	}
	
	/***    angle 0   ***/
	for(int i=x-1,j=y;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i--,j){
		if(*(board+8*i+j)==0){
			count[0]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			break;
		}
		else{
			if(i==0){
				count[0]=0;
				break;
			}
			count[0]++;
		}
	}
	
	/***    angle 45  ***/
	for(int i=x-1,j=y+1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i--,j++){
		if(*(board+8*i+j)==0){
			count[1]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			break;
		}
		else{
			if(i==0||j==7){
				count[1]=0;
				break;
			}
			count[1]++;
		}
	}
	
	/***    angle 90  ***/
	for(int i=x,j=y+1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i,j++){
		if(*(board+8*i+j)==0){
			count[2]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			break;
		}
		else{
			if(j==7){
				count[2]=0;
				break;
			}
			count[2]++;
		}
	}
	
	/***    angle 135 ***/
	for(int i=x+1,j=y+1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i++,j++){
		if(*(board+8*i+j)==0){
			count[3]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			break;
		}
		else{
			if(i==7||j==7){
				count[3]=0;
				break;
			}
			count[3]++;
		}
	}
	
	/***    angle 180 ***/
	for(int i=x+1,j=y;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i++,j){
		if(*(board+8*i+j)==0){
			count[4]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			break;
		}
		else{
			if(i==7){
				count[4]=0;
				break;
			}
			count[4]++;
		}
	}
	
	/***    angle 225 ***/
	for(int i=x+1,j=y-1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i++,j--){
		if(*(board+8*i+j)==0){
			count[5]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			break;
		}
		else{
			if(i==7||j==0){
				count[5]=0;
				break;
			}
			count[5]++;
		}
	}
	
	/***    angle 270 ***/
	for(int i=x,j=y-1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i,j--){
		if(*(board+8*i+j)==0){
			count[6]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			break;
		}
		else{
			if(j==0){
				count[6]=0;
				break;
			}
			count[6]++;
		}
	}
	
	/***    angle 315 ***/
	for(int i=x-1,j=y-1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i--,j--){
		if(*(board+8*i+j)==0){
			count[7]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			break;
		}
		else{
			if(i==0||j==0){
				count[7]=0;
				break;
			}
			count[7]++;
		}
	}
	
	int ans =count[0]+count[1]+count[2]+count[3]+count[4]+count[5]+count[6]+count[7];
	return ans;
}

/************************************************
int display_num_reverce(void){
	printf("- - - - - - - - - - - - -\n");
	printf("   a  b  c  d  e  f  g  h\n");
	for(int i = 0; i < 8; i++) {
		printf("%d  ",i+1);
			for(int j =0; j < 8; j++) {
				printf("%d  ",reverce_num[i][j]);
		}
		printf("\n");
	}
}
************************************************/


/***   reverce stones virtual board ***/
int reverce(char *board,int xy,int p){
	//x:row 0-7 y:cloumn p:player
	int count[8]; for(int i=0;i<8;i++){count[i]=0;}

	int x=xy/8;
	int y=xy-8*x;
	if(*(board+xy) != 0){
		return 0;					//no reverce 0!
	}
	
	/***    angle 0   ***/
	for(int i=x-1,j=y;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i--,j){
		if(*(board+8*i+j)==0){
			count[0]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			for(int s=i+1,t=j,u=count[0];u>0;s++,t,u--){
				*(board+8*s+t)=p;
			}
			break;
		}
		else{
			count[0]++;
		}
	}
	/***    angle 45  ***/
	for(int i=x-1,j=y+1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i--,j++){
		if(*(board+8*i+j)==0){
			count[1]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			for(int s=i+1,t=j-1,u=count[1];u>0;s++,t--,u--){
				*(board+8*s+t)=p;
			}
			break;
		}
		else{
			count[1]++;
		}
	}
	/***    angle 90  ***/
	for(int i=x,j=y+1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i,j++){
		if(*(board+8*i+j)==0){
			count[2]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			for(int s=i,t=j-1,u=count[2];u>0;s,t--,u--){
				*(board+8*s+t)=p;
			}
			break;
		}
		else{
			count[2]++;
		}
	}
	/***    angle 135  ***/
	for(int i=x+1,j=y+1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i++,j++){
		if(*(board+8*i+j)==0){
			count[3]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			for(int s=i-1,t=j-1,u=count[3];u>0;s--,t--,u--){
				*(board+8*s+t)=p;
			}
			break;
		}
		else{
			count[3]++;
		}
	}
	/***    angle 180  ***/
	for(int i=x+1,j=y;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i++,j){
		if(*(board+8*i+j)==0){
			count[4]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			for(int s=i-1,t=j,u=count[4];u>0;s--,t,u--){
				*(board+8*s+t)=p;
			}
			break;
		}
		else{
			count[4]++;
		}
	}
	/***    angle 225  ***/
	for(int i=x+1,j=y-1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i++,j--){
		if(*(board+8*i+j)==0){
			count[5]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			for(int s=i-1,t=j+1,u=count[5];u>0;s--,t++,u--){
				*(board+8*s+t)=p;
			}
			break;
		}
		else{
			count[5]++;
		}
	}
	/***    angle 270  ***/
	for(int i=x,j=y-1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i,j--){
		if(*(board+8*i+j)==0){
			count[6]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			for(int s=i,t=j+1,u=count[6];u>0;s,t++,u--){
				*(board+8*s+t)=p;
			}
			break;
		}
		else{
			count[6]++;
		}
	}
	/***    angle 315  ***/
	for(int i=x-1,j=y-1;(i>-1)&&(i<8)&&(j>-1)&&(j<8);i--,j--){
		if(*(board+8*i+j)==0){
			count[7]=0;
			break;
		}
		if(*(board+8*i+j)==p){
			for(int s=i+1,t=j+1,u=count[7];u>0;s++,t++,u--){
				*(board+8*s+t)=p;
			}
			break;
		}
		else{
			count[7]++;
		}
	}

	*(board+xy)=p;				//shitei no sonoba ni utsu.
	
	int ans=count[0]+count[1]+count[2]+count[3]+count[4]+count[5]+count[6]+count[7];
	return ans;
}

/************** weighting ***************
if(reverce_num[0][0]!=0){
	reverce_num[0][0]=reverce_num[0][0]+5;
}
if(reverce_num[0][7]!=0){
	reverce_num[0][7]=reverce_num[0][7]+5;
}
if(reverce_num[7][0]!=0){
	reverce_num[7][0]=reverce_num[7][0]+5;
}
if(reverce_num[7][7]!=0){
	reverce_num[7][7]=reverce_num[7][7]+5;
}


if(reverce_num[1][1]!=0){
	reverce_num[1][1]=reverce_num[1][1]-5;
}
if(reverce_num[6][1]!=0){
	reverce_num[6][1]=reverce_num[6][1]-5;
}
if(reverce_num[1][6]!=0){
	reverce_num[1][6]=reverce_num[1][6]-5;
}
if(reverce_num[6][6]!=0){
	reverce_num[6][6]=reverce_num[6][6]-5;
}
*****************************************/


/************** Max serch ***************
int max_serch(){	
	int max=0,maxx=0,maxy=0;
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			if(max < reverce_num[x][y]){
				max = reverce_num[x][y];
				maxx=x;maxy=y;
			}
		}
	}

	if(max == 0){
		return 100;					//pass
	}
//	display_num_reverce();
	return maxx*8+maxy;
}
*****************************************/

/***   copy board to board nbyte  ***/
char *copy_board(char *from,char *to, int n){
	char *dist;
	dist = to;		//backup 
	do{
		*to=*from;
		to++;
		from++;
		n--;
	}while(n>0);
	return dist;
}

/***   Display board ***/ 
int display_board(char *board,int mode){
	int comp = 0;
	int you  = 0;
	if(mode == 0){
		printf("   0 1 2 3 4 5 6 7\n");
		for(int i = 0; i < 8; i++) {
			printf("%d  ",i);
			for(int j =0; j < 8; j++) {
				switch(*(board+8*i+j)){
					case 0:
						printf("  ");
						break;
					case 1:
//						printf("o ");
						printf("1 ");
						comp++;
						break;
					case 2: 
//						printf("● "); 
						printf("2 "); 
						you++;
						break;
					default:
						return 1;
				}	
			}	
			printf("\n");
		}
	}
	else{
		printf("   a b c d e f g h\n");
		for(int i = 0; i < 8; i++) {
			printf("%d  ",i+1);
			for(int j =0; j < 8; j++) {
				switch(*(board+8*i+j)){
					case 0:
						printf("  ");
						break;
					case 1:
//						printf("o ");
						printf("\x1b[36mo \x1b[0m");
						comp++;
						break;
					case 2: 
//						printf("● "); 
						printf("\x1b[33mo \x1b[0m"); 
						you++;
						break;
					default:
						return 1;
				}	
			}
			printf("\n");
		}
	}
	printf("You: %d   Computer: %d\n",you,comp);
	printf("- - - - - - - - - - - - -\n");
	return 0;
}

//

/*** Count stone ***/
int count_stone(char *board,int player){
	int stone = 0;
	for(int i=0;i<64;i++){
		if(*(board+i)==player){
			stone++;
		}
	}
	return stone;
}


/***   Confirmation display for input point ***/ 
int confirm(char *board,int xy){
	int comp = 0;

	int you  = 0;
	printf("   a b c d e f g h\n");
	for(int i = 0; i < 8; i++) {
		printf("%d  ",i+1);
		for(int j =0; j < 8; j++) {
			if((8*i+j)==xy){
				printf("\x1b[35mo \x1b[0m");
//				printf("\x1b[5m\x1b[35mo \x1b[0m");
			}
			else{
				switch(*(board+8*i+j)){
					case 0:
						printf("  ");
						break;
					case 1:
						printf("\x1b[36mo \x1b[0m");
//						printf("\x1b[5m\x1b[36mo \x1b[0m");
						break;
					case 2: 
						printf("\x1b[33mo \x1b[0m"); 
						break;
					default:
						return -1;
				}
			}	
		}
		printf("\n");
	}
	printf("- - - - - - - - - - - - -\n");
	return 0;
}

int fcreat(char *board){
	struct tm   *time_inf;
	time_t today = time(NULL);
	time_inf = localtime(&today);
	strftime(fname,sizeof(fname),"%Y%m%d%a%H%M.log",time_inf);
	strftime(strings,sizeof(strings),"%Y-%m-%d (%a) %H:%M  OTHELLO GAME STARTED\n",time_inf);
	filewrite(fname,strings);

	*strings='\0';
	sprintf(strings,"%s  a b c d e f g h\n",strings);
	for(int x = 0; x < 8 ; x++) {
		sprintf(strings,"%s%d ",strings,x);
		for(int y = 0; y < 8 ; y++){
			switch(*(board+x*8+y)){
				case 0:
					sprintf(strings,"%s  ",strings);
					break;
				case 1:
					sprintf(strings,"%s1 ",strings);
					break;
				case 2: 
					sprintf(strings,"%s2 ",strings);
					break;
				default:
					return -11;
			}	
		}	
		sprintf(strings,"%s\n",strings);
	}
	filewrite(fname,strings);

	return 0;
}

int record(char *board,int player,int xy){
	*strings='\0';
	sprintf(strings,"%s============================\n",strings);
	if(player == COMP){
		if((xy >= 0)&&(xy <= 63)){
			sprintf(strings,    "%sPlayer:Computer  Stone:%c%c\n",strings,'0'+xy/8,'a'+xy-(xy/8)*8);
		} else {
			if(xy == 100 ){
				sprintf(strings,"%sPlayer:Computer  Passed!\n",strings);
			} else {
				sprintf(strings,"%sPlayer:Computer  sam system error!\n",strings);
			}
		}
	} else {
		if((xy >= 0)&&(xy <= 63)){
			sprintf(strings,    "%sPlayer:You       Stone:%c%c\n",strings,'0'+xy/8,'a'+xy-(xy/8)*8);
		} else {
			if(xy == 100 ){
				sprintf(strings,"%sPlayer:You       Passed!\n",strings);
			} else {
				sprintf(strings,"%sPlayer:You       Input check system error!\n",strings);
			}
		}
	}
	
	sprintf(strings,"%s  a b c d e f g h\n",strings);
	for(int x = 0; x < 8 ; x++) {
		sprintf(strings,"%s%d ",strings,x);
		for(int y = 0; y < 8 ; y++){
			switch(*(board+x*8+y)){
				case 0:
					sprintf(strings,"%s  ",strings);
					break;
				case 1:
					sprintf(strings,"%s1 ",strings);
					break;
				case 2: 
					sprintf(strings,"%s2 ",strings);
					break;
				default:
					return -11;
			}	
		}	
		sprintf(strings,"%s\n",strings);
	}

	filewrite(fname,strings);
	return 0;
}
 
int filewrite(char *fname,char *strings) {
 	FILE *fp;
 	fp = fopen(fname, "a"); if(fp == NULL) { return -1; }
	fprintf(fp,"%s",strings);
	fclose(fp);
	return 0;
}
