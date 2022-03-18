---
layout: post
comments: true
title: "Linux Basics Part- 2"
date: "2020-11-11"
paginate: true
keywords : [linux commands, linux operating system, linux mint, linux interview questions, linux foundation, linux download, linux kya hai, linux academy, linux administrator, linux administrator interview questions, linux architecture, linux and unix difference, linux admin job description, linux advanced interview questions, linux and windows difference, a linux distribution consists of which of the following, a linux command]
tags: 
  - "linux"
---

**Before beginning, I suggest all the readers, to try the following commands yourself as you read them**.

## **Advanced File operators**

recall using _**ls --all**_ command privileges and various other attributes of **files** in that directory  
**Chmod**  
chmod  allows to set different permissions for a file, and control who can read it. The syntax of this command is typically _**chmod <permissions> <file>**_.Permission setting system is very interesting and powerful. They are set in 3 digits

- first digit controls the **permissions of a user**.
- second digit controls the **permissions of a  group**.
- third digit controls the **permissions of everyone that's not the part of user or group**.

| **Digit** |         **Meaning**        |
|:---------:|:--------------------------:|
|     1     |  the file can be executed  |
|     2     | the file can be written to |
|     4     |    the file can be read    |

Now how to give permission to the file using above logic.

Suppose we have to give all rights to the users and by all rights we mean **execution, writing and reading** in that case the number for this permission will be **1+2+4 = 7** so **first number of chmod permission will be 7**.

now if we want to give only **writing and execution rights to groups**. **Our 2nd digit of chmod rights will be 1 + 4 = 5**

if we want to give **only execution rights to everyone** (except user and group) **3rd digit of chmod permissions will be 1**.

<img src="/images/linux-basics-2/image-2.png" class="center" >

**So our command will be: _chmod 751 <file>._**

**U**\-user **G**\-group **E**\-everyone that are not in group or user

now **_rw_** means "read and write" , meaning the user has read-write permissions to the file.

**_r_** means read so group and everyone else has read privileges.

now if we look the _'Downloads'_ folder we see **drwxr-xr-x**

now what this means, **d** means directory,**rw** means read-write **xr** means execution rights and **r** means read. So user can access this directory and can read, write and execute the files in it. Group can execute and read and everyone else can execute.

**Note:** It is possible to give someone no perms to a file, You can just put 0 as the digit. 770 Means that everyone that isn't a part of the user or group cant do anything to the file.

### **Chown**

chown means change owner.It allows us to change **the user and group for any file**.The syntax is:

`chown user:group file` 

**Note: chown is best used with sudo privivliges**

We can also change only user/group. For just we just write:

`chown <user>/<group> file`

important flag:

**`-R`** - allows us to operate with every file in the directory at once.

### rm

**rm means remove**. So it removes the respective file **permanently**.So it is a very dangerous command.

To avoid any mishap. we either use `-i` or `-I` flag.

**Important Flags:**

**`-i`** - asks for user's consent every time a file is deleted.

**`\-I`** asks for users's consent for deletion of every 3 files.

**`\-r`** used to delete a whole directory

### Find

find is one my most favorite commands. It is simple and incredibly powerful. As it says, it allows user to find files.

True power of this command though comes from the parameters you provide it For example you can use `find dir -user <username>` to list every file owned by a  specific user; you can use `find  <dir> -group** **<group name>` to list every file owned by a specific group. The sheer customizability of the command is its most powerful.

Important flags:

**To search the entire directory** - /

**To search current folder** - **.**

**to search file belonging to a group/user** - **`find <dir> -user/group <username>/<groupname>`**

**to find that is executable -**`find <dir> -executable`**

**To find a empty file and folders -** **`find <dir> -empty`**

**to find all readable file -** **`find <dir> -readable`**

**to find a file with particular extension -** **`find <dir> -name \*.mp3`**

**Output of find command to a file -** **`find <dir> -name \*.txt -fprint <file name to print to>`**

**Find all directories whose name contains the word "flag"-** `find / -type d -name "*flag"**`

now here type followed by d means directory if it was followed by f it meant files

**\-name** means name of the file/directory depending upon the `-type` flag

**error reduction (exclude all permission denied or error commands from the output) -** `find <dir> <filename> 2> /dev/null`

