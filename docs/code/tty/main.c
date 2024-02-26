#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uv.h>

uv_loop_t *loop;
uv_tty_t tty;
int main()
{
    loop = uv_default_loop();

    uv_tty_init(loop, &tty, STDOUT_FILENO, 0);
    uv_tty_set_mode(&tty, UV_TTY_MODE_NORMAL);

    if (uv_guess_handle(1) == UV_TTY)
    {
        uv_write_t req0;
        uv_buf_t buf0;
        buf0.base = "\033[41;37m";
        buf0.len = strlen(buf0.base);
        uv_write(&req0, (uv_stream_t *)&tty, &buf0, 1, NULL);
    }

    uv_write_t req1;
    uv_buf_t buf1;
    buf1.base = "Hello TTY\n";
    buf1.len = strlen(buf1.base);
    uv_write(&req1, (uv_stream_t *)&tty, &buf1, 1, NULL);

    uv_tty_reset_mode();
    return uv_run(loop, UV_RUN_DEFAULT);
}
