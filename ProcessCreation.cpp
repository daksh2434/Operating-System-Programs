#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
int main() {
    int status;
    pid_t pid = fork();

    if (pid < 0) {
        cout << "Fork failed";
    }
    else if (pid == 0) {
        cout << "Child PID: " << getpid() << endl;
        execlp("ls", "ls", "-l", NULL);
        cout << "Execution  failed";
        printf("\n");
    }
    else {
        cout << "Parent PID: " << getpid() << endl;
        cout << "Waiting for child" << endl;

        wait(&status);
        cout << "Child finished" << endl;
    }
    return 0;
}
