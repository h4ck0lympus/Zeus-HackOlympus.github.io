---
layout: post
comments: true
title: "Mr.Robot - TryHackMe"
date: "2020-11-17"
categories: 
  - "ctf"
  - "medium"
---

Hello guys, Mr.Robot is one of my most favorite series and today we will be solving its CTF.

**Level - Medium**

You all can attempt this CTF from this link:

[https://tryhackme.com/room/mrrobot](https://tryhackme.com/room/mrrobot)

So let the hacking begin.

First lets start with **reconnaissance** therefore a **_nmap scan_**.


<img src="/images/MrRobot/21.png" class="center" style="width: 70%">

Image of nmap scan

I ran the nmap scan and found 2 ports - 22 (ssh - closed) 80 (webserver).

Lets head to the Webserver.


<img src="/images/MrRobot/22.png" class="center" style="width: 70%">

Well, as expected from this CTF box, we got a cool, terminal look webpage.

Lets enumerate this webpage for more information.

After looking at the source page, we can easily see its a WordPress site. So there are 2 ways from here: **wpscan** or **gobuster**.

The wpscan method is better as it takes less time to solve. I will explain both the methods.

##### 1st Method - wpscan

As I have not used wpscan in my earlier writeups, I would try and explain what it is. wpscan is an inbuilt excellent Kali Tool to enumerate wordpress sites.

So, I enumerate it using wpscan and we found that it has a **_robots_** page. I can't attach the output of the command as it is too long.

_.....continued after method 2_

##### 2nd Method - gobuster

I ran a _**gobuster dir**_ search on it. It resulted in many _time exceeding errors_.

I went to all the sceptical URL's like _license, login, phpmyadmin_ etc. and most of them provided me some good results and hints that we are looking in the right direction. Like the license one:


<img src="/images/MrRobot/24.png" class="center" style="width: 70%">
Or the readme :


<img src="/images/MrRobot/25.png" class="center" style="width: 70%">
Well, I think you all have got an idea from where we'll be getting the best results and if not, don't worry as it is _**robots**_ file of the webserver.

##### The Robots file

When going at **robots** file:


<img src="/images/MrRobot/26.png" class="center" style="width: 70%">
We see two locations on the webserver which were not discovered before. Now, here _**fsocity.dic**_ is a wordlist and **key-1-of-3.txt** will reveal our first flag.


<img src="/images/MrRobot/27.png" class="center" style="width: 70%">
Now, we have got a dictionary. Lets use it somewhere. I know that I can't use it for _ssh_ brute forcing as the port is closed, so only one place is left where it can be used i.e., _the wordpress admin panel._

Now, the _**.dic**_ file is of around 5 MB which means approx. 5 lakh usernames and password respectively to try out but we don't have that much time, we'll have to filter our possibilities. If somehow we get to know the username, 50% of the total possibilities can be reduced, that's a lot of reduction and time saving.

We can cut it down more by using **uniq** command by filtering out all the duplicate strings.

You can compare the sizes before and after the filter operation.


<img src="/images/MrRobot/30.png" class="center" style="width: 70%">
So lets see how I enumerated the right user from the dictionary file.

I passed a lot of random credential pair like admin:admin , user:pass etc that are very common and I got common response: _**invalid username**_.


<img src="/images/MrRobot/29.png" class="center" style="width: 70%">
I used this to enumerate the correct user using **_hydra_** tool. **_Hydra_** is a tool through which we can brute force password for different services.

We have got an idea that the '_F_' parameter of hydra command is _Invalid Username_. If username would have been correct, It wouldn't have shown us this message instead, it would have given us a message regarding _invalid password_.

I'll gather the required information using _burp suite._


<img src="/images/MrRobot/31.png" class="center" style="width: 70%">
From the above data our command will be:

```
hydra -L dict_sorted.txt -p TestPass 10.10.73.3 http-post-form "/wp-login/:log=^USER^&pwd=^PASS^&wp-submit=Log+In&redirect_to=http%3A%2F%2F10.10.73.3%2Fwp-admin%2F&testcookie=1:F=Invalid username"
```

After some time:


<img src="/images/MrRobot/32.png" class="center" style="width: 70%">

As you can see we found 3 usernames.

Lets run this **_Hydra_** again using username **_elliot_** but this time we will be using our wordlist in password field.


<img src="/images/MrRobot/33.png" class="center" style="width: 70%">
So there we go, we found out the password of user **elliot**.

We have now got full control over the wordpress website. Lets see how can we exploit this to gain control over the system.

After exploring the wordpress dashboard, I explored that we can change the code of pre uploaded php files. I changed the code of one of the php file and changed it to already provided php-reverse-shell code in **_/usr/share/webshells/php_** directory. I copy-pasted the code after doing the required changes (host IP and port) and started a **_nc_** (_netcat listener_) .


<img src="/images/MrRobot/34.png" class="center" style="width: 70%">
Visit the page that you have edited and get back to **_nc_** reverse shell and you'll see we have got back our reverse shell.


<img src="/images/MrRobot/35.png" class="center" style="width: 70%">

<img src="/images/MrRobot/36.png" class="center" style="width: 70%">
**Note**: _If you are unable to get a reverse shell, probably it is because of host's firewall._

At last, we have got a reverse shell. I navigated to the **home** directory where I found a user named **robot**. I checked his directory and I can see that we have successfully found our 2nd flag but we don't have the permission to read it. We have another file that basically contains the credential pair of robot user. But, here the password is encrypted.


<img src="/images/MrRobot/37.png" class="center" style="width: 70%">
Lets try to Identify the hash type using **hashid** command. The top 3 possibilities are MD2, MD5 and MD4. I cracked the hash using this site: [crackstation](https://crackstation.net/)


<img src="/images/MrRobot/38.png" class="center" style="width: 70%">
I changed the user to robot using **su** command. User **robot** can read that file and there we go we found our **2nd flag**.  


<img src="/images/MrRobot/40.png" class="center" style="width: 70%">
  
Now, I want the root access of the system and for that I'll have to do **privilege escalation.**

I tried to inspect my sudo privileges but unfortunately, I can't run any command with sudo through user robot.

Lets see if we have any SUID privileges. We see from the output that **nmap** has SUID privileges. So lets exploit it.

I saw the privilege escalation of nmap from [gtfobins](https://gtfobins.github.io/gtfobins/nmap/). So, I tried the privilege escalation and bingo !! We did it.


<img src="/images/MrRobot/41.png" class="center" style="width: 70%">
We now have root access !

I found the third flag in the root directory.


<img src="/images/MrRobot/42.png" class="center" style="width: 70%">
* * *

I am not a professional, so only feedback can make me better.
