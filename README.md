# Minishell

- Minishell is a simple Unix-like shell that I created as a project for my C programming class.
- It supports basic shell functionality like running commands, changing directories, and setting environment variables.
- It was developed using C.
# Features
- Runs shell commands like ls, cd, echo, etc, without '&&' and '||'.
- Supports piping and redirection of input/output
- Implements environment variables
- Supports basic signal handling (Ctrl+C, Ctrl+D, Ctrl+\, Ctrl+L)
- Supports tab completion for commands and paths

# Getting Started
## Prerequisites
- A C compiler (e.g. GCC)
- Readline library installed
- Make command installed

# Installation
- Clone the repository:
```git clone https://github.com/Black-Hole1004/minishell.git```
- Navigate to the project directory:
 ```cd minishell```
 - run ```make```
 - then execute the binary ```./minishell```
 - And you're good to go, enjoy ! .
 
# Usage
- Once you have Minishell up and running, you can use it just like any other Unix shell. Here are a few examples of commands you can try:

```ls```  
```cd /usr/bin```  
```echo "Hello, world!" ```  
- You can also use piping and redirection to manipulate input and output:

``` ls -la | grep "minishell" ```   
```echo "This will be written to a file" > output.txt```  
- For more information on how to use Minishell, you can refer to the man page.

# Contributing
Contributions are always welcome! If you'd like to contribute to Minishell, please feel free to submit a pull request.
