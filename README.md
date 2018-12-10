# dino_term
dino_term is a rendition of the chrome dinosour game that lives in your terminal. I'm developing a basic game engine in C that leverages the ncurses library to handle terminal rendering in ascii characters. I'm currently developing a few demos as I work on basic pysics and mechanics. 

# Running the Demo
dino_term is built using make. It depends on the ncurses library for building. You can install the library using one of the following commands depending if you use mac or linux:

### Max OSX
``` console
brew install ncurses
```
### Linux
``` console
sudo apt-get install libncurses5-dev libncursesw5-dev
```
You can run the demo on your POSIX system by cloning the repository and running the following two commands:
``` console
user@machine:~/dino_term$ make
user@machine:~/dino_term$ ./dino_term
```

dino_term is a working title and I'm open to suggestions

# Progress
There is currently a framework that provides basic physics and user input. The next step is to use these tools to implement obstacles and the rest of the game mechanics. 

<p align="center"><img src="https://github.com/alexjodonnell/dino_term/blob/master/docs/Dino1.gif" width="335" height="229" /></p>
