‹/* -----------------------------------------------------------------------
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
	bonus = 0;
    printf ("TESTING village():\n");
	printf("Add village to index 0 (hand position 1) and use card effect of village on player 1\n");
	int b;
	for(b =0; b < 500; b++){
	seed = rand();

				numPlayer = 2;

	
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
															// set the number of cards on hand
				G.handCount[currentPlayer] = rand() % 5 + 1;											
				G.deckCount[currentPlayer] = 10 - G.handCount[currentPlayer];
				G.discardCount[currentPlayer] = rand() % 5;
				G.numActions = rand() % 5;
				G.handCount[1] = rand() % 5 + 1;											
				G.deckCount[1] = 10 - G.handCount[1];
				G.discardCount[1] = rand() % 5;
				//printf("second player: hand %d, deck %d, and discard %d\n", G.handCount[1], G.deckCount[1], G.discardCount[1]);
				int v;
				for(v = 0; v < G.discardCount[currentPlayer]; v++)
					G.discard[currentPlayer][v] = 1;
				
				//for(v = 0; v < G.discardCount[currentPlayer]; v++)
					//printf("discard card %d is a %d\n", v, G.discard[currentPlayer][v]);
				G.numActions = rand() % 5;
				//printf("num actions are %d\n", G.numActions);
				memcpy(&testcaseG, &G, sizeof(struct gameState));
				//G.hand[1][0] = village;
				//G.handCount[1]++;

				//G.whoseTurn = 1;
				int total = 0;
				int h;

				int firstDeckcount = G.deckCount[0];
				for (h = 0; h < 27; h++)	
					total += fullDeckCount(0, h, &G);
				//printf("first total is %d\n", total);
				
				//printf("start: numactions %d\n", G.numActions);
				
				cardEffect(village, choice1, choice2, choice3, &testcaseG, handpos, bonus);//play smithy from index 0 of hand
				//printf("Player 1's hand is %d, their deck is %d, and their discard pile is %d \n", testcaseG.handCount[0], testcaseG.deckCount[0], testcaseG.discardCount[0]);
				
				firstDeckcount = testcaseG.deckCount[0];
				int newtotal = 0;
				for (h = 0; h < 27; h++)	
					newtotal += fullDeckCount(0, h, &testcaseG);
				//printf("second total is %d\n", newtotal);
				addedCards = 1;
				addedCoins = 0;			
				
				int addedActions = 2;
				if(testcaseG.coins == G.coins)
					passedTests++;
				//printf("Passed: the expected coin total is %d, and the current coin total is %d\n", G.coins, testcaseG.coins);
				else{
					printf("Failed: the expected coin total is %d, and the current coin total is %d\n", G.coins, testcaseG.coins);
					failedTests++;
				}
				if(testcaseG.numActions == G.numActions+addedActions)
					passedTests++;
				//printf("Passed: %d actions correctly added, there were %d actions total and %d actions total expected\n", addedActions, testcaseG.numActions, G.numActions+2);
				else{
					printf("Failed: %d actions total, %d actions total expected\n", testcaseG.numActions, G.numActions+2); 
					failedTests++;
				}
				if(testcaseG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 1)
					passedTests++;
				//printf("Passed: %d card(s) correctly added to the discard pile\n", discardedCards);
				else{
					printf("Failed: %d card(s) added to the discard pile, and %d card was expected to be added to the discard pile\n", testcaseG.discardCount[currentPlayer] - G.discardCount[currentPlayer], discardedCards);
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
				//printf("Passed: the deck count is %d and the expected deck count is %d\n", testcaseG.deckCount[currentPlayer], G.deckCount[currentPlayer] - addedCards + shuffledCards);
				else{
					printf("Failed: the deck count is %d and the expected deck count is %d\n", testcaseG.deckCount[currentPlayer], G.deckCount[currentPlayer] - addedCards + shuffledCards);
					failedTests++;
				}
				if(testcaseG.deckCount[currentPlayer] + addedCards == G.deckCount[currentPlayer])
					passedTests++;
				//printf("Passed: 1 card was drawn from Player 1's deck\n");
				else{
					printf("Failed: %d card(s) were drawn from Player 1's deck, and 1 card was expected to be drawn\n", G.deckCount[currentPlayer] - testcaseG.deckCount[currentPlayer]);
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
				int counter = 0;
				for(m = 7; m < 17; m++)
					if(testcaseG.supplyCount[m] != G.supplyCount[m]){
						printf("Failed: The supply count of card %d changed\n", m);
						failedTests++;
					}
					else
						passedTests++;
						//counter++;
				//if(counter == 10)
					//printf("Passed: The supply counts of all the kingdom cards have stayed the same\n");
				
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
	}
	printf("%d tests failed, %d tests passed, %d tests total \n", failedTests, passedTests, failedTests+passedTests);
    printf("All tests taken!\n");
	
    return 0;
}