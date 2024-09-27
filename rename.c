#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#define PREFIX "[SPOTIFY-DOWNLOADER.COM]"  // Define the prefix we want to remove

void rename_files(const char *directory) {
    struct dirent *entry;
    DIR *dir = opendir(directory);

    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Check if it is a regular file
            char *filename = entry->d_name;

            // Check if filename starts with the "spotify - " prefix
            if (strncmp(filename, PREFIX, strlen(PREFIX)) == 0) {
                // Create the new name by removing the prefix
                const char *new_name = filename + strlen(PREFIX);

                // Allocate memory for the full path to rename the file
                char old_path[1024], new_path[1024];
                snprintf(old_path, sizeof(old_path), "%s/%s", directory, filename);
                snprintf(new_path, sizeof(new_path), "%s/%s", directory, new_name);

                // Rename the file
                if (rename(old_path, new_path) == 0) {
                    printf("Renamed: %s -> %s\n", filename, new_name);
                } else {
                    perror("Error renaming file");
                }
            }
        }
    }

    closedir(dir);
}

int main() {
    const char *directory = "Music Renamed";  // Use current directory or specify the directory path
    rename_files(directory);

    return 0;
}

