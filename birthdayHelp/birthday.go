//-----------------------------------------------------------------//
//  Developer: Aldo Vera-Espinoza                  ___     _______ //
//  Date: Sun May 26 20:21:01 2024                / \ \   / / ____|//
//                                               / _ \ \ / /|  _|  //
//  Project Name: Birthday remider simple(BRS)  / ___ \ V / | |___ //
//  Description:                               /_/   \_\_/  |_____|//
//    This program saves birthdays given to it and                 //
//   on start up will remind you of any comming up.                //
//-----------------------------------------------------------------//

//Might return to this sometime since I do not like how unclean it is.
//I need to learn more golang idomatic ways to do things.

package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"strconv"
	"strings"
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

//Prints birthdays occuring within 2 weeks
func displayUpcoming(file *os.File) error {
	scanner := bufio.NewScanner(file)
	const twoWeeks float64 = 336
	var buffer []string
	var now time.Time
	var dateWithCurrentYear time.Time
	var timeLeft time.Duration
	someDatesPrinted := false

	fmt.Println("UPCOMING:")

	for scanner.Scan() {
		buffer = strings.Split(scanner.Text(), " ")
		da, err := time.Parse(time.RFC3339, buffer[2])
		if err != nil {
			return fmt.Errorf("malformed date; possible corruption")
		}
		//This section deals with creating a new time.Time that just has an updated
		//year; it is done so that figuring out the leap year edge cases are left to
		//the libary.
		now = time.Now()
		dateWithCurrentYear = time.Date(now.Year(), da.Month(), da.Day(), 0, 0, 0, 0, da.Location())
		timeLeft = dateWithCurrentYear.Sub(now)
		if timeLeft.Hours() < twoWeeks {
			someDatesPrinted = true
			fmt.Printf("%s's birthday in %f hours;", buffer[0], timeLeft.Hours())
			fmt.Printf(" the date is %d/%d (day/month).\n", dateWithCurrentYear.Day(), dateWithCurrentYear.Month())
		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Println(err)
		return fmt.Errorf("failed to read line from file to display birthdays")
	}

	if !someDatesPrinted {
		fmt.Println("No birthdays comming up!")
	}

	return nil
}

//Creates the new birthdates and write them out to the given file.
func createReminders(file *os.File) error {
	fmt.Println()
	fmt.Println("Now in birthday reminder creater mode.")
	fmt.Println("Type \".quit\" or \".q\" to stop creating reminders.")
	fmt.Printf("You can open up the file \"%s\" and delete the undesired birthday.\n\n", FileName)
	var name string
	var day, month string
	var feild int = 0
	var intDay, intMonth int
	var err error

	fmt.Println("Type in the person's name:")
	for buffer := bufio.NewScanner(os.Stdin); buffer.Scan() && (buffer.Text() != ".q" && buffer.Text() != ".quit"); feild %= 3 {
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
			_, err = file.WriteString(name + " | " + time.Date(2024, time.Month(intMonth), intDay, 0, 0, 0, 0, time.Local).Format(time.RFC3339) + "\n")
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
