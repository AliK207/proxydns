export CC= gcc
export CFLAGS= -Wall -Wextra -Werror -I $(shell pwd)/libs/inc
export LD_RUN_PATH=$$LD_RUN_PATH:$(shell pwd)/libs/dynamic


all : makefiles install_hooks

makefiles:
		cd libs/Reseau && $(MAKE)  
		cd libs/Log && $(MAKE)
		cd src && $(MAKE) 
install_hooks:
		cp ../hooks/pre-commit ../.git/hooks

debug: all
debug: CFLAGS+= -g  -DDEBUG 


.PHONY: clean		
clean:	
		cd src && $(MAKE) clean
		cd libs/Reseau && $(MAKE) clean 
		cd libs/Log && $(MAKE) clean
