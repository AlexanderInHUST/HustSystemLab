#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

pid_t pid1, pid2;
int pipe_fd[2];

void shut1(int signum) {
    printf("%d says good bye.\n", getpid());
    close(pipe_fd[1]);
    exit(0);
}

void shut2(int signum) {
    printf("%d says good bye.\n", getpid());
    close(pipe_fd[0]);
    exit(0);
}

void sighandler(int signum) {
    kill(pid1, SIGUSR1);
    kill(pid2, SIGUSR1);
    printf("%d main good bye!\n", getpid());
//    exit(0);
}

void pid1_job() {
    signal(SIGINT, SIG_IGN);
    signal(SIGUSR1, shut1);
    int count = 0;
    char buf[100];
    close(pipe_fd[0]);
    while (1) {
        sprintf(buf, "send msg %d", count);
        write(pipe_fd[1], buf, sizeof(char) * 20);
        count++;
        sleep(1);
    }
}

void pid2_job() {
    signal(SIGINT, SIG_IGN);
    signal(SIGUSR1, shut2);
    char buf[100];
    close(pipe_fd[1]);
    while (1) {
        read(pipe_fd[0], buf, sizeof(char) * 100);
        printf("%s\n", buf);
    }
}

int main() {
    if (pipe(pipe_fd) == -1) {
        printf("pipe fail!");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1) {
        printf("fork fail!");
        exit(1);
    }

    if (pid1 == 0) {
        pid1_job();
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            printf("fork fail!");
            exit(1);
        }
        if (pid2 == 0) {
            pid2_job();
        } else {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            signal(SIGINT, sighandler);
//            while(1);
            wait(0);
            wait(0);
        }
    }
    return 0;
}