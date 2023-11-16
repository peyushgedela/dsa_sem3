#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool ishorizontal(char grid[100][100], char word[100], int x, int y, int n)
{
    for (int k = 0; k < strlen(word); k++)
    {
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != word[k])
        {
            return false;
        }
        y++;
    }
    return true;
}

bool isvertical(char grid[100][100], char word[100], int x, int y, int n)
{
    for (int k = 0; k < strlen(word); k++)
    {
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != word[k])
        {
            return false;
        }
        x++;
    }
    return true;
}

bool revhorizontal(char grid[100][100], char word[100], int x, int y, int n)
{
    for (int k = 0; k < strlen(word); k++)
    {
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != word[k])
        {
            return false;
        }
        y--;
    }
    return true;
}

bool revvertical(char grid[100][100], char word[100], int x, int y, int n)
{
    for (int k = 0; k < strlen(word); k++)
    {
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != word[k])
        {
            return false;
        }
        x--;
    }
    return true;
}

void wordsearch(char grid[100][100], char words[100][100], int n, int m)
{
    for (int win = 0; win < m; win++)
    {
        char *word = words[win];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // Check horizontally
                if (ishorizontal(grid, word, i, j, n))
                {
                    printf("Word '%s' found starting at (%d, %d) horizontally.\n", word, i, j);
                }

                // Check vertically
                if (isvertical(grid, word, i, j, n))
                {
                    printf("Word '%s' found starting at (%d, %d) vertically.\n", word, i, j);
                }
            }
        }
        // check horizontally in reverse order
        for (int i = 0; i < n; i++)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                if (revhorizontal(grid, word, i, j, n))
                {
                    printf("Word '%s' found starting at (%d, %d) reverse horizontally.\n", word, i, j);
                }
            }
        }
        // check vertically in reverse order
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < n; j++)
            {
                if (revvertical(grid, word, i, j, n))
                {
                    printf("Word '%s' found starting at (%d, %d) reverse vertically.\n", word, i, j);
                }
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of grids: ");
    scanf("%d", &n);
    char grid[100][100]; // grid
    printf("Enter the characters of the grid each row at a time\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%s", grid[i]); // grid input
    }
    printf("Enter no of words\n");
    int m;
    scanf("%d", &m);
    char words[100][100]; // word-bank
    printf("Enter the words each per line\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%s", words[i]); // word-bank input
    }

    // searching for the words
    wordsearch(grid, words, n, m);

    return 0;
}