#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h> // chdir 을 위한 헤더파일 (cd 명령어를 만들기 위함)
#include <sys/wait.h>

#define MAX_LEN_LINE    100

int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
    
    printf("안녕하세요 제가만든 shell을 사용해주셔서 감사합니다. \n");
    printf("종료키는 'exit' 입니다\n");
    printf("명령어 목록키는 'help' 입니다.\n\n\n\n\n");
    
    while (true) {
        char *s;
        int len;
        
        printf("MyShell $ ");
        s = fgets(command, MAX_LEN_LINE, stdin);

        
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        
        len = strlen(command);
        
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }

        
        if (strcmp(command, "exit") == 0) {
                printf("프로그램 종료합니다.\n");
                return(-1);
            }

        
      
        pid = fork();



        if (pid < 0) { //pid 는 음수
            fprintf(stderr, "fork failed\n");
            exit(1);
        }

        if (pid != 0) {  /* parent */ // pid 는 양수
            
            cpid = waitpid(pid, &status, 0);

            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }

            printf("Child process terminated\n");

            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }



        else {  /* child */ //pid 는 0


            if (strcmp(s, "help") == 0) {
                printf("명령어 : ls / 오늘의 학식 / 오늘의 날씨 / 눈뽕\n");
                return 0;
            }

            if (strcmp(s, "오늘의 학식") == 0){
                system("explorer.exe http://www.kookmin.ac.kr/user/unLvlh/lvlhSpor/todayMenu/index.do");
                exit(0);
            }

            if (strcmp(s, "오늘의 날씨") == 0){
                system("explorer.exe https://www.weather.go.kr/w/weather/forecast/short-term.do#");
                exit(0);
            }

            if (strcmp(s, "눈뽕") == 0){
                for (int i = 0; i < 50; i ++){
                     int c = rand()% 7 + 1;
                     usleep(50000);
                     printf("\033[4%dm                                                                                                                                                                                                                                                                                                                                                                                               \n", c);
                     }
                printf("\033[0m \n\n\n눈건강은 중요합니다.\n");
                exit(0);
            }

            if (strcmp(s, "ls")== 0){
		        args[0] = "/bin/ls";
	        }

            



            ret = execve(args[0], args, NULL);
            if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
        }

    }
    return 0;
}

