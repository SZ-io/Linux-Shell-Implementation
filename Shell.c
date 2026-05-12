#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	char input[500];
	char *args[22];
	int status;
	while (1){
		printf("Matan_Shell> ");
		fflush(stdout);
		
		// getting an input
		
		if (fgets(input , sizeof(input) , stdin) == NULL){
			break; // in case something went wrong
		}
		
		// cleaning the " \n " 
		
		input[strcspn(input , "\n")] = 0;
		
		// if the user wants to quit
		
		if (strcmp(input , "leave") == 0){
			break;
		}
		
		int i=0;
		char *token = strtok (input , " ");
		
		while (token != NULL && i < 21){
			args[i] = token;
			i++;
			token = strtok( NULL , " ");
		}
		args [i] = NULL;
		
		int pid = fork();
		 if (pid ==0)//child
		{
			//absolute path
			if (strchr(args[0], '/')!= NULL){
				execv(args[0],args);
			}
			// getting the path
			char * path_env = getenv("PATH");
			char path_copy[2000]; //copy so we wont corrupt the original one
			strcpy(path_copy, path_env);
			//cut ":"
			char *dir = strtok(path_copy, ":");
			while (dir !=NULL){
				char full_path[1000];
				strcpy(full_path, dir); //copy directory name
				strcat(full_path, "/"); //pate "/" after directory name
				strcat(full_path, args[0]); //copy command name (like ls)
				
				execv(full_path, args); //try and run the command
				dir = strtok(NULL, ":"); // if failed, try the next directory
			}
		//if we reached here than all directories failed
			printf("%s: command not found\n", args[0]);
			exit(1);
		}
		else //father
		{
			wait(&status);
		}
	}
	
	printf("Goodbye\n");
	return 0;
}
