#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>





// verify the test
int counterVariable = 0 ; 


// assertTrue function to collect coverage
void assertTrueFunction(int x, int y){

    if (x == y){
        printf("Test: PASSED\n" );
    }


    else {
        printf("Test: FAILED" );
  
    counterVariable++; 
}

}

int main(){
    
                int choice_1 = 0 ;
                int choice_2 = 0; 
                int choice_3 = 0 ; 
                int treasureCount = 0; 
                int treasureCountOriginal = 0; 
                int bonus = 0 ; 
                int numPlayers = 2; 
                int player_0 = 0;
                int player_1 = 1 ; 
                int cards; 
                int handPos = 0 ;

                int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

               int seed = 2000; 

               struct gameState G , stateOriginal; 

               printf("TESTING  adventurer()\n");






               // initialize a game
               initializeGame(numPlayers,k, seed, &G);

               // memory copy
               memcpy(&stateOriginal,&G,sizeof(struct gameState));

               cardEffect(adventurer,choice_1,choice_2,choice_3,&G,handPos,&bonus);

               printf("\n The player_0 gains 2 cards\n");

               assertTrueFunction(G.handCount[player_0],stateOriginal.handCount[player_0] + 2);

    



                // for loop to verify tresure

               for (int i = 0; i<G.handCount[player_0]; i++){
                    cards = G.hand[player_0][i];
                    if(cards == copper || cards == silver || cards == gold){

                            treasureCount++; 
                    }
               }
               

               for (int i = 0; i<stateOriginal.handCount[player_0]; i++){
                    cards = stateOriginal.hand[player_0][i];

                    if (cards == copper || cards == silver || cards == gold){

                        treasureCountOriginal ++ ;
                    }
               }



                printf("\nPlayer_0 has gained 2 treasure cards\n");
                assertTrueFunction(treasureCountOriginal + 2,treasureCount);


                    printf("\nvictory card piles is the same\n");
                    printf("Province Pile\n");
                    
                    assertTrueFunction(G.supplyCount[province],stateOriginal.supplyCount[province]);
                    
                    printf("Duchy Pile\n");
                    
                    assertTrueFunction(G.supplyCount[duchy],stateOriginal.supplyCount[duchy]);
                    
                    printf("Estate Pile\n");
                    
                    assertTrueFunction(G.supplyCount[estate],stateOriginal.supplyCount[estate]);

                    printf("\n kingdom card pile is the same\n");


                    for (int i = 0; i<10; ++i){
                        printf("testing the cards piles . . . \n");

                        assertTrueFunction(G.supplyCount [k[i]],stateOriginal.supplyCount[k[i]]);

                    }



                printf("\nPlayer_1 remains the same\n");
                
                printf("Hand Count\n");
                
                assertTrueFunction(G.handCount[player_1],stateOriginal.handCount[player_1]);
                
                printf("Deck Count\n");
                
                assertTrueFunction(G.deckCount[player_1],stateOriginal.deckCount[player_1]);



                if(counterVariable){
                                    printf("\nTest: Test Failed\n");
                                    printf("Failed  %d\n",counterVariable);
                                
                                }

                                else {

                                    printf("\nTest: Test Concluded\n\n");
                                }



                                return 0 ; 



}


