# $Id$ -*- sh -*-
# Setup GDB for debugging DDD

# Copyright (C) 1998 Technische Universitaet Braunschweig, Germany.
# Written by Andreas Zeller <zeller@ips.cs.tu-bs.de>.
# 
# This file is part of DDD.
# 
# DDD is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
# 
# DDD is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public
# License along with DDD -- see the file COPYING.
# If not, write to the Free Software Foundation, Inc.,
# 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
# 
# DDD is the data display debugger.
# For details, see the DDD World-Wide-Web page, 
# `http://www.cs.tu-bs.de/softech/ddd/',
# or send a mail to the DDD developers <ddd@ips.cs.tu-bs.de>.

# Debug the Debugger
# ------------------
# 
# I appreciate that the April 1997 _Communications_
# covers the issue of debugging
# and hope we programmers can be relieved
# from the pain of debugging
# with the help of advanced tools.
# However, all I'm looking for today
# is a well-debugged debugger.
# I have been working
# with C/C++ debuggers from several Unix vendors
# as well as a Microsoft Windows-based debugger.
# All of them more than occasionally fail
# to perform some very basic function,
# such as setting a break point,
# displaying a data structure,
# evaluating an expression,
# and looking up a symbol.
# Some of them simply crash too often.
#
# My observation is that the debugger
# is often buggier
# than the program being debugged.
# One debugging difficulty Eisenstadt points out
# is the inability of the debugging tool.
# This is certainly true.
# I should emphasize that the difficulty
# is often a debugger-reliability problem
# rather than a capability problem.
#
# W. QUOCK, San Mateo, California
# Communications of the ACM, August 1997/Vol.40, No. 8, p. 31

# Setup DDD environment

## General DDD project settings

define ddd_settings
# Conveniences
set verbose on
set print pretty on
set print object on
set print static-members off
set editing on
set history expansion on
set history filename .gdbhist
set history save on
set history size 1000

# Paths, etc.
directory .

# Environment
set environment DDD_HOME ./..
set environment XUSERFILESEARCHPATH %N
set environment XAPPLRESDIR .
end


## Debug DDD

define ddd
ddd_settings

# Default arguments
set args --gdb --trace cxxtest

# Stop on fatal errors
b ddd_x_fatal
b ddd_x_error
b ddd_xt_error
b ddd_fatal
b ddd_signal

# That's all!
echo Enter `run' to start DDD.\n
end

document ddd
    Setup environment for debugging DDD
end


## Debug VSL

define vsl
ddd_settings

# Default arguments
set args -I ./../vsllib ./ddd.vsl

# That's all!
echo Enter `run' to start VSL.\n
end

document vsl
    Setup environment for debugging VSL
end


## Debug DDD w/ Perl

define perl
    ddd
    set args --perl --trace ./perltest.pl
end
document perl
    Setup environment for debugging DDD with Perl
end


# Print DDD string types
define string
    p $.rep->s[0]@$.rep->len
end
document string
    Print value of last viewed DDD string
end

define pstring
    p $arg0.rep->s[0]@$arg0.rep->len
end
document string
    Print value of DDD string ARG
end

# Just let the user know we're here.
# echo Enter `ddd' to debug DDD.\n
