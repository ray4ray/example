package encap

import (
	"fmt"
	"testing"
	"unsafe"
)

type Employee struct {
	Id   string
	Name string
	Age  int
}

func (e Employee) String() string {
	fmt.Printf("Address is %x\n", unsafe.Pointer(&e.Name))
	return fmt.Sprintf("ID:%s-Name:%s-Age:%d", e.Id, e.Name, e.Age)
}

//avoid obj copy
//func (e *Employee) String() string {
//	fmt.Printf("Address is %x\n", unsafe.Pointer(&e.Name))
//	return fmt.Sprintf("ID: %s/Name:%s/Age:%d\n", e.Id, e.Name, e.Age)
//}

func TestCreateEmployeeObj(t *testing.T) {
	e := Employee{"0", "Bob", 20}
	e1 := Employee{Name: "Mike", Age: 30}
	e2 := new(Employee)
	e2.Id = "2"
	e2.Age = 22
	e2.Name = "Rose"
	fmt.Printf("e name address is %x\n", &(e.Name))
	fmt.Printf("e is %s\n", e.String())

	fmt.Printf("e1 is %s\n", e1.String())
	fmt.Printf("e1 ID: %s\n", e1.Id)
	fmt.Printf("e2 is %s \n", e2.String())
	fmt.Printf("e is %T\n", e)
	fmt.Printf("e2 is %T\n", e2)
}
