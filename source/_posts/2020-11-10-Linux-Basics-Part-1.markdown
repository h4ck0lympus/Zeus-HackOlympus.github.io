---
title: "Linux Basics Part-1"
date: "2020-11-10"
tags: 
  - "operator"
  - "operator"
  - "basics"
  - "linux"
  - "linux-basics"
  - "linux-operators"
  - "operatos"
  - "operator"
  - "operator"
---

**Before beginning, I suggest all the readers, to try the following commands yourself as you read them.**

##### Man

**man**: man command opens a manual of that respective command.

**_syntax : man <command>_**

#### cd

**cd**: cd means change directory. This command helps us to navigate through directories.

Some important flags:

- **cd ..** : navigate to previous directory.
- **cd <absolute path>** - navigate to absolute path (example: _cd /home/<username>/_).

#### ls

**ls**:ls means list. This command is used to list all files in the directory.

Some important flags :

- To print all files including the ones starting with a dot(.) (these are hidden), we use: **_ls -a_**
- To see details of all files including the owner and the set rights of the file: **_ls -all_**

#### cat

**cat**: If want to see what is a text written in any file, we use this command

#### touch

**touch**: This command creates an empty file

**_syntax : touch <filename>_**

#### **Running a binary**:

we use './' followed by the name of the file to run the file in Linux.

![](https://hackolympus.files.wordpress.com/2020/11/image.png?w=878)

#### su

**su** - This allows us to switch user within terminal without actually signing off.

**_syntax : su <username>_**

#### mkdir

**mkdir** - **mkdir means make directory**.It is used to make directory.

**_syntax:_** **_mkdir <directory name>_**

**Note: absolute path also works instead of giving name to file**

#### mv

**mv**: mv (move) allows yo to **move files from one place to another**.

The syntax of command is:

**_mv <file> <destination>_**

if we want to move to home location we can just type using relative path: _mv <file> ~_

we can also use mv to rename file:

**_mv <file> <newfilename>_**

#### cp

**cp (copy)** - use to copy file from one destination to another.

_cp <file> <destination>_

To copy entire directory we use **"-r"** flag

#### wc

**wc (word count)** - used to count total number of words and lines in a file

![](images/screenshot-from-2021-01-09-06-19-13-1-1.png)

**First Column** − Represents the **total number of lines in the file**.

**Second Column** − Represents the **total number of words in the file.**

**Third Column** − Represents the **total number of bytes in the file.** This is the actual size of the file.

**Fourth Column** − Represents the **file name**

#### **Linux operators**

**">"** **\-** To redirect the output to a specific file . **It will completely erase the contents in the file**.

**">>"-**  It is just like ">" but difference is, **it appends the output to the file**.

**"&&"** **\-**  It is just like **"and" of linux command line** .It will first run the first command and then the second. if either of the command is wrongly typed or has a syntax error of some type it will just show : _Command not found_

**";"(semi colon)**: to run multiple commands at the same time. Execution of command goes sequentially

**"||" (Or operator):** If one command fails other command **successfully runs**

**"|" (PIPE operator):** This command is very useful where the output of first command decides that if  second command will run or not. It allows user to take an output of a command and use it as an input for second command.

For example, I can use **_"cat"_** to get the output of a file, and **pipe(|)** that into _"**grep**"_ to search for a specific string in that respective file.

**"!"(Not operator):** This command is much like except statement. for example:

```
# first we created a folder
mkdir zeus
cd  zeus
touch a.doc b.doc a.pdf b.pdf a.xml b.xml a.html b.html
# now if we want to remove all files except files containing .html extension 
rm -r !(*.html) 
```

**"&&-||"(and-or operator):**The above operator is actually a combination of 'and' and 'or' operator. It is much like 'if-else' statement for example:

```
 # if we run ping on google, and want that at the end we want to print if the host is down or up 
ping www.google.com && echo "up" || echo "down"
# so if we see bold letters we can actually understand the command 
```

**Command Combination Operator {}** : Combine two or more commands, the second command depends upon the execution of the first command.For example:

```
 #Check if a directory 'bin' is available or  not, and output corressponding output
[-d bin] || {echo directory does not exist, creating directory now.; mkdir bin;} && echo directory exists 
```

**"$" :**  This is a special linux operator. It is used to **denote environment variables**.For example your current user is always stored in environment variable called **"$USER"**(Can view using echo command). Environment variables cannot be set using ">>". We use a command called **export <varname> = <value>**

Source: TryHackMe and OverTheWire
