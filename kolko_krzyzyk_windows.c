
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define MEM_SIZE 1000
struct Table{
int columns;
int row;
int *matrix;
};
void print(struct Table *temp)
{
    for (int i=0; i<temp->row; i++){
            
        for (int j=0;j<temp->columns;j++){
                if(temp->matrix[i*temp->columns+j]==2){
                printf("|X ");
                            }
                else if(temp->matrix[i*temp->columns+j]==1){
                printf("|O ");
                            }
                else{
                printf("|  ");                     
                    }
                }
            printf("|\n__________\n");
        }
}
int check(struct Table *temp){
	for (int i=0;i<temp->columns;i++)
	{
        	if((temp->matrix[i]==temp->matrix[i+3])&&(temp->matrix[i+3]==temp->matrix[i+6])&&(temp->matrix[i+6]==2))
		{
    			return 1;
		}
		else if((temp->matrix[i]==temp->matrix[i+3])&&(temp->matrix[i+3]==temp->matrix[i+6])&&(temp->matrix[i+6]==1))
		{
    			return 2;
		}
	}
	for (int i=0; i<=6; i=i+3)
	{
    		if((temp->matrix[i]==temp->matrix[i+1])&&(temp->matrix[i+1]==temp->matrix[i+2])&&(temp->matrix[i+2]==2))
    		{
        		return 1;
    		}
		else if((temp->matrix[i]==temp->matrix[i+1])&&(temp->matrix[i+1]==temp->matrix[i+2])&&(temp->matrix[i+2]==1))
		{
    			return 2;
		}
	}
	if((temp->matrix[0]==temp->matrix[4])&&(temp->matrix[4]==temp->matrix[8])&&(temp->matrix[8]==2)){
    		return 1;
	}
	else if((temp->matrix[0]==temp->matrix[4])&&(temp->matrix[4]==temp->matrix[8])&&(temp->matrix[8]==1))
	{
    		return 2;
	}
	if((temp->matrix[2]==temp->matrix[4])&&(temp->matrix[4]==temp->matrix[6])&&(temp->matrix[6]==2)){
    		return 1;
	}
	else if((temp->matrix[2]==temp->matrix[4])&&(temp->matrix[4]==temp->matrix[6])&&(temp->matrix[6]==1))
	{
    		return 2;
	}

	return 0;
}
void krzyzyk(struct Table *temp){

		
	while(1){
		if(temp->matrix[9] % 2 == 0){
    			if(check(temp)==2){
    				printf("przegrales,koniec gry\n");
    				print(temp);
    				return;
    			}
    			if(temp->matrix[9]==9){
        			printf("remis!\n");
        			return;
    			}
    			printf("Twoj ruch!\n");
    			print(temp);
    			int move;
    			while(1){
    				scanf("%d",&move);
    				if(temp->matrix[move-1]!=0)
    				{
        				printf("to pole jest juz zajete\n");
    				}
    				else break;
    			}
    			temp->matrix[move-1]=2;
			
    			print(temp);
    			temp->matrix[9]++;
    			if(check(temp)==1){
        			printf("Wygrales, koniec gry\n");
        			return;    
    			}
    			if(temp->matrix[9]==9){
        			printf("remis!\n");
        			return;}
    
 		}
		else{
    			printf("Kolej przeciwnika\n");
    			Sleep(4000);
}}
}
void kolko(struct Table *temp){
	while(1){
		if(temp->matrix[9] % 2 == 1){
    			if(check(temp)==1){
    				printf("przegrales,koniec gry\n");
    				print(temp);
    				return;
    			}
    			if(temp->matrix[9]==9){
        			printf("remis!\n");
        			return;
    			}
    			printf("Twoj ruch!\n");
    			print(temp);
    			int move;
    			while(1){
    				scanf("%d",&move);
    				if(temp->matrix[move-1]!=0)
   				{
        				printf("to pole jest juz zajete\n");
    				}
    				else break;
    			}
    			temp->matrix[move-1]=1;
    			print(temp);
    			temp->matrix[9]++;
    			if(check(temp)==2){
        			printf("Wygrales, koniec gry\n");
        			return;    
    			}
    			if(temp->matrix[9]==9){
        			printf("remis!\n");
        			return;}
    
 			}
		else{
    			printf("Kolej przeciwnika\n");
			print(temp);
    			Sleep(4000);
			
		    }
	}
}
int main(int argc, char *argv[])
{
	if(argc!=2){
		fprintf(stderr,"invalid number of arguments\n");
		return 1;
	}
	char role;

	HANDLE MapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,MEM_SIZE,argv[1]);
	role='X';
	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{	
		role='O';
	}
	struct Table temp;
	temp.row=3;
	temp.columns=3;
	printf("Jestem %c\n",role);
	void *Buf=MapViewOfFile(MapFile,FILE_MAP_ALL_ACCESS,0,0,MEM_SIZE);
	if(role=='X'){
		int size = 10;
		temp.matrix=malloc(sizeof(int) *size);
		
		for (int i=0;i<10;i++)
		{
    			temp.matrix[i]=0;
		}
		temp.matrix=Buf;
		krzyzyk(&temp);
	}
	else if(role=='O'){
		
		if(Buf!=NULL){
			
			temp.matrix=Buf;
		}
		
		kolko(&temp);
	}
	if(!UnmapViewOfFile(Buf)) {
 		fprintf(stderr, "Could not unmap view of file\n");
 		CloseHandle(MapFile);
 		return 4;
 	}
 	CloseHandle(MapFile);
	return 0;

}