---
layout: post
comments: true
title: "Linux Basics Part-1"
date: "2020-11-10"
tags: 
  - "linux"
---

**Before beginning, I suggest all the readers, to try the following commands yourself as you read them.**

### Man

**man**: man command opens a manual of that respective command.

**syntax :** `man <command>`

### cd

**cd**: cd means change directory. This command helps us to navigate through directories.


**syntax:** `cd <absolute path>` - navigate to absolute path (example: _cd /home/<username>/_).

### ls

**ls**:ls means list. This command is used to list all files in the directory.

Some important flags :

- To print all files including the ones starting with a dot(.) (these are hidden), we use: `ls -a`
- To see details of all files including the owner and the set rights of the file: `ls -all`

### cat

**cat**: If want to see what is a text written in any file, we use this command

### touch

**touch**: This command creates an empty file

**syntax** `touch <filename>`

### **Running a binary**:

we use './' followed by the name of the file to run the file in Linux.

<img src="/images/linux-basics-1/image.png" class="center" style="width:60%">

### su

**su** - This allows us to switch user within terminal without actually signing off.

**syntax** : `su <username>`

### mkdir

**mkdir** - **mkdir means make directory**.It is used to make directory.

**syntax:** `mkdir <directory name>`

**Note: absolute path also works instead of giving name to file**

### mv

**mv**: mv (move) allows yo to **move files from one place to another**.

**Syntax :** `mv <file> <destination>`

if we want to move to home location we can just type using relative path: _mv <file> ~_

we can also use mv to rename file:

`mv <file> <newfilename>`

### cp

**cp (copy)** - use to copy file from one destination to another.

**syntax:** `cp <file> <destination>`

To copy entire directory we use **"-r"** flag

### wc

**wc (word count)** - used to count total number of words and lines in a file

<img src="/images/linux-basics-1/wc.png" class="center" style="width: 60%">

**First Column** − Represents the **total number of lines in the file**.

**Second Column** − Represents the **total number of words in the file.**

**Third Column** − Represents the **total number of bytes in the file.** This is the actual size of the file.

**Fourth Column** − Represents the **file name**

### **Linux operators**

**">"** **\-** To redirect the output to a specific file . **It will completely erase the contents in the file**.

**">>"-**  It is just like ">" but difference is, **it appends the output to the file**.

**"&&"** **\-**  It is just like **"and" of linux command line** .It will first run the first command and then the second. if either of the command is wrongly typed or has a syntax error of some type it will just show : _Command not found_

**";"(semi colon)**: to run multiple commands at the same time. Execution of command goes sequentially

**"||" (Or operator):** If one command fails other command **successfully runs**

**"|" (PIPE operator):** Pipe the output of first command into the input of second command. 

