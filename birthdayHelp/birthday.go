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
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"sync"
	"time"
)

const (
	FileName = "HelpMeRememberBirthdays.txt"
)

func clearScreen() error {
	cmd := exec.Command("clear")
	cmd.Stdout = os.Stdout
	var err error = nil
	if cmd.Run() != nil {
		err = fmt.Errorf("failed to clear screen")
	}
	return err
}

func welcome() {
	fmt.Println("WELCOME!!!")
	time.Sleep(2 * time.Second)
	fmt.Println("On future start up, this program will display upcoming birthdays.")
	time.Sleep(2 * time.Second)
	fmt.Println("For now you will go create reminders.")
	time.Sleep(3 * time.Second)
}

func displayUpcoming() {
	fmt.Println("Still working on it.")
}

func createFile(wg *sync.WaitGroup) {
	defer wg.Done()
	file, err := os.Create(FileName)
	if err != nil {
		panic("Could not create a file.")
	}
	file.Close()
}

func firstTime() {
	fmt.Printf("File \"%s\" Not found.\n", FileName)
	fmt.Printf("Setting up")

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

	_, err := os.OpenFile(FileName, os.O_APPEND|os.O_RDWR, 0644)
	if os.IsNotExist(err) {
		firstTime()
	} else if err != nil {
		fmt.Println(err)
		panic("Cannot recover. Exiting.")
	}

	displayUpcoming()
}
