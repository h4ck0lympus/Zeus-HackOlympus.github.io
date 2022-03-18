---
layout: post
comments: true
title: "Brooklyn Nine Nine - TryHackMe"
date: "2020-10-11"
paginate: true
keywords: 
    - brooklyn 99 try hack me
    - brooklyn nine nine try hack me
    - brooklyn nine nine tryhackme
    - brooklyn nine nine tryhackme writeup
    - tryhackme brooklyn nine nine
categories: 
  - "ctf"
  - "very easy"
---

Hello guys. This is my first tryhackme writeup so please give your honest reviews. Since I am not a professional, your honest reviews will charge my batteries.

To attempt this machine go to this link : [Brooklyn99](https://tryhackme.com/room/brooklynninenine)

So let the hacking begin.

Lets start by doing reconnaissance.

First, I ran a basic nmap version scan on the box.

<img src="/images/b99/image-1.png" class="center">

As we can see there are 3 ports open. First, I went to the webpage of the machine.


<img src="/images/b99/image-2.png" class="center">
  
uff, A rabbit hole I viewed the page source but i found nothing special.

Next I inspected FTP port. I tried anonymous login and it worked:

<img src="/images/b99/image-3.png" class="center">

And we found a file: **note\_to\_jake.txt**. I downloaded the file by using get file command

Lets see what is written in that file:

```
From Amy,Jake please change your password. It is too weak and holt will be mad if someone hacks into the nine nine
```

Looks like we have found a vulnerable username - **jake**

lets fire up hydra and let it do the rest of the job.


<img src="/images/b99/image-4.png" class="center">
we have found a password lets try to connect using that password

**LOGIN SUCCESSFUL**

Lets enumerate this machine.

In the user folder of jake. We found nothing interesting. I ran **sudo -l** command to see if I have any admin rights and yes i was right.


<img src="/images/b99/image-5.png" class="center">
we can run **less** command with sudo rights.

From here I went to **holt** user folder where I found user.txt but only **holt** could open it from his user but as we all know we have sudo privileges on less command so I viewed it with less.


<img src="/images/b99/image-6.png" class="center">
And here we go, we found our first flag.

##### **Privilege Escalation**

Time for privilege escalation. In the **holt** user folder I found another file: **nano.save**

We will use this file for privilege escalation

We will open this file with sudo privileges using less


<img src="/images/b99/image-7.png" class="center">
We will run the following command to open shell:

```
!/bin/bash
```


<img src="/images/b99/image-8.png" class="center">
And here we go, we got a root shell.


<img src="/images/b99/image-9.png" class="center">
Now just go to root folder and we will get **root.txt**


<img src="/images/b99/image-10.png" class="center">
This is my first writeup so any suggestions will be highly appreciated
