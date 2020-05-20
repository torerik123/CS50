#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
        {
            if (strcmp(name, candidates[i].name) == 0)          //  Compare user vote with names of candidates
            {
                for (int j = 0; i < candidate_count; i++)       //  Update preferences array to indicate that voter[i] that candidate[i] as their rank[j]
                {
                    preferences[voter][rank] = i;               //  Updates array with voter and rank for candidate i
                    break;
                }
                    
                 return true;
            }
        }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // The function should update the number of votes each candidate has at this stage in the runoff.
    for (int i = 0; i < voter_count;i++)
    {
            for (int j = 0; j < voter_count;j++)
            {
                
                if (candidates[preferences[i][j]].eliminated == false)  //  If candidate is not eliminated:
                {   
                    candidates[preferences[i][j]].votes += 1;           //  Update number of votes by 1
                    break;
                }
            }
            
    return;
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //  If any candidate has more than half of the vote, their name should be printed to stdout and the function should return true.
    for (int i = 0; i < candidate_count;i++)
    {   
        string most = candidates[i].name;
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", most);
            return true;
        }
    }
//  If nobody has won the election yet, the function should return false.
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;                          // Sets min to the total number of voters
    for (int i = 0; i < candidate_count; i++)
       {
            if (candidates[i].eliminated == false   // Executes if candidate is not eliminated and has less votes than min
            && candidates[i].votes < min)
            {
                min = candidates[i].votes;          //  Updates min to the number of votes candidate[i] has
                
            }   
       }
       return min;
    
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)    //  Returns false if candidate is not eliminated or has more votes than min
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count;i++)
    {
        if (candidates[i].votes == min)         // If the candidate has minimum number of votes, the candidate is eliminated
        {
            candidates[i].eliminated = true;   
        }    
    }
    return;
}
