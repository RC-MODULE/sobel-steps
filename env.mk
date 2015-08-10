NMPP             = $(ROOT)/deps/nmpp
NMPROFILER       = $(ROOT)/deps/nmprofiler
MB7707_MAC       ?= 1A-2B-3C-4D-5E-6F
#http_proxy        = http://user:pass@proxy:80/

ifeq ($(OS),Windows_NT)
  MC5103 ?= C:\Program Files (x86)\Module\MC5103 SDK
  MB7707 ?= C:\Program Files (x86)\Module\MB7707 SDK
  MC7601 ?= c:\Program Files (x86)\Module\MC7601 SDK
  VSHELL32 ?= $(VSHELL32)
  SHELL = cmd
  OS_RM = del /Q
  OS_RD = rd /Q /S 
  PATH := $(MC5103)/bin);$(MB7707)/bin;$(PATH)  
  OS_WGET = wget
  #powershell netsh winhttp import proxy source=ie; Import-Module bitstransfer; start-bitstransfer -source 
else
  OS_RM = rm -f -r
  OS_RD = rm -d -r
  OS_WGET = wget
endif


 