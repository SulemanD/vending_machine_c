#include <stdio.h>
#include <stdlib.h>

#define MULTIPLE 5
#define MINCOST 30
#define MAXCOST 115
#define COIN1 5
#define COIN2 10 
#define COIN3 20 

void intro(int price){
	printf("Pop is %d centimes. ", price);
	printf("Please insert any combination of nickels [N or n], dimes [D or d] or Pentes [P or p]. You can also press R or r for coin return.\n");
}

void check(char coin, int *p){
	int value = 0;
	if(coin == 'n' || coin == 'N'){
		printf("Nickel detected.\n");
		value = COIN1;		
	}
	else if(coin == 'd' || coin == 'D'){
		printf("Dime detected.\n");
		value = COIN2;
        }
	else if(coin == 'p' || coin == 'P'){
                printf("Pente detected.\n");
		value = COIN3;
        }
	*p = value;

}

int *refund(int *sump){
	int tempsum = *sump;
	int coinone = 0;
	int cointwo = 0;
	while (tempsum > 0){
	if(tempsum%COIN2 == 0) {
		tempsum = tempsum - COIN2;
		cointwo++;
	}
	else {
		tempsum = tempsum - COIN1;
		coinone++;
	}
 
	}

	int *amounts = malloc(2);
	amounts[0] = coinone;
	amounts[1] = cointwo;
	return 	amounts;
}

void giveref(int *sp){
	int *refundamt = refund(sp);
        printf("Change given %d centimes as %d dime(s) and %d nickel(s).\n", *sp, refundamt[1], refundamt[0]);

}

int main(int argc, char *argv[]){
	int price;
	if (argc == 2){price = atoi(argv[1]);}
	if(argc != 2 ) {
		printf("Please specify the selling price as a command line argument.\n" );
		printf("Usage: %s [price]\n", argv[0]);	
	}
	else if(price > MAXCOST || price < MINCOST) {
		printf("Price must be between %i and %i centimes inclusive.\n", MINCOST, MAXCOST);
		}
	else if(price % 5){
		printf("Price must be a multiple of %i.\n", MULTIPLE);	
	}

	else{	
		char coin;

		printf("Welcome to my C Pop Machine!\n");
		intro(price);
		
		
		int sum = 0;
		
		while (sum!= -1){
			int inserted;
			printf("Enter a coin(NDPR): ");
			scanf(" %c", &coin);
                        check(coin, &inserted);
			
			if(coin == 'R' || coin == 'r'){
				giveref(&sum);
				sum = 0;

			}
			else if(coin == 'K' || coin == 'k'){
				giveref(&sum);
				printf("Shutting down. Goodbye.\n");
				
				sum = -1;
			}	
			else{
				if(inserted == 0){
                			printf("Unknown coin reject.\n");
					continue;
				}
				else{
					sum = sum + inserted;
					printf("You have inserted a total of %d centimes\n", sum);
						if (sum <  price) {
						printf("Please insert %d more centimes.\n", price-sum);
						}
				}
			}

			if(sum == 0){
			intro(price);
			}
			else if(sum == price){
				printf("Pop is dispensed. Thank you for your business! Please come again.\n");
				sum = sum - price;
				giveref(&sum);
				intro(price);
			}
		}
	}
}