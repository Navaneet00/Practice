// ----- Run this file in Ubuntu (where it is stored in linux_lab dir) -----

// #include <iostream>
// #include <sys/wait.h>
// #include <cstdlib>
// #include <unistd.h>
// using namespace std;

// int main(){

//    pid_t pid = fork();

//    if(pid < 0){
//       cerr << "Fork failed" << endl;
//       return 1;
//    }

//    else if(pid == 0){
//       // Child process
//       cout << "Child Process" << endl;
//       cout << "Child Process Id: " << getpid() << endl;
//       cout << "Parent Process Id: " << getppid() << endl;

//       exit(42);
//    }
   
//    else{
//       // Parent Process
//       cout << "Parent Process" << endl;
//       int status;
//       wait(&status);

//       cout << "Parent Process waited here" << endl;

//       if(WIFEXITED(status)){
//           cout << "Child exited with code: " << WEXITSTATUS(status) << endl;
//       }
//    }

//    return 0;

// }