package main

import "fmt"

func computeIntegerSign(value int) bool {
	return !(value < 0)
}

func oppositeSigns(first int, second int) bool {
	//The important thing is the sign bit. Upon only one of them being negative
	//the xor will still yeild a negative sign making the resulting value
	//less than zero.
	return (first ^ second) < 0
}

func main() {
	fmt.Println("Hello! This file has functions for playing around with bits.")
	fmt.Println("Source: https://graphics.stanford.edu/~seander/bithacks.html#OperationCounting")
	fmt.Println("This is more so for me to get used to Go and bits.")

	fmt.Println("Is -343 negative? ", computeIntegerSign(-343))
	fmt.Println("Do 45 and 67 have opposite signs? ", oppositeSigns(45, 67))
}
