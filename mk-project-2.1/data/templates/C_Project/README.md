# A C project with mk-project

## Introduction


The **source** are separated from the dependencies (*Icons*, *Configuration files*, *...*)

Because the dependencies go at distributing into a special folder.

```make

$(pkgdatadir)

```

Expanded to:

`/usr/share/project-name`

`/usr/local/share/project-name`

According the prefix settings (/usr or /usr/local or anything you want).

that you can set at compile time:


```c
$ cc -DPREFIX="/usr/local" ...
```

**or**

```c++
$ c++ -DPREFIX="/usr/local"
```

**:note:** Take a look at the main ``Makefile`` at the target **test-install**.

---

They are and you can create as many as you want in the folder:

`./share/project-name`

---

The **source** are separated from the documentation files (*info*, *man*, *html*,  ...)

Because the doc files go, at distributing, into a special folders:

```make

$(mandir)

$(infodir)

$(docdir)

```

## Source

The **source** are compiled into **object files** and then linked to an executable located at `./bin` for the sake of a proper compilation.

### Headers files

Following headers files will be generated:

* `./src/headers/defines.h`

They are some predefined constant and macros but you can add and remove as many as you want.

You can include this file where you want.


* `./src/headers/includes.h`

Contains the included headers.

You can include this file where you want.

* `./src/global_vars.h`

The global variable are proper declared in this file.

You can include this file where global variables were needed.

You must declare the global variables with **extern**.

```c

extern const char *name ;

```

### source files

Following source file are generated:

* `./src/main.c`

But you can add as many source files as you want (add them to the make **$(SRC_FILES)** variable).

* `./src/global_vars.c`

The global variables are define in this file and this one will be compiled separately.
You can define as many global variables as you want the compilation will success.

You must define the global variables without **extern**.

```c

const char *name = "mk-project" ;

```

#### Adding source files.

Normally you must make a header file for every **source** (*.c*) file.

In the **header** (*.h*) file you must declare the functions as **extern**.

```c

extern void print_it(const char *string) ;

```

So you can use the header file everywhere you want.

---

And define them without **extern** in the **source** (*.c*) file.

```c

void print_it(const char *string) {

  /** Do work... **/

  return ;

}

```

As long as you add the source files path in the **$(SRC_FILES)** variable.

And the header file path to the **$(HDR_FILES)** variable.

Everything will be are right...
