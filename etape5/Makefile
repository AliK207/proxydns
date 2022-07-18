export CC= gcc
export CFLAGS= -Wall -Wextra -Werror -I $(shell pwd)/libs/inc
export LD_RUN_PATH=$$LD_RUN_PATH:$(shell pwd)/libs/dynamic


all : makefiles install_hooks

makefiles:
		cd libs/Reseau && $(MAKE)  
		cd libs/Log && $(MAKE)
		cd libs/Threads && $(MAKE)
		cd libs/Memoire && $(MAKE)
		cd libs/Memoire/tests && $(MAKE)
		cd libs/Log/tests && $(MAKE)
		cd libs/Threads/tests && $(MAKE)
		cd libs/Reseau/tests && $(MAKE)
		cd libs/ShMem && $(MAKE)
		cd src && $(MAKE) 
install_hooks:
		cp ../hooks/pre-commit ../.git/hooks

debug: all
debug: CFLAGS+= -g  -DDEBUG 


.PHONY: clean		
clean:	
		cd src && $(MAKE) clean
		cd libs/Reseau && $(MAKE) clean 
		cd libs/Threads && $(MAKE) clean
		cd libs/Memoire && $(MAKE) clean
		cd libs/Memoire/tests && $(MAKE) clean
		cd libs/Log/tests && $(MAKE) clean
		cd libs/Log && $(MAKE) clean
		cd libs/Reseau/tests && $(MAKE) clean
		cd libs/Threads/tests && $(MAKE) clean
		cd libs/ShMem && $(MAKE) clean

