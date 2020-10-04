#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

void merge_sort(pair array[], int left_start, int right_end);
void merge(pair array[], int left_start, int m, int right_end);
bool find_cycle(int i, int j, int candidate_count);

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

        // printf("ranks[0]: %i\n", ranks[0]);
        // printf("ranks[1]: %i\n", ranks[1]);
        // printf("ranks[2]: %i\n", ranks[2]);

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop through i for winner
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop through  for loser
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;

                    pair_count++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;

                    pair_count++;
                }
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Merge Sort
    int left_start = 0;
    int right_end = pair_count - 1;
    int m;

    merge_sort(pairs, left_start, right_end);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int n = 0; n < pair_count; n++)
    {
        int i = pairs[n].winner;
        int j = pairs[n].loser;

        if (n < 2)
        {
            locked[i][j] = true;
        }
        else if (!find_cycle(i, j, candidate_count))
        {
            locked[i][j] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;
    for (int j = 0; j < candidate_count; j++)
    {
        int count = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                count++;
            }
        }
        if (count == candidate_count)
        {
            winner = j;
        }
    }

    for (int n = 0; ; n++)
    {
        if (candidates[winner][n] == '\0')
        {
            printf("\n");
            return;
        }
        else
        {
            printf("%c", candidates[winner][n]);
        }
    }

    return;
}

// Merge Sort (https://www.geeksforgeeks.org/merge-sort/)
void merge_sort(pair array[], int left_start, int right_end)
{
    if (left_start < right_end)
    {
// Find middle
        int m = left_start + (right_end - left_start) / 2;

// Sort first and second halves
        merge_sort(array, left_start, m);
        merge_sort(array, m + 1, right_end);

        merge(array, left_start, m, right_end);
    }
}

// Merge two sorted arrays
void merge(pair array[], int left_start, int m, int right_end)
{
    int i, j, k;
    int size_left = m - left_start + 1;
    int size_right = right_end - m;

// Create temporary arrays
    pair L[size_left], R[size_right];

// Copy data to temp arrays L[] and R[]
    for (i = 0; i < size_left; i++)
    {
        L[i] = array[left_start + i];
    }

    for (j = 0; j < size_right; j++)
    {
        R[j] = array[m + 1 + j];
    }

// Initial index of first subarray
    i = 0;

// Initial index of second subarray
    j = 0;

// Initial index of merged subarray
    k = left_start;

// Merge the temp arrays back into array[left_start..right_end]
    while (i < size_left && j < size_right)
    {
        if (preferences[L[i].winner][L[i].loser] >= preferences[R[j].winner][R[j].loser])
        {
            array[k] = L[i];
            i++;
        }

        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }

// Copy the remaining elements of L[]
    while (i < size_left)
    {
        array[k] = L[i];
        i++;
        k++;
    }

// Copy the remaining elements of R[]
    while (j < size_right)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

//
bool find_cycle(int i, int j, int total_candidates)
{
    for (int n = 0; n < total_candidates; n++)
    {
        if (locked[j][n] == true)
        {
            if (n == i)
            {
                return true;
            }
            else
            {
                if (find_cycle(i, n, total_candidates))
                {
                    return true;
                }
            }
        }
    }

    return false;
}