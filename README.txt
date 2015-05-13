This directory contains the raw material for two demo programs. One
draws a chess set and board, and allows you to move around the board
and the other shows a pair of axes, in the room space and the head
space (assuming a head tracker).

The Makefile included here should build both demos properly, in the
Granoff cave, and on any of the CS linux machines.

These instructions are guaranteed fresh until 11/2014.

 -Tom Sgouros
  9/15/2014

ON A CS LINUX MACHINE
---------------------

To build and run on a CS linux machine, follow these instructions:

 1. Find a usable $G tree that contains vrg3d.  $G represents an
    archive of many years of graphics lab contributions.  It's quite
    large, so though you could download the whole thing from its CVS
    archive, we don't recommend it.  (We mention it because there are
    wiki instructions out there advising you do exactly that.  Ignore
    them while we track them down and exterminate, er, edit them.)

    If you don't have a pet tree of your own, try setting it to:

    $ export G=/research/graphics/tools/linux

    Also, do this:

    $ export GARCH=linux

    These are instructions for the bash shell. If you use the C shell,
    or tcsh, you'll set environment variables with setenv.  The other
    shell commands should work the same way in either shell.

 2. Unpack the vdemo tar file, jump in, and issue the make command:

    $ tar xzf vdemo.tgz
    $ cd vdemo
    $ make

 3. You should now have two executables, "chess" and "demo". Run them:

    $ ./chess  or
    $ ./demo

    The chess program uses the arrow keys (and shift + arrow keys) to
    move around your view of the chessboard.  The demo program uses
    the mouse to move around a set of axes.  This will make more sense
    when you're using it in the cave.


 4. vrg3d uses setup files to define its display.  These can be found in 
    any of a handful of directories defined in the vrg3d code. (Check out
    vrg3d/VRApp.cpp.)

    There is a "desktop.vrsetup" that comes with vrg3d, and you can
    use it like this:

    $ ./demo desktop  or
    $ ./chess desktop

    This will just make a bigger window for you.

 5. Park your project in the archive. When you get down to brass tacks
    and start making something new of your own, you should store your
    work in the graphics group's CVS archive.  Instructions for this
    are below.


IN THE OLD CAVE (GRANOFF)
-------------------------

There are three different machines in the cave that deserve names to
make the following instructions a little easier to follow.  

 - The cave 'kiosk' is mounted on a stand hanging off the side of the
   cave.  It has a touch screen and a graphical UI that controls
   what's running in the cave.

 - The 'cave server' machine is mounted in the stand directly below
   the kiosk.  You do not need to know about this to run programs in
   the cave, but it will be important in using to move programs from
   CS to the cave.

 - The 'dev1' machine is on the workbench to the left of the kiosk.
   You will log into this machine in order to run your work in the
   cave.  The /home and /share directories are shared with the cave
   server, so whatever you see in those directories on one machine
   will be on the other machine, too.

To build and run in the cave, follow these instructions, after
unpacking this file somewhere. (And presumably if you are reading
this, you have already mastered that step.)


 1. Get an account of your own in the cave.  This is not strictly
    necessary, but will make a lot of things much easier.  Do this by
    applying for a CCV account at ccv.brown.edu/start/account and then
    send a note to john_huffman@brown.edu explaining that you want a
    matching account on the cave machines.

 2. Set the following environment variables:

    $ export G=/share/cs/gfx/G
    $ export GARCH=linux

 3. The make process should work the same as above.  You can run the
    resulting demo and chess programs on the desktop of the cave's
    'dev1' machine (on the bench).

 4. To run on the cave itself, first make sure that nothing else is
    running by poking the skull and crossbones icon on the kiosk
    screen until the "Current Running Program" says "None".

 5. Issue the following command:

    $ /share/cave/bin/run ./chess

    If nothing happens, or you see messages to the effect of "Did not
    connect to all nodes," try poking the "Video Config" tab on the
    kiosk and choose "CAVE On".

 6. Go grab a pair of glasses and admire the stereo image.

    At least one person should be wearing the glasses with the
    motion-tracker balls on it.  The real show is really for whoever
    is wearing those.  And the chess demo code uses the black "wand"
    joystick.  Turn it on with the little power button down and to the
    right of the joystick.  If the projectors are aligned properly,
    you should see a red "laser" line coming more or less from the
    wand location.  If the alignment is off, you will see the red line
    to the left or right of your hand.

 7. To stop your program, turn to the kiosk and hit the skull and
    crossbone button.  Note that the "run" script executes your
    program on other computers, so stopping that process (e.g. by
    hitting ctrl-C) won't stop your program.

Note: The vrg3d software litters your directory with an empty file
    called "<memory>".  This can be deleted safely so long as your
    code is not running at the time.

It may come to pass that you want to develop software for the cave.
This might involve moving software from the CS machines to the cave.
This is not difficult, but there are a few steps.

