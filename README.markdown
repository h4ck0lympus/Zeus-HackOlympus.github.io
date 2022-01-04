# Source branch for octopress site 

## deploy  

1. install rvm and python2 
2. install ruby version 2.5.1 (stable for Ubuntu 18.04) and 'rvm use 2.5.1'
3. clone source branch in blog folder 
4. clone master branch in blog/\_deploy
3. `gem install bundler`
4. `bundle install`
5. `rake generate`
6. use github api and `git remote set-url origin https://<token>@github.com/Zeus-HackOlympus/Zeus-HackOlympus.github.io.git` 
7. `rake deploy`
8. push source branch changes :
    ```
    git add .
    git commit -m 'your message'
    git push origin source
    ```


## TODO ARTICLES 
- x86-64 assembly language 
- Linux Intro to scripting 
- Using gdb 
