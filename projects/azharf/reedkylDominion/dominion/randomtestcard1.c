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
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i, addedCards;
    
	srand (time(NULL));
	//int seed = 1000;
	int seed;
	int addedCoins;
	int shuffledCards = 0;
    int numPlayer = 2;
    int maxBonus = 10;
	int discardedCards = 1;
	int currentPlayer = 0;
    int p, r, handCount;
    int bonus = 0;
	int passedTests = 0;
	int failedTests = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testcaseG;
	
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
	printf ("TESTING Smithy():\n");
	printf("Add smithy to index 0 (hand position 1) and use card effect of smithy\n");
	int b;
	for(b =0; b < 500; b++){
	seed = rand();
	//printf("seed is %d\n", seed);
	bonus = 0;
    
				numPlayer = 2;



				//printf("Test %d add smithy to index 0 (hand position 1) and use card effect of smithy\n", b+1);
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game set the number of cards on hand															 
				G.handCount[currentPlayer] = rand() % 5 + 1;

				G.deckCount[currentPlayer] = 10 - G.handCount[currentPlayer];
				
				G.discardCount[currentPlayer] = rand() % 5;
				G.handCount[1] = rand() % 5 + 1;											
				G.deckCount[1] = 10 - G.handCount[1];
				G.discardCount[1] = rand() % 5;
				//printf("second player: hand %d, deck %d, and discard %d\n", G.handCount[1], G.deckCount[1], G.discardCount[1]);
				int v;
				for(v = 0; v < G.discardCount[currentPlayer]; v++)
					G.discard[currentPlayer][v] = 1;
				
				// copy the game state to a test case
				memcpy(&testcaseG, &G, sizeof(struct gameState));

				testcaseG.hand[0][0] = smithy;

				int total = 0;
				int h;

				int firstDeckcount = G.deckCount[0];
				for (h = 0; h < 27; h++)	
					total += fullDeckCount(0, h, &G);
				//printf("first total is %d\n", total);
				
				
				
				cardEffect(smithy, choice1, choice2, choice3, &testcaseG, handpos, bonus);//play smithy from index 0 of hand
				//printf("Player 1's hand is %d, their deck is %d, and their discard pile is %d \n", testcaseG.handCount[0], testcaseG.deckCount[0], testcaseG.discardCount[0]);
				firstDeckcount = testcaseG.deckCount[0];
				int newtotal = 0;
				for (h = 0; h < 27; h++)	
					newtotal += fullDeckCount(0, h, &testcaseG);
				//printf("second total is %d\n", newtotal);
				
				addedCards = 3;
				addedCoins = 0;
				if(testcaseG.coins == G.coins)
					passedTests++;
				//printf("Passed: the expected coin total is %d, and the current coin total is %d\n", G.coins, testcaseG.coins);
				else{
					printf("Failed: the expected coin total is %d, and the current coin total is %d\n", G.coins, testcaseG.coins);
					failedTests++;
				}
				//else(testcaseG.discardCount[currentPlayer] != G.discardCount[currentPlayer] + 1)
				if(testcaseG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 1)
					passedTests++;
					//printf("Passed: %d card(s) correctly added to the discard pile\n", discardedCards);
				else{
					printf("Failed: %d card(s) added to the discard pile, %d card expected to be added to the discard pile\n", testcaseG.discardCount[currentPlayer] - G.discardCount[currentPlayer], discardedCards);
					failedTests++;
				}
				if (testcaseG.handCount[currentPlayer] == G.handCount[currentPlayer] + addedCards - discardedCards)
					passedTests++;
					//printf("Passed: The hand count for the current Player is %d and the expected hand count is %d \n", testcaseG.handCount[currentPlayer], G.handCount[currentPlayer] + addedCards - discardedCards);
				else{
					printf("Failed: The hand count for the current Player is %d and the expected hand count is %d \n", testcaseG.handCount[currentPlayer], G.handCount[currentPlayer] + addedCards - discardedCards);
					failedTests++;
				}
				if(testcaseG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - addedCards + shuffledCards)
					passedTests++;
				//printf("Passed: the current deck count is %d, and the expected deck count is %d.\n", testcaseG.deckCount[currentPlayer], G.deckCount[currentPlayer] - addedCards + shuffledCards);
				else{
					printf("Failed: the deck count is %d, and the expected deck count is %d\n", testcaseG.deckCount[currentPlayer], G.deckCount[currentPlayer] - addedCards + shuffledCards);
					failedTests++;
				}
				if(testcaseG.deckCount[currentPlayer] + addedCards == G.deckCount[currentPlayer])
					passedTests++;
				//printf("Passed: 3 cards were drawn from Player 1's deck\n");
				else{
					printf("Failed: %d cards were drawn from Player 1's deck, and 3 cards were expected to be drawn\n", G.deckCount[currentPlayer] - testcaseG.deckCount[currentPlayer]);
					failedTests++;
				}
				//printf("test 1B: were any cards trashed or added unnecessarily to Player 1's full deck?\n");
				if(total == newtotal)
					passedTests++;
					//printf("Test passed, no cards were trashed unnecessarily from Player 1's full deck\n");
				else if(total > newtotal){
					printf("Test failed, %d card(s) was/were trashed unnecessarily from Player 1's full deck\n", total-newtotal);
					failedTests++;
				}
				else{
					printf("Test failed, some cards were added unnecessarily to Player 1's full deck\n");
					failedTests++;
				}
				if(testcaseG.handCount[1] == G.handCount[1])
					passedTests++;
					//printf("Passed: Player 2's hand count didn't change\n");
				else{
					printf("Failed: Player 2's hand count changed\n");
					failedTests++;
				}
				if(testcaseG.deckCount[1] == G.deckCount[1])
					passedTests++;
					//printf("Passed: Player 2's deck count didn't change\n");
				else{
					printf("Failed: Player 2's deck count changed\n");
					failedTests++;
				}
				if(testcaseG.discardCount[1] == G.discardCount[1])
					passedTests++;
					//printf("Passed: Player 2's discard count didn't change\n");
				else{
					printf("Failed: Player 2's discard count changed\n");
					failedTests++;
				}
				if(testcaseG.supplyCount[estate] == G.supplyCount[estate] && testcaseG.supplyCount[duchy] == G.supplyCount[duchy] && testcaseG.supplyCount[province] == G.supplyCount[province])
					passedTests++;
				//printf("Passed: the victory card counts are unchanged\n");
				else{
					printf("Failed: the victory card counts have changed\n");
					failedTests++;
				}
				int m;
				//int counter = 0;
				for(m = 7; m < 17; m++)
					if(testcaseG.supplyCount[m] != G.supplyCount[m]){
						printf("Failed: The supply count of card %d changed\n", m);
						failedTests++;
					}
					else
						passedTests++;
						//printf("Passed: The supply counts of all the kingdom cards have stayed the same\n");
						
					//if(testcaseG.supplyCount[m] == G.supplyCount[m])
						//printf("Passed: The supply count of kingdom card %d has stayed the same\n", m);
					//else
						//printf("Failed: The supply count of kingdom card %d has changed\n", m);
	}
	printf("%d tests failed, %d tests passed, %d tests total \n", failedTests, passedTests, failedTests+passedTests);
    printf("All tests taken!\n"); 
	
	

    return 0;
}