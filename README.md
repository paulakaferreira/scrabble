# Scrabble
This project aims to develop a Scrabble-like game written in C.
The game is to be played in french.
# Installing Git on Linux:
1. Write "git" on your command line (prompt). If your computer does not have a version of git yet, it will tell you exactly what to write in your next command line in order to install it;
2. Your computer will ask you for your user password. It will probably be the same password as the one you use to log in to your computer;
3. During the installation, write 'y' to continue;
4. After git has been installed, write 'git' again on your command line. A series of basic git commands may appear. If this is the case, it means your computer has succesfully installed git and you're ready to use it.
# Installing Git on Windows:
Follow this step-by-step: https://www.geeksforgeeks.org/how-to-install-git-on-windows-command-line/
# Getting started with Git on Windows - draft
Start the ssh-agent in the background
$ eval $(ssh-agent -s)
> Agent pid 59566

Create a repository on your computer. This should be the place where your code will be.
To create a repository on your command line (Windows: using the git-bash command prompt): mkdir nameoffolder && cd nameoffolder
(mkdir is for 'make directory' and cd is for 'change directory'. This command creates a directory of name nameoffolder and changes the directory you're working on on your command prompt to the nameoffolder)
To link your repository with this GitHub project: "git remote add origin git@github.com:paulakaferreira/scrabble.git"
Testing your first commit to GitHub:
- Create a file called "test.txt" on your nameoffolder repository.
- On command line, write "git add test.txt"
- 

# Useful links:
https://girliemac.com/blog/2017/12/26/git-purr/

https://reglesdejeux.github.io/regles-du-scrabble/index.html
