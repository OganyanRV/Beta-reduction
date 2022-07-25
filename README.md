# Lambda-Calculus. Beta-reduction of lambda terms with de Braun indices
**This repository is outdated. The actual project is [here](https://github.com/OganyanRV/Lambda-calculus-interpreter). The problem with this version is that I do not use an abstract syntax tree to find redexes, I look for them in a string, which works, but it is ideologically wrong.**

Course work of [Oganyan Robert](https://t.me/robasti). Third year of study, 6th term.

Here is a simple **interpreter** for *beta-reduction* of terms. **Beta reduction** of lambda terms has been implemented using **de Bruijn (de Braun) notation** and related: **alpha conversions**, **naming contexts**, **shifts** and **substitutions**.

Implemented with C++14, JetBrains Clion.

## Work demonstration

### Gif

![work_demo](./src_md/work_demo.gif)


### Screenies

Start screen.

![img](./src_md/clip_image001.png)

Rule's list.

 ![img](./src_md/clip_image003.png)

Starting own-written tests.

![img](./src_md/clip_image005.png)

Lets reduce this term: ![img](./src_md/clip_image007.png) . 

*![img](./src_md/clip_image009.png)*

That is correct.

 

Now lets try this one: ![img](./src_md/clip_image011.png) The result should be ![img](./src_md/clip_image013.png).

*![img](./src_md/clip_image015.png)*

Correct. Now lets calculate (0 + 2 * 1) = 2

 

![img](./src_md/clip_image017.png)

We are having ![img](./src_md/clip_image019.png)**.** Reduction has been done correct.

Quit the program.

![img](./src_md/clip_image020.png)

