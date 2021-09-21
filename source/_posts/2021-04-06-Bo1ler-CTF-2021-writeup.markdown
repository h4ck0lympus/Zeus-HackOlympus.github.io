---
layout: post
title: "Bo1ler CTF -2021  writeup"
date: "2021-04-06"
comments: true
categories: 
  - "ctf"
tags: 
  - "writeups"
---

So recently I played Bo1ler CTF. Normally I don't write writeups for a CTF (due to time constraints) but this time I decided to write one as I found the challenges quite good and informative for beginners like me. Well hats off to Bo1ler CTF team.

I am writing this writeup mainly for **pyjail** challenges so my main focus will be on them only but I'll be providing the writeups for other challenges also.

#### **Jails**

#### Pyjailgolf1

So in this challenge we were given the following code which was running on the shell server `nc chal.b01lers.com 1334` :
```python
line = input('>>> ')

flag="\[REDACTED\]"

if len(line) > 10:
    raise Exception()

try:
    eval(line)
except:
    pass
```
Basically there is an **`eval`** function which is vulnerable. You will input any python command and it will be executed. But this was not the problem, problem was that we have to print the value of variable flag by running a command whose length is less than 10 chars. Now if you simply do `print(flag)` it will not work and will raise an Exception. All other commands like hex(), id(), exec() etc will not work because they are functions and they return the value rather than printing it. So calling them is no good for us.

Now you see why I am writing a writeup for this challenge. Because its so small, simple and cute yet challenging. Its a pure "out of the box" thinking challenge. Every beginner can approach this because it doesn't require a specific skillset like pwn (binary exploitation) challenges (except python but lets be honest, who doesn't know it 😬) .

Well after going through my python notes and doing some research work on google I found a command `help()`. Yup! the answer was help command !!


<img src="/images/boiler/image-1.png" class="center" style="width: 60%">

**Flag:** `pctf{JusT_a5k_4_h3lP!}`

See the most basic commands which we neglect during our learning period helped us in this challenge. After this I researched more on `help()` command and by luck next jail challenge could be done using `help()` command itself.

### Pyjailgolf2

This challenge is almost same as the last one the only difference is the char limit. This time we have to do all our work in just 9 chars. Lets take a look at the script :
```python
line = input('>>> ')

flag="\[REDACTED\]"

if len(line) > 9:
    raise Exception()

try:
    eval(line)
except:
    pass
```
`nc chal.b01lers.com 1335`

So as I said before this time we will use `help()` command like before but there is a little change of plans. Rather than using `help(flag)` to read the value of variable flag we will use `help()` interactive version.


<img src="/images/boiler/image-2.png" class="center" style="width: 60%">

So the,

**Flag** `pctf{Un1c0d3_i5_sw34t}`

I don't know if this is the intended method to solve because by looking at the flag it doesn't look like it but whatever, we got the flag ¯\\\_(ツ)\_/¯ .

Well this is it I was only able to do the first 2 pyjails. So lets move to other challenge categories .

## **Reverse Engineering**

### weenie\_hut\_general

This challenge was an easy reverse engineering challenge. I am not a reverse engineering player myself but I was able to do it easily.

The given files can be found from this [link](https://ctf.b01lers.com/download?file_key=ad1a1baf12da64c84dc72ecc9befccddec544cd0310acefb87275692d212f7a3&team_key=c2e8f607c31b1896dfe445997fb87e1315424096425ea90c9b38ee0cd0b39032)

So running the file is no good as it does not contain main function and will return a Segmentation fault. Lets open it in ghidra and see the decompiled source code.

Upon opening in ghidra I found a function `trytorev`. After reading and understanding the code it was pretty obvious what it does. See for yourself:


<img src="/images/boiler/image-3.png" class="center" style="width: 60%">

it first initializes a seed to get psedurandom number from rand function.

It then looks for a number such that the bitwise XOR of param1, uvar1(storing first random number) and 0x3597b741 is equal to pseudorandom number uvar2 .

So I first made a script to do the reverse of all these operations in python (A nooby mistake, I know ). Python's random number function does not work in the same way like C rand function. So my team mate ([DaBaddest](https://ctftime.org/user/82627)) made the reverse script in C and that worked :

His script :

{% include_code boiler.c %}

And this returned us the flag

**Flag** : `bctf{1432175799}`

### Swirler

Another Easy reverse engineering challenge for beginners like me

Given files can be found from this [link](https://ctf.b01lers.com/download?file_key=64844ebf04da4d9513927c3d720e00799c5db04477d7b6c496bab371edd889f3&team_key=c2e8f607c31b1896dfe445997fb87e1315424096425ea90c9b38ee0cd0b39032) . With the files another [link](http://chal.b01lers.com:8001) was also given to us .

Ok first lets look at the given files it was a png picture file nothing special. Lets look at the given link.

Main function of the site was to take a picture and "swirl" it so that no one can look at its contents. It was JS reverse engineering and was no big thing. I copied the source code of the site and used [https://jsfiddle.net/](https://jsfiddle.net/) to deploy it and 'fiddle' with source code side by side to see how it works.

```javascript
const fsSource = `
    precision highp float;

    varying vec2 vPos;

    uniform sampler2D uSampler;
    uniform vec2 uResolution;
    uniform float uTime;

    uniform float uRadius;
    uniform float uSwirlFactor;

    void main(void) {
      vec2 uv = gl_FragCoord.xy / uResolution.xy;

      float dist = distance(uv, vec2(0.5));
      mat2 rotmat;
      if (dist < uRadius) {
          float percent = (uRadius - dist) / uRadius;
          float angle = percent * percent * uSwirlFactor * uTime;
          float sina = sin(angle);
          float cosa = cos(angle);
          rotmat = mat2(cosa, sina, -sina, cosa);
      } else {
          rotmat = mat2(1, 0, 0, 1);
      }

      vec2 texCoord = rotmat * (uv - vec2(0.5)) + vec2(0.5);
      vec4 diffuse = texture2D(uSampler, texCoord);
      gl_FragColor = diffuse;
    }
  \`;

```

This was the vulnerable script I just converted the following code block :
```javascript
if (dist < uRadius) {
          float percent = (uRadius - dist) / uRadius;
          float angle = percent * percent * uSwirlFactor * uTime;
          float sina = sin(angle);
          float cosa = cos(angle);
          rotmat = mat2(cosa, sina, -sina, cosa);
```
to :

```javascript
if (dist < uRadius) {
          float percent = (uRadius - dist) / uRadius;
          float angle = percent * percent * -uSwirlFactor * uTime;
          float sina = sin(angle);
          float cosa = cos(angle);
          rotmat = mat2(cosa, sina, -sina, cosa);
```
and ran the code with `flag.png` and we got a qrcode

<img src="/images/boiler/canvas.png" class="center" style="width: 60%">

after scanning we got the flag :

**Flag:** `pctf{sw1rly_sw1rly_qr_c0d3}`

## WEB

### gdpr

This was a web challenge so a link was given : [chal.b01lers.com:1004](http://chal.b01lers.com:1004)

After opening the site It opened a page like this :


<img src="/images/boiler/image-4.png" class="center" style="width: 60%">
If you look closely when the page is loaded it covers some content. So I disabled the JS on my browser to check what it is and it loaded a page like this :


<img src="/images/boiler/image-5.png" class="center" style="width: 60%">
After visiting the link we got the flag


<img src="/images/boiler/image-6.png" class="center" style="width: 60%">

**Flag**: `bctf{annoying_but_good?}`

Well that was it folks.

Will come again with some another interesting writeup.

Till then, farewell
