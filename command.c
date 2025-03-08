#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>



void listDir() {
    DIR *dir;
    struct dirent *ent;

    dir = opendir(".");

    if (dir == NULL) {
        perror("Unable to open directory\n");
        return;
    }

    while ((ent = readdir(dir)) != NULL) {
            write(fileno(stdout), ent->d_name, strlen(ent->d_name));
            write(fileno(stdout), " ", 1);
    }

    write(fileno(stdout), "\n", 1);  // Ensure newline at the end
    closedir(dir);
}

void showCurrentDir() {
   // write(fileno(stdout), "showCurrentDir works\n", 21);

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    write(fileno(stdout), cwd, strlen(cwd));
    write(fileno(stdout), "\n", 1);
} /*for the pwd command*/

void makeDir(char *dirName) {
    //write(fileno(stdout), "makeDir works\n", 14);

    if (mkdir(dirName, 0777) == -1){
	 write(fileno(stdout), "Directory already exists!\n", strlen("Directory already exists!\n"));
    }
    else{
        return;   
    }

} /*for the mkdir command*/

void changeDir(char *dirName) {
    //write(fileno(stdout), "changeDir works\n", 16);

    if (chdir(dirName) == -1){
	    perror("chdir failed");
    }

} /*for the cd command*/


void copyFile(char *sourcePath, char *destinationPath) {
    struct stat statbuf;

    // Open the source file for reading
    int sourceFd = open(sourcePath, O_RDONLY);
    if (sourceFd == -1) {
        write(fileno(stdout), "Source file does not exist\n", strlen("Source file does not exist\n"));
        return;
    }

    // Check if the destination path is a directory
    if (stat(destinationPath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
        // If the destination is a directory, append the filename to the destination path
        char *filename = strrchr(sourcePath, '/');
        if (filename == NULL) {
            filename = sourcePath;  // No '/' in sourcePath, it's a local file
        } else {
            filename++;  // Skip the '/'
        }

        char fullDestPath[1024];
        //snprintf(fullDestPath, sizeof(fullDestPath), "%s/%s", destinationPath, filename);

	
        strcpy(fullDestPath, destinationPath);   // Copy the destination path to fullDestPath
        strcat(fullDestPath, "/");               // Append the "/" character
        strcat(fullDestPath, filename);          // Append the filename to complete the full path

        // Open the destination file for writing
        int destFd = open(fullDestPath, O_WRONLY | O_CREAT, 0644);
        if (destFd == -1) {
            write(fileno(stdout), "Failed to create destination file\n", strlen("Failed to create destination file\n"));
            close(sourceFd);
            return;
        }

        // Copy the file content
        char buffer[1024];
        int bytesRead;
        while ((bytesRead = read(sourceFd, buffer, sizeof(buffer))) > 0) {
            write(destFd, buffer, bytesRead); // Write to destination file
        }

        // Close file descriptors
        close(sourceFd);
        close(destFd);

    } else {
        // If the destination is not a directory, copy the file directly to the destination
        int destFd = open(destinationPath, O_WRONLY | O_CREAT, 0644);
        if (destFd == -1) {
            write(fileno(stdout), "Failed to create destination file\n", strlen("Failed to create destination file\n"));
            close(sourceFd);
            return;
        }

        // Copy the file content
        char buffer[1024];
        int bytesRead;
        while ((bytesRead = read(sourceFd, buffer, sizeof(buffer))) > 0) {
            write(destFd, buffer, bytesRead); // Write to destination file
        }

        // Close file descriptors
        close(sourceFd);
        close(destFd);
    }
}


void moveFile(char *sourcePath, char *destinationPath) {
    struct stat statbuf;
    
    // Open the source file for reading
    int sourceFd = open(sourcePath, O_RDONLY);
    if (sourceFd == -1) {
        write(fileno(stdout), "Source file does not exist\n", strlen("Source file does not exist\n"));
        return;
    }

    // Check if the destination path is a directory
    if (stat(destinationPath, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
        // If the destination is a directory, append the filename to the destination path
        char *filename = strrchr(sourcePath, '/');
        if (filename == NULL) {
            filename = sourcePath;  
        } else {
            filename++;  // Skip the '/'
        }
        
        char fullDestPath[1024];

        //snprintf(fullDestPath, sizeof(fullDestPath), "%s/%s", destinationPath, filename);

        strcpy(fullDestPath, destinationPath);   // Copy the destination path to fullDestPath
        strcat(fullDestPath, "/");               // Append the "/" character
        strcat(fullDestPath, filename);          // Append the filename to complete the full path

        
        // Open the destination file for writing
        int destFd = open(fullDestPath, O_WRONLY | O_CREAT, 0644);
        if (destFd == -1) {
            write(fileno(stdout), "Failed to create destination file\n", strlen("Failed to create destination file\n"));
            close(sourceFd);
            return;
        }

        // Move the file content
        char buffer[1024];
        int bytesRead;
        while ((bytesRead = read(sourceFd, buffer, sizeof(buffer))) > 0) {
            write(destFd, buffer, bytesRead); // Write to destination file
        }

        // Close file descriptors and remove the source file
        close(sourceFd);
        close(destFd);
        unlink(sourcePath);  // Remove the source file
    } else {
        // If the destination is not a directory, just move the file directly
        int destFd = open(destinationPath, O_WRONLY | O_CREAT, 0644);
        if (destFd == -1) {
            write(fileno(stdout), "Failed to create destination file\n", strlen("Failed to create destination file\n"));
            close(sourceFd);
            return;
        }

        // Move the file content
        char buffer[1024];
        int bytesRead;
        while ((bytesRead = read(sourceFd, buffer, sizeof(buffer))) > 0) {
            write(destFd, buffer, bytesRead); // Write to destination file
        }

        // Close file descriptors and remove the source file
        close(sourceFd);
        close(destFd);
        unlink(sourcePath);  // Remove the source file
    }
}




void deleteFile(char *filename) {
    //write(fileno(stdout), "deleteFile works\n",17);

    int fileExist = open(filename, O_RDONLY);

    if (fileExist == -1){
        write(fileno(stdout), "File does not exist\n", strlen("File does not exist\n"));
        return;
    }

    remove(filename);

} /*for the rm command*/

void displayFile(char *filename) {
    //write(fileno(stdout), "displayFile works\n", 18);

    int sourceFd = open(filename, O_RDONLY); // open source file for reading

    if (sourceFd == -1) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }



    char buffer[1024];

    int byteCount = read(sourceFd, buffer, 1024);

    while (byteCount > 0) {
        write(fileno(stdout), buffer, byteCount); // write to destination file
        byteCount = read(sourceFd, buffer, 1024); 
    }


} /*for the cat command*/


