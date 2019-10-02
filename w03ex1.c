/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 *                   O
 *                 /   \
 *                O     O
 *               / \   / \
 *              O   O O   O
 *                .     .
 *                .     .
 *                .     .
 */

/* Example output:
 * 
 * 
9565 Process produced number '14'
9570 Process produced number '25'
9574 Process produced number '53'
Process: 9567, right child: 9570, left child: 9573, height: 1 
9573 Process produced number '71'
Process: 9563, right child: 9565, left child: 9568, height: 1 
9568 Process produced number '64'
Process: 9564, right child: 9571, left child: 9574, height: 1 
 |Right: 25, Left: 71| 
9571 Process produced number '89'
9572 Process produced number '78'
 |Right: 89, Left: 53| 
Process: 9562, right child: 9566, left child: 9567, height: 2 
Process: 9566, right child: 9569, left child: 9572, height: 1 
 |Right: 14, Left: 64| 
9569 Process produced number '91'
Process: 9561, right child: 9563, left child: 9564, height: 2 
 |Right: 78, Left: 142| 
 |Right: 91, Left: 78| 
Process: 9560, right child: 9561, left child: 9562, height: 3 
 |Right: 169, Left: 96| 
 |Right: 220, Left: 265| 
 * 
 * 
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void create_tree(int height);
void node();
void parent(pid_t right, pid_t left);
int read_file(pid_t pid);

void w03ex1(){
    create_tree(3);
}

void create_tree(int height){
    if (height <= 0) {
        node(); // This function will produce a random number.
        return;
    }
    
    pid_t pid = fork(); // First child
    
    if (pid > 0){ // Parent
        pid_t pid2 = fork(); // Second child
        if (pid2 > 0){ // Parent
            wait(NULL); // Waiting for child to complete.
            printf("Process: %d, right child: %d, left child: %d, height: %d \n",
                    getpid(), pid, pid2, height);
            parent(pid, pid2);
        }
        if (pid2 == 0){ // Right child
            create_tree(--height);
        }
    }
    if (pid == 0){ // Left child
        create_tree(--height);
    }
}

void node(){
    char filename[20];
    sprintf(filename, "%d.txt", getpid());
    srand(getpid());
    int r = rand()%100;
    printf("%d Process produced number '%d'\n", getpid(), r);
    fflush(stdout);
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d", r);
    fclose(fp);
}

void parent(pid_t right, pid_t left){
    wait(NULL); // Parent is waiting for the 'write operation' to finish.
    int right_value = read_file(right);
    int left_value = read_file(left);
    printf(" |Right: %d, Left: %d| \n", right_value, left_value);
    char filename[20];
    sprintf(filename, "%d.txt", getpid());
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d", right_value + left_value);
    fclose(fp);
}

int read_file(pid_t pid){
    char filename[20];
    int r;
    sprintf(filename, "%d.txt", pid);
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &r);
    fclose(fp);
    return r;
}