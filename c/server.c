#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
void free_handle(uv_handle_t *handle) { free(handle); }

void free_write_req(uv_write_t *req, int status) { free(req); }

void on_alloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  *buf = uv_buf_init((char *)malloc(suggested_size), suggested_size);
}

void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
  if (nread > 0) {
    // Handle the received data (buf->base contains the received data)
    // In this example, we simply echo the data back to the client

    // Prepare the HTTP response
    const char *response_template =
        "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\n\r\n%s";
    size_t response_length = strlen(buf->base);
    char *response = (char *)malloc(response_length + 200);
    snprintf(response, response_length + 200, response_template,
             response_length, buf->base);

    // Send the HTTP response back to the client
    uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
    uv_buf_t wrbuf = uv_buf_init(response, strlen(response));
    uv_write(req, client, &wrbuf, 1, free_write_req);
  } else if (nread < 0) {
    // Error or connection closed by the client
    if (nread != UV_EOF) {
      // fprintf(stderr, "Read error: %s\n", uv_strerror(nread));
    }
    uv_close((uv_handle_t *)client, free_handle);
  } else if (nread == 0) {
    // Empty read, do nothing or handle as needed
  }

  free(buf->base);
}

void on_connection(uv_stream_t *server, int status) {
  if (status < 0) {
    fprintf(stderr, "Connection error: %s\n", uv_strerror(status));
    return;
  }

  uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(uv_default_loop(), client);

  if (uv_accept(server, (uv_stream_t *)client) == 0) {
    uv_read_start((uv_stream_t *)client, on_alloc, on_read);
  } else {
    uv_close((uv_handle_t *)client, free_handle);
  }
}

int main() {
  uv_tcp_t server;
  uv_tcp_init(uv_default_loop(), &server);

  struct sockaddr_in bind_addr;
  uv_ip4_addr("0.0.0.0", 8081, &bind_addr);

  uv_tcp_bind(&server, (const struct sockaddr *)&bind_addr, 0);
  int r = uv_listen((uv_stream_t *)&server, 128, on_connection);
  if (r) {
    fprintf(stderr, "Listen error: %s\n", uv_strerror(r));
    return 1;
  }

  printf("Async HTTP/1.1 Echo Server listening on port 8080...\n");

  return uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
