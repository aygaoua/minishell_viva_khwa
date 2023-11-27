/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_gpt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 01:48:49 by azgaoua           #+#    #+#             */
/*   Updated: 2023/11/27 02:11:11 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to expand environment variables in a string
char* expand_variables(char* input_string) {
    size_t output_size = 1;  // Start with a single character for the null terminator
    char* output_string = calloc(output_size, 1);
    if (output_string == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    const char* start = input_string;
    char* output_ptr = output_string;

    while (*start != '\0') {
        // Look for the beginning of a variable placeholder
        if (*start == '$') {
            const char* end = start + 1;  // Point to the character after the '$'

            // Extract the variable name
            while (*end != '\0' && (*end == '_' || (*end >= 'a' && *end <= 'z') || (*end >= 'A' && *end <= 'Z') || (*end >= '0' && *end <= '9'))) {
                ++end;
            }

            // If a valid variable name is found
            if (start + 1 != end) {
                // Extract the variable name
                size_t var_len = end - (start + 1);
                char var_name[var_len + 1];
                strncpy(var_name, start + 1, var_len);
                var_name[var_len] = '\0';

                // Get the environment variable value
                const char* var_value = getenv(var_name);
                if (var_value != NULL) {
                    // Resize the output buffer to accommodate the variable value
                    size_t var_value_len = strlen(var_value);
                    output_size += var_value_len;
                    output_string = realloc(output_string, output_size);
                    if (output_string == NULL) {
                        perror("Memory reallocation failed");
                        exit(EXIT_FAILURE);
                    }

                    // Copy the variable value to the output buffer
                    strcat(output_string, var_value);
                    output_ptr = output_string + strlen(output_string);
                    start = end;  // Move to the character after the variable name
                    continue;
                }
            }
        }

        // Copy non-special characters as is
        *output_ptr++ = *start++;
        *output_ptr = '\0';  // Null-terminate the output string after each character copy
    }

    return output_string;
}

// int main() {
//     const char* input_string = "This is a $HOME directory with $USER and $NON_EXISTING_VAR";
//     char* result = expand_variables(input_string);
//     printf("%s\n", result);

//     free(result);  // Don't forget to free the allocated memory

//     return 0;
// }


