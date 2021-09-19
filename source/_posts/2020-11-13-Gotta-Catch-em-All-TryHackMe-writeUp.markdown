---
title: "Gotta Catch'em All! TryHackMe WriteUp"
date: "2020-11-13"
categories: 
  - "ctf"
  - "easy"
---

Hello guys, I am not a professional so feedback will be appreciated.

**level - very easy**

**You can attempt this CTF challenge here**: [Gotta Catch em' all](https://tryhackme.com/room/pokemon)

So let the hacking begin.

Lets start with a nmap scan on the box.

![](https://hackolympus.files.wordpress.com/2020/11/image-8.png?w=1002)

As you can see we found port **22 (ssh) and 80 (webserver)** open.

As usual we go to the webpage and we found Apache default webpage running on it.

![](https://hackolympus.files.wordpress.com/2020/11/image-9.png?w=921)

now I started inspecting elements and believe me this step took me a great amount of time. The author was very clever, he/she camouflaged the ssh credentials in inspect element itself just above the "check the console" comment

![](https://hackolympus.files.wordpress.com/2020/11/image-10.png?w=597)

It was right in front of my eyes all the time but I was not able to find it but at last we found it.

lets login through ssh with the found credentials.

In _**Desktop**_ directory I found a zip file. I unzip it and we found our first flag but its encoded and it looks like its in **hex.**

![](https://hackolympus.files.wordpress.com/2020/11/image-16.png?w=896)

I decoded this using this webite:

[https://www.asciitohex.com/](https://www.asciitohex.com/)

![](https://hackolympus.files.wordpress.com/2020/11/image-17.png?w=550)

So here we go our first flag.

After finding first flag I looked more into the home directory for some other interesting stuff and in videos I accessed a couple of subfolders after that I found a '.cplusplus' file.

I looked into it and voilà we found credentials for other user- _ash_.

![](https://hackolympus.files.wordpress.com/2020/11/image-12.png?w=1024)

Now exit from ssh and login into user ash.

ash had a un-interactive shell

I checked my **sudo** privileges and here we go we can use all sudo commands for this user.

so I took no time to change my user into root.

![](https://hackolympus.files.wordpress.com/2020/11/image-18.png?w=895)

Now we know that all flags are in this machine, we just have to search for it.

So I began my search and I found 2nd flag in in webserver folder in _**/var/www/html**_

now if we run cat command we see

![](https://hackolympus.files.wordpress.com/2020/11/image-14.png?w=610)

Now this is encoded and if you look closely it appears that words are rotated so its a rot algorithm. So I used the following site to decode it:

and there we go we found our second flag.

[http://theblob.org/rot.](http://theblob.org/rot.cgi)[cgi](http://theblob.org/rot.cgi)

so if we decode it the rot 1 gives us understandable results

![](https://hackolympus.files.wordpress.com/2020/11/image-15.png?w=397)

I looked into _**ash user**_ folder but I found nothing interesting over there.

I searched into **/home** directory and I found **roots-pokemon.txt**

I looked into it and we found the answer of **task4 root's favorite pokemon.**

So I searched more but I could not find the last flag.

so I ran the _**find**_ command

![](https://hackolympus.files.wordpress.com/2020/11/image-19.png?w=653)

reading the above file we found that its also encoded and its base64 so I decoded it and we found our last flag.

![](https://hackolympus.files.wordpress.com/2020/11/image-20.png?w=772)

Hope you enjoyed this writeup. Thanks all for reading.

Again I am not a professional so feedback is much appreciated.
