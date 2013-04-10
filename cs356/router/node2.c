//Node2

#include <stdio.h>
#include <stdlib.h>

#define THIS_NODE 2
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
} dt2;



extern float clocktime; /* emulator clock */
struct rtpkt *pkt2; /* packet holds min distances in packet->mincost[i] */

/* function prototypes */
void sendMin2();
void rtinit2();
void rtupdate2( struct rtpkt *rcvdpkt );
void printdt2( struct distance_table *dtptr );
extern void tolayer2( struct rtpkt packet );


/* initialization of distance table for this node */
void rtinit2() 
{
	int i, j;
	pkt2 = (struct rtpkt *)malloc( sizeof(struct rtpkt) );
	pkt2->sourceid = THIS_NODE;

	printf("NODE2: initialization event at t=%f\n", clocktime );

	dt2.costs[2][0] = 3; dt2.costs[2][1] = 1; dt2.costs[2][2] = 0; dt2.costs[2][3] = 2;

	//Two for loops for infinite values.
	for (i=0; i<2; i++)
	{ 	
		for (j=0; j<4; j++)
		{ 
			dt2.costs[i][j]=999;
		}
	}
	for (i=3; i<4; i++)
	{ 	
		for (j=0; j<4; j++)
		{ 
			dt2.costs[i][j]=999;
		}
	}


	pkt2->mincost[0] = dt2.costs[0][0] = 3;	/* cost to node 0 via 0 */
	pkt2->mincost[1] = dt2.costs[1][1] = 1;	/* cost to node 1 via 1 */
	pkt2->mincost[2] = 0;					/* cost to itself (redundant => using 0) */
	pkt2->mincost[3] = dt2.costs[3][3] = 2;	/* cost to node 3 via 3 */

	printf("...after init distance table is:\n");
	printdt2(&dt2);	/* print conents of distance table after initialization */

	pkt2->sourceid = THIS_NODE;

	sendMin2();		/* sends this node's current minimum (initialized) costs */
}

/* update of the distance table for this node */
void rtupdate2(rcvdpkt)
struct rtpkt *rcvdpkt;
{
	int i, change = 0, via = rcvdpkt->sourceid;
	
	printf("\nNODE2: rtupdate event at t=%f\n", clocktime );

	for(i=0; i<4; i++ ){
		if(i==THIS_NODE || i==via || rcvdpkt->mincost[i]==INFINITY) continue;

		if( pkt2->mincost[i] > (dt2.costs[i][via]=rcvdpkt->mincost[i]+dt2.costs[via][via]) ){
			pkt2->mincost[i] = dt2.costs[i][via];
			change = 1;
		}
	}

	printf("...after update distance table is:\n");
	printdt2(&dt2);

	if( change )
		sendMin2();
	else
		printf("NODE2: min values haven't been changed\n");
}

/* sends new minimum distances of this node to the medium */
void sendMin2()
{
	int i;

	printf("NODE2: send-new-min event at t=%f\n\n", clocktime );

	/* send to all directly attached nodes (0, 1, 3) */
	for(i=0; i<4; i++ ){
		if(i==THIS_NODE ) continue;
		pkt2->destid = i;
		tolayer2(*pkt2);
	}
}

/* printout of distance table for this node */
void printdt2(dtptr)
struct distance_table *dtptr;
{
printf("                via     \n");
printf("   D2 |    0     1    3 \n");
printf("  ----|-----------------\n");
printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	dtptr->costs[0][1],dtptr->costs[0][3]);
printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	dtptr->costs[1][1],dtptr->costs[1][3]);
printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	dtptr->costs[3][1],dtptr->costs[3][3]);
}





