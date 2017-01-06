#include <stdio.h>

void main(void){
	FILE *fp,*fw;
	char buff[100],ch;
	int prev = 0;
	fp = fopen("prog.c","r");
	while((ch = fgetc(fp))!= EOF){
		if(ch == '/' && prev==0){
			prev = 1;
		}else if(prev==1 && ch == '/'){
			// printf("%c",ch);
			while((ch = fgetc(fp)) != '\n'){
				if(ch == EOF)
					break;
			}
		}else if(prev==1 && ch == '*'){
			while((ch = fgetc(fp)) != '*'){
				if(ch == EOF)
					break;
			}
		}else if(prev==1 && ch != '/'){
			printf("%c", ch);
			prev = 0;
		}else{
			printf("%c",ch);

		}
	}
	fclose(fp);
	printf("\n");
}