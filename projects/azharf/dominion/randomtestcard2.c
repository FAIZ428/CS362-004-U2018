#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>






// counter variables defined

int cardEffectsFail = 0; 
int discardCardFails = 0 ; 
int drawCardFail = 0 ; 
int deckHandCountFail = 0; 


void smithyTesting( int player, struct gameState *afterGame){


  int i; 
  
  int j ; 
  
  int k; 
  
  int l ; 
  
  int m ; 


// craete gamestate to verify the function
 struct gameState newGame ; 




memcpy(&newGame,afterGame,sizeof(struct gameState));

int bonus  = 0; 

// testing the function smithy card 
i = cardEffect(smithy,0,0,0, afterGame,0, &bonus);

j = drawCard(player, &newGame); 

k = drawCard(player, &newGame);

l = drawCard(player, &newGame); 

 m = discardCard(0, player, &newGame,0);

 // retrieve values deck

 
  int afterHC = afterGame->handCount[player];
  
  int afterDC = afterGame->deckCount[player]; 

  int beforeHC = newGame.handCount[player];
  
  int beforeDC =  newGame.deckCount[player];

 



  if (j == -1 && newGame.deckCount[player] != 0){

      drawCardFail++;
  }

  if( k == -1 && newGame.deckCount[player] !=0){

      drawCardFail++;
  }

  if (l == -1 && newGame.deckCount[player] != 0){

      drawCardFail++;
  }


    // verifying discards

      if (!(i == 0 && m == 0))
      {
        if (i)
        {
          cardEffectsFail++;
        }

        if (m)
        {
          discardCardFails++;
        }
      }


      if(!(afterHC == beforeHC && afterDC == beforeDC))
      {
        deckHandCountFail ++ ; 
      }



}


int main(){




   
    printf("Function: smithyTesting()\n");
    

    int times = 10000;
    
    int  gamePlayers;
    
    struct gameState state;
    
    srand(time(NULL));

    for (int n = 0; n < times; n++) {
        
        for ( int i = 0; i < sizeof(struct gameState); i++) {
           
            ((char*)&state)[i] = floor(Random() * 256);
        
        }
        gamePlayers = floor(Random() * MAX_PLAYERS);
        
        state.deckCount[gamePlayers] = floor(Random() * MAX_DECK);
        
        state.discardCount[gamePlayers] = floor(Random() * MAX_DECK);
       
        state.handCount[gamePlayers] = floor(Random() * MAX_HAND);
        
        state.playedCardCount = floor(Random() * (MAX_DECK-1));
        
        state.whoseTurn = gamePlayers;
       




        smithyTesting(gamePlayers,&state);
    }
    int Fail_of_cards = cardEffectsFail + discardCardFails +
                        drawCardFail + deckHandCountFail;
   
    printf("\n***** RESULTS *****\n");
    
   
    printf("PASSED TESTS: %d\n",times - Fail_of_cards);
   
   
    printf("FAILED TESTS: %d\n",Fail_of_cards);

    if (Fail_of_cards == 0) {
       
        printf (" PASSED RANDOM TEST \n\n");
    }
    
    else {
       
        printf("\n $$$$$$ FAILURE  DETAILS $$$$$$\n");
       
        printf("drawCard() fail: %d\n",drawCardFail);
        
        printf("cardEffect() fail: %d\n",cardEffectsFail);
        
        printf("discardCard() fail: %d\n",discardCardFails);
        
        printf("Hand/Deck Count failure: %d\n",deckHandCountFail);
       
       
    }
   
   
   
    return 0;















}
















