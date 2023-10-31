package main

import (
	"io"
	"net/http"
)

func main() {
	router := http.NewServeMux()
	router.HandleFunc("/", echo)
	panic(http.ListenAndServe(":8080", router))
}

func echo(w http.ResponseWriter, r *http.Request) {
	body, err := io.ReadAll(r.Body)
	if err != nil {
		panic("konnte Body nicht lesen")
	}
	w.Write(body)

}
