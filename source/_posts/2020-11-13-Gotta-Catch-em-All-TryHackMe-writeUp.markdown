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


<img src="/images/gottacatchemallTHM/8.png" class="center" style="width: 60%">


As you can see we found port **22 (ssh) and 80 (webserver)** open.

As usual we go to the webpage and we found Apache default webpage running on it.


<img src="/images/gottacatchemallTHM/9.png" class="center" style="width: 60%">

now I started inspecting elements and believe me this step took me a great amount of time. The author was very clever, he/she camouflaged the ssh credentials in inspect element itself just above the "check the console" comment


<img src="/images/gottacatchemallTHM/10.png" class="center" style="width: 60%">

It was right in front of my eyes all the time but I was not able to find it but at last we found it.

lets login through ssh with the found credentials.

In _**Desktop**_ directory I found a zip file. I unzip it and we found our first flag but its encoded and it looks like its in **hex.**


<img src="/images/gottacatchemallTHM/16.png" class="center" style="width: 60%">

I decoded this using this webite:

[https://www.asciitohex.com/](https://www.asciitohex.com/)


<img src="/images/gottacatchemallTHM/17.png" class="center" style="width: 60%">
So here we go our first flag.

After finding first flag I looked more into the home directory for some other interesting stuff and in videos I accessed a couple of subfolders after that I found a '.cplusplus' file.

I looked into it and voilà we found credentials for other user- _ash_.

![](https://hackolympus.files.wordpress.com/2020/11/image-12.png?w=1024)

<img src="/images/gottacatchemallTHM/12.png" class="center" style="width: 60%">
Now exit from ssh and login into user ash.

ash had a un-interactive shell

I checked my **sudo** privileges and here we go we can use all sudo commands for this user.

so I took no time to change my user into root.


<img src="/images/gottacatchemallTHM/18.png" class="center" style="width: 60%">
Now we know that all flags are in this machine, we just have to search for it.

So I began my search and I found 2nd flag in in webserver folder in _**/var/www/html**_

now if we run cat command we see


<img src="/images/gottacatchemallTHM/14.png" class="center" style="width: 60%">
Now this is encoded and if you look closely it appears that words are rotated so its a rot algorithm. So I used the following site to decode it:

and there we go we found our second flag.

[http://theblob.org/rot.](http://theblob.org/rot.cgi)[cgi](http://theblob.org/rot.cgi)

so if we decode it the rot 1 gives us understandable results


<img src="/images/gottacatchemallTHM/15.png" class="center" style="width: 60%">

I looked into _**ash user**_ folder but I found nothing interesting over there.

I searched into **/home** directory and I found **roots-pokemon.txt**

I looked into it and we found the answer of **task4 root's favorite pokemon.**

So I searched more but I could not find the last flag.

so I ran the _**find**_ command


<img src="/images/gottacatchemallTHM/19.png" class="center" style="width: 60%">

reading the above file we found that its also encoded and its base64 so I decoded it and we found our last flag.

<img src="/images/gottacatchemallTHM/20.png" class="center" style="width: 60%">

Hope you enjoyed this writeup. Thanks all for reading.

Again I am not a professional so feedback is much appreciated.
