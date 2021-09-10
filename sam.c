
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

#define WEIGHT_CNR0 100
#define WEIGHT_CNR1 100
#define WEIGHT_CNR2 50 
#define WEIGHT_CNR3 30
#define WEIGHT_CNR4 20
#define WEIGHT_CNR5 10
#define WEIGHT_CNRDEF 10
#define WEIGHT_ALWNC 3
#define WEIGHT_STONE 10 
#define THRESHOLD_REMAIN 6 
#define WEIGHT_LINE0 -20
#define WEIGHT_LINE1 -10
#define WEIGHT_LINE2 -20

/*
#define WEIGHT_CNR0 50
#define WEIGHT_CNR1 50
#define WEIGHT_CNR2 20 
#define WEIGHT_CNR3 10
#define WEIGHT_CNR4 5
#define WEIGHT_CNR5 2
#define WEIGHT_CNRDEF 2
#define WEIGHT_ALWNC 5
#define WEIGHT_STONE 100
#define THRESHOLD_REMAIN 10
#define WEIGHT_LINE -10
*/

//#define LIMIT_DEPTH 5
#define LIMIT_CHAILD 24
#define COMP 1
#define YOU 2

/*
typedef struct node{
	int depth;		//
	int player;		// 1:computer   2:you
	int xy;			// 0 to 63 place stone.
	int pass;		//pass hantei
	int score;
	int conner;
	char board[64];	//
	struct node *chaild[LIMIT_CHAILD];
} node_t;
*/

int maketree(int,int,node_t *,node_t *,node_t *);
void nodefree(node_t *);
void read(node_t *);
int get_score(char *);
int get_conner(node_t *,node_t *); 
int eva_score(node_t *);
int eva_conner(node_t *);
int get_line(int,char *);
//int read_history(node_t *);
extern char *copy_board(char *,char *, int);
extern int count_reverce(char *,int,int);
extern int reverce(char *,int,int);
extern int count_stone(char *, int);
extern int display_board(char *,int);
unsigned int sequence;
int store_max_chaild;
int total_reef; 
extern int set_depth;
extern int flag_score;
//node_t *history[LIMIT_DEPTH+2];

int next(char *board)
{
	sequence = 0;
	store_max_chaild = 0;
	total_reef = 0;

//	for(int i=0;i<=LIMIT_DEPTH+1;i++){
//		history[i]=NULL;
//	}

/*** bannmenn tennkai ***/	
	node_t *root;
	root = (node_t*)malloc(sizeof(node_t));
		if(root==NULL){ return -1; }  //malloc error 
	root->depth = 0;
	root->player = 2;		//root is you!
	root->pass = 0;			//pass hantei
	copy_board(board,root->board,64);//	
	for(int n=0;n < LIMIT_CHAILD;n++){
		root->chaild[n]= NULL; 
	}

	int chaild_num = 0;
	for(int xy=0,i=0;(xy<64) && (chaild_num<LIMIT_CHAILD);xy++){
		if(count_reverce(root->board,xy,COMP) != 0){
			node_t *next;
			next = (node_t*)malloc(sizeof(node_t));
				if(next==NULL){ return -1; }  //malloc error 
			root->chaild[chaild_num]=next;
			maketree(xy,chaild_num,root,next,root) ;
			chaild_num++;
		}
	}

/*** evaluation ***/

/**  pass judgement **/
	if(root->chaild[0] == NULL){
		printf("pass!\n");
		nodefree(root);	
		return 100;		//100 is Pass code.
	}

srand((unsigned int)time(NULL));
rand();rand();rand();rand();rand();

/** Hyouka (max serch) **/	
	int value[LIMIT_CHAILD];
	value[0]=root->chaild[0]->score+
			 root->chaild[0]->conner+
			 get_line(root->chaild[0]->xy,root->chaild[0]->board)+
	 		 (rand()%10-5);
	int max_value =value[0];
	int max_num =0;
	for(int n=1;root->chaild[n]!=NULL;n++){
		value[n]=root->chaild[n]->score+
				 root->chaild[n]->conner+
				 get_line(root->chaild[n]->xy,root->chaild[n]->board)+
		 		 (rand()%10-5);
//		printf("sc:%4d cn:%4d li:%4d\n",root->chaild[n]->score,root->chaild[n]->conner,get_line(root->chaild[n]->xy));
//		printf("%2d  %6d\n",root->chaild[n]->depth,root->chaild[n]->score);
		if(max_value < value[n]){
			max_value=value[n];
			max_num = n;
		}
//		printf("root->chaild[%2d]->conner %6d\n",n,value[n]);
    }

  /* hyouji */
  if(flag_score == 1){
	printf(" BR  XY   TOTAL   SCORE  CONNER    LINE\n");  
	for(int n=0;root->chaild[n]!=NULL;n++){
		if(n==max_num){printf("*");}else{printf(" ");}
		printf("%02d  %c%c  %6d  %6d  %6d  %6d\n",n,'0'+root->chaild[n]->xy/8+1,'a'+(root->chaild[n]->xy-(root->chaild[n]->xy/8)*8),value[n],root->chaild[n]->score,root->chaild[n]->conner,get_line(root->chaild[n]->xy,root->chaild[0]->board)); 
	}
  }
//	printf("Total:node %9d  Reef %6d  Max_chaild %2d\n",sequence,total_reef,store_max_chaild);   


/*** memory free & return ***/  
	int return_code=root->chaild[max_num]->xy;
	nodefree(root);	
	return return_code;

	//todo abnormal end
}


