# shell

A basic Unix shell written in C.

## Build

```bash
make
```

## Run

```bash
./shell
```

## Features

- Interactive prompt
- Dynamic input buffer which grows automatically for long commands
- Supports any command available on your system via `$PATH`
- Colorized error messages (pretty cool, my fav part)
- Graceful handling of empty input

## Built-in Commands

| Command | Description |
|---------|-------------|
| `exit` | Exit the shell |

## How It Works

1. Reads input character by character into a dynamically allocated buffer
2. Tokenizes the input by whitespace into an args array
3. Checks for built-in commands, otherwise forks a child process and calls `execvp`
4. Parent waits for the child to finish before prompting again

## Example

```
my_shell>>> ls -la
my_shell>>> echo hello world
my_shell>>> exit
```

## TODO
 
- [ ] `cd` — change directory
- [ ] `help` — list available built-in commands
- [ ] Pipe support (`|`)
- [ ] Redirection support (`>`, `<`)
