#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_PATH 256

// Function prototypes
int simulate_ls(char *path);
int simulate_cp(char *source, char *destination);
int simulate_wc(char *filename);

// Function to check file type
char get_file_type(struct stat *statbuf)
{
    if (S_ISREG(statbuf->st_mode))
    {
        return '-';
    }
    else if (S_ISDIR(statbuf->st_mode))
    {
        return 'd';
    }
    else
    {
        return '?';
    }
}

// Function to simulate ls -l
int simulate_ls(char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    if ((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return 1;
    }

    printf("total 0\n"); // Simulate total block count (always 0 here)

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        snprintf(path + strlen(path), MAX_PATH - strlen(path), "/%s", entry->d_name);
        if (stat(path, &statbuf) == -1)
        {
            perror("stat");
            return 1;
        }
        printf("%c  %d %s %s %ld %s %s\n", get_file_type(&statbuf),
               statbuf.st_nlink, "user", "group", statbuf.st_size,
               ctime(&statbuf.st_ctime), entry->d_name);
        path[strlen(path) - strlen(entry->d_name) - 1] = '\0'; // Remove added path
    }

    closedir(dir);
    return 0;
}

// Function to simulate cp
int simulate_cp(char *source, char *destination)
{
    FILE *source_fp, *dest_fp;
    char ch;

    if ((source_fp = fopen(source, "rb")) == NULL)
    {
        perror("fopen (source)");
        return 1;
    }

    if ((dest_fp = fopen(destination, "wb")) == NULL)
    {
        perror("fopen (destination)");
        fclose(source_fp);
        return 1;
    }

    while ((ch = fgetc(source_fp)) != EOF)
    {
        if (fputc(ch, dest_fp) == EOF)
        {
            perror("fputc");
            fclose(source_fp);
            fclose(dest_fp);
            return 1;
        }
    }

    fclose(source_fp);
    fclose(dest_fp);
    return 0;
}

// Function to simulate wc (line count only)
int simulate_wc(char *filename)
{
    FILE *fp;
    int line_count = 0;
    char ch;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        perror("fopen");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_count++;
        }
    }

    fclose(fp);
    printf("%d\n", line_count);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <command> <arguments>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "ls") == 0)
    {
        if (argc != 3)
        {
            printf("ls: requires one argument (directory path)\n");
            return 1;
        }
        return simulate_ls(argv[2]);
    }
    else if (strcmp(argv[1], "cp") == 0)
    {
        if (argc != 3)
        {
            printf("cp: requires two arguments (source file, destination file)\n");
            return 1;
        }
        return simulate_cp(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "wc") == 0)
    {
        if (argc != 3)
        {
            printf("wc: requires one argument (filename)\n");
            return 1;
        }
        return simulate_wc(argv[2]);
    }
    else
    {
        printf("Invalid command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