int maketree(int stone,int id,node_t *before,node_t *now,node_t *root)
{
	sequence++;
	now->depth = before->depth + 1;
	now->xy = stone;
	if(before->player==COMP){
		now->player=YOU;
	}else{
		now->player=COMP;
	}
	copy_board(before->board,now->board,64);//	
	
	if(before->pass ==0 ){
		reverce(now->board,stone,now->player);
	}		//before->pass =1 => no reverce.becuse pass.


	for(int n=0;n < LIMIT_CHAILD;n++){
		now->chaild[n]= NULL; 
	}

	if(now->depth >= set_depth){
		now->score=get_score(now->board);	now->conner=0;
		now->conner=get_conner(before,now);
		return 0;
	}

	int next_player;
	if(now->player==COMP){
		next_player=YOU;
	}else{
		next_player=COMP;
	}

	for(int xy=0,i=0;xy<64;xy++){
		if(count_reverce(now->board,xy,next_player) != 0){
			node_t *next;
			next = (node_t*)malloc(sizeof(node_t));
				if(next==NULL){
                     return -1;
				}  //malloc error 
			now->chaild[i]=next;
			now->pass = 0; 
			before->pass =0;
			maketree(xy,i,now,next,root);
			i++;
			if(i >= LIMIT_CHAILD){
				return -2;		//todo  brake;
			}
		}
	}
   
	if(now->chaild[0] == NULL){		//pass hantei
		now->pass = before->pass+1;
		if(now->pass == 2){
			now->score = get_score(now->board);
			return -4;		//pass renzoku
		}
		
		node_t *next;
		next = (node_t*)malloc(sizeof(node_t));
		if(next==NULL){
			 return -1;
		}		//malloc error 
		now->chaild[0]=next;
		maketree(0,0,now,next,root);	//pass one
		now->conner=get_conner(before,now);
		now->score = now->chaild[0]->score;
		return 0;
	}

	now->conner=get_conner(before,now);
	now->score = eva_score(now);
//	printf("now->depth:%2d  now->score: %6d\n",now->depth,now->score);
	return 0;		//normal end.
}

void read(node_t *p)
{
	for(int i=0;i<LIMIT_CHAILD;i++){
		if(p->chaild[i] == NULL) {
			return;
		}
		read(p->chaild[i]);
		return;
	}
}

void nodefree(node_t *node){
	if(node!=NULL){
		for(int n=0;n<LIMIT_CHAILD;n++){
			nodefree(node->chaild[n]);
		}
		free(node);
	}
}

int get_score(char *board){

	int count_comp=0;
	int count_you=0;
	for(int xy=0;xy<64;xy++){
		if(count_reverce(board,xy,COMP)!=0){
			count_comp++;
		}
		if(count_reverce(board,xy,YOU)!=0){
			count_you++;
		}
	}
	int allowance = (count_comp-count_you)*WEIGHT_ALWNC;

	int count = 0;
	if((64-count_stone(board,COMP)-count_stone(board,YOU)) <= THRESHOLD_REMAIN){
		count = count_stone(board,COMP)-count_stone(board,YOU);
	}
	int stone = count*WEIGHT_STONE;

	return allowance+stone;
}

int eva_score(node_t *now){
	if(now->chaild[0]==NULL){return 0;}
	int value = now->chaild[0]->score;
	for(int i=1;now->chaild[i] != NULL;i++){
		if(now->player==COMP){
			if(value < now->chaild[i]->score){
				value = now->chaild[i]->score;
			 }
		}
		else{
			if(value > now->chaild[i]->score){
				value = now->chaild[i]->score;
			}
		}
	}
	return value;
}

int eva_conner(node_t *now){
	if(now->chaild[0]==NULL){return 0;}
	int value = now->chaild[0]->conner;
	for(int i=1;now->chaild[i] != NULL;i++){
		if(now->player==COMP){
			if(value < now->chaild[i]->conner){
				value = now->chaild[i]->conner;
			 }
		}
		else{
			if(value > now->chaild[i]->conner){
				value = now->chaild[i]->conner;
			}
		}
	}
//	printf("xy:%2d  depth:%2d  value:%6d\n",now->xy,now->depth,value);
	return value;
}



