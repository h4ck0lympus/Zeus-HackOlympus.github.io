---
layout: post
comments: true
title: "Magic Number"
date: "2020-10-16"
categories: 
  - "forensics"

---

Ever heard of file signatures or magic number of a file ?

- File Signature or magic number are special parts in the starting of hex-dump through which we can interpret the file type/extension

- We can use magic number to solve ctf challenges and forensics.

- Sometimes files get corrupt because there is a change in magic number. Solving this problem can un-corrupt that respective file.

- to see magic number we use any hexadecimal editor or viewer.

for this tutorial I'll use xxd but windows users can use [HxD](https://mh-nexus.de/en/hxd/).

### xxd

xxd is a tool to make hexdump or reverse that is convert hexdumpt to binary.

**general syntax**: `xxd <flag> <filename>`

When no flag is given xxd, standard output is printed by xxd.

**Important flags**:

- **_\-b_** - show binary dump instead of hexdump
- **_\-c_** - output is in the form of 'C' include file style
- **_\-ps_** - detailed hexdump

Now I would like to introduce you to a command **_'head'_**.

### Head command

This command basically outputs few starting lines of the file.

**general syntax**: `head <flag> <file>`

If no flag is given then by default this will print the first 10 lines of a file

**important flags**:

- **_\-n_** <num> - "-n" followed by a number, will print that respective number of lines.
- **\-q** - this will never print header of file containing its name
- **\-c** <num>- "-c" followed by a number will print the given number of bytes of a file from the start.

So now you know the necessary commands lets get back to magic number.

So as I was saying that starting bytes of a file will tell us about the extension of the file.

so what we do with _xxd_ and _head_ is, we print the first few lines of hexdump. This few lines contains our magic number.We look for a special sequence of hex this special sequence is known as magic number and this will tell us the extension of file.

You'll understand it more clearly by the following example.

I have a file.

![](https://hackolympus.files.wordpress.com/2020/11/image-3.png?w=495)

<img src="/images/magic-number/image-3.png">

I don't know the file type so what I'll do, I will check its hexdump.

<img src="/images/magic-number/image-5.png">

through its hex dump I can easily see its a jpeg file as we know that magic number for jpeg is **`ffd8 ffe0 0010 4a96`**. Sure we could have also checked this without using hexdump and using _**file**_ command but file command also uses the same logic.

But sometimes(specially in ctf challenges) hexdump is modified and file becomes corrupt hence unreadable so to fix that we modify the hashdump.

Now lets look another example.

I have a file named file2 I don't know its file type. So I use magic number to find out what file extension it has.

<img src="/images/magic-number/image-7.png">

And there we go, we found it its a pdf file.

I suggest you to practice with some of the files by yourself.

Check out this link to view the file signatures of different files.

[https://en.wikipedia.org/wiki/List\_of\_file\_signatures](https://en.wikipedia.org/wiki/List_of_file_signatures)
