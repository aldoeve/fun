//-----------------------------------------------------------------//
//  Developer: Aldo Vera-Espinoza                  ___     _______ //
//  Date: Sun May 26 20:21:01 2024                / \ \   / / ____|//
//                                               / _ \ \ / /|  _|  //
//  Project Name: Birthday remider simple(BRS)  / ___ \ V / | |___ //
//  Description:                               /_/   \_\_/  |_____|//
//    This program saves birthdays given to it and                 //
//   on start up will remind you of any comming up.                //
//-----------------------------------------------------------------//

package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"strconv"
	"sync"
	"time"
)

const (
	FileName = "HelpMeRememberBirthdays.txt"
)

//Clears terminal screen.
func clearScreen() error {
	cmd := exec.Command("clear")
	cmd.Stdout = os.Stdout
	var err error = nil
	if cmd.Run() != nil {
		err = fmt.Errorf("failed to clear screen")
	}
	return err
}

//Displays a welcome message.
func welcome() {
	fmt.Println("WELCOME!!!")
	time.Sleep(2 * time.Second)
	fmt.Println("On future start up, this program will display upcoming birthdays.")
	time.Sleep(2 * time.Second)
	fmt.Println("For now you will go create reminders.")
	time.Sleep(3 * time.Second)
}

func displayUpcoming(file *os.File) error {
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		fmt.Println(err)
		return fmt.Errorf("failed to read line from file to display birthdays")
	}

	return nil
}

//Creates the new birthdates.
func createReminders(file *os.File) error {
	fmt.Println()
	fmt.Println("Now in birthday reminder creater mode.")
	fmt.Println("Type \".quit\" to stop creating reminders.")
	fmt.Printf("You can open up the file \"%s\" and delete the undesired birthday.\n\n", FileName)
	var name string
	var day, month string
	var feild int = 0
	var intDay, intMonth int
	var err error

	fmt.Println("Type in the person's name:")
	for buffer := bufio.NewScanner(os.Stdin); buffer.Scan() && buffer.Text() != ".quit"; feild %= 3 {
		switch feild {
		case 0:
			name = buffer.Text()
			feild++
			fmt.Println("Type in the day:")
		case 1:
			day = buffer.Text()
			feild++
			fmt.Println("Type in the month:")
		case 2:
			month = buffer.Text()
			feild++
			intDay, err = strconv.Atoi(day)
			if err != nil {
				return fmt.Errorf("could not change the day to an int")
			}
			intMonth, err = strconv.Atoi(month)
			if err != nil {
				return fmt.Errorf("could not change the month to an int")
			}
			_, err = file.WriteString(name + "|" + time.Date(0, time.Month(intMonth), intDay, 0, 0, 0, 0, time.Local).String() + "\n")
			if err != nil {
				return fmt.Errorf("failed to write to file")
			}
			fmt.Println("Saved.")
			fmt.Println("Type in the person's name:")
		default:
			return fmt.Errorf("failed to parse data")
		}
	}

	return nil
}

//Creates a file.
func createFile(wg *sync.WaitGroup) {
	defer wg.Done()
	file, err := os.Create(FileName)
	if err != nil {
		panic("Could not create a file.")
	}
	if err := file.Close(); err != nil {
		fmt.Println(err)
	}
}

//Oversees creating the proper files and displays a welcome message.
func firstTime() {
	fmt.Printf("File \"%s\" Not found.\n", FileName)
	fmt.Printf("Setting up")

	//Starts up a worker to create the files whilest a simple animation plays.
	var wg sync.WaitGroup
	wg.Add(1)
	go createFile(&wg)
	for i := 0; i < 3; i++ {
		time.Sleep(1 * time.Second)
		fmt.Printf(".")
	}
	wg.Wait()

	err := clearScreen()
	if err != nil {
		fmt.Println(err)
	}

	welcome()
}

func main() {
	const operatingSystem = runtime.GOOS
	if operatingSystem != "linux" {
		typeOfos := fmt.Errorf("Non-Linux type operating systems are not supported")
		fmt.Println(typeOfos)
		os.Exit(1)
		return
	}

	//Attempts to open the file; on faluire assumes that this is the applications
	//first time.
	file, err := os.OpenFile(FileName, os.O_APPEND|os.O_RDWR, 0644)
	if os.IsNotExist(err) {
		firstTime()
		file, err = os.OpenFile(FileName, os.O_APPEND|os.O_RDWR, 0644)
	}
	if err != nil {
		fmt.Println(err)
		panic("Cannot recover. Exiting.")
	}

	if err = displayUpcoming(file); err != nil {
		fmt.Println(err)
		fmt.Println("Exiting.")
		file.Close()
		return
	}

	if err = createReminders(file); err != nil {
		fmt.Println(err)
		fmt.Println("Exiting.")
		file.Close()
		return
	}

	if err = file.Close(); err != nil {
		fmt.Println(err)
	}
}
