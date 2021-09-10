

typedef struct node{
	int depth;		//
	int player;		// 1:computer   2:you
	int xy;			// 0 to 63 place stone.
	int pass;		//pass hantei
	int score;
	int conner;
	char board[64];	//
	struct node *chaild[24];
} node_t;

