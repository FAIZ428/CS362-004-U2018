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
    //int seed = 1000;
	int seed;
	int addedCoins;
	int shuffledCards = 0;
    int numPlayer = 2;
    int maxBonus = 10;
	int discardedCards = 1;
	int currentPlayer = 0;
    int p, r, handCount;
	int passedTests = 0;
	int failedTests = 0;
    int bonus = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testcaseG;
	
	int h;
	int total;
	int newtotal;
	int firstDeckcount;
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
	
    printf ("TESTING adventurer():\n");
	printf("Add adventurer to index 0 (hand position 1) and use card effect of adventurer for player 1\n");
	numPlayer = 2;
	int b;
	for(b = 0; b < 500; b++){
		seed = rand();
		
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
															// set the number of cards on hand
				G.handCount[currentPlayer] = rand() % 5 + 1;											
				//G.handCount[currentPlayer] = 1;
				G.deckCount[currentPlayer] = 10 - G.handCount[currentPlayer];
				//sets the top of the deck to a copper
				if(b == 0)
					G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = 4;
				if(b == 1)
					G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = 5;
				if(b == 2)
					G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = 6;
				//if(b == 3 )
					//G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = rand() % 19 + 7;
				//if(b == 4)
					//G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = rand() % 3;
				/*int vb = rand() % 12;
				if( vb <= 4)
					G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = rand() % 2 + 4;
				else if(vb > 4 && vb < 9)
					G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = 1;
				else
				{
					G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = 1;
					G.deck[currentPlayer][G.deckCount[currentPlayer]-2] = 1;
				}*/
				if(b > 489){
					G.handCount[currentPlayer] = rand() % 5 + 1;
					G.deckCount[currentPlayer] = 0;
					G.discardCount[currentPlayer] = rand() % 5 + 2;
					for(h = 0; h < G.discardCount[currentPlayer]; h++)
						G.discard[currentPlayer][h] = rand() % 2 + 4; //The entire discard pile is treasure
				}
					
				//make the second card from the top a copper
				//G.deck[currentPlayer][G.deckCount[currentPlayer]-2] = 4;
				//else
				//	G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = 4;
				if(b < 490)
					G.discardCount[currentPlayer] = rand() % 5;
				//G.discardCount[currentPlayer] = 1;
				
				//printf("first player: hand %d, deck %d, and discard %d\n\n", G.handCount[0], G.deckCount[0], G.discardCount[0]);
				G.handCount[1] = rand() % 5 + 1;											
				G.deckCount[1] = 10 - G.handCount[1];
				G.discardCount[1] = rand() % 5;
				//printf("second player: hand %d, deck %d, and discard %d\n\n", G.handCount[1], G.deckCount[1], G.discardCount[1]);
				int v;
				if(b < 490)
					for(v = 0; v < G.discardCount[currentPlayer]; v++)
						G.discard[currentPlayer][v] = 1; 
						
				memcpy(&testcaseG, &G, sizeof(struct gameState));
				testcaseG.hand[0][0] = adventurer;
				//G.handCount[1]++;

				//G.whoseTurn = 1;
				total = 0;
				
				
				firstDeckcount = G.deckCount[0];
				for (h = 0; h < 27; h++)	
					total += fullDeckCount(0, h, &G);
				//for(h =0; h < testcaseG.handCount[0]; h++)
					//printf("hand card %d is %d\n", h, testcaseG.hand[0][h]);
				//for(h =0; h < testcaseG.handCount[0]; h++)
					//printf("deck card %d is %d\n", h, testcaseG.deck[0][h]);
				int nonTreasures;
				//int w;
				//if(G.deckCount[0] >= 3)
					//for(w = G.deckCount[0]-3; w < G.deckCount[0]; w++)
				if(G.deckCount[currentPlayer] > 0)		
					if(G.deck[0][G.deckCount[0]-1] > 6 || G.deck[0][G.deckCount[0]-1] < 4)
						if(G.deck[0][G.deckCount[0]-2] > 6 || G.deck[0][G.deckCount[0]-2] < 4)
							if(G.deck[0][G.deckCount[0]-3] > 6 || G.deck[0][G.deckCount[0]-3] < 4)
								nonTreasures = 3;
							else
								nonTreasures = 2;
						else
							nonTreasures = 1;
					else
						nonTreasures = 0;
				else
					nonTreasures = 0;
				//int topcard = G.deck[currentPlayer][G.deckCount[currentPlayer]-1];
				//printf("pre-card effect first player: hand %d, deck %d, and discard %d\n\n", testcaseG.handCount[0], testcaseG.deckCount[0], testcaseG.discardCount[0]);
				cardEffect(adventurer, choice1, choice2, choice3, &testcaseG, handpos, bonus);//play adventurer from index 0 of hand
				
				//printf("first player: hand %d, deck %d, and discard %d\n\n", testcaseG.handCount[0], testcaseG.deckCount[0], testcaseG.discardCount[0]);
					
				//printf("non treasure cards number is %d\n", nonTreasures);
				firstDeckcount = testcaseG.deckCount[0];
				newtotal = 0;
				for (h = 0; h < 27; h++)	
					newtotal += fullDeckCount(0, h, &testcaseG);
				addedCards = 2;
				addedCoins = 0;
				//if(testcaseG.discardCount[0] > 0)
					//printf("top discard card is %d \n", testcaseG.discard[0][testcaseG.discardCount[0]-1]);
				if(testcaseG.coins == G.coins)
					passedTests++;
				//printf("Passed: the expected coin total is %d, and the current coin total is %d\n", G.coins, testcaseG.coins);
				else{
					failedTests++;
					printf("Failed: the expected coin total is %d, and the current coin total is %d\n", G.coins, testcaseG.coins);
				}
				//else(testcaseG.discardCount[currentPlayer] != G.discardCount[currentPlayer] + 1)
				if(G.deckCount[currentPlayer] > 0){
					if(testcaseG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + discardedCards + nonTreasures)
						passedTests++;
					//printf("Passed: %d card(s) correctly added to the discard pile.  Current discard pile is %d, initial discard pile was %d\n", discardedCards, testcaseG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
					else{
						printf("Failed: %d card(s) added to the discard pile, %d cards expected to be added to the discard pile. Current discard pile is %d, initial discard pile is %d\n", testcaseG.discardCount[currentPlayer] - G.discardCount[currentPlayer], discardedCards + nonTreasures,testcaseG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
						failedTests++;
					}
				}
				else{
					if(testcaseG.discardCount[currentPlayer] == discardedCards)
						passedTests++;
					//printf("passed there is 1 card in the discard pile\n");
					else{
						failedTests++;
						printf("failed, expected 1 card in the discard pile, there are %d cards\n", testcaseG.discardCount[currentPlayer]);
					}
				}	
				if (testcaseG.handCount[currentPlayer] == G.handCount[currentPlayer] + addedCards - discardedCards)
					passedTests++;
				//printf("Passed: The hand count for the current Player is %d and the expected hand count is %d \n", testcaseG.handCount[currentPlayer], G.handCount[currentPlayer] + addedCards - discardedCards);
				else{
					failedTests++;
					printf("Failed: The hand count for the current Player is %d and the expected hand count is %d \n", testcaseG.handCount[currentPlayer], G.handCount[currentPlayer] + addedCards - discardedCards);
				}
				if(G.deckCount[currentPlayer] > 0){
					if(testcaseG.deckCount[currentPlayer] + addedCards + nonTreasures == G.deckCount[currentPlayer])
						passedTests++;
					//printf("Passed: %d cards were drawn from Player 1's deck\n", testcaseG.deckCount[currentPlayer] + addedCards + nonTreasures);
					else{
						failedTests++;
						printf("Failed: %d card(s) were drawn from Player 1's deck, and %d cards were expected to be drawn, 2 treasures and %d non-treasures\n", G.deckCount[currentPlayer] - testcaseG.deckCount[currentPlayer], addedCards + nonTreasures, nonTreasures);
					}
				}
				else
					if(G.discardCount[currentPlayer] - testcaseG.deckCount[currentPlayer] == 2)
						passedTests++;
					//printf("Passed: 2 cards were drawn from Player 1's deck\n");
					else{
						printf("Failed: %d card(s) were drawn from Player 1's deck and 2 cards were expected to be drawn\n", G.discardCount[currentPlayer] - testcaseG.deckCount[currentPlayer]);
						failedTests++;
					}
				if(G.deckCount[currentPlayer] - testcaseG.deckCount[currentPlayer] == 2 + nonTreasures){				
					if(testcaseG.hand[0][testcaseG.handCount[0]-1] > 3 && testcaseG.hand[0][testcaseG.handCount[0]-1] < 7)
						if(testcaseG.hand[0][testcaseG.handCount[0]-2] > 3 && testcaseG.hand[0][testcaseG.handCount[0]-2] < 7)
							passedTests++;
						//printf("Passed: both new cards in Player 1's hand are treasures \n");
						else{
							printf("Failed: only 1 new card in Player 1's hand is a treasure \n");
							failedTests++;
						}
						else if(testcaseG.hand[0][testcaseG.handCount[0]-2] > 3 && testcaseG.hand[0][testcaseG.handCount[0]-2] < 7){
							printf("Failed: only 1 new card in Player 1's hand is a treasure \n");
							failedTests++;
						}
						else{
							failedTests++;
							printf("Failed: both new cards in Player 1's hand aren't treasures \n");
						}
				}
				else{
					if(testcaseG.hand[0][testcaseG.handCount[0]-1] > 3 && testcaseG.hand[0][testcaseG.handCount[0]-1] < 7){
						failedTests++;
						printf("Failed: only 1 new card in Player 1's hand is a treasure \n");
					}
					else{
						printf("Failed: there are no new treasures in Player 1's hand \n");
						failedTests++;
					}	
				}
				if(G.deckCount[currentPlayer] > 0){
					if(testcaseG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - addedCards - nonTreasures + shuffledCards)
						passedTests++;
					//printf("Passed: the deck count is %d and the expected deck count is %d\n", testcaseG.deckCount[currentPlayer], G.deckCount[currentPlayer] - addedCards - nonTreasures + shuffledCards);
					else{
						failedTests++;
						printf("Failed: the deck count is %d and the expected deck count is %d\n", testcaseG.deckCount[currentPlayer], G.deckCount[currentPlayer] - addedCards - nonTreasures + shuffledCards);
					}
				}
				else
					if(G.discardCount[currentPlayer]-2 == testcaseG.deckCount[currentPlayer])
						passedTests++;
					//printf("Passed: the deck count is %d and the expected deck count is %d\n", testcaseG.deckCount[currentPlayer], G.discardCount[currentPlayer]-2);
					else{
						failedTests++;
						printf("Failed: the deck count is %d and the expected deck count is %d\n", testcaseG.deckCount[currentPlayer], G.discardCount[currentPlayer]-2);
					}
				if(testcaseG.handCount[1] == G.handCount[1])
					passedTests++;
				//printf("Passed: Player 2's hand count didn't change\n");
				else{
					failedTests++;
					printf("Failed: Player 2's hand count changed\n");
				}
				if(testcaseG.deckCount[1] == G.deckCount[1])
					passedTests++;
				//printf("Passed: Player 2's deck count didn't change\n");
				else{
					failedTests++;
					printf("Failed: Player 2's deck count changed\n");
				}
				if(testcaseG.discardCount[1] == G.discardCount[1])
					passedTests++;
				//printf("Passed: Player 2's discard count didn't change\n");
				else{
					failedTests++;
					printf("Failed: Player 2's discard count changed\n");
				}
				if(testcaseG.supplyCount[estate] == G.supplyCount[estate] && testcaseG.supplyCount[duchy] == G.supplyCount[duchy] && testcaseG.supplyCount[province] == G.supplyCount[province])
					passedTests++;
				//printf("Passed: the victory card counts are unchanged\n");
				else{
					failedTests++;
					printf("Failed: the victory card counts have changed\n");
				}
				//printf("test 1B: were any cards trashed or added unnecessarily to Player 1's full deck?\n");
				if(total == newtotal)
					passedTests++;
				//printf("Test passed, no cards were trashed unnecessarily from Player 1's full deck\n");
				else if(total > newtotal){
					failedTests++;
					printf("Test failed, %d card(s) was/were trashed unnecessarily from Player 1's full deck\n", total-newtotal);
				}
				else{
					failedTests++;
					printf("Test failed, %d cards were added unnecessarily to Player 1's full deck\n", newtotal-total);
				}
				int m;
				int counter = 0;
				for(m = 7; m < 17; m++)
					if(testcaseG.supplyCount[m] != G.supplyCount[m]){
						failedTests++;
						printf("Failed: The supply count of card %d changed\n", m);
					}
					else
						passedTests++;
				//if(counter == 10)
					//printf("Passed: The supply counts of all the kingdom cards have stayed the same\n\n");				
	}

	printf("%d tests failed, %d tests passed, %d tests total \n", failedTests, passedTests, failedTests+passedTests);
    printf("All tests taken!\n");

    return 0;
}