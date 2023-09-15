#include <iostream>
#include <fstream>
#include <string>
#include <regex>

// Function to check if the phone number format is correct (xxx-xxx-xxxx)
bool is_valid_phone_number_format(const std::string &number) {
    const std::regex phone_regex("^[0-9]{3}-[0-9]{3}-[0-9]{4}$");
    return std::regex_match(number, phone_regex);
}

// Function to remove quotes and leading/trailing whitespace from a string
std::string remove_quotes(const std::string &input) {
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), '\"'), result.end());
    result.erase(0, result.find_first_not_of(" \t\n"));
    result.erase(result.find_last_not_of(" \t\n") + 1);
    return result;
}

// Function to parse JSON data and display state information
void parse_json_and_display(const std::string &number) {
    std::string first_three_digits = number.substr(0, 3);

    // Load JSON data from codes.json
    std::ifstream json_file("codes.json");
    if (!json_file.is_open()) {
        std::cout << "Error: Unable to open codes.json." << std::endl;
        return;
    }

    // Read and parse JSON data
    std::string data;
    std::string line;

    while (std::getline(json_file, line)) {
        data += line;
    }
    json_file.close();

    // Parse JSON data
    size_t state_start = data.find(first_three_digits);
    if (state_start != std::string::npos) {
        state_start += first_three_digits.length();
        size_t state_end = data.find('}', state_start);
        if (state_end != std::string::npos) {
            // Extract state information
            std::string state_info = data.substr(state_start, state_end - state_start);

            // Extract and format state information without quotes and colons
            size_t state_pos = state_info.find("\"State\"");
            size_t country_pos = state_info.find("\"Country\"");
            size_t timezone_pos = state_info.find("\"Timezone\"");
            size_t region_pos = state_info.find("\"Region\"");

            if (state_pos != std::string::npos && country_pos != std::string::npos &&
                timezone_pos != std::string::npos && region_pos != std::string::npos) {
                std::string state = state_info.substr(state_pos + 9, 2);
                std::string country = state_info.substr(country_pos + 10, timezone_pos - country_pos - 11);
                std::string timezone = state_info.substr(timezone_pos + 11, region_pos - timezone_pos - 12);
                std::string region = state_info.substr(region_pos + 10);

                // Remove quotes and format state information
                state = remove_quotes(state);
                country = remove_quotes(country);
                timezone = remove_quotes(timezone);
                region = remove_quotes(region);

                // Output state information in the desired format
                std::cout << "State: " << state << std::endl;
                std::cout << "Country: " << country << std::endl;
                std::cout << "Timezone: " << timezone << std::endl;
                std::cout << "Region: " << region << std::endl;
            } else {
                std::cout << "Invalid JSON format for state information." << std::endl;
            }
        } else {
            std::cout << "State information not found for the given prefix." << std::endl;
        }
    } else {
        std::cout << "State information not found for the given prefix." << std::endl;
    }
}

int main() {
    const char *ascii = 
    "  ____  _                      ____  _   _ ____  \n"
    " |  _ \\| |__   ___  _ __   ___|  _ \\| \\ | / ___| \n"
    " | |_) | '_ \\ / _ \\| '_ \\ / _ \\ | | |  \\| \\___ \\ \n"
    " |  __/| | | | (_) | | | |  __/ |_| | |\\  |___) |\n"
    " |_|   |_| |_|\\___/|_| |_|\\___|____/|_| \\_|____/ \n";

    std::cout << ascii << std::endl;
    
    std::cout << "[ \u00A7 ] PhoneDNS SecLabX | Licensed under MIT License" << std::endl;
    std::cout << "[ \u00A7 ] Original creator: https://github.com/SecLabX" << std::endl;
    std::cout << "[ \u00A7 ] Creator of this version: https://github.com/SecLabX" << std::endl;

    while (true) {
        std::string number;
        std::cout << "------------------" << std::endl;
        std::cout << "DNS -> ";
        std::cin >> number;

        // Check if the number has a valid format
        if (!is_valid_phone_number_format(number)) {
            std::cout << "Invalid phone number format. Please enter a valid phone number in the format xxx-xxx-xxxx." << std::endl;
        } else {
            // Find and display state information
            parse_json_and_display(number);
        }
    }

    return 0;
}
