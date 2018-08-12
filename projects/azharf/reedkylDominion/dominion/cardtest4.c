/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
	bonus = 0;
    printf ("TESTING council room():\n");
	
				numPlayer = 2;

	printf("test 1 add council_room to index 0 (hand position 1) and use card effect of council_room on player 2\n");
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
															// set the number of cards on hand

				G.hand[1][0] = council_room;
				G.handCount[1]++;
				G.handCount[1];

				G.whoseTurn = 1;
				int total = 0;
				int h;

				int firstDeckcount = G.deckCount[1];
				for (h = 0; h < 27; h++)
					total += fullDeckCount(1, h, &G);
				
				int x = cardEffect(council_room, -1, -1, -1, &G, 0, bonus);//play smithy from index 0 of hand
				
				int newtotal = 0;
				for (h = 0; h < 27; h++)
					newtotal += fullDeckCount(1, h, &G);
				printf("test 1A: are there two buys after the council room card is played?\n");
				if(G.numBuys == 2)
					printf("test passed, there are 2 buys for player 2\n");
				else
					printf("test failed, there aren't 2 buys for player 2, there are %d buys\n", G.numBuys);
				printf("test 1B: are there 4 cards in Player 2's hand after council room is played?\n");
				if(G.handCount[1] == 4)
					printf("test passed, there are 4 cards in Player 2's hand\n");
				else
					printf("test failed, there aren't 4 cards in Player 2's hand\n");
				printf("test 1C: were there any cards trashed unnecessarily from player 2's hand?\n");
				if(total == newtotal)
					printf("test passed, no cards were trashed unnecessarily from Player 2's hand\n");
				else if(total < newtotal)
					printf("test failed, %d card(s) was/were added unnecessarily to Player 2's hand\n", newtotal - total);
				else
					printf("test failed, %d card(s) was/were trashed unnecessarily from Player 2's hand\n", total - newtotal);
				printf("test 1D: were four cards successfully drawn from the deck?\n");
				if(G.deckCount[1] == (firstDeckcount - 4))
					printf("test passed, four cards were drawn from the deck \n");
				else
					printf("test failed, four cards weren't drawn from the deck \n");
				
	printf("\ntest 2 add council_room to index 0 (hand position 1) and use card effect of council_room on player 1\n");
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
															// set the number of cards on hand

				G.hand[0][5] = council_room;
				G.handCount[0]++;
				G.handCount[0];

				G.whoseTurn = 0;
				total = 0;

				firstDeckcount = G.deckCount[0];
				for (h = 0; h < 27; h++)
					total += fullDeckCount(0, h, &G);

				int z = cardEffect(council_room, -1, -1, -1, &G, 5, bonus);//play smithy from index 0 of hand
				
				newtotal = 0;
				for (h = 0; h < 27; h++)
					newtotal += fullDeckCount(0, h, &G);
				printf("test 2A: are there two buys after the council room card is played?\n");
				if(G.numBuys == 2)
					printf("test passed, there are 2 buys for player 1\n");
				else
					printf("test failed, there aren't 2 buys for player 1, there are %d buys\n", G.numBuys);
				printf("test 2B: are there 9 cards in Player 1's hand after council room is played?\n");
				if(G.handCount[0] == 9)
					printf("test passed, there are 9 cards in Player 1's hand\n");
				else
					printf("test failed, there aren't 9 cards in Player 1's hand\n");
				printf("test 2C: were there any cards trashed unnecessarily from player 1's hand?\n");
				if(total == newtotal)
					printf("test passed, no cards were trashed unnecessarily from Player 1's hand\n");
				else if(total < newtotal)
					printf("test failed, %d card(s) was/were added unnecessarily to Player 1's hand\n", newtotal - total);
				else
					printf("test failed, %d card(s) was/were trashed unnecessarily from Player 1's hand\n", total - newtotal);
				printf("test 2D: were four cards successfully drawn from the deck?\n");
				if(G.deckCount[0] == (firstDeckcount - 4))
					printf("test passed, four cards were drawn from the deck \n");
				else
					printf("test failed, four cards weren't drawn from the deck \n");

    printf("All tests taken!\n");

    return 0;
}
