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
    
    counterVariable ++; 
}

}





int main(){


int choice_1 = 0 ;
          int choice_2 = 0; 
          int choice_3 = 0 ; 
          
        int bonus = 0 ; 
        int numPlayers = 2; 
          int player_0 = 0;
          int player_1 = 1 ; 
          int cards; 
          int handPos = 0 ;

          int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

               int seed = 2000; 

               struct gameState state , stateOriginal; 

               printf("TESTING  feast()\n");

                memset(&state,23,sizeof(struct gameState)); 

                memset(&stateOriginal,23,sizeof(struct gameState)); 

                initializeGame(numPlayers, k , seed, &state);

                memcpy(&stateOriginal,&state,sizeof(struct gameState));
                // call cardEffect function 
                cardEffect(feast, choice_1, choice_2, choice_3,&state,handPos, &bonus);



                printf("\n The player_0 gains 4 cards\n");
                assertTrueFunction(state.handCount[player_0],stateOriginal.handCount[player_0] + 3);




                 printf("\n The player_0 gains 4 cards in piles\n");
                 assertTrueFunction(state.handCount[player_0],stateOriginal.handCount[player_0] - 4);

                 printf("\n The player_0 buys 4 cards \n");
                 assertTrueFunction(state.handCount[player_0],stateOriginal.handCount[player_0] + 1);

                  printf("\nvictory card piles is the same\n");
                  
                  printf("Province Pile\n");
                  
                  assertTrueFunction(state.supplyCount[province],stateOriginal.supplyCount[province]);
                     
                     printf("Duchy Pile\n");
                     
                     assertTrueFunction(state.supplyCount[duchy],stateOriginal.supplyCount[duchy]);
          
          printf("Estate Pile\n");
            
            assertTrueFunction(state.supplyCount[estate],stateOriginal.supplyCount[estate]);




                printf("\n kingdom card pile is the same\n");
                for (int i = 0; i<10; ++i){
              printf("testing the cards piles . . . \n");

              assertTrueFunction(state.supplyCount [k[i]],stateOriginal.supplyCount[k[i]]);
            


        
}

          printf("\nPlayer_1 gets a card\n");



            assertTrueFunction(state.handCount[player_1],stateOriginal.handCount[player_1] + 1);

            printf("\nPlayer_1 gets a card from deck\n");
             assertTrueFunction(state.handCount[player_1],stateOriginal.handCount[player_1] -1);

             



             
          if(counterVariable){
                                    printf("\nTest: Test Failed\n");
                                    printf("Failed:  %d\n",counterVariable);
                                
                                }

                                else {

                                    printf("\nTest: Test Concluded\n\n");
                                }



                                return 0 ; 







}