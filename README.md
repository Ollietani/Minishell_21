# Minishell

<img width="751" alt="Screen Shot 2021-12-02 at 10 37 31 PM" src="https://user-images.githubusercontent.com/64180934/144491128-401e5ba7-bef4-41c1-8187-e0b81eda1f1f.png">

## Description
School 21 project. Implementation of shell in C.

Task file: [Subject.pdf](https://github.com/Ollietani/Minishell_21/blob/d5cd1938e66a98ec39da78f79583abac80bd2d93/Subject.pdf)

This is group project. It was made by  **[Ollietani](https://github.com/Ollietani)** and **[alkhrtnv](https://github.com/alkhrtnv)**.

## Usage

#### Project requiries:
- GNU Readline Library

#### To run program:

1. Clone repository: `git clone git@github.com:Ollietani/Minishell_21.git`

2. `cd` to directory `Minishell_21`

3. Run `make` to execute minishell

4. After building run `./minishell`

## Project requirements
- Shell should implement the buildins:
  - `echo` with option -n
  
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options

- Not interpret unclosed quotes or unspecified special characters like `\` or `;`
- Have a working History
- Search and launch the right executable
- `’`  and  `"`  inhibit all interpretation of a sequence of characters
- Redirections:
   - `<`   should redirect input
   - `>`   should redirect output
   - `<<` read input from the current source until a line containing only the delimiter is seen
   - `>>` should redirect output with append mode
- Pipes `|` The output of each command in the pipeline is connected via a pipe to the
input of the next command
- Environment variables ($ followed by characters) should expand to their values
- `$?` should expand to the exit status of the most recently executed foreground pipeline
- `ctrl-C` `ctrl-D` `ctrl-\` should work like in bash
- When interactive:
   - `ctrl-C` print a new prompt on a newline
   - `ctrl-D` exit the shell
   - `ctrl-\` do nothing
