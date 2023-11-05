package src

import (
	"bufio"
	"fmt"
	"os"
	areacodes "phonedns/src/areaCodes"
)

const (
	EXIT_SUCCESS = 0
	EXIT_FAILURE = 1
	BUFFER_LEN   = 16
	PN_STR_LEN   = 12
)

const (
	TITLE_SPLASH_STR = `    ____  _                      ____  _   _ ____
   |  _ \| |__   ___  _ __   ___|  _ \| \ | / ___|
   | |_) | '_ \ / _ \| '_ \ / _ \ | | |  \| \___ \
   |  __/| | | | (_) | | | |  __/ |_| | |\  |___) |
   |_|   |_| |_|\___/|_| |_|\___|____/|_| \_|____/
  `

	INFO_SPLASH_STR = `
  § PhoneDNS Nebrix | Licensed under MIT License
  § Original creator: https://github.com/Nebrix
  § Creator of this version: https://github.com/Nebrix`
)

func strLen(buffer string) int {
	return len(buffer)
}

func isDigit(ch byte) bool {
	return bool(ch >= '0' && ch <= '9')
}

func isDigitsAndDashes(pnStr string) bool {
	isDigits := true
	firstDash := 3
	secondDash := 7

	for i := 0; i < PN_STR_LEN-1; i++ {
		if i == firstDash || i == secondDash {
			continue
		}
		if !isDigit(pnStr[i]) {
			isDigits = false
			break
		}
	}
	return isDigits
}

func isPhoneNumber(buffer string) bool {
	correctLen := strLen(buffer) == PN_STR_LEN
	correctDash := buffer[3] == '-' && buffer[7] == '-'
	correctDigits := isDigitsAndDashes(buffer)
	return correctLen && correctDash && correctDigits
}

func PhoneDNS() {
	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println(TITLE_SPLASH_STR)
	fmt.Println(INFO_SPLASH_STR)

	for {
		fmt.Println("------------------")
		fmt.Printf("DNS -> ")
		scanner.Scan()
		inputBuffer := scanner.Text()

		isValidNumber := isPhoneNumber(string(inputBuffer))
		areaCodeIndex := areacodes.GetAreaCode(string(inputBuffer))
		hasValidAreaCode := areaCodeIndex < len(areacodes.AreaCodes) && areacodes.AreaCodes[areaCodeIndex].State != ""

		if !hasValidAreaCode {
			fmt.Fprintln(os.Stderr, "Invalid area code.")
			isValidNumber = false
		}

		if isValidNumber && hasValidAreaCode {
			fmt.Printf("State    :%v\n", areacodes.AreaCodes[areaCodeIndex].State)
			fmt.Printf("Country  :%v\n", areacodes.AreaCodes[areaCodeIndex].Country)
			fmt.Printf("Timezone :%v\n", areacodes.AreaCodes[areaCodeIndex].Timezone)
			fmt.Printf("Region   :%v\n", areacodes.AreaCodes[areaCodeIndex].Regions)
		} else {
			fmt.Fprintln(os.Stderr, "Invalid phone number format. Please enter a valid phone number in the format xxx-xxx-xxxx.")
		}
	}
}
