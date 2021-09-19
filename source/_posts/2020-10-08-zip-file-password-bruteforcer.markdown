---
title: "zip file password bruteforcer"
date: "2020-10-08"
categories: 
  - "python-for-pentesting"
---

Sometime we know a lot about our victim. Now consider a situation where victim has created a zip file but has protected it with a password. You don’t know what exactly the password is but you surely what password he/she can use (considering you have done enough reconnaissance on your victim).

So what to do in these kinds of situations ? Should we test the every possible password, well that’s a good option but sometimes our wordlist is so long the it becomes tedious to test them by our self. So what we can do is, we can build a simple script which will test all the password in a file and will return us the correct password.

1. For this, we will be using Python’s built in _**zipfile**_ module and sys module as we want to take arguments from the user.

```python
import zipfile
import sys
```

2.Now we will check if user has given correct intput or not.

```python
import sys
import zipfile

if (len(sys.argv)) < 2:
    print("Usage : python3 zipfile.py <wordlist> <zipfile>")
```

3.If input is correct then:

```python
import sys
import zipfile

if (len(sys.argv)) < 2:
    print("Usage : python3 zipfile.py <wordlist> <zipfile>")
if len(sys.argv) == 3:
    file = sys.argv\[1\]
    zf = zipfile.ZipFile(sys.argv\[2\])
    f = open(file)
    for words in f.readlines():
        pwd = words.strip()
        try:
            zf.extractall(pwd = str.encode(pwd))
            print("\[+\] Password found: {} Success".format(pwd))
            break

        except:
            continue
        else:print("\[-\] Not Found use more dense wordlist")
```
Now what the code does is:

first it opens the wordlist and then executes a 'for' loop. Through this for loop it tries string in each line as password of the file. If the password is correct, it will extract the files of the zip file and then it will extract that zip file. If not then, We'll have to use more dense wordlist i.e. wordlist containing more possibilities
