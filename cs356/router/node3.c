//Node3

#include <stdio.h>
#include <stdlib.h>

#define THIS_NODE 3
#define INFINITY 999

extern struct rtpkt {
int sourceid;       /* id of sending router sending this pkt */
int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
int mincost[4];     /* min cost to node 0 ... 3 */
};

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
int costs[4][4];
} dt3;



extern float clocktime; /* emulator clock */
struct rtpkt *pkt3; /* packet holds min distances in packet->mincost[i] */

/* function prototypes */
void sendMin3();
void rtinit3();
void rtupdate3( struct rtpkt *rcvdpkt );
void printdt3( struct distance_table *dtptr );
extern void tolayer2( struct rtpkt packet );


/* initialization of distance table for this node */
void rtinit3() 
{
	int i, j;
	pkt3 = (struct rtpkt *)malloc( sizeof(struct rtpkt) );
	pkt3->sourceid = THIS_NODE;

	printf("NODE3: initialization event at t=%f\n", clocktime );

	dt3.costs[3][0] = 7; dt3.costs[3][1] = 999; dt3.costs[3][2] = 2; dt3.costs[3][3] = 0;
	
	//A for loop to fill in the remaining infinite values.
	for (i=0; i<3; i++)
	{ 	
		for (j=0; j<4; j++)
		{ 
			dt3.costs[i][j]=999;
		}
	}

	pkt3->mincost[0] = dt3.costs[0][0] = 7;	/* cost to node 0 via 0 */
	pkt3->mincost[1] = INFINITY;			/* cost to non-directly attached node */
	pkt3->mincost[2] = dt3.costs[2][2] = 2;	/* cost to node 3 via 3 */
	pkt3->mincost[3] = 0;					/* cost to itself (redundant => using 0) */

	printf("...after init distance table is:\n");
	printdt3(&dt3);	/* print conents of distance table after initialization */

	pkt3->sourceid = THIS_NODE;

	sendMin3();		/* sends this node's current minimum (initialized) costs */
}

/* update of the distance table for this node */
void rtupdate3(rcvdpkt)
struct rtpkt *rcvdpkt;
{
	int i, change = 0, via = rcvdpkt->sourceid;
	
	printf("\nNODE3: rtupdate event at t=%f\n", clocktime );

	for(i=0; i<4; i++ ){
		if(i==THIS_NODE || i==via || rcvdpkt->mincost[i]==INFINITY) continue;

		if( pkt3->mincost[i] > (dt3.costs[i][via]=rcvdpkt->mincost[i]+dt3.costs[via][via]) ){
			pkt3->mincost[i] = dt3.costs[i][via];
			change = 1;
		}
	}

	printf("...after update distance table is:\n");
	printdt3(&dt3);

	if( change )
		sendMin3();
	else
		printf("NODE3: min values haven't been changed\n");
}

/* sends new minimum distances of this node to the medium */
void sendMin3()
{
	int i;

	printf("NODE3: send-new-min event at t=%f\n\n", clocktime );

	/* send to all directly attached nodes (0, 2) */
	for(i=0; i<4; i++ ){
		if(i==THIS_NODE || i==1 ) continue;
		pkt3->destid = i;
		tolayer2(*pkt3);
	}
}

/* printout of distance table for this node */
void printdt3(dtptr) struct distance_table *dtptr;
{
	printf("             via     \n");
	printf("   D3 |    0     2 \n");
	printf("  ----|-----------\n");
	printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
	printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
	printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}
