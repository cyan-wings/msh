# MSH

<p align="center">
  <img src="https://github.com/cyan-wings/msh/blob/main/msh.png" alt="msh 42 project badge"/>
</p>

MSH can be pronounced as 'mash' or 'mesh'. It is an abbreviation for Matthew's Shell or Meng's Shell which coincidentally stands for minishell.

## Project brief

This project is to create a shell like BASH with basic essential functions.
This project uses GNU's readline library which handles the terminal interaction (history & input reading).
For everything else this project only allows a few low-level functions and a few POSIX system calls.

<b>Allowed functions:</b>
```readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs```

## Features

### Basics:
- History of previous entered commands (including commands entered in past sessions)
- Search and launch the right executable (based on the PATH variable, using a relative or an absolute path)
- Environment variables ($ followed by a sequence of characters) expand to their values
- Wildcards * in the current working directory
- ctrl-C, ctrl-D and ctrl-\ behave like in bash
- ```’``` (single quotes - prevent from interpreting meta-characters in quoted sequence)
- ```"``` (double quotes - prevent from interpreting meta-characters in quoted sequence except for $)
- ```$?``` expands to the last exit status
- ```|``` connect cmds or groups with pipes; output of a cmd is connected to the input of the next cmd via a pipe
- ```&&``` and ```||``` list operations
- ```(``` with ```)``` parenthesis with indicates a subshell and for priorities

### Builtins:
- ```echo``` with option -n
- ```cd``` (relative or absolute path, ```-``` for OLDPWD, without arg for HOME)
- ```pwd``` without options
- ```export``` without options
- ```unset``` without options
- ```env``` without options
- ```exit [exit_status]``` without options

### Redirections:

- ```< file``` Redirecting Input
- ```<< limiter``` Here Document with expanded env variables(if any)
- ```<< limiter_quoted``` Here Document
- ```> file``` Redirecting Output
- ```>> file``` Appending Redirected Output

### Workflow:

1. Env variables are initialised.
2. Input command is obtained via readline and saved to history.
3. Tokenisation removes whitespaces and puts all tokens in a linked-list structure.
4. Token list is parsed using recursive descent parse method.
5. A here document interrupt for input happens during parsing. (This is consistent with most shells)
6. Execution is performed based on the node type of the AST.
7. Expansion of env variables, quotes and wildcards happens right before construction of the argv array for execution.
8. Clean up and freeing of unused memory before waiting for the next input command.

## How to use

msh currently works on all UNIX based systems (i.e., macOS, Linux, WSL).

<b>Requirements:</b>
- GCC / CLANG Compiler
- GNU Make

```
git clone https://github.com/cyan-wings/msh msh
```
```
cd msh && make
```
```
./msh
```

## Debug mode

Export the MSH_DEBUG_TOKEN env to print the token list:

```
export MSH\_DEBUG\_TOKEN=true
```

Export the MSH_DEBUG_PARSE env to print the AST parse tree:

```
export MSH\_DEBUG\_PARSE=true
```

## Changing the prompt

Export the PS1 env (also works in Bash and other similar shells)
```
export PS1='enter your prompt wish...$ '
```

