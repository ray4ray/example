package interface_test

type Programmer interface {
	WriteHelloWorld() string
}

type GoProgrammer struct{

}

func (go *GoProgrammer) WriteHelloWorld() string{
  return "fmt.Println(\"hello world\)"
}

func TestClient (t.testing.T){
  var p Progammer
  p = new(interface)
  
}
