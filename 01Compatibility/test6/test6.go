package main

import (
	"fmt"
	"time"
)

func main() {
	for (true) {
		fmt.Println("Hello, world!")
		time.Sleep(5*time.Second)
	}
}