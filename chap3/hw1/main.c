#include <stdio.h>
#include <string.h>
#include "copy.h"

int main(){
	char lines[5][100];
	int lengths[5];
	int i, j;
	char temp[100];
	int temp_len;

	for(i= 0; i< 5; i++){
		gets(lines[i]);
		lengths[i]= strlen(lines[i]);
	}

	for(i= 0; i< 4; i++){
		for(j= i+ 1; j< 5; j++){
			if(lengths[i]< lengths[j]){
				temp_len= lengths[i];
				lengths[i]= lengths[j];
				lengths[j]= temp_len;

				copy(lines[i], temp);
				copy(lines[j], lines[i]);
				copy(temp, lines[j]);
			}
		}
	}

	printf("\n");
	for(i= 0; i< 5; i++){
		printf("%s\n", lines[i]);
	}

	return 0;
}


