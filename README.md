
# 21sh

## Description

21sh is the third project of the Unix branch in Hive Helsinki. It is an advanced shell interpreter built on top of minishell with added features such as redirections, aggregations, AST execution, piping, command line editing and command separating. As in minishell, we used Bash as reference shell.

## Features

- Redirections (">", ">>", "<" and "<<")
- Aggregations (e.g., "2>&1", "2>&-")
- Abstract Syntax Tree (AST) execution
- Piping ("|")
- Command separating (";")
- Command line editing (termcaps library)

## Project Overview

This project represents the first group project in the Unix branch. Collaborating with Simo, who was responsible for implementing the termcaps section.

## Challenges

The most challenging aspects of the project included understanding AST, lexical analysis, and tokenizing as concepts. Through asking questions, watching tutorials, and reading articles, the team gained a better understanding of how these elements connect and function together. Once these concepts were grasped, the implementation process became more manageable.<br>
Here is link, where we got a lot of help to building our shell: https://www.youtube.com/@hhp3

## Acknowledgments

The successful completion of this project wouldn't have been possible without the support and assistance of fellow hivers and the vibrant Unix community at the campus. Their guidance and contributions were instrumental in overcoming challenges and reaching the project's goals.

## Usage 

Download source code and enter target folder:<br>
```
git clone https://github.com/MiikaViini/21sh.git ; cd 21sh
```

Compile:<br>
```
make
```

Run:<br>
```
./21sh
```

Have fun!!
