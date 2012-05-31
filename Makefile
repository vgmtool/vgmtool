ifeq ($(platform),)
platform = unix
ifeq ($(shell uname -a),)
platform = win
else ifneq ($(findstring MINGW,$(shell uname -a)),)
platform = win
else ifneq ($(findstring Darwin,$(shell uname -a)),)
platform = osx
endif
endif

# platform
ifeq ($(platform),unix)
include Makefile.unix
else ifeq ($(platform),osx)
include Makefile.osx
else ifeq ($(platform),win)
include Makefile.win
else
unknown_platform: help;
endif

help:;