"2>" is common standard error (stderr) redirection method. I have redirected all the standard error to **/dev/null**, which is a device file. In comming writeups I'll be talking more on this

**/dev/null** is like a null space or "black hole" of linux.

"\*" is a wildcard operator, it generally means all.

**find size related file/directory search**

Now if we want to find file of a specific size, or near to (more or less) to that size, we use **_\-size_** flag with some other important attributes.

| Keyword | meaning |
| --- | --- |
| c  | bytes |
| k | kilobytes |
| M | Megabytes |
| G | Gigabytes |

Now using the above table understand the following command.

if I want to find file named "password" my command will be which is less than 1 my command will be:

**_find -type f -name "password" -size -1k_** **_2> /dev/null_**

notice that I have redirected stderr (standard error) to /dev/null for error reduction

what if we want to find a file which is greater than 1 Mb but less than 5 Mb:

**_find -type f -size +1M -size -5M_**

so in short we use "+" for more than and "-" for less than.

**time related commmands**

Now there are 3 attributes for time related commands:

- **\-atime** : access time
- **\-mtime** : modification time
- **\-ctime** : change time

now if I want to find a file **that is accessed precisely 4 days ago** then we will use: _**\-atime 4**_

if I want to find a file that is accesse_d_ **within last 4 days**_: **-atime -4**_

If we want to find file that was **accessed recently(within 24 hours)** then we use **\-atime 0**

if I want to find a file that is accessed **after 4 da_ys_**_: **-atime +4**_

the same logic applies for **_\-mtime_** and **_\-ctime_**

Now what if, we don't want to find files using hours but minutes, then we use **_\-min_ using the above attributes - a,c or m** and everything else is also same.

**\-perm** flag

As I have written earlier in chmod:

| **Digit** |         **Meaning**        |
|:---------:|:--------------------------:|
|     1     |  the file can be executed  |
|     2     | the file can be written to |
|     4     |    the file can be read    |

**_\-perm_** also uses the above digits with same meaning to search for permission.

**_\-perm_** accept 4 bit input which means a 4 digit number.

- 1st bit - special privileges like SUID
- 2nd bit - owner privileges
- 3rd bit - group privileges
- 4th bit for everyone else

**general syntax :** _find -perm <mode>_

there are 3 different modes:

- if we just give permission through bits(example -perm 444), files with that **particular permissions** will be shown.
- If we use "-" as prefix to bit-permission, files **with at least one of the permission will be shown**(for example if we search for 666 and some file has 776 then it will be shown)
- If we use "/" either the owner the group or other should have the permission to the file For example, if we do `find -perm /555`, and if a file has `544` then it will be shown because user privileges are satisfied.

**Using Symbolic Notation** **to search for permissions**

In symbolic notations

**u -> user g -> group o -> others**

**r -> read w -> write x -> executable**

for instance:

if we want to find file with all user having executable permission then:

_**find -perm -u=x**_

if we want to find file with all user having read write and groups having executable permission then:

_**find -perm -u=rw,-g=x**_

**Note**: we can use "=" or "+" the output will be same

**\-not** flag

Suppose we have to find all files except the ones having provided permission then we use _**\-not**_ flag.

for instance all files except the one having permission 777 then: `find -type f -not -perm 777`

**Combining find commands with linux operators can be really helpful.**

**Find command really helps in solving CTF challenges. There are many other find commands. I suggest you all to look over the man page of this command.**

### Grep

This command allows you to find specific string inside data.

The syntax of this command is: `grep <string> <file>`

for multiple files: `grep <string> <file1> <file2> .....`

Using grep with find makes the it usability to increase by tenfolds.

#### Standard Unix Streams

If you have not understood what I did during **find** command, this will probably help you

- **stdin** − This is referred to as the _standard input_ and the associated file descriptor is 0. This is also represented as STDIN. The Unix program will read the default input from STDIN.
- **stdout** − This is referred to as the _standard output_ and the associated file descriptor is 1. This is also represented as STDOUT. The Unix program will write the default output at STDOUT
- **stderr** − This is referred to as the _standard error_ and the associated file descriptor is 2. This is also represented as STDERR. The Unix program will write all the error messages at STDERR.
