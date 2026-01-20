---
comments: true
title: "Reflections on Trusting Trust"
date: 2022-08-29
keywords: ["reflection on trusting trust", "ken thompson", "computer science", "computer security", "security"]
---

[*Reflections on Trusting Trust*](https://dl.acm.org/doi/pdf/10.1145/358198.358210), written by the legendary Sir Ken Thompson, essentially raises a deep but valid question: should we trust the code written by someone else ?

The paper begins with a very interesting series of talks on various pieces of code, divided into stages and the most fascinating and overwhelming was stage 3, where Sir Ken Thompson provides us with a case study.

In this case study, he tries to introduce us with an idea about how compilers can be made to have backdoors inside of them. A compiler can be designed in such a way that it injects intentionally vulnerable code into a specific program.

This is a very critical thing for me to think about because compilers are used to convert code into binary, so even if the original code is free from any bugs or vulnerabilities, compiling it with an unsafe compiler will automatically make it vulnerable to attacks, and no one except the person who wrote the compiler may know about it.

Now, for me personally, this whole case study changed my perspective on software. Should I even trust the OS on which I am doing my work? In fact, should I even trust the software that I am using for my regular usage ? And what’s frightening is the fact that Unix was open source so this kind of compiler mishap is noticeable but what about software that is commercial and whose source code is not in public ? Is it game over ?

These questions might sound ambiguous but are very valid because whenever we use a software, we never think about its security and that’s what is going to harm us in the long run.

Moral is and as Ken Thompson says in his paper, “*You can't trust code that you did not totally create yourself…*”  So if we should not trust the code written by someone else, should we just stop using code ? The answer is No because that’s obviously not possible. But what we can do is and as Ken Thompson says in the beginning of the paper is, “to trust the people who wrote the software.”  Obviously this is also not a fool proof statement because people too can’t be trusted.

In my opinion bad people(otherwise known as black hat hackers)  will continue to evade system security because code is written by humans and humans make mistakes which leads to vulnerability and therefore exploits. But it is the job of expert good hackers(otherwise known as white hat hackers ) to find those mistakes, before the bad people can get their hands on it.



