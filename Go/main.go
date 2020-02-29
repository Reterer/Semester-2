package main

import (
	"fmt"
)

func main() {
	for i := 0; i < 100; i++ {
		if i%15 == 0 {
			fmt.Println("FIZZBASS")
		} else if i%5 == 0 {
			fmt.Println("FIZZ")
		} else if i%3 == 0 {
			fmt.Println("BASS")
		}
	}
	fmt.Println("Привет мир!")
}
