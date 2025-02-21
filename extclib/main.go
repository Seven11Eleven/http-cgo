package main

/*
#cgo CFLAGS: -I.
#cgo LDFLAGS: -L. -lnet
#include "net.h"
#include <stdlib.h>  // Для free()
*/
import "C"

import (
	"fmt"
	"unsafe"
)

const buffSize = 1024

func main() {
	addr := C.CString("127.0.0.1:8080")
	defer C.free(unsafe.Pointer(addr))

	listener := C.listen_net(addr)
	if listener < 0 {
		fmt.Printf("Ошибка запуска сервера: %d\n", listener)
		return
	}

	fmt.Println("Сервер слушает 127.0.0.1:8080...")

	buffer := make([]byte, buffSize)

	for {
		conn := C.accept_net(listener)
		if conn < 0 {
			fmt.Println("Ошибка: accept")
			return
		}

		for {
			length := C.recv_net(conn, (*C.char)(unsafe.Pointer(&buffer[0])), C.size_t(buffSize))
			if length <= 0 {
				break
			}
			fmt.Printf("Получено: %s\n", string(buffer[:length]))

			for i := 0; i < int(length); i++ {
				buffer[i] = byte(C.to_upper(C.int(buffer[i])))
			}

			C.send_net(conn, (*C.char)(unsafe.Pointer(&buffer[0])), C.size_t(length))
		}
		C.close_net(conn)
	}
}
