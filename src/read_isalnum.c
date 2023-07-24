/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_isalnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:09:58 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/19 11:12:32 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // Required for read function
#include <ctype.h>  // Required for isalnum function

ssize_t read_isalnum(int fildes, void *buf, size_t nbyte)
{
    // Cast the buffer to a char pointer
    char *buffer = (char *)buf;

    // Initialize a counter for valid characters
    ssize_t count = 0;

    // Read nbyte bytes from the file descriptor fildes
    ssize_t bytes_read = read(fildes, buffer, nbyte);

    // Check if read was successful
    if (bytes_read == -1)
    {
        // Return -1 to indicate an error
        return -1;
    }

    // Iterate through the buffer and filter out non-alphanumeric characters
    for (ssize_t i = 0; i < bytes_read; i++)
    {
        if (isalnum(buffer[i]))
        {
            // If the character is alphanumeric, store it in the buffer
            buffer[count] = buffer[i];
            count++;
        }
    }

    // Null-terminate the buffer to make it a valid string
    buffer[count] = '\0';

    // Return the number of valid characters stored in the buffer
    return count;
}

#include <stdio.h>
#include <fcntl.h> // Required for open function

int main()
{
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Error: Failed to open the file\n");
        return 1;
    }

    char buffer[256];
    ssize_t bytes_read = read_isalnum(fd, buffer, sizeof(buffer));
    close(fd);

    if (bytes_read == -1)
    {
        fprintf(stderr, "Error: Failed to read from the file\n");
        return 1;
    }

    printf("Read %zd valid characters: %s\n", bytes_read, buffer);

    return 0;
}
