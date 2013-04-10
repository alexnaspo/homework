//Node1

#include <stdio.h>
#include <stdlib.h>

#define THIS_NODE 1
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

int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table
{
int costs[4][4];
} dt1;


extern float clocktime; /* emulator clock */
struct rtpkt *pkt1; /* packet holds min distances in packet->mincost[i] */

/* function prototypes */
void sendMin1();
void rtinit1();
void rtupdate1( struct rtpkt *rcvdpkt );
void printdt1( struct distance_table *dtptr );
void linkhandler1( int linkid, int newcost );
extern void tolayer2( struct rtpkt packet );


/* initialization of distance table for this node */
void rtinit1() 
{
	int i, j;
	pkt1 = (struct rtpkt *)malloc( sizeof(struct rtpkt) );
	pkt1->sourceid = THIS_NODE;

	printf("NODE1: initialization event at t=%f\n", clocktime );

dt1.costs[1][0] = 1; dt1.costs[1][1] = 0; dt1.costs[1][2] = 1; dt1.costs[1][3] = 999;

	//Two for loops for infinite values.
	for (i=0; i<1; i++)
	{ 	
		for (j=0; j<4; j++)
		{ 
			dt1.costs[i][j]=999;
		}
	}

	for (i=2; i<4; i++)
	{ 	
		for (j=0; j<4; j++)
		{ 
			dt1.costs[i][j]=999;
		}
	}


	pkt1->mincost[0] = dt1.costs[0][0] = 1;	/* cost to node 0 via 0 */
	pkt1->mincost[1] = 0;					/* cost to itself (redundant => using 0) */
	pkt1->mincost[2] = dt1.costs[2][2] = 1; /* cost to node 2 via 2 */
	pkt1->mincost[3] = INFINITY;			/* cost to non-directly attached node */

	printf("...after init distance table is:\n");
	printdt1(&dt1);	/* print conents of distance table after initialization */

	pkt1->sourceid = THIS_NODE;

	sendMin1();		/* sends this node's current minimum (initialized) costs */
}

/* update of the distance table for this node */
void rtupdate1(rcvdpkt)
struct rtpkt *rcvdpkt;
{
	int i, change = 0, via = rcvdpkt->sourceid;
	
	printf("\nNODE1: rtupdate event at t=%f\n", clocktime );

	for(i=0; i<4; i++ ){
		if(i==THIS_NODE || i==via || rcvdpkt->mincost[i]==INFINITY) continue;

		if( pkt1->mincost[i] > (dt1.costs[i][via]=rcvdpkt->mincost[i]+dt1.costs[via][via]) ){
			pkt1->mincost[i] = dt1.costs[i][via];
			change = 1;
		}
	}

	printf("...after update distance table is:\n");
	printdt1(&dt1);

	if( change )
		sendMin1();
	else
		printf("NODE1: min values haven't been changed\n");
}

/* sends new minimum distances of this node to the medium */
void sendMin1()
{
	int i;

	printf("NODE1: send-new-min event at t=%f\n\n", clocktime );
	
	/* send to all directly attached nodes (0, 2) */
	for(i=0; i<4; i++ ){
		if(i==THIS_NODE || i==3 ) continue;
		pkt1->destid = i;
		tolayer2(*pkt1);
	}
}

/* printout of distance table for this node */
void printdt1(dtptr)
struct distance_table *dtptr;

{
printf("             via   \n");
printf("   D1 |    0     2 \n");
printf("  ----|-----------\n");
printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}
void linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */	
{
}