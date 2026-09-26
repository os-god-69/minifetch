#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main() {
    // 1. Hostname & User
    char hostname[BUFFER_SIZE] = "unknown";
    char *username = getenv("USER");
    gethostname(hostname, sizeof(hostname));
    if (!username) username = "user";

    // 2. System Statistics
    struct sysinfo info;
    sysinfo(&info);
    long uptime_hours = info.uptime / 3600;
    long uptime_mins = (info.uptime % 3600) / 60;
    long total_ram = (info.totalram * info.mem_unit) / (1024 * 1024);
    long free_ram = (info.freeram * info.mem_unit) / (1024 * 1024);
    long used_ram = total_ram - free_ram;

    // 3. Kernel Info
    struct utsname os_info;
    uname(&os_info);

    // 4. OS Name & ID Detection
    char os_name[BUFFER_SIZE] = "Linux";
    char os_id[BUFFER_SIZE] = "linux"; // Used to match the logo easily
    FILE *f = fopen("/etc/os-release", "r");
    if (f) {
        char line[BUFFER_SIZE];
        while (fgets(line, sizeof(line), f)) {
            // Get user-friendly name
            if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
                char *start = line + 12;
                if (*start == '"') start++;
                size_t len = strlen(start);
                while (len > 0 && (start[len - 1] == '\n' || start[len - 1] == '"' || start[len - 1] == '\r')) {
                    start[len - 1] = '\0';
                    len--;
                }
                strncpy(os_name, start, sizeof(os_name));
            }
            // Get underlying ID (e.g., arch, ubuntu, fedora)
            if (strncmp(line, "ID=", 3) == 0) {
                char *start = line + 3;
                if (*start == '"') start++;
                size_t len = strlen(start);
                while (len > 0 && (start[len - 1] == '\n' || start[len - 1] == '"' || start[len - 1] == '\r')) {
                    start[len - 1] = '\0';
                    len--;
                }
                strncpy(os_id, start, sizeof(os_id));
            }
        }
        fclose(f);
    }

    // 5. Render Layout Based on OS ID
    // We check if the ID string contains common distro names
    if (strstr(os_id, "arch") != NULL) {
        // ARCH LINUX ART (Cyan)
        printf("\033[1;36m       /\\        \033[0m   \033[1;32m%s\033[0m@\033[1;32m%s\033[0m\n", username, hostname);
        printf("\033[1;36m      /  \\       \033[0m   ---------------------\n");
        printf("\033[1;36m     /\\   \\      \033[0m   \033[1;36mOS:\033[0m     %s\n", os_name);
        printf("\033[1;36m    /  __  \\     \033[0m   \033[1;36mKernel:\033[0m %s\n", os_info.release);
        printf("\033[1;36m   /  (  )  \\    \033[0m   \033[1;36mUptime:\033[0m %ldh %ldm\n", uptime_hours, uptime_mins);
        printf("\033[1;36m  /  ______  \\   \033[0m   \033[1;36mMemory:\033[0m %ld MiB / %ld MiB\n", used_ram, total_ram);
        printf("\033[1;36m /_             \\\033[0m\n");
    } 
    else if (strstr(os_id, "ubuntu") != NULL) {
        // UBUNTU ART (Orange)
        printf("\033[1;31m   ---       ---  \033[0m   \033[1;32m%s\033[0m@\033[1;32m%s\033[0m\n", username, hostname);
        printf("\033[1;31m /     \\   /     \\\033[0m   ---------------------\n");
        printf("\033[1;31m|       | |       |\033[0m   \033[1;31mOS:\033[0m     %s\n", os_name);
        printf("\033[1;31m|       | |       |\033[0m   \033[1;31mKernel:\033[0m %s\n", os_info.release);
        printf("\033[1;31m \\     /   \\     /\033[0m   \033[1;31mUptime:\033[0m %ldh %ldm\n", uptime_hours, uptime_mins);
        printf("\033[1;31m   ---       ---  \033[0m   \033[1;31mMemory:\033[0m %ld MiB / %ld MiB\n", used_ram, total_ram);
    } 
    else if (strstr(os_id, "fedora") != NULL) {
        // FEDORA ART (Blue)
        printf("\033[1;34m      _____      \033[0m   \033[1;32m%s\033[0m@\033[1;32m%s\033[0m\n", username, hostname);
        printf("\033[1;34m     /  __  \\    \033[0m   ---------------------\n");
        printf("\033[1;34m    /  /  /  /   \033[0m   \033[1;34mOS:\033[0m     %s\n", os_name);
        printf("\033[1;34m   /  /_ /  /    \033[0m   \033[1;34mKernel:\033[0m %s\n", os_info.release);
        printf("\033[1;34m  /  ____  /     \033[0m   \033[1;34mUptime:\033[0m %ldh %ldm\n", uptime_hours, uptime_mins);
        printf("\033[1;34m /  /    /_/     \033[0m   \033[1;34mMemory:\033[0m %ld MiB / %ld MiB\n", used_ram, total_ram);
        printf("\033[1;34m/__/             \033[0m\n");
    } 
    else {
        // GENERIC LINUX ART / PENGUIN ACCENT (Yellow)
        printf("\033[1;33m     _____       \033[0m   \033[1;32m%s\033[0m@\033[1;32m%s\033[0m\n", username, hostname);
        printf("\033[1;33m    /     \\      \033[0m   ---------------------\n");
        printf("\033[1;33m   ((  o o ))    \033[0m   \033[1;33mOS:\033[0m     %s\n", os_name);
        printf("\033[1;33m    \\  \\=/  /    \033[0m   \033[1;33mKernel:\033[0m %s\n", os_info.release);
        printf("\033[1;33m   / \\  .  / \\   \033[0m   \033[1;33mUptime:\033[0m %ldh %ldm\n", uptime_hours, uptime_mins);
        printf("\033[1;33m  (   \\___/   )  \033[0m   \033[1;33mMemory:\033[0m %ld MiB / %ld MiB\n", used_ram, total_ram);
        printf("\033[1;33m   \\_________/   \033[0m\n");
    }
    
    // Color Blocks at the bottom
    printf("                    "); 
    for (int i = 0; i < 8; i++) {
        printf("\033[4%dm   ", i);
    }
    printf("\033[0m\n\n"); 

    return 0;
}
