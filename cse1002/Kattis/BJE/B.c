#include <stdio.h>

int main(void){
// 1 1 2 2 2 8
    int king, queen, rook, bishop, knight, pawn;
    scanf(" %d %d %d %d %d %d", &king, &queen, &rook, &bishop, &knight, &pawn); 
    
    if(king==1){
        printf("0");
    } else if(king>1){
        int count=0;
        while(king!=1){
            king--;
            count--;
        }
        printf("%d",count);
    } else if(king<1){
        int count=0;
        while(king!=1){
            king++;
            count++;
        }
        printf("%d",count);
    }
    
    if(queen==1){
        printf(" 0");
    } else if(queen>1){
        int count=0;
        while(queen!=1){
            queen--;
            count--;
        }
        printf(" %d",count);
    } else if(queen<1){
        int count=0;
        while(queen!=1){
            queen++;
            count++;
        }
        printf(" %d",count);
    } 

    if(rook==2){
        printf(" 0");
    } else if(rook>2){
        int count=0;
        while(rook!=2){
            rook--;
            count--;
        }
        printf(" %d",count);
    } else if(rook<2){
        int count=0;
        while(rook!=2){
            rook++;
            count++;
        }
        printf(" %d",count);
    } 
    
    if(bishop==2){
        printf(" 0");
    } else if(bishop>2){
        int count=0;
        while(bishop!=2){
            bishop--;
            count--;
        }
        printf(" %d",count);
    } else if(bishop<2){
        int count=0;
        while(bishop!=2){
            bishop++;
            count++;
        }
        printf(" %d",count);
    } 
    
    if(knight==2){
        printf(" 0");
    } else if(knight>2){
        int count=0;
        while(knight!=2){
            knight--;
            count--;
        }
        printf(" %d",count);
    } else if(knight<2){
        int count=0;
        while(knight!=2){
            knight++;
            count++;
        }
        printf(" %d",count);
    } 
    
     if(pawn==8){
        printf(" 0");
    } else if(pawn>8){
        int count=0;
        while(pawn!=8){
            pawn--;
            count--;
        }
        printf(" %d",count);
    } else if(pawn<8){
        int count=0;
        while(pawn!=8){
            pawn++;
            count++;
        }
        printf(" %d",count);
    } 
    
    return 0;
}