From the CS network, you cannot get directly to the cave machines, but
you can reach ssh.ccv.brown.edu, and from there go to the cave, using
its IP address (10.2.128.224).

    $ ssh user@ssh.ccv.brown.edu
    <blah blah welcome message>

    [user@login002 ~]$ ssh user@10.2.128.224
    <blah blah welcome to cave-server>

    [user@cave-server ~]$

You can use scp to copy files from one stop to the next if you want to
"push" the files you need from CS to the cave. However, it's probably
easier to log into the cave machines (dev1 or cave-server, it doesn't
matter) and use scp to "pull" files from your home directory instead:

    [user@cave-server ~]$ scp user@ssh.cs.brown.edu:~/myfiles.tgz .

If you copy the ~/.ssh/id_rsa.pub file contents from the cave machines
into your ~/.ssh/authorized_keys file at CS, you can check things into
and out of the viz CVS tree ($G) directly.  See the CVS instructions
below.


IN THE NEW CAVE (HOORAY!)
-------------------------

TBD...



PARK YOUR PROJECT RIGHT HERE (CVS INSTRUCTIONS)
-----------------------------------------------

The graphics group maintains a CVS-driven archive of student work.
This archive also supports the $G software tree, but they are
different things.  To put your software into the tree, check out the
cs237 class directory as follows:

  $ cvs -d /research/graphics/cvsroot checkout project/class/cs237/2014

This will create a directory called project and inside it you will
find another directory called cs237, inside of which is 2014.  Start
your project this way:

  $ cd project/class/cs237/2014
  $ mkdir myproject
  $ cvs add myproject
  $ cd myproject

Now you are inside your very own directory.  Go wild, but please make
sure that the code you check into CVS is working code.  Feel free to
use it to keep interim versions during the development process, but we
want the code in the archive to work.

The code you write here may eventually be incorporated into the $G
tree.  References within your directory (libraries and so forth)
should all be relative.  References to other people's software in the
archive should reference it relative to $G.  If that software isn't
yet available in the reference $G tree, consult David Laidlaw or
staff.

Do *NOT* edit the software in the reference $G tree directly.  If your
project becomes so complex that it cannot be accommodated with the
strategy outlined here, please consult David Laidlaw or staff for a
better solution.


CVS in 2 minutes
----------------

Now that you've checked out a working directory, all the CVS commands
you will need to use are these:

  cvs add
  cvs commit
  cvs update -d

After you create a file or sub-directory, add it to the archive with
'cvs add'.  When you change something, use 'cvs commit' to put the
changes into the archive, and use 'cvs update' to bring any changes in
the archive down to your working version.  (The '-d' brings along any
subdirectories you might have established.)  Use the CVS documentation
(it's pretty good) to figure out the options for these commands.
There is plenty of other functionality there -- comparing versions,
reverting changes, marking releases -- but you can explore them at
your leisure without my guidance.


Using CVS to transfer work to the Cave
--------------------------------------

If you've been working happily over on one or another of the CS
machines, and want to move your work over to the cave, you can use CVS
to do that.  Make sure everything you want to transfer over is checked
in to CVS, then go over to the cave and do this.

  $ cvs -d :ext:myname@ssh.cs.brown.edu:/research/graphics/cvsroot checkout project/class/cs237/2014/myproject

Presumably you know to substitute your name for 'myname' and the name
of your project directory for 'myproject', but in case you'd forgotten
that, this note is here to remind you.

The result will be a subdirectory of wherever you issued the command
called 'project' inside of which you'll find 'class' and so on down to
your 'myproject' directory.  Subdirectories nesting this deep are kind
of a drag, but you can always do this right after:

  $ cp -R project/class/cs237/2014/myproject myproject

Now your CVS-connected subdirectory is in place on the cave machine
and you can transfer work there in the future using 'cvs update -d'.



Why CVS?
--------

You may be wondering why the graphics group cleaves to the antiquated
CVS version control software rather than using something newer and
flashier like Git or Mercurial or even the almost-as-antiquated
Subversion, for heaven's sake.  There are two reasons:

 1. It's an archive first, and a version control system second.  Git,
    for example, was developed the other way around, and in fact the
    central archive is entirely optional.  But we *want* a central
    archive, and as much as we want to be au courant in all things,
    there is just too much software already here to consider porting
    it to github.

 2. Per-file versioning.  Modern version control systems use the
    version identifier to mark the state of the entire archive.  By
    contrast, CVS uses version numbers to mark individual files.  In
    an archive that encompasses a wide variety of different projects
    developed independently and that have little or nothing to do with
    each other, a system-wide version number makes no sense.

Finally, there is nothing exclusive about this arrangement.  If you
really want to use git or github or Mercurial or whatever, go ahead,
it's a free country.  Just check your work into CVS from time to time
so that your contribution to the graphics group is archived somewhere
permanent.
