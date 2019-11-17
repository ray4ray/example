package fn_test

import (
	"fmt"
	"math/rand"
	"testing"
	"time"
)

func returnMultiValues() (int, int) {
	return rand.Intn(10), rand.Intn(20)
}

func TestFn(t *testing.T) {
	a, b := returnMultiValues()
	fmt.Println(a, b)
}

func TestFn1(t *testing.T) {
	a, _ := returnMultiValues()
	fmt.Println(a)
}

func testSpent(inner func(op int) int) func(op int) int {
	return func(n int) int {
		start := time.Now()
		ret := inner(n)

		fmt.Println("time spent", time.Since(start).Seconds())
		return ret
	}
}

func slowFun(op int) int {
	time.Sleep(time.Second * 1)
	return op
}

func TestFn2(t *testing.T) {
	a, _ := returnMultiValues()
	t.Log(a)
	tsSF := testSpent(slowFun)
	t.Log(tsSF(10))
}

func Sum(ops ...int) int {
	ret := 0
	for _, op := range ops {
		ret += op
	}
	return ret
}

func TestVarParams(t *testing.T) {
	fmt.Println(Sum(1, 2, 3, 4))
	fmt.Println(Sum(1, 2, 3, 4, 5))
}

func Clear() {
	fmt.Println("Clear resource")
}

func TestDefer(t *testing.T) {
	defer Clear()
	fmt.Println("start")
	//panic("err")
}
