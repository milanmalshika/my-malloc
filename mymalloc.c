#include<stdio.h>  						 //".c"
#include<stddef.h>
//#include<C:\Users\Milan Malshika\Desktop\MyMalloc\mymalloc.h>

char memoryArray[25000] = {'\0'};		//create the empty array

char *start = memoryArray;				//start pointer points to the first block of the array

char freeflag = 'f';					//create the flags
char allocate = 'a';

char *search_block(size_t byte){		//find a matching block
	char *temp;
	temp = start;
	int size = 0;
	size = *(int *)(temp+1);
	
	while(!(*temp==freeflag && size>=byte)){				//find the space
		
		if(temp+size+byte>=memoryArray+24999){				//when the memory is full
			printf("Memory is Full\n");
			return NULL;
			break;
		}
		if(!temp){
			printf("Not founded a space.\n");
			return NULL;
			break;
		}
		temp = temp+size;
		size = *(int *)(temp+1);
	}
	printf("Found a space\n");
	return temp;
}

char *MyMalloc(size_t byte){
	
	
	if(!*start){											//started memory allocate
		*start = freeflag;
		*(int *)(start+1) = 24999;
		printf("First allocated..\n");
	}
	
	size_t s= byte;
	char *block = search_block(s);
	
	
		
	if(block){
		char *temp;											//set the block
		int block_size= *(int *)(block+1);
		block_size = block_size -s -5;
		temp = block + 5 +s;
		*temp = freeflag;
		*(int *)(temp +1) = block_size;
		
		*(int *)(block +1) = s+5;
		*block = allocate;
		printf("Allocated memory....\n");
	}
	else{
		return NULL;
		printf("Not founded block.....\n");
	}
	
	
	return block;
	
}


void MyFree(char *address){										//free a allocated block
	char *temp, *next, *previous;
	
	temp = start;
	int size = *(int *)(temp+1);
	*temp = *start;
	
	while(temp!=address){										//temp is send in front of the memory
		if(!*temp){
			printf("lll\n");
			break;
		}
		previous = temp;
		temp = temp + size;
		next= temp + *(int *)(temp+1);
	} 
					
	if(*next==freeflag){										//after call the free function, merge the free blocks near by			
		*temp = freeflag;
		*(int *)(temp+1)= *(int *)(temp+1) + *(int *)(next+1);
		printf("next free and freeflag set\n");
	}
	if(*previous==freeflag){
		*temp = freeflag;
		*(int *)(previous+1)= *(int *)(temp+1) + *(int *)(previous+1);
		printf("previous free and freeflag set\n"); 
	}
	
	else{
		*address = freeflag;
		printf("free flag set\n");
	}
}
 

int main(){
	char* check1 = MyMalloc(400);
    char* check2 = MyMalloc(800);
    char* check3 = MyMalloc(500);

    printf(" 400   : %p \n", check1);
    printf(" 800   : %p \n", check2);
    printf(" 500   : %p \n", check3);
    
    MyFree(check3);
    MyFree(check2);
    
    char* check4 = MyMalloc(900);

	printf(" 900 : %p \n", check4);  
	
	return 0;
}

