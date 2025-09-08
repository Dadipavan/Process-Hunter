  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

void fetch_process_name(pid_t pid) {
    char path[BUFFER_SIZE], buffer[BUFFER_SIZE];
    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    FILE *file = fopen(path, "r");
    if (file) {
        if (fgets(buffer, sizeof(buffer), file)) {
            printf("Process Name      : %s", buffer);
        }
        fclose(file);
    } else {
        perror("Error reading process name");
    }
}

void fetch_cmdline(pid_t pid) {
    char path[BUFFER_SIZE], buffer[BUFFER_SIZE];
    snprintf(path, sizeof(path), "/proc/%d/cmdline", pid);
    FILE *file = fopen(path, "r");
    if (file) {
        printf("Command-line     : ");
        while (fgets(buffer, sizeof(buffer), file)) {
            for (int i = 0; buffer[i]; i++)
                if (buffer[i] == '\0') buffer[i] = ' ';
            printf("%s", buffer);
        }
        printf("\n");
        fclose(file);
    } else {
        perror("Error reading command-line");
    }
}

void fetch_status(pid_t pid) {
    char path[BUFFER_SIZE], buffer[BUFFER_SIZE];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    FILE *file = fopen(path, "r");
    if (file) {
        printf("=== Status Info ===\n");
        while (fgets(buffer, sizeof(buffer), file)) {
            if (strncmp(buffer, "State:", 6) == 0 ||
                strncmp(buffer, "PPid:", 5) == 0 ||
                strncmp(buffer, "Threads:", 8) == 0 ||
                strncmp(buffer, "VmSize:", 7) == 0 ||
                strncmp(buffer, "Uid:", 4) == 0 ||
                strncmp(buffer, "Gid:", 4) == 0) {
                printf("%s", buffer);
            }
        }
        fclose(file);
    } else {
        perror("Error reading process status");
    }
}

void fetch_executable_path(pid_t pid) {
    char path[BUFFER_SIZE], buffer[BUFFER_SIZE];
    snprintf(path, sizeof(path), "/proc/%d/exe", pid);
    ssize_t len = readlink(path, buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        printf("Executable Path  : %s\n", buffer);
    } else {
        perror("Error reading executable path");
    }
}

int check_pid_exists(pid_t pid) {
    char proc_path[BUFFER_SIZE];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d", pid);
    struct stat sb;
    return (stat(proc_path, &sb) == 0 && S_ISDIR(sb.st_mode));
}

int main() {
    pid_t pid;

    printf("Enter Process ID (PID): ");
    if (scanf("%d", &pid) != 1 || pid <= 0) {
        fprintf(stderr, "Invalid input. Please enter a valid positive PID.\n");
        return EXIT_FAILURE;
    }

    if (!check_pid_exists(pid)) {
        fprintf(stderr, "Error: PID %d does not exist.\n", pid);
        return EXIT_FAILURE;
    }

    printf("\nFetching information for PID: %d\n", pid);
    printf("---------------------------------------\n");

    fetch_process_name(pid);
    fetch_cmdline(pid);
    fetch_status(pid);
    fetch_executable_path(pid);

    printf("---------------------------------------\n");
    printf("Process information retrieved successfully.\n");

    return EXIT_SUCCESS;
}
