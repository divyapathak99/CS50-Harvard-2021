#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool cycle(int winner, int loser);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }
    //clear preferences array.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = false;
        }
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }


    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}



// Update ranks given a new vote.
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

//calculate length of ranks[].
// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int a = 0;
    int b = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            a = ranks[i];
            b = ranks[j];
            preferences[a][b] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other.
void add_pairs(void)
{
    // TODO:
    int k = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[k].winner = j;
                pairs[k].loser = i;
                pair_count += 1;
                k += 1;
            }
            else if (preferences[i][j] > preferences[j][i])
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                pair_count += 1;
                k += 1;
            }
        }

    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODOcd
    int temp = 0, temp1 = 0, a = 0, b = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            temp = abs(preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
            temp1 = abs(preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]);
            if (temp < temp1)
            {
                a = pairs[i].winner;
                b = pairs[i].loser;
                pairs[i] = pairs[j];
                pairs[j].winner = a;
                pairs[j].loser = b;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int a = pairs[i].winner;
        int b = pairs[i].loser;
        locked[a][b] = true;
        if (cycle(a, b))
        {
            locked[a][b] = false;  
        }
    }
}


// Print the winner of the election
void print_winner(void)
{
    // TODO
    int count = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                count += 1;
                
            }
        }
        if (count == candidate_count)
        {
            printf("%s\n", candidates[j]);
        }
        count = 0;
    }
    return;
}
 
//To check if any pair creates a cycle.
bool cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner])
        {
            return cycle(i, loser);
        }
    }
    return false;
}