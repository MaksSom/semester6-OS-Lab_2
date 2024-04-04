#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NumOfPhilosophers 5

int randomEatingTime()
{
    int size = 10;
    int possibleEatingTime[size];

    // possibleEatingTime = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    for(int i = 1; i <= size; i++)
        possibleEatingTime[i-1] = i;

    return possibleEatingTime[rand() % size]; 
}

int loopCounter(int a)
{
    if(a < 0)
        return NumOfPhilosophers + a;
    if(a >= NumOfPhilosophers)
        return NumOfPhilosophers - a;
    return a;
}

void thinking(int *state, int *forks, int *result)
{
    switch (state[0])
    {
    case 0:
        if(forks[loopCounter(-1)] == 0)
        {
            state[0] = 1;
            forks[loopCounter(-1)] = 1;
            printf("Pfilosoph num 1 took right fork\n");
        }
        else
            printf("Pfilosoph num 1 waiting for the right fork\n");
        break;
    
    case 1:
        if(forks[loopCounter(0)] == 0)
            {
                state[0] = 2*10 + randomEatingTime();
                forks[loopCounter(0)] = 1;

                printf("Pfilosoph num 1 took right fork and started eating for %d turns\n", state[0] - 20);
            }
            else
            {
                state[0] = 0;
                forks[loopCounter(-1)] = 0;

                printf("Pfilosoph num 1 put down right fork\n");
            }
            break;

    case 20:
        forks[loopCounter(0)] = 0;
        forks[loopCounter(-1)] = 0;
        state[0] = 0;

        printf("Pfilosoph num 1 finished eating and put down both forks\n");
        result[0]++;
        break;
    default:
        if(state[0] > 20)
            {
                state[0]--;
            }
        printf("Pfilosoph num 1 eating (%d left)\n", state[0] - 20);
        break;
    }

    for(int counter = 1; counter < NumOfPhilosophers; counter++)
    {
        switch (state[counter])
        {
        case 0:
            if(forks[loopCounter(counter)] == 0)
            {
                state[counter] = 1;
                forks[loopCounter(counter)] = 1;

                printf("Pfilosoph num %d took left fork\n", counter+1);
            }
            else
                printf("Pfilosoph num %d waiting for the left fork\n", counter+1);
            break;
        case 1:
            if(forks[loopCounter(counter - 1)] == 0)
            {
                state[counter] = 2*10 + randomEatingTime();
                forks[loopCounter(counter) - 1] = 1;

                printf("Pfilosoph num %d took right fork and started eating for %d turns\n", counter+1, state[counter] - 20);
            }
            else
            {
                state[counter] = 0;
                forks[loopCounter(counter)] = 0;

                printf("Pfilosoph num %d put down left fork\n", counter+1);
            }
            break;
        case 20:
            forks[loopCounter(counter - 1)] = 0;
            forks[loopCounter(counter)] = 0;
            state[counter] = 0;

            printf("Pfilosoph num %d finished eating and put down both forks\n", counter+1);
            result[counter]++;
            break;
        default:
            if(state[counter] > 20)
            {
                state[counter]--;
            }
            printf("Pfilosoph num %d eating (%d left)\n", counter+1, state[counter] - 20);
            break;
        }
    }
}

int main(){

    int N = NumOfPhilosophers;
    int state[N];
    int forks[N];
    int result[N];

    for (int i = 0; i < N; i++) {
        state[i] = 0;
        forks[i] = 0;
        result[i] = 0;
    }
    /*
    states:
    0 - waiting (no forks)
    1 - has right fork
    2 + [1...] - has 2 forks (eating)

    forks:
    0 - unused
    1 - being used
    */

    srand(time(NULL));
    
    thinking(&state, &forks, &result);
    for(int i = 0; i < 1000; i++)
    {
        printf("\n---------------Round %d---------------\n\n", i);
        thinking(&state, &forks, &result);
    }

    printf("\n");
    for(int i = 0; i < N; i++)
    {
        printf("%d ", result[i]);
        printf(" ");
    }
    
    return 0;
    
}
