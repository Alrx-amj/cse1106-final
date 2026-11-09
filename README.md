# cse1106-final
cse1106-final

## Description
this project show cases push and pull, git status, git add and etc 

## Technologies
we use terminal for this

## How to run 
to run pull from terminal 

## What I learned 
I learned how to connect and set up an editor on terminal thats connected to git hub

## Future Improvements
I wish to improve in memorizing keys and shortcuts on terminal





    float memory, storage;

if (argc > 1 && argv[1][0] == 't') {
    printf("Enter fake memory usage: ");
    if (scanf("%f", &memory) != 1) break;

    printf("Enter fake storage usage: ");
    if (scanf("%f", &storage) != 1) break;

    if (memory < 0 || memory > 100 ||
        storage < 0 || storage > 100) {
        printf("Values must be between 0 and 100\n");
        continue;
    }
} else {
    memory = getMemory();
    storage = getStorage();
}
