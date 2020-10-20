#ifndef PIPE2_H
#define PIPE2_H

#ifndef LINUX
int pipe2(int pipefd[2], int flags);
#endif

#endif