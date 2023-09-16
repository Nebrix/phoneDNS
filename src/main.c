#include "areacodes.h"
#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define BUFFER_LEN 16

#define TITLE_SPLASH_STR                                         \
    "  ____  _                      ____  _   _ ____         \n" \
    " |  _ \\| |__   ___  _ __   ___|  _ \\| \\ | / ___|     \n" \
    " | |_) | '_ \\ / _ \\| '_ \\ / _ \\ | | |  \\| \\___ \\ \n" \
    " |  __/| | | | (_) | | | |  __/ |_| | |\\  |___) |      \n" \
    " |_|   |_| |_|\\___/|_| |_|\\___|____/|_| \\_|____/     \n"

#define INFO_SPASH_STR                                                   \
    "[ \u00A7 ] PhoneDNS SecLabX | Licensed under MIT License        \n" \
    "[ \u00A7 ] Original creator: https://github.com/SecLabX         \n" \
    "[ \u00A7 ] Creator of this version: https://github.com/SecLabX    "

#define PN_STR_LEN 12 // xxx-xxx-xxxx

typedef enum {

    dns_false = 0,
    dns_true  = 1

} dns_bool;

int str_len(const char* buffer, int buffer_len)
{
    const char*       ch  = buffer;
    const char* const end = buffer + buffer_len;
    while (buffer && *ch && ch < end) {
        ++ch;
    }
    return ch - buffer - 1;
}

dns_bool is_digit(char ch)
{
    dns_bool is_a_digit = ch >= '0' && ch <= '9';

    return is_a_digit;
}

// Assumes correct length of string for phone number
dns_bool is_digits_and_dashes(const char* pn_str)
{
    dns_bool is_digits = dns_true;

    const char*       i           = pn_str;
    const char* const end         = pn_str + PN_STR_LEN - 1;
    const char* const first_dash  = pn_str + 3;
    const char* const second_dash = pn_str + 7;

    while (i && *i && is_digits && i < end) {

        if (i == first_dash || i == second_dash) {
            ++i;
        }

        ++i;
    }

    return is_digits;
}

dns_bool is_phone_number(const char* buffer, int buffer_len)
{
    dns_bool correct_length = str_len(buffer, buffer_len) == PN_STR_LEN;
    dns_bool correct_dashes = (buffer[3] == '-') && (buffer[7] == '-');
    dns_bool correct_digits = is_digits_and_dashes(buffer);
    return correct_length && correct_dashes && correct_digits;
}

int get_area_code(const char* pn_str)
{
    int result = 0;
    result += (pn_str[0] - '0') * 100;
    result += (pn_str[1] - '0') * 10;
    result += (pn_str[2] - '0') * 1;
    return result;
}

int main(void)
{
    printf("%s\n", TITLE_SPLASH_STR);
    printf("%s\n", INFO_SPASH_STR);
    printf("%s\n", "Enter 'q' to exit.");
    const char exit_program = 'q';

    while (dns_true) {

        char input_buffer[BUFFER_LEN] = { 0 };

        printf("%s\n", "------------------");
        printf("%s", "DNS -> ");

        dns_bool input_read = (dns_bool)(fgets(input_buffer, BUFFER_LEN, stdin) == input_buffer);

        if (!input_read) {
            fprintf(stderr, "Error: Unable to read input.");
            return EXIT_FAILURE;
        } else if (*input_buffer == exit_program) {
            printf("Exiting.\n");
            return EXIT_SUCCESS;
        }

        dns_bool is_valid_number     = is_phone_number(input_buffer, BUFFER_LEN);
        int      area_code_index     = get_area_code(input_buffer);
        dns_bool has_valid_area_code = AreaCodes[area_code_index].state != NULL;

        if (!has_valid_area_code) {

            fprintf(stderr, "%s\n", "Invalid area code.");
            is_valid_number = dns_false;
        }

        if (is_valid_number && has_valid_area_code) {

            printf("State    : %s\n", AreaCodes[area_code_index].state);
            printf("Country  : %s\n", AreaCodes[area_code_index].country);
            printf("Timezone : %d\n", AreaCodes[area_code_index].timezone);
            printf("Region   : %s\n", AreaCodes[area_code_index].regions);

        } else {

            fprintf(stderr, "%s\n", "Invalid phone number format. Please enter a valid phone number in the format xxx-xxx-xxxx.");
        }
    }

    return EXIT_SUCCESS;
}
