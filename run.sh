#!/bin/bash
gcc srcs/handle_path.c srcs/handle_prompt.c srcs/utils.c srcs/commands_parse.c srcs/echo_builtin.c srcs/env_builtin.c srcs/exit_builtin.c srcs/export_builtin.c srcs/unset_builtin.c srcs/main.c srcs/cd_builtin.c libft.a srcs/exec_commands.c srcs/pwd_builtin.c -ltermcap && ./a.out 
#gcc srcs/handle_path.c srcs/termcaps.c srcs/handle_prompt.c srcs/utils.c srcs/commands_parse.c srcs/echo_builtin.c srcs/env_builtin.c srcs/exit_builtin.c srcs/export_builtin.c srcs/unset_builtin.c srcs/main.c srcs/cd_builtin.c libft.a srcs/exec_commands.c srcs/pwd_builtin.c -lncurses && ./a.out 
