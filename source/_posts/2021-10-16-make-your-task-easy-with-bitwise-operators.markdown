---
layout: post
title: "Make your task easy with bitwise operators"
date: 2021-10-16 20:32:09 +0530
comments: true
categories: 
---

*I'll keep on updating this as I find more interesting tricks* 

So recently I was going through my notes of C programming and for some reason I wanted to see the header file for ctype.h when I discovered this easter egg: 


<img src="/images/ctype.png" class="center" style="width: 60%">


Now many of you might know about this but for me this was completely new !! And it truly amazed me. So here I am, writing a short blog about it. 

Though its completely clear. 

### Fast to lowercase method  

To convert an ascii character to lower case we can do bitwise OR with 0x20 (32) which is space charater. 

In practical : 

```c
/**
 * @author      : HackOlympus (zeus@hackolympus)
 * @file        : tolower
 * @created     : Saturday Oct 16, 2021 20:42:42 IST
 */

#include <stdio.h>

int main()
{
    printf("%c\n",'C' | 0x20) ;
    printf("%c\n",'c' | 0x20) ;
    return 0 ;

}
```


