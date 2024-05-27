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
	"os"
	"os/exec"
	"runtime"
)

func firstTime(fileName *string) {
	cmd := exec.Command("clear")
	cmd.Stdout = os.Stdout
	cmd.Run()
}

func main() {
	fileName := "Birthdays.txt"
	operatingSystem := runtime.GOOS
	if operatingSystem != "Linux" {
		panic("Not yet made for any other operating system.Sorry.")
	}
	_, err := os.OpenFile(fileName, os.O_APPEND|os.O_RDWR, 0644)
	if err != nil {
		firstTime(&fileName)
	}

}