int get_conner(node_t *before,node_t *now){
	int weight;
	int count_conner=0;
	switch(now->depth){
		case 0:
		case 1:
			weight = WEIGHT_CNR1;
			break;
		case 2:
			weight = WEIGHT_CNR2;
			break;
		case 3:
			weight = WEIGHT_CNR3;
			break;
		case 4:
			weight = WEIGHT_CNR4;
			break;
		default:
			weight = WEIGHT_CNRDEF;
			break;
	}

	if((*(before->board + 0) == 0)&&(*(now->board + 0) ==COMP)){count_conner++;}
	if((*(before->board + 0) == 0)&&(*(now->board + 0) ==YOU )){count_conner--;}
	if((*(before->board + 7) == 0)&&(*(now->board + 7) ==COMP)){count_conner++;}
	if((*(before->board + 7) == 0)&&(*(now->board + 7) ==YOU )){count_conner--;}
	if((*(before->board +56) == 0)&&(*(now->board +56) ==COMP)){count_conner++;}
	if((*(before->board +56) == 0)&&(*(now->board +56) ==YOU )){count_conner--;}
	if((*(before->board +63) == 0)&&(*(now->board +63) ==COMP)){count_conner++;}
	if((*(before->board +63) == 0)&&(*(now->board +63) ==YOU )){count_conner--;}

	int value = 0;
	if(now->chaild[0]!=NULL){
		value = now->chaild[0]->conner;
		if(now->player==YOU){
			for(int i=1;now->chaild[i] != NULL;i++){
				if(value < now->chaild[i]->conner){
					value = now->chaild[i]->conner;
				 }	
			}
		}
		else{
			for(int i=1;now->chaild[i] != NULL;i++){
				if(value > now->chaild[i]->conner){
					value = now->chaild[i]->conner;
				}
			}
		}
	}
//	printf("d:%2d xy:%2d  cnr:%2d  wht%4d  val:%3d\n",now->depth,now->xy,count_conner,weight,value);

	return count_conner * weight + value ;
}

int get_line(int xy,char *board){
	int value0 = 0;
	if((xy== 9)||(xy==14)||(xy==49)||(xy==54)){
		value0 = WEIGHT_LINE0;
	}
	int value1 = 0;
	if((xy== 1)||(xy== 6)||(xy== 8)||(xy==14)||
	   (xy==48)||(xy==55)||(xy==57)||(xy==62)){
		value1 = WEIGHT_LINE1;
	}


	int amari=xy%8;
	int shou=xy/8;
	int value2=0;
	if((((amari == 0)||(amari == 7))&&
		((((*(board+xy-8))==2)&&((*(board+xy+8))==0))||
		(((*(board+xy+8))==2)&&((*(board+xy-8))==0))))
		||
		(((shou == 0)||(shou == 7))&&
		((((*(board+xy-1))==2)&&((*(board+xy+1))==0))||
		(((*(board+xy+1))==2)&&((*(board+xy-1))==0))))){
		
		value2 = WEIGHT_LINE2;
	}
	return value0+value1+value2;
}
		



//int read_history(node_t *node){
//	return 0;
//}

/*
		if(node->depth==set_depth){
			return;
		}
		best choice;
		printf("d:%d  xy:%c%c  sc:%6d  cn:%6d\n",node->chaild[n]->depth,'0'+node->chaild[n]->xy/8+1,'a'+(node->chaild[n]->xy-(node->chaild[n]->xy/8)*8),node->chaild[n]->score,node->chaild[n]->conner);
		read_history(node->chaild[bestn]);
	
	}

	for(int n=0;node->chaild[n]!=NULL;n++){
		value[n]=node->chaild[n]->score+



				 nodr->chaild[n]->conner+
				 get_line(root->chaild[n]->xy,root->chaild[0]->board);
		if(max_value < value[n]){
			max_value=value[n];
			max_num = n;
		}
    }
	int value[LIMIT_CHAILD];
	value[0]=node->chaild[0]->score+
			 root->chaild[0]->conner+
			 get_line(root->chaild[0]->xy,root->chaild[0]->board);
	int max_value =value[0];
	int max_num =0;
	for(int n=1;node->chaild[n]!=NULL;n++){
		value[n]=node->chaild[n]->score+
				 nodr->chaild[n]->conner+
				 get_line(root->chaild[n]->xy,root->chaild[0]->board);
		if(max_value < value[n]){
			max_value=value[n];
			max_num = n;
		}
    }



	printf("d:%d  xy:%c%c  sc:%6d  cn:%6d\n",node->depth,'0'+node->xy/8+1,'a'+(node->xy-(node->xy/8)*8),node->score,node->conner);
	return 0;
*/
