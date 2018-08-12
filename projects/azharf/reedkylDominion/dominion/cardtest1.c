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
    printf ("TESTING Smithy():\n");
				numPlayer = 2;

	printf("test 1 add smithy to index 0 (hand position 1) and use card effect of smithy\n");
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game set the number of cards on hand															 

				G.hand[1][0] = smithy;
				G.handCount[1]++;

				G.whoseTurn = 1;
				int total = 0;
				int h;
				
				//printf("deck count is %d\n", G.deckCount[1]);//should be 11
				int firstDeckcount = G.deckCount[1];
				for (h = 0; h < 27; h++)	
					total += fullDeckCount(1, h, &G);
				
				int x = cardEffect(smithy, -1, -1, -1, &G, 0, bonus);//play smithy from index 0 of hand
								
				int newtotal = 0;
				for (h = 0; h < 27; h++)
					newtotal += fullDeckCount(1, h, &G);
				printf("test 1A: are there 3 cards in Player 2's hand?\n");
				if(G.handCount[1] == 3)
					printf("test passed, there are three cards in Player 2's hand\n");
				else
					printf("test failed, there aren't three cards in Player 2's hand\n");
				printf("test 1B: were any cards trashed or added unnecessarily to Player 2's full deck?\n");
				if(total == newtotal)
					printf("test passed, no cards were trashed unnecessarily from Player 2's full deck\n");
				else if(total > newtotal)
					printf("test failed, %d card(s) was/were trashed unnecessarily from Player 2's full deck\n", total-newtotal);
				else
					printf("test failed, some cards were added unnecessarily to Player 2's full deck\n");
				printf("test 1C: were three cards drawn from the deck successfully?\n");
				//printf("initial deckCount is %d and then deck count is %d\n", firstDeckcount, G.deckCount[1]);
				if(G.deckCount[1] == (firstDeckcount - 3))
					printf("test passed, three cards were drawn from the deck successfully\n");
				else
					printf("test failed, three cards weren't drawn from the deck successfully, %d cards were drawn\n", firstDeckcount-G.deckCount[1]);
printf("\ntest 2 add smithy to index 2 (hand position 3) and use card effect of smithy\n");
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
															// set the number of cards on hand
                
				G.hand[1][2] = smithy; //The third card of Player 2's hand changes to smithy
				G.handCount[1]++; //Increases player 2's hand count by 1
				
				G.whoseTurn = 1; //Changes the turn of the game to player 2
				total = 0;
				
				firstDeckcount = G.deckCount[1];
				//Test cards of all types to get the total number of cards
				for (h = 0; h < 27; h++)
					total += fullDeckCount(1, h, &G);
				
				int z = cardEffect(smithy, -1, -1, -1, &G, 2, bonus);//play smithy from index 0 of hand
				newtotal = 0;
				for (h = 0; h < 27; h++)
					newtotal += fullDeckCount(1, h, &G);
				printf("test 2A: are there 3 cards in Player 2's hand?\n");
				if(G.handCount[1] == 3)
					printf("test passed, there are three cards in Player 2's hand\n");
				else
					printf("test failed, there aren't three cards in Player 2's hand\n");
				printf("test 2B: were any cards trashed unnecessarily from Player 2's hand?\n");
				//printf("the total is %d and newtotal is %d\n", total, newtotal);
				if(total == newtotal)
					printf("test passed, no cards were trashed unnecessarily from Player 2's hand\n");
				else if (total > newtotal)
					printf("test failed, %d card(s) was/were trashed unnecessarily from Player 2's full deck\n", total-newtotal);
				else
					printf("test failed, some cards were added unnecessarily\n");
				printf("test 2C: were three cards drawn from the deck successfully?\n");
				if(G.deckCount[1] == firstDeckcount - 3)
					printf("test passed, three cards were drawn from the deck successfully\n");
				else
					printf("test failed, three cards weren't drawn from the deck successfully, %d cards were drawn\n", firstDeckcount-G.deckCount[1]);

			

    printf("All tests taken!\n");

    return 0;
}
